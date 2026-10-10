#if !defined(TERMINAL_EMULATOR_DIR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_DIRECTORY_H_

#include <concepts> // same_as derived_from
#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

class RootDirectory;

class Directory: public Entry
{
 public:
  using Container = std::vector<Entry*>;
  using iterator = Container::iterator;
  using const_iterator = Container::const_iterator;
  
 private:
  Container content_;
  
 public:
  using Entry::Entry;
  Directory(const std::string& name, const Container& content, 
    Directory& current_dir);
  
  std::string displayName() const override;
  bool isUniqueName(const std::string& name);
  
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  
  Entry& next(const std::string& child_name) override;
  const Entry& next(const std::string& child_name) const override;
  
  template <typename T = Entry>
  requires (!std::same_as<T, RootDirectory> && std::derived_from<T, Entry>)
  void add(const T& elem);
  
  void remove(const Entry& elem);
  std::string display() const override;
  
  Directory& operator-(const Entry& elem);
  
  template <typename T = Entry>
  Directory& operator+(const T& elem);
};

template <typename T>
requires (!std::same_as<T, RootDirectory> && std::derived_from<T, Entry>)
void Directory::add(const T& elem)
{
  if(this -> next(elem.name()) == *this)
  {
    content_.push_back(new T(elem));
  }
}
template <typename T>
Directory& Directory::operator+(const T& elem)
{
  this -> add(elem);
  return *this;
}

} // namespace term_emul

#endif