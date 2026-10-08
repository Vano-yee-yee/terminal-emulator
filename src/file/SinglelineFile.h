#if !defined(TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_

#include <string>

#include "dir/Directory.h"
#include "file/MultilineFile.h"

namespace term_emul
{

class SinglelineFile: public MultilineFile
{
 public:
   SinglelineFile(const std::string& name, const std::string& content,
     Directory& current_dir);
   
   void edit(const std::string& new_content) override;
};

} // namespace term_emul

#endif