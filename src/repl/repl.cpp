#include <map>
#include <stdlib.h>

#ifndef _WIN32
#include <editline/readline.h>
#include <term.h>
#include <unistd.h>
#endif

#include "dataPattern/singleton.h"
#include "interfaces/helpers.h"
#include "interfaces/pch.h"
#include "parser.h"
#include "repl.h"
#include "replTypes.h"
#include "runtime/runtime.h"

namespace {
struct Lookup {
  RuntimeTypes type;
  size_t index;
};

struct ReplActions {
private:
  ReplActions() = delete;

public:
  static void print(const Lookup &lookup);
  static void print(const std::string &assignment);
  static void clear();
  static void quit();
  static void help();
  static bool assignment(const std::string &line);
  static Lookup callFunction(const std::string functionCall);
  static Lookup callFunction(const std::string &functionName,
                             const std::vector<std::string> &arguments);
  static size_t loadBinary(std::string path);
};

struct Singleton_Repl_Members {
  Singleton_Repl_Members() {}
  void consoleRead();
  void executeLine(const std::string &line);
  // These are place holder functions
  std::string name() { return "disasm"; }
  std::string version() { return "0.0.1"; }

private:
  std::map<std::string, Lookup> mapAssignments;
  std::vector<std::unique_ptr<Binary>> binaries;
  friend class ReplActions;
};
} // namespace

typedef SingletonBase<Singleton_Repl_Members> Singleton;

void Singleton_Repl_Members::consoleRead() {
#ifndef _WIN32
  char *buffer = readline(">>> ");

  // Add input history
  if (buffer[0] != '\0') {
    add_history(buffer);
  }

  std::string line(buffer);
  free(buffer);
#else
  std::string line = "";
  std::cout << ">>> ";
  std::getline(std::cin, line);
#endif
  executeLine(line);
}

// TODO We will need to build an ast to do this the right way.
// For now lets get something working.
void Singleton_Repl_Members::executeLine(const std::string &line) {
  auto &instance = Singleton::get();
  std::string opcode = line.substr(0, 5);
  StringHelpers::trim(opcode);
  ReplActionType action = ReplLookupHelpers::ActionFind(opcode);
  if(action == ReplActionType::UNKNOWN) {
    opcode = line.substr(0, 10);
    action = ReplLookupHelpers::ActionFind(opcode);
  }
  switch (action) {
  case ReplActionType::PRINT:
    ReplActions::print(line.substr(6));
    break;
  case ReplActionType::LOADPLUGIN:
    std::cerr << "Non-assignment "<< ReplActionType::LOADPLUGIN << " not handled yet, standby." << std::endl;
    break;
  case ReplActionType::LOADBINARY:
    std::cerr << "Non-assignment "<< ReplActionType::LOADBINARY << " not handled yet, standby." << std::endl;
    break;
  case ReplActionType::QUIT:
    ReplActions::quit();
    break;
  case ReplActionType::HELP:
    ReplActions::help();
    break;
  case ReplActionType::CLEAR:
    ReplActions::clear();
    break;
  default:
    if (!ReplActions::assignment(line)) {
      std::cerr << "Not handled yet, standby" << std::endl;
    }
  }
}

#ifdef _WIN32
void ReplActions::clear() { std::cout << std::string(50, '\n'); }
#else
void ReplActions::clear() {
  if (!cur_term) {
    int result;
    setupterm(NULL, STDOUT_FILENO, &result);
    if (result <= 0)
      return;
  }
  putp(tigetstr("clear"));
}
#endif

void ReplActions::help() {
  std::cout << "  action  | description" << std::endl;
  std::cout << "-----------------------" << std::endl;
  for (auto action : ReplActionDescriptionMap) {
    std::cout << std::left << std::setw(12) << action.first << action.second
              << std::endl;
  }
}

void ReplActions::quit() { exit(EXIT_SUCCESS); }

void ReplActions::print(const std::string &assignment) {
  auto &instance = Singleton::get();
  auto iter = instance.mapAssignments.find(assignment);
  if (iter != instance.mapAssignments.end()) {
      ReplActions::print(iter->second);
  } else {
    std::cerr << "identifier " << assignment << " Not found!" << std::endl;
  }
}

void ReplActions::print(const Lookup &lookup) {
  std::cout << "called print" << std::endl;
  auto &instance = Singleton::get();
  switch (lookup.type) {
  case RuntimeTypes::BINARY:
    std::cout << "called print on a binary with index: " << lookup.index << std::endl;
    assert(lookup.index < instance.binaries.size());
    std::cout << *(instance.binaries[lookup.index].get()) << std::endl;
    break;
  default:
    throw std::runtime_error("Only Binary types are supported for now");
  }
}

// TODO rewrite this as an AST
bool ReplActions::assignment(const std::string &line) {

  std::vector<std::string> assignmentExpr;
  StringHelpers::stringFunc trim = StringHelpers::trim;
  bool success = StringHelpers::Split(line, assignmentExpr, '=', trim);
  std::cout << "assignmentExpr: " << assignmentExpr << std::endl;
  if (success) {
    assert(assignmentExpr.size() == 2);
    std::string assignmentIdentifier = assignmentExpr[0];
    Lookup lookup = ReplActions::callFunction(assignmentExpr[1]);
    if (lookup.type != RuntimeTypes::UNKNOWN &&
        lookup.index != static_cast<size_t>(-1)) {
      auto &instance = Singleton::get();
      instance.mapAssignments[assignmentIdentifier] = lookup;
      return true;
    }
  }
  return false;
}

Lookup ReplActions::callFunction(const std::string functionCall) {
  std::cout << "functionCall: " << functionCall << std::endl;
  size_t openParenIndex = functionCall.find_first_of("(");
  std::string functionName = functionCall.substr(0, openParenIndex);
  std::cout << "functionName: " << functionName << std::endl;
  openParenIndex = functionCall.find_last_of("(");
  size_t closeParenIndex = functionCall.find_first_of(")");
  std::string functionArguments =
      functionCall.substr(openParenIndex+1, closeParenIndex - openParenIndex - 1);
  std::cout << "functionArguments: " << functionArguments << std::endl;
  std::vector<std::string> argumentList;
  StringHelpers::stringFunc trim = StringHelpers::trim;
  bool success =
      StringHelpers::Split(functionArguments, argumentList, ',', trim);
  if (success) {
    std::cout << "argumentList: " << argumentList << std::endl;
    return ReplActions::callFunction(functionName, argumentList);
  }
  Lookup lookup{RuntimeTypes::UNKNOWN, static_cast<size_t>(-1)};
  return lookup;
}

Lookup ReplActions::callFunction(const std::string &functionName,
                                 const std::vector<std::string> &arguments) {

  Lookup lookup{RuntimeTypes::UNKNOWN, static_cast<size_t>(-1)};
  ReplActionType action = ReplLookupHelpers::ActionFind(functionName);
  switch (action) {
  case ReplActionType::LOADBINARY:
    assert(arguments.size() == 1);
    lookup.index = ReplActions::loadBinary(arguments[0]);
    lookup.type = RuntimeTypes::BINARY;
    break;
  case ReplActionType::LOADPLUGIN:
    std::cerr << "Error: " << functionName << " is not handled yet, standby"
              << std::endl;
    break;
  default:
    std::cerr << "Error: " << functionName
              << " is not a library defined function!" << std::endl;
  }
  return lookup;
}

size_t ReplActions::loadBinary(std::string path) {
  auto &instance = Singleton::get();
  instance.binaries.push_back(ASMParser::Parser(path));
  return instance.binaries.size() > 0 ? instance.binaries.size() - 1 : 0;
}

void Repl::run() {
  auto &instance = Singleton::get();
  std::cout << instance.name() << " " << instance.version() << std::endl;
  while (true) {
    instance.consoleRead();
  }
}