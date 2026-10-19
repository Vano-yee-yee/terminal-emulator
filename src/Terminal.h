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
 public:
  using CommandLine = std::vector<std::string>;
  using CLIt = CommandLine::iterator;
  using CLConstIt = CommandLine::const_iterator;
  
 private:
  RootDirectory root_;
  CurDirT current_;
  
  mutable std::ostream out_;
  mutable std::istream in_;
  
 public:
  Terminal(RootDirectory&& root = RootDirectory{}, 
    const std::ostream& out = std::cout, 
    const std::istream& in = std::cin);
  Terminal(const std::ostream& out, const std::istream& in = std::cin);
  Terminal(const std::istream& in);
  
  Terminal(const Terminal&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(Terminal&&) = delete;
  
 private:
  bool ParseCommand(CommandLine& command) const;
  Entry* Get(const std::string& path);
  const Entry* Get(const std::string& path) const;
  
  void Help() const noexcept;
  void Ls(CLConstIt begin, CLConstIt end) const;
  void Cd(CLConstIt begin, CLConstIt end);
  
  void Cat(CLConstIt begin, CLConstIt end) const;
  void Edit(CLConstIt begin, CLConstIt end);
  
 public:
   void Run();
//  void Run() const;
};

} // namespace term_emul

#endif