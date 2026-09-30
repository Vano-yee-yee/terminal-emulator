#include "file/SinglelineFile.h"

#include <string>

#include "functions.h"

namespace term_emul
{

SinglelineFile::SinglelineFile(const std::string& name, const std::string& content)
: MultilineFile(name)
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