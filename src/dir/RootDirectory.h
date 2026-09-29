#if !defined(TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_

#include <string>
#include <vector>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{

class RootDirectory: public Directory
{
  RootDirectory(const std::vector<Entry*>& content);
 public:
  RootDirectory(const RootDirectory&) = delete;
  
  static RootDirectory& getInstance(const std::vector<Entry*>& content = {});
  
  void rename(const std::string& new_name) = delete;
  
  void hide() = delete;
  void unhide() = delete;
  
  RootDirectory& operator=(const RootDirectory&) = delete;
  using Directory::operator+;
  void operator+() = delete;
  using Directory::operator-;  
  void operator-() = delete;
};

} // namespace term_emul

#endif