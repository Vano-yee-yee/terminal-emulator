#if !defined(TERMINAL_EMULATOR_TERMINAL_H_)
#define TERMINAL_EMULATOR_TERMINAL_H_

#include <iostream> // cout cin
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "dir/Directory.h"
#include "dir/RootDirectory.h"

namespace term_emul
{

class Terminal
{
  RootDirectory root_;
  Directory& current_;
  
  std::istream in_;
  std::ostream out_;
  
 public:
  Terminal(Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal(RootDirectory&& root = RootDirectory(), 
    const std::ostream& out = std::cout, 
    const std::istream& in = std::cin);
  Terminal(const std::ostream& out, const std::istream& in = std::cin);
  Terminal(const std::istream& in);
  
 private:
  void help() noexcept;
  
  bool parseCommand(std::vector<std::string>& command);
 public:
  void run();
  
  Terminal& operator=(const Terminal&) = delete;
  Terminal& operator=(Terminal&&) = delete;
};

} // namespace term_emul

#endif