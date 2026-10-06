#include "Entry.h"

#include <ostream>
#include <string>

#include "dir/Directory.h"
#include "functions.h"

namespace term_emul
{

Entry::Entry(const std::string& name, Directory* current_dir)
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
  const std::string new_name = std::string(".") + name_;
  if(!this -> isHidden() && func::isUniqueName(cur_dir_, new_name))
  {
    name_ = new_name;
  }
}
void Entry::unhide()
{
  const std::string new_name = name_.substr(1);
  if(this -> isHidden() && func::isUniqueName(cur_dir_, new_name))
  {
    name_ = new_name;
  }
}

std::string Entry::displayName() const
{
  return name_;
}
std::string Entry::displayContent() const
{
  return std::string();
}

void Entry::edit(const std::string& new_content)
{}

Directory& Entry::back()
{
  return *cur_dir_;
}
const Directory& Entry::back() const
{
  return *cur_dir_;
}

std::ostream& operator<<(std::ostream& out, const Entry& ent)
{
  return out << ent.display();
}

std::string Entry::display() const
{
  return this -> displayName();
}

} // namespace term_emul