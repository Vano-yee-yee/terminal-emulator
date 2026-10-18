#include "dir/RootDirectory.h"

#include <string>

#include "aliases.h"
#include "dir/Directory.h"

namespace term_emul
{

RootDirectory::RootDirectory()
: Directory{""}
{
  name_ = "/";
}
RootDirectory::RootDirectory(const Container& content)
: Directory{"", content}
{
  name_ = "/";
}
RootDirectory::RootDirectory(Container&& content)
: Directory("", content)
{
  name_ = "/";
}

std::string RootDirectory::DisplayName() const
{
  return name();
}

RootDirectory* RootDirectory::Clone(CurDirT current_dir) const
{
  return nullptr;
}

} // namespace term_emul