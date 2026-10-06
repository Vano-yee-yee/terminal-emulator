#include "dir/Directory.h"

#include <algorithm> // find_if for_each
#include <string>
#include <typeinfo> // bad_cast
#include <vector>

#include "dir/RootDirectory.h"
#include "Entry.h"

namespace term_emul
{

Directory::Directory(const std::string& name, const Directory::Container& content,
  Directory* current_dir)
: Entry(name, current_dir), content_(content)
{}

Entry* Directory::find(const std::string& name)
{
  const Directory::iterator it = std::find_if(this -> begin(), this -> end(), 
    [&name](Entry* e)
    {
      return e -> name() == name;
    });
  if(it == this -> end())
  {
    return nullptr;
  }
  return *it;
}
Entry& Directory::operator[](const std::string& name)
{
  return *this -> find(name);
}

const Entry* Directory::find(const std::string& name) const
{
  const Directory::const_iterator it = std::find_if(this -> cbegin(), this -> cend(), 
    [&name](const Entry* e)
    {
      return e -> name() == name;
    });
  if(it == this -> cend())
  {
    return nullptr;
  }
  return *it;
}
const Entry& Directory::operator[](const std::string& name) const
{
  return *this -> find(name);
}

void Directory::add(const Entry& elem)
{
  try
  {
    dynamic_cast<const RootDirectory&>(elem);
  }
  catch(std::bad_cast)
  {
    if(this -> find(elem.name()) == nullptr)
    {
      content_.push_back(new Entry(elem));
    }
  }
}
Directory& Directory::operator+(const Entry& elem)
{
  this -> add(elem);
  return *this;
}

void Directory::remove(const Entry& elem)
{
  Entry* ef = this -> find(elem.name());
  if(ef != nullptr)
  {
    ef -> hide();
  }
}
Directory& Directory::operator-(Entry& elem)
{
  this -> remove(elem);
  return *this;
}

std::string Directory::displayName() const
{
  return name_ + '/';
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

std::string Directory::displayContent() const
{
  std::string res;
  std::for_each(this -> cbegin(), this -> cend(), [&res](const Entry* e)
  {
    res += e -> displayName() + ' ';
  });
  return res;
}

} // namespace term_emul