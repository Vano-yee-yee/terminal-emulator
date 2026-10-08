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
  if(func::isValidName(new_name) && func::isUniqueName(cur_dir_, new_name))
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
  if(!this -> isHidden())
  {
    this -> rename(std::string(".") + name_);
  }
}
void Entry::unhide()
{
  if(this -> isHidden())
  {
    this -> rename(name_.substr(1));
  }
}

std::string Entry::displayName() const
{
  return std::string("'") + name_ + '\'';
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
  return cur_dir_;
}

std::ostream& operator<<(std::ostream& out, const Entry& ent)
{
  return out << ent.display();
}

std::string Entry::display() const
{
  return this -> displayName();
}

Entry& Entry::next(const std::string& child_name)
{
  return *this;
}
const Entry& Entry::next(const std::string& child_name) const
{
  return *this;
}

std::string Entry::fullName() const
{
  std::string res(name_),
    buf(name_);
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

} // namespace term_emul