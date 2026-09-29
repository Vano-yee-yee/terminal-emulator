#include "Directory.h"

#include <algorithm>
#include <string>
#include <vector>

#include "Entry.h"

namespace term_emul
{

Directory::Directory(const std::string& name, const std::vector<Entry>& content)
: Entry(name), content_(content)
{}

Entry* Directory::find(const std::string& name)
{
  const auto it = std::find_if(content_.begin(), content_.end(), [name](Entry& e)
    {
      return e.name() == name;
    });
  if(it == content_.end())
    return nullptr;
  return &*it;
}
Entry* Directory::operator[](const std::string& name)
{
  return this -> find(name);
}

const Entry* Directory::find(const std::string& name) const
{
  const auto it = std::find_if(content_.begin(), content_.end(), 
    [name](const Entry& e)
    {
      return e.name() == name;
    });
  if(it == content_.end())
    return nullptr;
  return &*it;
}
const Entry* Directory::operator[](const std::string& name) const
{
  return this -> find(name);
}

void Directory::add(const Entry& elem)
{
  if((*this)[elem.name()] == nullptr)
  {
    content_.push_back(elem);
  }
}
void Directory::remove(Entry* elem)
{
  -(*elem);
}

std::string Directory::displayName() const
{
  return name_ + '/';
}

std::vector<Entry>::iterator Directory::begin()
{
  return content_.begin();
}
std::vector<Entry>::iterator Directory::end()
{
  return content_.end();
}
std::vector<Entry>::const_iterator Directory::cbegin() const
{
  return content_.cbegin();
}
std::vector<Entry>::const_iterator Directory::cend() const
{
  return content_.cend();
}

} // namespace term_emul