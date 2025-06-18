#include "Serializer.h"

#include <QDomDocument>
#include <QJsonDocument>
#include <QTextStream>

#include "../Media/Media.h"
#include "MediaJSONVisitor.h"
#include "MediaXMLVisitor.h"

namespace memory {

namespace {  // Dettagli interni (visibilità limitata a questo file)

enum class Format { JSON, XML };

Format detectFormat(const QString& fileName) {
  const QString lower = fileName.toLower();
  if (lower.endsWith(".json")) return Format::JSON;
  return Format::XML;
}

bool openFileForWrite(QFile& file) {
  return file.open(QIODevice::WriteOnly | QIODevice::Text |
                   QIODevice::Truncate);
}

int writeJsonFile(const std::vector<const media::Media*>& mediaList,
                  QFile& file) {
  QJsonArray jsonArray;

  for (const auto* media : mediaList) {
    if (!media || media->getTitle().empty()) continue;

    MediaJSONVisitor visitor;
    media->accept(visitor);
    jsonArray.append(visitor.getDocument().object());
  }

  QJsonDocument doc(jsonArray);

  if (!openFileForWrite(file)) return -1;

  qint64 written = file.write(doc.toJson(QJsonDocument::Indented));
  return (written > 0) ? 0 : -2;
}

int writeXmlFile(const std::vector<const media::Media*>& mediaList,
                 QFile& file) {
  QDomDocument doc("MediaCollection");
  QDomElement root = doc.createElement("MediaList");
  doc.appendChild(root);

  for (const auto* media : mediaList) {
    if (!media || media->getTitle().empty()) continue;
    MediaXMLVisitor visitor;
    media->accept(visitor);
    root.appendChild(
        doc.importNode(visitor.getDocument().documentElement(), true));
  }

  if (!openFileForWrite(file)) return -1;

  QTextStream stream(&file);
  doc.save(stream, 2);  // Indentazione a 2 spazi, come JSON

  return 0;
}

}  // anonymous namespace

int Serializer::serialize(const std::vector<const media::Media*>& mediaList,
                          QFile& file) {
  const Format format = detectFormat(file.fileName());
  return (format == Format::JSON) ? writeJsonFile(mediaList, file)
                                  : writeXmlFile(mediaList, file);
}

}  // namespace memory
