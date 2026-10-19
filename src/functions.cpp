#include "functions.h"

#include <algorithm> // none_of for_each
#include <sstream> // istringstream
#include <string> // string getline
#include <utility> // move
#include <vector>

#include "aliases.h"
#include "Entry.h" // cur_dir_

namespace term_emul
{
namespace func
{

bool IsValidName(const std::string& name)
{
  return name.size() && name != "." && name != ".." && 
    std::none_of(name.cbegin(), name.cend(), [](char sym)
    {
      return sym == '/';
    });
}
bool IsSingleline(const std::string& str)
{
  return std::none_of(str.cbegin(), str.cend(), [](char sym)
  {
    return sym == '\n';
  });
}

std::vector<std::string> DelimPath(const std::string& path)
{
  std::vector<std::string> res;
  if (!path.size())
  {
    res.push_back(path);
    return res;
  }
  
  if (path[0] == '/')
  {
    res.push_back("/");
  }
  std::istringstream path_stream{path};
  for (std::string path_elem; std::getline(path_stream, path_elem, '/');)
  {
    if (path_elem != "")
    {
      res.push_back(path_elem);
    }
  }
  return res;
}
std::string InQuotes(const std::string& str)
{
  std::string res{"'"};
  bool in_quotes = true;
  std::for_each(str.cbegin(), str.cend(), [&res, &in_quotes](char sym)
  {
    if (sym == '\'')
    {
      if (in_quotes)
      {
        in_quotes = false;
        res += '\'';
      }
      res += '\\';
      res += sym;
    }
    else
    {
      if (!in_quotes)
      {
        in_quotes = true;
        res += '\'';
      }
      res += sym;
    }
  });
  if(in_quotes)
  {
    res += '\'';
  }
  return res;
}

DirContainer&& MoveContainer(DirContainer& content, CurDirT current_dir) noexcept
{
  for (DirContainer::iterator it = content.begin(); it != content.end(); ++it)
  {
    (*it) -> cur_dir_ = current_dir;
  }
  return std::move(content);
}

} // namespace func
} // namespace term_emul