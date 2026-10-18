#if !defined(TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_

#include <string>

#include "aliases.h"
#include "Entry.h"

namespace term_emul
{

class MultilineFile: public Entry
{
 public:
  MultilineFile* Clone(CurDirT current_dir) const override;
  
  using Entry::Entry;
  MultilineFile(const std::string& name, const std::string& content, 
    CurDirT current_dir = nullptr);
  
  void edit(const std::string& new_content) override;
};

} // namespace term_emul

#endif