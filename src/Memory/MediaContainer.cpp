#include "MediaContainer.h"

namespace memory {

const std::array<std::string, static_cast<size_t>(MediaContainer::Type::TypeCount)> MediaContainer::kTypeStrings{
    "Tutti", "Libro", "Album", "Film", "e-Book", "Audiolibro", "Serie TV"};

std::string MediaContainer::typeToString(Type type) { return kTypeStrings[static_cast<size_t>(type)]; }
std::string MediaContainer::typeToString(size_t type) { return kTypeStrings[type]; }

void MediaContainer::addMedia(const media::Media& media) {
  Type t = detectType(media);
  if (t == Type::All) {
    return;
  }

  // Rimuove eventuali duplicati prima di inserire
  removeMedia(media);

  // Inserisce una copia in "All"
  data_[static_cast<int>(Type::All)].push_back(media.makePtr());

  // Inserisce una copia nel tipo specifico
  data_[static_cast<int>(t)].push_back(media.makePtr());
}

void MediaContainer::addMedia(const std::vector<media::Media>& listaMedia) {
  for (const auto& media : listaMedia) {
    addMedia(media);
  }
}

MediaContainer::Type MediaContainer::detectType(const media::Media& media) const {
  if (dynamic_cast<const media::Series*>(&media)) return Type::Series;
  if (dynamic_cast<const media::AudioBook*>(&media)) return Type::AudioBook;
  if (dynamic_cast<const media::Ebook*>(&media)) return Type::Ebook;
  if (dynamic_cast<const media::Movie*>(&media)) return Type::Movie;
  if (dynamic_cast<const media::Album*>(&media)) return Type::Album;
  if (dynamic_cast<const media::Novel*>(&media)) return Type::Novel;
  return Type::All;
}

void MediaContainer::removeMedia(const media::Media& media) {
  for (auto& vec : data_) {
    for (auto& m : vec) {
      if (!m->getTitle().empty() && typeid(*m) == typeid(media) && *m == media) {
        m->setTitle("");  // Marca come "rimossa"
      }
    }
  }
}

void MediaContainer::clear() {
  for (auto& vec : data_) {
    vec.clear();
  }
}

std::vector<const media::Media*> MediaContainer::getAll() const { return getByType(Type::All); }

std::vector<const media::Media*> MediaContainer::getByType(Type type) const {
  std::vector<const media::Media*> result;
  for (const auto& ptr : data_[static_cast<int>(type)]) {
    if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
      result.push_back(ptr.get());
    }
  }
  return result;
}

std::vector<const media::Media*> MediaContainer::getByGroup(Type type) const {
  std::vector<const media::Media*> result;

  auto append_group = [&](Type t) {
    for (const auto& ptr : data_[static_cast<int>(t)]) {
      if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
        result.push_back(ptr.get());
      }
    }
  };

  switch (type) {
    case Type::Novel:
      append_group(Type::Novel);
      append_group(Type::Ebook);
      append_group(Type::AudioBook);
      break;
    case Type::Movie:
      append_group(Type::Movie);
      append_group(Type::Series);
      break;
    case Type::All:
      append_group(Type::All);
      break;
    default:
      append_group(type);
      break;
  }

  return result;
}

std::vector<const media::Media*> MediaContainer::filter(const media::Media& media) const {
  std::vector<const media::Media*> results;
  Type t = detectType(media);

  for (const media::Media* m : getByGroup(t)) {
    if (!m->getTitle().empty() && media.filter(*m)) {  // Ignora media senza titolo
      results.push_back(m);
    }
  }
  return results;
}

int MediaContainer::serialize(QFile& file) const {
  std::vector<const media::Media*> raw_all;
  for (const auto& ptr : data_[static_cast<int>(Type::All)]) {
    if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
      raw_all.push_back(ptr.get());
    }
  }
  return Serializer::serialize(raw_all, file);
}

}  // namespace memory
