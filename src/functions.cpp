#include "functions.h"

#include <algorithm>
#include <string>

namespace term_emul
{
namespace func
{

bool isValidName(const std::string& name)
{
  return std::none_of(name.begin(), name.end(), [](char sym){ return sym == '/';})
    && name != "." && name != "..";
}

} // namespace func
} // namespace term_emul