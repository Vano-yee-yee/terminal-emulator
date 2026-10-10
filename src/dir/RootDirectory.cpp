#include "dir/RootDirectory.h"

#include <string>

#include "dir/Directory.h"

namespace term_emul
{

RootDirectory::RootDirectory()
: Directory("", *this)
{
  name_ = "/";
}
RootDirectory::RootDirectory(const Container& content)
: Directory("", content, *this)
{
  name_ = "/";
}

std::string RootDirectory::displayName() const
{
  return this -> name();
}

} // namespace term_emul