#if !defined(TERMINAL_EMULATOR_DIR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_DIRECTORY_H_

#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

class Directory: public Entry
{
  std::vector<Entry*> content_;
  
 public:
  using Entry::Entry;
  Directory(const std::string& name, const std::vector<Entry*>& content, 
    Directory* current_dir = nullptr);
  
  std::vector<Entry*>::iterator begin() noexcept;
  std::vector<Entry*>::iterator end() noexcept;
  std::vector<Entry*>::const_iterator cbegin() const noexcept;
  std::vector<Entry*>::const_iterator cend() const noexcept;
  
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