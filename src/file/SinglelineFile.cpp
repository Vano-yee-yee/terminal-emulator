#include "file/SinglelineFile.h"

#include <string>

#include "dir/Directory.h"
#include "file/MultilineFile.h"
#include "functions.h"

namespace term_emul
{

SinglelineFile::SinglelineFile(const std::string& name, const std::string& content,
  Directory& current_dir)
: MultilineFile(name, current_dir)
{
  if(func::isSingleline(content))
  {
    content_ = content;
  }
}

void SinglelineFile::edit(const std::string& new_content)
{
  if(func::isSingleline(new_content))
  {
    content_ = new_content;
  }
}

} // namespace term_emul