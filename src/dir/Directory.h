#if !defined(TERMINAL_EMULATOR_DIR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_DIRECTORY_H_

#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

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
    Directory* current_dir = nullptr);
  
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  
  Entry* find(const std::string& name);
  const Entry* find(const std::string& name) const;
  
  std::string displayName() const override;
  
  void add(const Entry& elem);
  void remove(const Entry& elem);
  std::string displayContent() const override;
  
  Entry& operator[](const std::string& name);
  const Entry& operator[](const std::string& name) const;
  Directory& operator+(const Entry& elem);
  Directory& operator-(Entry& elem);
};

} // namespace term_emul

#endif