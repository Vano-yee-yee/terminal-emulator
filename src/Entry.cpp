#include "Entry.h"

#include <ostream>
#include <string>

#include "dir/Directory.h"
#include "functions.h"

namespace term_emul
{

Entry::Entry(const std::string& name, Directory& current_dir)
: cur_dir_(current_dir)
{
  if(func::isValidName(name))
  {
    name_ = name;
  }
}

const std::string& Entry::name() const noexcept
{
  return name_;
}
void Entry::rename(const std::string& new_name)
{
  if(func::isValidName(new_name) && cur_dir_.isUniqueName(new_name))
  {
    name_ = new_name;
  }
}

bool Entry::isHidden() const noexcept
{
  return name_[0] == '.';
}
void Entry::hide()
{
  const std::string hname = std::string(".") + name_;
  if(!this -> isHidden() && cur_dir_.isUniqueName(hname))
  {
    name_ = hname;
  }
}
void Entry::unhide()
{
  const std::string unh_name = name_.substr(1);
  if(this -> isHidden() && cur_dir_.isUniqueName(unh_name))
  {
    name_ = unh_name;
  }
}

std::string Entry::displayName() const
{
  std::string res = std::string("'") + func::escapeQuotes(name_);
  if(res[res.size() - 1] != '\'')
  {
    res += '\'';
  }
  return res;
}
std::string Entry::displayContent() const
{
  return std::string();
}

void Entry::edit(const std::string& new_content)
{}

Directory& Entry::back()
{
  return cur_dir_;
}
const Directory& Entry::back() const
{
  return const_cast<Entry*>(this) -> back();
}

std::ostream& operator<<(std::ostream& out, const Entry& ent)
{
  return out << ent.display();
}

std::string Entry::display(bool hidden, DisplaySort sort_type) const
{
  return this -> displayName();
}

Entry& Entry::next(const std::string& child_name)
{
  return *this;
}
const Entry& Entry::next(const std::string& child_name) const
{
  return const_cast<Entry*>(this) -> next(child_name);
}

std::string Entry::fullName() const
{
  std::string res = name_,
    buf = name_;
  for(const Directory* dir = &this -> back(); dir -> name() != buf; 
    buf = dir -> name(), dir = &dir -> back())
  {
    if(dir -> name() == "/")
    {
      res = dir -> name() + res;
    }
    else
    {
      res = dir -> name() + '/' + res;
    }
  }
  return res;
}

bool Entry::operator==(const Entry& ent) const
{
  return this -> fullName() == ent.fullName();
}

std::string Entry::displayFullName() const
{
  std::string res = std::string("'") + func::escapeQuotes(this -> fullName());
  if(res[res.size() - 1] != '\'')
  {
    res += '\'';
  }
  return res;
}

} // namespace term_emul