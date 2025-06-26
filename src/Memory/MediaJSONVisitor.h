#ifndef MEMORY_JSON_VISITOR_H
#define MEMORY_JSON_VISITOR_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "../Media/IConstMediaVisitor.h"

namespace memory {
class MediaJSONVisitor : public media::IConstMediaVisitor {
 private:
  QJsonObject root_;

  void addStringArray(QJsonObject &obj, const QString &key, const std::vector<std::string> &vec);
  void addValue(QJsonObject &obj, const QString &key, const std::string &value);
  void addValue(QJsonObject &obj, const QString &key, int value);
  void addValue(QJsonObject &obj, const QString &key, unsigned int value);
  void addFlag(QJsonObject &obj, const QString &key);

 public:
  QJsonDocument getDocument() const;

  void visit(const media::Media &) override;
  void visit(const media::Album &) override;
  void visit(const media::Movie &) override;
  void visit(const media::Series &) override;
  void visit(const media::Novel &) override;
  void visit(const media::AudioBook &) override;
  void visit(const media::Ebook &) override;
};
}  // namespace memory

#endif
