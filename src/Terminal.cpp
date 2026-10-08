#include "Terminal.h"

#include <algorithm> // for_each
#include <iostream> // cout
#include <istream>
#include <iterator> // istream_itearator
#include <ostream> // ostream endl
#include <sstream> // istringstream
#include <string> // string getline
#include <utility> // move
#include <vector>

#include "dir/RootDirectory.h"
#include "functions.h"

namespace term_emul
{

Terminal::Terminal(RootDirectory&& root, const std::ostream& out, 
  const std::istream& in)
: root_(std::move(root)), current_(root_), out_(out.rdbuf()), in_(in.rdbuf())
{}
Terminal::Terminal(const std::ostream& out, const std::istream& in)
: Terminal(RootDirectory(), out, in)
{}
Terminal::Terminal(const std::istream& in)
: Terminal(std::cout, in)
{}

void Terminal::run()
{
  for(std::string command; 
    out_ << current_.displayName() << " # ", std::getline(in_, command);
    )
  {
    std::istringstream command_stream(command);
    command_stream >> command;
    
    if(command == "exit")
    {
      break;
    }
    if(command == "help")
    {
      this -> help();
    }
    else if(command.size() > 0)
    {
      out_ << command << ": unknown command. Use help to show possible commands" 
        << std::endl;
    }
  }
}

void Terminal::help() noexcept
{
  out_ << "Terminal poor alpha\n"
    "\nhelp                                     Print avaible command info"
    "\nexit                                     Terminate command proccessor"
    "\nls [-a, --all] [path1] [path2]...        Show directory children names or filename"
    "\n                                         -a, --all  Show hidden entries"
    "\ncd [dir]                                 Change working directory. Default is '/'"
    "\ncat <file1> [file2]...                   Output file content"
    "\ntouch [-s, --single] <file1> [file2]...  Create file, if it is not exist"
    "\n                                         -s, --single  Create singleline file"
    "\nmkdir <dir1> [dir2]...                   Create directory, if it is not exist"
    "\nrm <path1> [path2]...                    Remove (hide) file or directory"
    "\nrestore <path1> [path2]...               Recover (unhide) file or directory"
    "\nmv <path> <path2>                        Move file or directory to other location <path2>"
    "\nedit <file> <str>                        Change file content to <str>\n"
    << std::endl;
}

} // namespace term_emul