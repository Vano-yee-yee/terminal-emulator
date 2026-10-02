#if !defined(TERMINAL_EMULATOR_TERMINAL_H_)
#define TERMINAL_EMULATOR_TERMINAL_H_

#include <iostream>
#include <istream>
#include <ostream>

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
    std::ostream& out = std::cout, 
    std::istream& in = std::cin);
  Terminal(std::ostream& out, std::istream& in = std::cin);
  Terminal(std::istream& in);
  
 private:
  void help() noexcept;
 public:
  void run();
  
  Terminal& operator=(const Terminal&) = delete;
  Terminal& operator=(Terminal&&) = delete;
};

} // namespace term_emul

#endif