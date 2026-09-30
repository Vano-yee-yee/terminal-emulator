#if !defined(TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_MULTILINEFILE_H_

#include <string>

#include "Entry.h"

namespace term_emul
{

class MultilineFile: public Entry
{
 protected:
  std::string content_;
 public:
  using Entry::Entry;
  MultilineFile(const std::string& name, const std::string& content);
  
  std::string displayContent() const override;
  virtual void edit(const std::string& new_content);
};

} // namespace term_emul

#endif