#if !defined(TERMINAL_EMULATOR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIRECTORY_H_

#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

class Directory: public Entry
{
  std::vector<Entry> content_;
 public:
  using Entry::Entry;
  Directory(const std::string& name, const std::vector<Entry>& content);
  
  void add(const Entry& elem);
  void remove(Entry* elem);
  
  Entry* find(const std::string& name);
  const Entry* find(const std::string& name) const;
  
  Entry* operator[](const std::string& name);
  const Entry* operator[](const std::string& name) const;
  
  std::string displayName() const override;
  
  std::vector<Entry>::iterator begin();
  std::vector<Entry>::iterator end();
  std::vector<Entry>::const_iterator cbegin() const;
  std::vector<Entry>::const_iterator cend() const;
};

} // namespace term_emul

#endif