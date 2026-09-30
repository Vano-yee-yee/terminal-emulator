#include "dir/RootDirectory.h"

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

} // namespace term_emul