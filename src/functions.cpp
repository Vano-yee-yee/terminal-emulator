#include "functions.h"

#include <algorithm> // none_of find_if for_each
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
bool isSingleline(const std::string& str)
{
  return std::find_if(str.cbegin(), str.cend(), [](char sym)
  {
    return sym == '\n';
  })
  == str.cend();
}
std::vector<std::string> delimPath(const std::string& path)
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
std::string escapeQuotes(const std::string& str)
{
  std::string res;
  bool in_quotes = true;
  std::for_each(str.cbegin(), str.cend(), [&res, &in_quotes](char sym)
  {
    if(sym == '\'')
    {
      if(in_quotes)
      {
        in_quotes = false;
        res += '\'';
      }
      res += '\\';
      res += sym;
    }
    else
    {
      if(!in_quotes)
      {
        in_quotes = true;
        res += '\'';
      }
      res += sym;
    }
  });
  return res;
}

} // namespace func
} // namespace term_emul