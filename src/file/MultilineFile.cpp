#include "file/MultilineFile.h"

#include <string>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{

MultilineFile::MultilineFile(const std::string& name, const std::string& content,
  Directory& current_dir)
: Entry(name, current_dir), content_(content)
{}

std::string MultilineFile::displayContent() const
{
  return content_;
}
void MultilineFile::edit(const std::string& new_content)
{
  content_ = new_content;
}

} // namespace term_emul