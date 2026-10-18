#include "file/SinglelineFile.h"

#include <string>

#include "aliases.h"
#include "file/MultilineFile.h"
#include "functions.h"

namespace term_emul
{

void SinglelineFile::edit(const std::string& new_content)
{
  if (func::IsSingleline(new_content))
  {
    text_ = new_content;
  }
}

SinglelineFile::SinglelineFile(const std::string& name, const std::string& content,
  CurDirT current_dir)
: MultilineFile{name, current_dir}
{
  this -> edit(content);
}

SinglelineFile* SinglelineFile::Clone(CurDirT current_dir) const
{
  return new SinglelineFile{*this, current_dir};
}

} // namespace term_emul