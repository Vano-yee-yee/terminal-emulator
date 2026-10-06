#include "Terminal.h"

#include <iostream> // cout
#include <istream>
#include <ostream>
#include <sstream> // istringstream
#include <string> // string getline
#include <utility> // move

#include "dir/RootDirectory.h"

namespace term_emul
{

Terminal::Terminal(RootDirectory&& root, const std::ostream& out, 
  const std::istream& in)
: root_(std::move(root)), current_(root), out_(out.rdbuf()), in_(in.rdbuf())
{}
Terminal::Terminal(const std::ostream& out, const std::istream& in)
: Terminal(RootDirectory(), out, in)
{}
Terminal::Terminal(const std::istream& in)
: Terminal(std::cout, in)
{}

void Terminal::run()
{
  std::string str;
  while(out_ << current_.displayName() << " # ", std::getline(in_, str))
  {
    std::istringstream sstr(str);
    sstr >> str;
    if(str == "exit")
    {
      break;
    }
    if(str == "help")
    {
      this -> help();
    }
    else if(str == "ls")
    {
      // maybe use std::for_each with std::istream_iterator
      while(sstr >> str)
      {
        
      }
    }
/*    else if(str == "cd")
    {
      sstr >> str;
      this -> cd(str);
    }*/
    else if(str.size() > 0)
    {
      out_ << str << ": unknown command. Use help for possible commands" 
        << std::endl;
    }
  }
}

void Terminal::help() noexcept
{
  out_ << "Terminal poor alpha\n"
      "\nhelp                         Print avaible command info"
      "\nexit                         Terminate command proccessor"
      "\nls <path>                    Show information about files"
      "\ncd <dir>                     Change working directory"
      "\ncat <file>                   Show file content"
      "\ntouch <file> [-s, --single]  Create file, if it is not exist"
      "\nmkdir <dir>                  Create directory, if it is not exist"
      "\nrm <path>                    Remove(hide) file or directory"
      "\nrestore <path>               Recover file or directory"
      "\nmv <path> <path2>            Move file or directory to other"
        " location <path2>"
      "\nedit <file> <str>            Change content of file to <str>\n"
    << std::endl;
}

} // namespace term_emul