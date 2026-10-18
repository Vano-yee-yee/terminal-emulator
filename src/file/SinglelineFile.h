#if !defined(TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_

#include <string>

#include "aliases.h"
#include "file/MultilineFile.h"

namespace term_emul
{

class SinglelineFile: public MultilineFile
{
 public:
  SinglelineFile* Clone(CurDirT current_dir) const override;
  
  using MultilineFile::MultilineFile;
  SinglelineFile(const std::string& name, const std::string& content,
    CurDirT current_dir = nullptr);
  
  void edit(const std::string& new_content) override;
};

} // namespace term_emul

#endif