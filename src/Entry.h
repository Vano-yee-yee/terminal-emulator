#if !defined(TERMINAL_EMULATOR_ENTRY_H_)
#define TERMINAL_EMULATOR_ENTRY_H_

#include <string>

namespace term_emul
{

class Entry
{
 protected:
  std::string name_;
 public:
  Entry() = delete;
  Entry(const std::string& name);
  
  const std::string& name() const;
  void rename(const std::string& new_name);
  virtual std::string displayName() const;
  
  bool isHidden() const;
  void hide();
  void unhide();
  
  virtual void add(const Entry&);
  virtual std::string displayContent() const;
  
  void operator+();
  void operator-();
};

} // namespace term_emul

#endif