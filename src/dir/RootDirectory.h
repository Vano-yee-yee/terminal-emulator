#if !defined(TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_

#include <string>
#include <vector>

#include "dir/Directory.h"

namespace term_emul
{

class RootDirectory: public Directory
{
 public:
  RootDirectory();
  RootDirectory(const Container& content);
  
  void rename(const std::string&) = delete;
  std::string displayName() const override;
  
  void hide() = delete;
  void unhide() = delete;
};

} // namespace term_emul

#endif