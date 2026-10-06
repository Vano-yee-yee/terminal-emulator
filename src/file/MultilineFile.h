#if !defined(TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_

#include <string>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{

class MultilineFile: public Entry
{
 protected:
  std::string content_;
  
 public:
  using Entry::Entry;
  MultilineFile(const std::string& name, const std::string& content, 
    Directory* current_dir = nullptr);
  
  void edit(const std::string& new_content) override;
  std::string displayContent() const override;
};

} // namespace term_emul

#endif