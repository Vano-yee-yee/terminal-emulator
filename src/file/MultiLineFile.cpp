#include "file/MultiLineFile.h"

#include <string>

namespace term_emul
{

MultiLineFile::MultiLineFile(const std::string& name, const std::string& content)
: Entry(name), content_(content)
{}

std::string MultiLineFile::displayContent() const
{
  return content_;
}
void MultiLineFile::edit(const std::string& new_content)
{
  content_ = new_content;
}

} // namespace term_emul