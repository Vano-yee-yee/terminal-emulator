#if !defined(TERMINAL_EMULATOR_FUNCTIONS_H_)
#define TERMINAL_EMULATOR_FUNCTIONS_H_

#include <string>
#include <vector>

#include "aliases.h"

namespace term_emul
{
namespace func
{

bool IsValidName(const std::string& name);
bool IsSingleline(const std::string& str);

std::vector<std::string> DelimPath(const std::string& path);
std::string EscapeQuotes(const std::string& str);

DirContainer&& MoveContainer(DirContainer& content, CurDirT current_dir) noexcept;

} // namespace func
} // namespace term_emul

#endif