#if !defined(TERMINAL_EMULATOR_TERMINAL_H_)
#define TERMINAL_EMULATOR_TERMINAL_H_

#include <iostream> // cout cin
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "dir/RootDirectory.h"
#include "Entry.h"

namespace term_emul
{

class Terminal
{
  RootDirectory root_;
  CurDirT current_;
  
  mutable std::istream in_;
  mutable std::ostream out_;
  
 public:
  Terminal(RootDirectory&& root = RootDirectory{}, 
    const std::ostream& out = std::cout, 
    const std::istream& in = std::cin);
  Terminal(const std::ostream& out, const std::istream& in = std::cin);
  Terminal(const std::istream& in);
  
  Terminal(Terminal&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(Terminal&&) = delete;
  
 private:
  bool ParseCommand(std::vector<std::string>& command) const;
  Entry* Get(const std::string& path);
  const Entry* Get(const std::string& path) const;
  
  void Help() const noexcept;
  void Ls(std::vector<std::string>::const_iterator begin, 
    std::vector<std::string>::const_iterator end) const;
  
 public:
  void Run();
};

} // namespace term_emul

#endif