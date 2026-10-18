#include "dir/Directory.h"

#include <algorithm> // find_if for_each none_of sort
#include <functional> // less greater
#include <string>
#include <utility> // move swap
#include <vector>

#include "aliases.h"
#include "Entry.h"
#include "functions.h"

namespace term_emul
{

Directory::Directory(const std::string& name, const Directory::Container& content, 
  CurDirT current_dir)
: Entry{name, current_dir}
{
  for (const DirVal& e: content)
  {
    content_.push_back(DirVal{e -> Clone(CurDirT{this})});
  }
}
Directory::Directory(const std::string& name, Directory::Container&& content, 
  CurDirT current_dir)
: Entry{name, current_dir}, content_(func::MoveContainer(content, CurDirT{this}))
{}
Directory::Directory(const Directory& other, CurDirT current_dir)
: Entry{static_cast<const Entry&>(other), current_dir}
{
  for (const DirVal& e: other.content_)
  {
    content_.push_back(DirVal{e -> Clone(CurDirT{this})});
  }
}
Directory::Directory(Directory&& other, CurDirT current_dir) noexcept
: Entry{static_cast<Entry&&>(std::move(other)), current_dir}, 
  content_(func::MoveContainer(other.content_, CurDirT{this}))
{}

Directory& Directory::operator=(const Directory& other)
{
  if (&other == this)
  {
    return *this;
  }
  
  name_ = other.name_;
  cur_dir_ = other.cur_dir_;
  content_.resize(0);
  for (const DirVal& e: other.content_)
  {
    content_.push_back(DirVal{e -> Clone(CurDirT{this})});
  }
  return *this;
}
Directory& Directory::operator=(Directory&& other) noexcept
{
  if (&other == this)
  {
    return *this;
  }
  
  std::swap(name_, other.name_);
  std::swap(cur_dir_, other.cur_dir_);
  content_ = func::MoveContainer(other.content_, CurDirT{this});
  return *this;
}

DirVal Directory::next(const std::string& child_name)
{
  const iterator it = std::find_if(begin(), end(), [&child_name](DirVal& e)
  {
    return e -> name() == child_name;
  });
  if (it == end())
  {
    return nullptr;
  }
  return *it;
}

void Directory::add(const Entry& elem)
{
  Entry* new_el = elem.Clone(CurDirT(this));
  if (new_el == nullptr) // except RootDirectory
  {
    return;
  }
  if (next(elem.name()) == nullptr)
  {
    content_.push_back(DirVal{new_el});
  }
  else
  {
    delete new_el;
  }
}
Directory& Directory::operator+=(const Entry& elem)
{
  add(elem);
  return *this;
}

void Directory::remove(const std::string& name)
{
  DirVal ef = next(name);
  if (ef != nullptr)
  {
    ef -> Hide();
  }
}
void Directory::remove(Entry& elem)
{
  DirVal ef = next(elem.name());
  if (ef != nullptr && ef.get() == &elem)
  {
    ef -> Hide();
  }
}
Directory& Directory::operator-=(Entry& elem)
{
  remove(elem);
  return *this;
}

std::string Directory::DisplayName() const
{
  return Entry::DisplayName() + '/';
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

std::string Directory::Display(bool hidden, DisplaySort sort_type) const
{
  std::vector<std::string> names;
  std::for_each(cbegin(), cend(), [&names, &hidden](const DirVal& e)
  {
    if (!e -> IsHidden() || e -> IsHidden() && hidden)
    {
      names.push_back(e -> DisplayName());
    }
  });
  
  switch (sort_type)
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

bool Directory::IsUniqueName(const std::string& name) const
{
  return std::none_of(cbegin(), cend(), [&name](const DirVal& e)
  {
    return e -> name() == name;
  });
}

Directory* Directory::Clone(CurDirT current_dir) const
{
  return new Directory{*this, current_dir};
}

} // namespace term_emul