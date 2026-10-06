#include "dir/RootDirectory.h"

#include <vector>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{

RootDirectory::RootDirectory()
: Directory("", nullptr)
{
  name_ = "/";
}
RootDirectory::RootDirectory(const Container& content)
: Directory("", content, nullptr)
{
  name_ = "/";
}

Directory& RootDirectory::back()
{
  return *this;
}
const Directory& RootDirectory::back() const
{
  return *this;
}

std::string RootDirectory::displayName() const
{
  return name_;
}

} // namespace term_emul