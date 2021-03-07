#include <map>
#ifndef _WIN32
#include <editline/readline.h>
#endif

#include "dataPattern/singleton.h"
#include "interfaces/pch.h"
#include "repl.h"

namespace {
struct Singleton_Repl_Members {
  Singleton_Repl_Members() {}
  std::string consoleRead();
  std::string executeLine(const std::string &line);
  // These are place holde functions
  std::string name() { return "disasm"; }
  std::string version() { return "0.0.1"; }

private:
  std::map<std::string, void *> mapAssignments;
};
} // namespace

typedef SingletonBase<Singleton_Repl_Members> Singleton;

std::string Singleton_Repl_Members::consoleRead() {
#ifndef _WIN32
  char *buffer = readline(">>> ");

  // Add input history
  if (buffer[0] != '\0') {
    add_history(buffer);
  }

  std::string line(buffer);
  free(buffer);
#else
  string line = "";
  cout << ">>> ";
  std::getline(std::cin, line);
#endif
  return executeLine(line);
}

std::string Singleton_Repl_Members::executeLine(const std::string &line) {
  return "";
}

void Repl::run() {
  auto &instance = Singleton::get();
  std::cout << instance.name() << " " << instance.version() << std::endl;
  while (true) {
    instance.consoleRead();
  }
}