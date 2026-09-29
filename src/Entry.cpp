#include "Entry.h"

#include <algorithm>
#include <string>

#include "Directory.h"
#include "functions.h"

namespace term_emul
{

Entry::Entry(const std::string& name, Directory* dot_dir)
{
  if(func::isValidName(name))
  {
    name_ = name;
  }
  dot_dir_ = dot_dir;
}

const std::string& Entry::name() const
{
  return name_;
}
void Entry::rename(const std::string& new_name)
{
  if(func::isValidName(new_name) && this -> isUniqueName(new_name))
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
    std::string new_name = std::string(".") + name_;
    if(this -> isUniqueName(new_name))
    {
      name_ = new_name;
    }
  }
}
Entry& Entry::operator-()
{
  this -> hide();
  return *this;
}

void Entry::unhide()
{
  if(this -> isHidden())
  {
    std::string new_name = name_.substr(0);
    if(this -> isUniqueName(new_name))
    {
      name_ = new_name;
    }
  }
}
Entry& Entry::operator+()
{
  this -> unhide();
  return *this;
}

std::string Entry::displayName() const
{
  return name_;
}

void Entry::add(const Entry&)
{}
Entry& Entry::operator+(const Entry& elem)
{
  this -> add(elem);
  return *this;
}

std::string Entry::displayContent() const
{
  return this -> displayName();
}

bool Entry::isUniqueName(const std::string& name)
{
  return dot_dir_ == nullptr || dot_dir_ != nullptr && 
    std::none_of(dot_dir_ -> cbegin(), dot_dir_ -> cend(), [&name](const Entry* e)
    {
      return e -> name() == name;
    });
}

} // namespace term_emul