#if !defined(TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_)
#define TERMINAL_EMULATOR_FILE_SINGLELINEFILE_H_

#include <string>

#include "Entry.h"
#include "file/MultiLineFile.h"

namespace term_emul
{

class SingleLineFile: public MultiLineFile
{
 public:
   SingleLineFile(const std::string& name, const std::string& content);
   
   void edit(const std::string& new_content) override;
};

} // namespace term_emul

#endif