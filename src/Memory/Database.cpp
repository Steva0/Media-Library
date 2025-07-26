#include "Database.h"

namespace memory {

const std::array<std::string, static_cast<size_t>(Database::Type::TypeFilterCount)> Database::kTypeStrings{
    "Tutti", "Libro", "Album", "Film", "e-Book", "Audiolibro", "Serie TV"};

std::string Database::typeToString(Type type) { return kTypeStrings[static_cast<size_t>(type)]; }
std::string Database::typeToString(size_t type) { return kTypeStrings[type]; }

const media::Media* Database::addMedia(const media::Media& media) {
  removeMedia(media);
  data_.push_back(media.makePtr());
  return data_[data_.size() - 1].get();
}

const media::Media* Database::updateMedia(const media::Media* newMedia, const media::Media* oldMedia) {
  for (std::unique_ptr<media::Media>& media : data_) {
    if (media.get() == oldMedia) {
      media = newMedia->makePtr();
      return media.get();
    }
  }
  return nullptr;
}

void Database::removeMedia(const media::Media& media) {
  for (auto& m : data_) {
    if (!m->getTitle().empty() && typeid(*m) == typeid(media) && *m == media) {
      m->setTitle("");  // Marca come "rimossa"
    }
  }
}

void Database::clear() { data_.clear(); }

std::vector<const media::Media*> Database::filter(const media::Media& media) const {
  std::vector<const media::Media*> results;

  for (const auto& m : data_) {
    if (!m->getTitle().empty() && media.filter(*m)) {  // Ignora media senza titolo
      results.push_back(m.get());
    }
  }
  return results;
}

int Database::serializeAll(QFile& file) const {
  std::vector<const media::Media*> raw_all;

  for (const auto& ptr : data_) {
    if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
      raw_all.push_back(ptr.get());
    }
  }
  return Serializer::serialize(raw_all, file);
}

std::vector<const media::Media*> Database::getAll() const {
  std::vector<const media::Media*> clone;
  clone.reserve(data_.size());

  for (const auto& m : data_) {
    clone.push_back(m.get());
  }
  return clone;
}

void Database::open(const QString& path) { data_ = file_manager_.deserialize(path); }

void Database::save() {
  std::vector<const media::Media*> save_data;
  save_data.reserve(data_.size());

  for (const std::unique_ptr<media::Media>& media : data_) {
    save_data.push_back(media.get());
  }

  file_manager_.save(save_data);
}

void Database::close(bool changes) {
  if (!changes) {
    file_manager_.close();
  } else {
    save();
    file_manager_.close();
  }
}

}  // namespace memory
