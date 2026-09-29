#include "RootDirectory.h"

#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

RootDirectory::RootDirectory(const std::vector<Entry*>& content)
: Directory("", content)
{
  name_ = "/";
}

RootDirectory& RootDirectory::getInstance(const std::vector<Entry*>& content)
{
  static RootDirectory r(content);
  return r;
}

} // namespace term_emul