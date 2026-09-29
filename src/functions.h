#if !defined(TERMINAL_EMULATOR_FUNCTIONS_H_)
#define TERMINAL_EMULATOR_FUNCTIONS_H_

#include <string>

namespace term_emul
{
namespace func
{

bool isValidName(const std::string& name);
bool isSingleLine(const std::string& str);

} // namespace func
} // namespace term_emul

#endif