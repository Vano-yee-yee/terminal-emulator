#if !defined(TERMINAL_EMULATOR_DIR_DIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_DIRECTORY_H_

#include <string>

#include "aliases.h"
#include "Entry.h"

namespace term_emul
{

class Directory: public Entry
{
 public:
  using Container = DirContainer;
  using iterator = Container::iterator;
  using const_iterator = Container::const_iterator;
  
 protected:
  Container content_;
  
 public:
  Directory* Clone(CurDirT current_dir) const override;
  
  using Entry::Entry;
  Directory(const std::string& name, const Container& content, 
    CurDirT current_dir = nullptr);
  
  Directory(const Directory& other, CurDirT current_dir = nullptr);
  Directory& operator=(const Directory& other);
  Directory(Directory&& other, CurDirT current_dir = nullptr) /*noexcept*/;
  Directory& operator=(Directory&& other) /*noexcept*/;
  ~Directory() = default;
  
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  
  std::string DisplayName() const override;
  
  bool IsUniqueName(const std::string& name) const;
  
  DirVal next(const std::string& child_name) override;
  std::string Display(bool hidden = false, 
    DisplaySort sort_type = DisplaySort::kAsceding) const override;
  void add(const Entry& elem);
  void remove(Entry& elem);
  void remove(const std::string& name);
  
  Directory& operator+=(const Entry& elem);
  Directory& operator-=(Entry& elem);
};

} // namespace term_emul

#endif