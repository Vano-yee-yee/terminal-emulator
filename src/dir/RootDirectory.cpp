#include "dir/RootDirectory.h"

#include <vector>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{

RootDirectory::RootDirectory()
: Directory("")
{
  name_ = "/";
}
RootDirectory::RootDirectory(const Container& content)
: Directory("", content)
{
  name_ = "/";
}

} // namespace term_emul