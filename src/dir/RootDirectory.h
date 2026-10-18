#if !defined(TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_)
#define TERMINAL_EMULATOR_DIR_ROOTDIRECTORY_H_

#include <string>

#include "aliases.h"
#include "dir/Directory.h"

namespace term_emul
{

class RootDirectory: public Directory
{
 public:
  RootDirectory* Clone(CurDirT current_dir) const override;
  
  RootDirectory();
  RootDirectory(const Container& content);
  RootDirectory(Container&& content);
  
  void rename(const std::string&) = delete;
  std::string DisplayName() const override;
  
  void Hide() = delete;
  void Unhide() = delete;
};

} // namespace term_emul

#endif