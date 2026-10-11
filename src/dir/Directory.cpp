#include "dir/Directory.h"

#include <algorithm> // find_if for_each none_of
#include <functional> // less greater
#include <string>
#include <vector>

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
  return Entry::displayName() + '/';
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

std::string Directory::display(DisplaySort sort_type) const
{
  std::vector<std::string> names;
  std::for_each(this -> cbegin(), this -> cend(), [&names](const Entry* e)
  {
    names.push_back(e -> displayName());
  });
  switch(sort_type)
  {
    case DisplaySort::kAsceding:
      std::sort(names.begin(), names.end(), std::less<std::string>{});
      break;
    case DisplaySort::kDesceding:
      std::sort(names.begin(), names.end(), std::greater<std::string>{});
      break;
    default:
      break;
  }
  
  std::string res;
  std::for_each(names.cbegin(), names.cend(), [&res](const std::string& str)
  {
    res += str + ' ';
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