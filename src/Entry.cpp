#include "Entry.h"

#include <memory> // const_pointer_cast
#include <ostream>
#include <stdexcept> // out_of_range invalid_argument
#include <string>
#include <utility> // move swap

#include "aliases.h"
#include "dir/Directory.h"
#include "functions.h"

namespace term_emul
{

Entry::Entry(const std::string& name, CurDirT current_dir)
: cur_dir_(current_dir)
{
  if (func::IsValidName(name))
  {
    name_ = name;
  }
  else
  {
    throw std::invalid_argument(std::string("'") + name 
      + " is not a valid Entry name");
  }
}
Entry::Entry(const Entry& other, CurDirT current_dir)
: name_(other.name_), text_(other.text_)
{
  if (current_dir == nullptr)
  {
    cur_dir_ = other.cur_dir_;
  }
  else
  {
    cur_dir_ = current_dir;
  }
}
Entry::Entry(Entry&& other, CurDirT current_dir) noexcept
: name_(std::move(other.name_)), text_(std::move(other.text_))
{
  if (current_dir == nullptr)
  {
    std::swap(cur_dir_, other.cur_dir_);
  }
  else
  {
    cur_dir_ = current_dir;
  }
}

const std::string& Entry::name() const & noexcept
{
  return name_;
}
std::string&& Entry::name() && noexcept
{
  return std::move(name_);
}

void Entry::rename(const std::string& new_name)
{
  if (func::IsValidName(new_name) && (cur_dir_ == nullptr || cur_dir_ != nullptr 
    && cur_dir_ -> IsUniqueName(new_name))
  )
  {
    name_ = new_name;
  }
}

bool Entry::IsHidden() const noexcept
{
  return name_.size() && name_[0] == '.';
}

void Entry::Hide()
{
  if(name_ == "")
  {
    return;
  }
  
  const std::string hname = std::string(".") + name_;
  if (!IsHidden() && (cur_dir_ == nullptr || cur_dir_ != nullptr 
    && cur_dir_ -> IsUniqueName(hname))
  )
  {
    name_ = hname;
  }
}
void Entry::Unhide()
{
  if(name_ == "")
  {
    return;
  }
  
  const std::string unh_name = name_.substr(1);
  if (IsHidden() && (cur_dir_ == nullptr || cur_dir_ != nullptr
    && cur_dir_ -> IsUniqueName(unh_name))
  )
  {
    name_ = unh_name;
  }
}

std::string Entry::DisplayName() const
{
  std::string res = std::string("'") + func::EscapeQuotes(name_);
  if (*--res.end() != '\'')
  {
    res += '\'';
  }
  return res;
}

const std::string& Entry::content() const & noexcept
{
  return text_;
}
std::string&& Entry::content() && noexcept
{
  return std::move(text_);
}

void Entry::edit(const std::string& new_content)
{}

CurDirT Entry::back() noexcept
{
  return cur_dir_;
}
ConstCurDirT Entry::back() const noexcept
{
  return const_cast<Entry*>(this) 
    -> back();
}

std::ostream& operator<<(std::ostream& out, const Entry& ent)
{
  return out << ent.Display();
}

std::string Entry::Display(bool hidden, DisplaySort sort_type) const
{
  return DisplayName();
}

DirVal Entry::next(const std::string& child_name)
{
  return nullptr;
}
DirConstVal Entry::next(const std::string& child_name) const
{
  return std::const_pointer_cast<DirConstVal::element_type>(const_cast<Entry*>(
    this) -> next(child_name));
}

std::string Entry::FullName() const
{
  std::string res = name_;
  for (CurDirT dir = cur_dir_; dir != nullptr; dir = dir -> cur_dir_)
  {
    if (dir -> name_ == "/")
    {
      res = dir -> name_ + res;
    }
    else
    {
      res = dir -> name_ + '/' + res;
    }
  }
  return res;
}

bool Entry::operator==(const Entry& ent) const
{
  return FullName() == ent.FullName();
}
bool Entry::operator!=(const Entry& ent) const
{
  return !((*this) == ent);
}

std::string Entry::DisplayFullName() const
{
  std::string res = std::string("'") + func::EscapeQuotes(FullName());
  if (*--res.end() != '\'')
  {
    res += '\'';
  }
  return res;
}

Entry* Entry::Clone(CurDirT current_dir) const
{
  return new Entry{*this, current_dir};
}

Entry& Entry::operator[](const std::string& name)
{
  DirVal res = next(name);
  if (res == nullptr)
  {
    std::string msg{"Element '"};
    msg += func::EscapeQuotes(name);
    if (*--msg.end() != '\'')
    {
      msg += '\'';
    }
    msg += " not found";
    throw std::out_of_range{msg};
  }
  return *res;
}
const Entry& Entry::operator[](const std::string& name) const
{
  return (*const_cast<Entry*>(this))[name];
}

} // namespace term_emul