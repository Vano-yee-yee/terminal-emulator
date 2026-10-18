#if !defined(TERMINAL_EMULATOR_ENTRY_H_)
#define TERMINAL_EMULATOR_ENTRY_H_

#include <ostream>
#include <string>

#include "aliases.h"
#include "functions.h"

namespace term_emul
{

class Entry
{
 protected:
  std::string name_;
  std::string text_;
  CurDirT cur_dir_;
  
  friend DirContainer&& func::MoveContainer(DirContainer& content, 
    CurDirT current_dir) noexcept;
 public:
  virtual Entry* Clone(CurDirT current_dir) const;
  
  Entry(const std::string& name, CurDirT current_dir = nullptr);
  
  Entry() = delete;
  Entry(const Entry& other, CurDirT current_dir = nullptr);
  Entry& operator=(const Entry& other) = default;
  Entry(Entry&& other, CurDirT current_dir = nullptr) noexcept;
  Entry& operator=(Entry&& other) noexcept = default;
  virtual ~Entry() = default;
  
  const std::string& name() const & noexcept;
  std::string&& name() && noexcept;
  void rename(const std::string& new_name);
  virtual std::string DisplayName() const;
  
  std::string FullName() const;
  std::string DisplayFullName() const;
  
  bool IsHidden() const noexcept;
  void Hide();
  void Unhide();
  
  const std::string& content() const & noexcept;
  std::string&& content() && noexcept;
  virtual void edit(const std::string& new_content);
  
  CurDirT back() noexcept;
  ConstCurDirT back() const noexcept;
  virtual DirVal next(const std::string& child_name);
  DirConstVal next(const std::string& child_name) const;
  virtual std::string Display(bool hidden = false, 
    DisplaySort sort_type = DisplaySort::kAsceding) const;
  
  bool operator==(const Entry& ent) const;
  bool operator!=(const Entry&) const;
  Entry& operator[](const std::string& name);
  const Entry& operator[](const std::string& name) const;
};

std::ostream& operator<<(std::ostream& out, const Entry& ent);

} // namespace term_emul

#endif