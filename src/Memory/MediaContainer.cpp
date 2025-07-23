#include "MediaContainer.h"

namespace memory {

const std::array<std::string, static_cast<size_t>(MediaContainer::Type::TypeCount)> MediaContainer::kTypeStrings{
    "Tutti", "Libro", "Album", "Film", "e-Book", "Audiolibro", "Serie TV"};

std::string MediaContainer::typeToString(Type type) { return kTypeStrings[static_cast<size_t>(type)]; }
std::string MediaContainer::typeToString(size_t type) { return kTypeStrings[type]; }

void MediaContainer::addMedia(const media::Media& media) {
  removeMedia(media);
  data_.push_back(media.makePtr());
}

void MediaContainer::removeMedia(const media::Media& media) {
  for (auto& m : data_) {
    if (!m->getTitle().empty() && typeid(*m) == typeid(media) && *m == media) {
      m->setTitle("");  // Marca come "rimossa"
    }
  }
}

void MediaContainer::clear() { data_.clear(); }

std::vector<const media::Media*> MediaContainer::filter(const media::Media& media) const {
  std::vector<const media::Media*> results;

  for (const auto& m : data_) {
    if (!m->getTitle().empty() && media.filter(*m)) {  // Ignora media senza titolo
      results.push_back(m->makePtr().release());
    }
  }
  std::cout << "#results = " << results.size() << '\n';
  return results;
}

int MediaContainer::serialize(QFile& file) const {
  std::vector<const media::Media*> raw_all;

  for (const auto& ptr : data_) {
    if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
      raw_all.push_back(ptr.get());
    }
  }
  return Serializer::serialize(raw_all, file);
}

std::vector<const media::Media*> MediaContainer::getAll() const {
  std::vector<const media::Media*> clone;
  clone.reserve(data_.size());

  for (const auto& m : data_) {
    clone.push_back(m->makePtr().release());
  }
  return clone;
}
}  // namespace memory
