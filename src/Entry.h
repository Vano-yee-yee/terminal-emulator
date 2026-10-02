#if !defined(TERMINAL_EMULATOR_ENTRY_H_)
#define TERMINAL_EMULATOR_ENTRY_H_

#include <string>

namespace term_emul
{

class Directory;

class Entry
{
  Directory* cur_dir_;
 protected:
  std::string name_;
  
 public:
  Entry() = delete;
  Entry(const std::string& name, Directory* current_dir = nullptr);
  
  const std::string& name() const noexcept;
  void rename(const std::string& new_name);
  virtual std::string displayName() const;
  
  bool isHidden() const noexcept;
  void hide();
  void unhide();
  
  virtual void edit(const std::string& new_content);
  virtual std::string displayContent() const;
  
  Entry& operator-();
  Entry& operator+();
};

} // namespace term_emul

#endif