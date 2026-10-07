#if !defined(TERMINAL_EMULATOR_DIR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_DIRECTORY_H_

#include <concepts> // same_as
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
    Directory* current_dir);
  
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  
  Entry* find(const std::string& name);
  const Entry* find(const std::string& name) const;
  
  std::string displayName() const override;
  
  template <typename T = Entry>
  requires (!std::same_as<T, RootDirectory>)
  void add(const T& elem);
  
  void remove(const Entry& elem);
  std::string display() const override;
  
  Entry& operator[](const std::string& name);
  const Entry& operator[](const std::string& name) const;
  template <typename T = Entry>
  Directory& operator+(const T& elem);
  
  Directory& operator-(const Entry& elem);
};

template <typename T>
requires (!std::same_as<T, RootDirectory>)
void Directory::add(const T& elem)
{
  if(this -> find(elem.name()) == nullptr)
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