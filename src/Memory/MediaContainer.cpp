#include "MediaContainer.h"

namespace memory {

const std::array<std::string, static_cast<size_t>(MediaContainer::Type::TypeCount)> MediaContainer::kTypeStrings{
    "Tutti", "Libro", "Album", "Film", "e-Book", "Audiolibro", "Serie TV"};

std::string MediaContainer::typeToString(Type type) { return kTypeStrings[static_cast<size_t>(type)]; }
std::string MediaContainer::typeToString(size_t type) { return kTypeStrings[type]; }

MediaContainer::MediaOpVisitor::MediaOpVisitor(MediaContainer *container, Operation op)
    : container_(container), const_container_(container), operation_(op) {}

MediaContainer::MediaOpVisitor::MediaOpVisitor(const MediaContainer *container, Operation op)
    : container_(nullptr), const_container_(container), operation_(op) {}

void MediaContainer::MediaOpVisitor::appendGroup(Type t) {
  for (const auto& ptr : const_container_->data_[static_cast<int>(t)]) {
    if (!ptr->getTitle().empty()) {  // Ignora media senza titolo
      groups_.push_back(ptr.get());
    }
  }
}

void MediaContainer::MediaOpVisitor::visit(const media::Media&) {
  switch (operation_) {
    case Operation::kGetGroups:
      for (size_t i = 1; i < static_cast<size_t>(Type::TypeCount); ++i) {
        appendGroup(static_cast<Type>(i));
      }
      break;
    default: break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::Album& album) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(album);
      container_->data_[static_cast<int>(Type::Album)].push_back(album.makePtr());
      break;

    case Operation::kGetGroups:
      appendGroup(Type::Album);
      break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::Novel& novel) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(novel);
      container_->data_[static_cast<int>(Type::Novel)].push_back(novel.makePtr());
      break;
      
    case Operation::kGetGroups:
      appendGroup(Type::Novel);
      appendGroup(Type::Movie);
      appendGroup(Type::Series);
      break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::AudioBook& audiobook) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(audiobook);
      container_->data_[static_cast<int>(Type::AudioBook)].push_back(audiobook.makePtr());
      break;
      
    case Operation::kGetGroups:
      appendGroup(Type::AudioBook);
      break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::Ebook& ebook) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(ebook);
      container_->data_[static_cast<int>(Type::Ebook)].push_back(ebook.makePtr());
      break;
      
    case Operation::kGetGroups:
      appendGroup(Type::Ebook);
      break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::Movie& movie) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(movie);
      container_->data_[static_cast<int>(Type::Movie)].push_back(movie.makePtr());
      break;
      
    case Operation::kGetGroups:
      appendGroup(Type::Movie);
      appendGroup(Type::Series);
      break;
  }
}
void MediaContainer::MediaOpVisitor::visit(const media::Series& series) {
  switch (operation_) {
    case Operation::kAddMedia:
      container_->removeMedia(series);
      container_->data_[static_cast<int>(Type::Series)].push_back(series.makePtr());
      break;
      
    case Operation::kGetGroups:
      appendGroup(Type::Series);
      break;
  }
}
void MediaContainer::addMedia(const media::Media& media) {
  MediaOpVisitor v(this, MediaOpVisitor::Operation::kAddMedia);
  media.accept(v);
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

std::vector<const media::Media*> MediaContainer::getAll() const {
  MediaOpVisitor v(this);
  media::Media{}.accept(v);
  return v.getGroups();
}

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
  // Type t = detectType(media);
  MediaOpVisitor v(this, MediaOpVisitor::Operation::kGetGroups); // la pigrizia impera
  media.accept(v);

  for (const media::Media* m : v.getGroups()) {
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
