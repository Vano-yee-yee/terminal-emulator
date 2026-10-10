#include "dir/Directory.h"

#include <algorithm> // find_if for_each none_of
#include <string>

#include "dir/RootDirectory.h"
#include "Entry.h"

namespace term_emul
{

Directory::Directory(const std::string& name, const Directory::Container& content,
  Directory& current_dir)
: Entry(name, current_dir), content_(content)
{}

Entry& Directory::next(const std::string& child_name)
{
  const iterator it = std::find_if(this -> begin(), this -> end(), 
    [&child_name](Entry* e)
    {
      return e -> name() == child_name;
    });
  if(it == this -> end())
  {
    return *this;
  }
  return **it;
}
/*const Entry& Directory::next(const std::string& child_name) const
{
  const const_iterator it = std::find_if(this -> cbegin(), this -> cend(), 
    [&child_name](const Entry* e)
    {
      return e -> name() == child_name;
    });
  if(it == this -> cend())
  {
    return *this;
  }
  return **it;
}*/

void Directory::remove(const Entry& elem)
{
  Entry& ef = this -> next(elem.name());
  if(ef != *this)
  {
    ef.hide();
  }
}
Directory& Directory::operator-(const Entry& elem)
{
  this -> remove(elem);
  return *this;
}

std::string Directory::displayName() const
{
  return std::string("'") + this -> name() + "'/";
}

Directory::iterator Directory::begin() noexcept
{
  return content_.begin();
}
Directory::iterator Directory::end() noexcept
{
  return content_.end();
}
Directory::const_iterator Directory::cbegin() const noexcept
{
  return content_.cbegin();
}
Directory::const_iterator Directory::cend() const noexcept
{
  return content_.cend();
}

std::string Directory::display() const
{
  std::string res;
  std::for_each(this -> cbegin(), this -> cend(), [&res](const Entry* e)
  {
    res += e -> displayName() + ' ';
  });
  return res;
}

bool Directory::isUniqueName(const std::string& name) const
{
  return std::none_of(this -> cbegin(), this -> cend(), 
    [&name](const Entry* e)
    {
      return e -> name() == name;
    });
}

} // namespace term_emul