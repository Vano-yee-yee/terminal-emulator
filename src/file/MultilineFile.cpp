#include "file/MultilineFile.h"

#include <string>

#include "aliases.h"
#include "Entry.h"

namespace term_emul
{

MultilineFile::MultilineFile(const std::string& name, const std::string& content, 
  CurDirT current_dir)
: Entry{name, current_dir}
{
  text_ = content;
}

void MultilineFile::edit(const std::string& new_content)
{
  text_ = new_content;
}

MultilineFile* MultilineFile::Clone(CurDirT current_dir) const
{
  return new MultilineFile{*this, current_dir};
}

} // namespace term_emul