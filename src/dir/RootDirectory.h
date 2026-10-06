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
 public:
  RootDirectory();
  RootDirectory(const Container& content);
  
  void rename(const std::string&) = delete;
  
  void hide() = delete;
  void unhide() = delete;
  
  using Directory::operator+;
  void operator+() = delete;
  using Directory::operator-;
  void operator-() = delete;
};

} // namespace term_emul

#endif