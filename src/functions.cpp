#include "functions.h"

#include <algorithm>
#include <sstream>
#include <string>
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
    std::none_of(current -> cbegin(), current -> cend(), 
      [&name](const Entry* e)
      {
        return e -> name() == name;
      });
}
bool isSingleline(const std::string& str)
{
  return str.size() > 0 && std::none_of(str.cbegin(), str.cend(), [](char sym)
  {
    return sym == '\n';
  });
}

std::vector<std::string> delim_path(const std::string& path)
{
  std::vector<std::string> res;
  std::istringstream ss(path);
  std::string str;
  while(std::getline(ss, str, '/'))
  {
    res.push_back(str);
  }
  return res;
}

} // namespace func
} // namespace term_emul