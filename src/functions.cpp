#include "functions.h"

#include <algorithm> // none_of find_if
#include <sstream> // istringstream
#include <string> // string getline
#include <vector>

#include "dir/Directory.h"
#include "Entry.h"

namespace term_emul
{
namespace func
{

bool isValidName(const std::string& name)
{
  return name.size() > 0 && name != "." && name != ".." && 
    std::none_of(name.cbegin(), name.cend(), [](char sym)
    {
      return sym == '/';
    });
}
bool isUniqueName(const Directory* current, const std::string& name)
{
  return current == nullptr || current != nullptr && 
    std::none_of(current -> cbegin(), current -> cend(), [&name](const Entry* e)
    {
      return e -> name() == name;
    });
}
bool isSingleline(const std::string& str)
{
  return std::find_if(str.cbegin(), str.cend(), [](char sym)
  {
    return sym == '\n';
  })
  == str.cend();
}

std::vector<std::string> delim_path(const std::string& path)
{
  std::vector<std::string> res;
  if(path.size() > 0 && path[0] == '/')
  {
    res.push_back("/");
  }
  
  std::istringstream path_stream(path);
  for(std::string path_elem; std::getline(path_stream, path_elem, '/');)
  {
    if(path_elem != "")
    {
      res.push_back(path_elem);
    }
  }
  return res;
}

} // namespace func
} // namespace term_emul