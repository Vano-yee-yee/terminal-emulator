#include "file/SingleLineFile.h"

#include <string>

#include "functions.h"

namespace term_emul
{

SingleLineFile::SingleLineFile(const std::string& name, const std::string& content)
: MultiLineFile(name)
{
  if(func::isSingleLine(content))
  {
    content_ = content;
  }
}

void SingleLineFile::edit(const std::string& new_content)
{
  if(func::isSingleLine(new_content))
  {
    content_ = new_content;
  }
}

} // namespace term_emul