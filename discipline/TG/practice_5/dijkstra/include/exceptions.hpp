#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <stdexcept>
#include <string>
#include <sstream>

class Basic_error : public std::runtime_error
{
public:
  Basic_error(const std::string& arg, const char *file, int line)
    : std::runtime_error(arg)
  {
    std::ostringstream o;
    o << file << ":" << line << ": " << arg;
    msg = o.str();
  }

  ~Basic_error() throw() { }
 
  virtual const char* what() const throw()
  {
    return msg.c_str();
  }
protected:
  std::string msg;
};

class Index_error : public Basic_error
{
public:
  Index_error(const char *file, int line)
    : Basic_error("index out of range", file, line) {}
};

class Source_node_error : public Basic_error
{
public:
  Source_node_error(const char *file, int line)
    : Basic_error("source node does not exist", file, line) {}
};

class Destination_node_error : public Basic_error
{
public:
  Destination_node_error(const char *file, int line)
    : Basic_error("destination node does not exist", file, line) {}
};

#endif
