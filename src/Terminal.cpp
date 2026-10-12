#include "Terminal.h"

#include <algorithm> // for_each
#include <iostream> // cout
#include <istream>
#include <ostream> // ostream endl
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

bool Terminal::parseCommand(std::vector<std::string>& command)
{
  std::string el_buf;
  enum class State{kNone = 0, kQuot, kDquot, kEsc} st = State::kNone;
  bool completed = false;
  for(std::string line; !completed && std::getline(in_, line);)
  {
    std::for_each(line.cbegin(), line.cend(), [&st, &el_buf, &command](char sym)
    {
      switch(sym)
      {
        case '\'':
          switch(st)
          {
            case State::kQuot:
              st = State::kNone;
              break;
            case State::kNone:
              st = State::kQuot;
              break;
            case State::kDquot:
              el_buf += sym;
              break;
            case State::kEsc:
              st = State::kNone;
              el_buf += sym;
          }
          break;
        case '"':
          switch(st)
          {
            case State::kDquot:
              st = State::kNone;
              break;
            case State::kNone:
              st = State::kDquot;
              break;
            case State::kQuot:
              el_buf += sym;
              break;
            case State::kEsc:
              st = State::kNone;
              el_buf += sym;
          }
          break;
        
        case ' ':
        case '\t':
        case '\v':
        case '\f':
          switch(st)
          {
            case State::kNone:
              if(el_buf.size() > 0)
              {
                command.push_back(el_buf);
                el_buf.resize(0);
              }
              break;
            case State::kQuot:
            case State::kDquot:
              el_buf += sym;
              break;
            case State::kEsc:
              st = State::kNone;
              el_buf += sym;
          }
          break;
        
        case '\\':
          switch(st)
          {
            case State::kNone:
              st = State::kEsc;
              break;
            case State::kQuot:
            case State::kDquot:
              el_buf += sym;
              break;
            case State::kEsc:
              st = State::kNone;
              el_buf += sym;
          }
          break;
        
        default:
          switch(st)
          {
            case State::kNone:
            case State::kQuot:
            case State::kDquot:
              el_buf += sym;
              break;
            case State::kEsc:
              st = State::kNone;
              el_buf += sym;
          }
      }
    });
    
    switch(st)
    {
      case State::kNone:
        completed = true;
        break;
      case State::kQuot:
      case State::kDquot:
        el_buf += '\n';
        break;
      case State::kEsc:
        st = State::kNone;
        el_buf += '\n';
    }
    if(!completed)
    {
      out_ << "> ";
    }
  }
  if(el_buf.size() > 0)
  {
    command.push_back(el_buf);
  }
  return static_cast<bool>(in_);
}

void Terminal::run()
{
  for(std::vector<std::string> comm; 
    out_ << current_.displayName() << " # ", this -> parseCommand(comm);
    comm.resize(0))
  {
    if(comm.size() > 0)
    {
      if(comm[0] == "exit")
      {
        break;
      }
      if(comm[0] == "help")
      {
        this -> help();
      }
      else
      {
        out_ << comm[0] << ": unknown command. Use help to show possible commands" 
          << std::endl;
      }
    }
  }
}

void Terminal::help() noexcept
{
  out_ << "Terminal poor alpha\n"
    "\nhelp                                Print avaible command info"
    "\nexit                                Terminate command proccessor"
    "\nls [-a] [-c|-d] [path1] [path2]...  Show directory children names or filename"
    "\n                                    -a, --all  Show hidden entries"
    "\n                                    -c, --asc  Change sort of names by asceding (default)"
    "\n                                    -d, --desc Change sort of names by desceding"
    "\n                                    -n, --none Do not sort"
    "\ncd [dir]                            Change working directory. Default is '/'"
    "\ncat <file1> [file2]...              Output file content"
    "\ntouch [-s] <file1> [file2]...       Create file, if it is not exist"
    "\n                                    -s, --single  Create singleline file"
    "\nmkdir <dir1> [dir2]...              Create directory, if it is not exist"
    "\nrm <path1> [path2]...               Remove (hide) file or directory"
    "\nrestore <path1> [path2]...          Recover (unhide) file or directory"
    "\nmv <path> <path2>                   Move file or directory to other location <path2>"
    "\nedit <file> <str>                   Change file content to <str>\n"
    << std::endl;
}

} // namespace term_emul