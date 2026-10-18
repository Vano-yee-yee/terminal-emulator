#if !defined(TERMINAL_EMULATOR_ALIASES_H_)
#define TERMINAL_EMULATOR_ALIASES_H_

#include <memory> // shared_ptr
#include <vector>

namespace term_emul
{

class Entry;
class Directory;

using DirVal = std::shared_ptr<Entry>;
using DirConstVal = std::shared_ptr<const Entry>;
using DirContainer = std::vector<DirVal>;

using CurDirT = Directory*;
using ConstCurDirT = const Directory*;

enum class DisplaySort
{
  kNone = 0, kAsceding, kDesceding
};

} // namespace term_emul

#endif