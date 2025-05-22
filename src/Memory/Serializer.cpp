#include "Serializer.h"
#include "MediaJSONVisitor.h"
#include "MediaXMLVisitor.h"
#include "../Media/Media.h"

#include <QTextStream>
#include <QJsonDocument>
#include <QDomDocument>

namespace memory {

namespace { // Dettagli interni (visibilità solo a questo file)

enum class Format { JSON, XML };

Format detectFormat(const QString& fileName) {
    const QString lower = fileName.toLower();
    if (lower.endsWith(".json")) return Format::JSON;
    return Format::XML;
}

bool openFileForWrite(QSaveFile& file) {
    return file.open(QIODevice::WriteOnly | QIODevice::Text);
}

int writeJsonFile(const std::vector<const media::Media*>& mediaList, QSaveFile& file) {
    QJsonArray jsonArray;

    for (const auto* media : mediaList) {
        if (!media) continue;
        MediaJSONVisitor visitor;
        media->accept(visitor);
        jsonArray.append(visitor.getDocument().object());
    }

    QJsonDocument doc(jsonArray);

    if (!openFileForWrite(file)) return -1;

    file.write(doc.toJson(QJsonDocument::Indented));
    return file.commit() ? 0 : -2;
}

int writeXmlFile(const std::vector<const media::Media*>& mediaList, QSaveFile& file) {
    QDomDocument doc("MediaCollection");
    QDomElement root = doc.createElement("MediaList");
    doc.appendChild(root);

    for (const auto* media : mediaList) {
        if (!media) continue;
        MediaXMLVisitor visitor;
        media->accept(visitor);
        QDomNode imported = doc.importNode(visitor.getDocument().documentElement(), true);
        root.appendChild(imported);
    }

    if (!openFileForWrite(file)) return -1;

    QTextStream stream(&file);
    doc.save(stream, 2);
    return file.commit() ? 0 : -2;
}

} // namespace anonimo

int Serializer::serialize(const std::vector<const media::Media*>& mediaList, QSaveFile& file) {
    const Format format = detectFormat(file.fileName());
    return (format == Format::JSON) ? writeJsonFile(mediaList, file)
                                    : writeXmlFile(mediaList, file);
}

} // namespace memory
