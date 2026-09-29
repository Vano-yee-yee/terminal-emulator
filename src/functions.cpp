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

} // namespace func
} // namespace term_emul