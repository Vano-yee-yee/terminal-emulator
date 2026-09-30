#include "functions.h"

#include <algorithm>
#include <string>

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
  return str.size() > 0 && std::none_of(str.cbegin(), str.cend(), [](char sym)
  {
    return sym == '\n';
  });
}

} // namespace func
} // namespace term_emul