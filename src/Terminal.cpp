#include "Terminal.h"

#include <algorithm> // for_each
#include <iostream> // cout
#include <istream>
#include <ostream> // ostream endl
#include <string> // string getline
#include <typeinfo> // bad_cast
#include <utility> // move
#include <vector>

#include "dir/RootDirectory.h"
#include "Entry.h"
#include "functions.h"

namespace term_emul
{

Terminal::Terminal(RootDirectory&& root, const std::ostream& out, 
  const std::istream& in)
: root_(std::move(root)), current_(&root_), out_(out.rdbuf()), in_(in.rdbuf())
{}
Terminal::Terminal(const std::ostream& out, const std::istream& in)
: Terminal(RootDirectory{}, out, in)
{}
Terminal::Terminal(const std::istream& in)
: Terminal(std::cout, in)
{}

void Terminal::Run()
{
  for (CommandLine cl; 
    out_ << ' ' << current_ -> DisplayName() << " # ", ParseCommand(cl);
    cl.resize(0))
  {
    if (cl.size())
    {
      if (cl[0] == "exit")
      {
        break;
      }
      if (cl[0] == "help")
      {
        Help();
      }
      else if (cl[0] == "ls")
      {
        Ls(++cl.begin(), cl.cend());
      }
      else if (cl[0] == "cd")
      {
        Cd(++cl.begin(), cl.end());
      }
      else if (cl[0] == "cat")
      {
        Cat(++cl.begin(), cl.end());
      }
      else
      {
        out_ << cl[0] << ": unknown command. Use help to show possible commands" 
          << std::endl;
      }
    }
  }
}

void Terminal::Help() const noexcept
{
  out_ << "Terminal poor alpha\n"
    "\nhelp                               Print avaible command info"
    "\nexit                               Terminate command proccessor"
    "\nls -a -c|-d|-n [path1] [path2]...  Show directory children names or filename"
    "\n                                   -a, --all  Show hidden entries"
    "\n                                   -c, --asc  Change sort of names by asceding (default)"
    "\n                                   -d, --desc Change sort of names by desceding"
    "\n                                   -n, --none Do not sort"
    "\ncd [dir]                           Change working directory. Default is '/'"
    "\ncat <file1> [file2]...             Output file content"
    "\ntouch -s <file1> [file2]...        Create file, if it is not exist"
    "\n                                   -s, --single  Create singleline file"
    "\nmkdir <dir1> [dir2]...             Create directory, if it is not exist"
    "\nrm <path1> [path2]...              Remove (hide) file or directory"
    "\nrestore <path1> [path2]...         Recover (unhide) file or directory"
    "\nmv <path> <path2>                  Move file or directory to other location <path2>"
    "\nedit <file> <str>                  Change file content to <str>"
    << std::endl;
}

bool Terminal::ParseCommand(CommandLine& command) const
{
  std::string el_buf;
  enum class State{kNone = 0, kQuot, kDquot, kEsc} st = State::kNone;
  bool completed = false;
  for (std::string line; !completed && std::getline(in_, line);)
  {
    std::for_each(line.cbegin(), line.cend(), [&st, &el_buf, &command](char sym)
    {
      switch (sym)
      {
        case '\'':
          switch (st)
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
          switch (st)
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
          switch (st)
          {
            case State::kNone:
              if (el_buf.size())
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
          switch (st)
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
          switch (st)
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
    
    switch (st)
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
    if (!completed)
    {
      out_ << "> ";
    }
  }
  if (el_buf.size())
  {
    command.push_back(el_buf);
  }
  return static_cast<bool>(in_);
}

void Terminal::Ls(CLConstIt begin, CLConstIt end) const
{
  bool hidden = false;
  DisplaySort sort = DisplaySort::kAsceding;
  for (; begin != end && begin -> size() && (*begin)[0] == '-'; ++begin)
  {
    auto&& el = *begin;
    if (el == "-a" || el == "--all")
    {
      hidden = true;
    }
    else if (el == "-c" || el == "--asc")
    {
      sort = DisplaySort::kAsceding;
    }
    else if (el == "-d" || el == "--desc")
    {
      sort = DisplaySort::kDesceding;
    }
    else if (el == "-n" || el == "--none")
    {
      sort = DisplaySort::kNone;
    }
    else
    {
      out_ << "ls: unknown parameter " << el << std::endl;
      return;
    }
  }
  
  switch (end - begin)
  {
    case 0:
      out_ << current_ -> Display(hidden, sort) << std::endl;
      break;
    case 1:
      {
        const Entry* elem = Get(*begin);
        if (elem == nullptr)
        {
          out_ << "ls: " << *begin << ": is not a file or directory" << std::endl;
        }
        else
        {
          out_ << elem -> Display(hidden, sort) << std::endl;
        }
      }
      break;
    default:
      std::for_each(begin, end, [this, &hidden, &sort](const std::string& path)
      {
        const Entry* elem = Get(path);
        if (elem == nullptr)
        {
          out_ << "ls: " << path << ": is not a file or directory\n";
        }
        else
        {
          out_ << elem -> DisplayFullName() << ":\n" << 
            elem -> Display(hidden, sort) << "\n\n";
        }
      });
  }
}

Entry* Terminal::Get(const std::string& path)
{ 
  Entry* res = nullptr;
  std::vector<std::string> dpath = func::DelimPath(path);
  auto&& it = dpath.begin();
  if (dpath.size() && dpath[0] == "/")
  {
    res = static_cast<Entry*>(&root_);
    ++it;
  }
  else
  {
    res = static_cast<Entry*>(current_);
  }
  
  for (; res != nullptr && it != dpath.cend(); ++it)
  {
    if (*it == "..")
    {
      if (res -> back() != nullptr)
      {
        res = res -> back();
      }
    }
    else if (*it != ".")
    {
      res = (res -> next(*it)).get();
    }
  }
  return res;
}
const Entry* Terminal::Get(const std::string& path) const
{
  return const_cast<Terminal*>(this) -> Get(path);
}

void Terminal::Cd(CLConstIt begin, CLConstIt end)
{
  switch (end - begin)
  {
    case 0:
      current_ = CurDirT{&root_};
      break;
    default:
      Entry* e = Get(*begin);
      if (e == nullptr)
      {
        out_ << "cd: " << *begin << ": is not a file or direcory" << std::endl;
        return;
      }
      try
      {
        current_ = &dynamic_cast<Directory&>(*e);
      }
      catch (std::bad_cast)
      {
        out_ << "cd: " << *begin << ": is not a direcory" << std::endl;
      }
  }
}
void Terminal::Cat(CLConstIt begin, CLConstIt end) const
{
  std::for_each(begin, end, [this](const std::string& path)
  {
    const Entry* e = Get(path);
    if(e == nullptr)
    {
      out_ << "cat: " << path << ": is not a file or directory\n";
    }
    else
    {
      out_ << e -> content();
    }
  });
}

} // namespace term_emul