#if !defined(TERMINAL_EMULATOR_TERMINAL_H_)
#define TERMINAL_EMULATOR_TERMINAL_H_

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "dir/Directory.h"
#include "dir/RootDirectory.h"
/*
#include "Entry.h"
#include "file/MultilineFile.h"
*/

namespace term_emul
{

class Terminal
{
  RootDirectory root_;
  Directory current_;
  
  std::istream in_;
  std::ostream out_;
 public:
  Terminal() = delete;
  Terminal(Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal(RootDirectory&& root, 
    const std::ostream& out = std::ostream(std::cout.rdbuf()),
    const std::istream& in = std::istream(std::cin.rdbuf()) );
  
  private:
  void help() noexcept;
  public:
  void run();
  
  Terminal& operator=(const Terminal&) = delete;
  Terminal& operator=(Terminal&&) = delete;
};

} // namespace term_emul

#endif