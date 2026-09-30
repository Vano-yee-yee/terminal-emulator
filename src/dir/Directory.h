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
  Directory(const std::string& name, const std::vector<Entry*>& content);
  
  std::string displayName() const override;
  
  void add(const Entry& elem) override;
  void remove(Entry& elem);
  std::string displayContent() const override;
  
  Entry* find(const std::string& name);
  const Entry* find(const std::string& name) const;
  
  std::vector<Entry*>::iterator begin() noexcept;
  std::vector<Entry*>::iterator end() noexcept;
  std::vector<Entry*>::const_iterator cbegin() const noexcept;
  std::vector<Entry*>::const_iterator cend() const noexcept;
  
  Entry& operator[](const std::string& name);
  const Entry& operator[](const std::string& name) const;
  using Entry::operator+;
  Entry& operator-(Entry& elem);
};

} // namespace term_emul

#endif