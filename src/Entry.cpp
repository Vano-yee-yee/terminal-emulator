#include "Entry.h"

#include <string>

#include "functions.h"

namespace term_emul
{

Entry::Entry(const std::string& name)
{
  if(func::isValidName(name))
  {
    name_ = name;
  }
}

const std::string& Entry::name() const
{
  return name_;
}
void Entry::rename(const std::string& new_name)
{
  if(func::isValidName(new_name))
  {
    name_ = new_name;
  }
}

bool Entry::isHidden() const
{
  return name_.size() != 0 && name_[0] == '.';
}
void Entry::hide()
{
  if(!this -> isHidden())
  {
    name_ = std::string(".") + name_;
  }
}
void Entry::operator-()
{
  this -> hide();
}
void Entry::unhide()
{
  if(this -> isHidden())
  {
    name_ = name_.substr(1);
  }
}
void Entry::operator+()
{
  this -> unhide();
}

std::string Entry::displayName() const
{
  return name_;
}

void Entry::add(const Entry&)
{}

std::string Entry::displayContent() const
{
  return this -> displayName();
}

} // namespace term_emul