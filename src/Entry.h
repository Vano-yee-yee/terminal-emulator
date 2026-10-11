#if !defined(TERMINAL_EMULATOR_ENTRY_H_)
#define TERMINAL_EMULATOR_ENTRY_H_

#include <ostream>
#include <string>

namespace term_emul
{

class Directory;

enum class DisplaySort
{
  kNone, kAsceding, kDesceding
};
class Entry
{
  Directory& cur_dir_;
 protected:
  std::string name_;
  
 public:
  Entry() = delete;
  Entry(const std::string& name, Directory& current_dir);
  
  const std::string& name() const noexcept;
  void rename(const std::string& new_name);
  virtual std::string displayName() const;
  
  std::string fullName() const;
  
  bool isHidden() const noexcept;
  void hide();
  void unhide();
  
  virtual void edit(const std::string& new_content);
  virtual std::string displayContent() const;
  
  Directory& back();
  const Directory& back() const;
  virtual Entry& next(const std::string& child_name);
  const Entry& next(const std::string& child_name) const;
  
  virtual std::string display(DisplaySort sort_type = DisplaySort::kAsceding) const;
  
  bool operator==(const Entry& ent) const;
  bool operator!=(const Entry&) const = default;
};

std::ostream& operator<<(std::ostream& out, const Entry& ent);

} // namespace term_emul

#endif