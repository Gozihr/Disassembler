// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <map>
#include <stdlib.h>

#ifndef _WIN32
#include "replCurses.h"
#include <editline/readline.h>
#include <term.h>
#include <unistd.h>
#endif

#include "dataPattern/singleton.h"
#include "diff/difftool.h"
#include "disassemble.h"
#include "interfaces/helpers.h"
#include "interfaces/pch.h"
#include "parser.h"
#include "repl.h"
#include "replTypes.h"
#include "runtime/runtime.h"
#include "version/version.h"

namespace {
struct Lookup {
  RuntimeTypes type;
  size_t index;
};

class ReplActions {
private:
  ReplActions() = delete;

public:
  static Lookup &getLookup(const std::string &assignment);
  static void print(const Lookup &lookup);
  static void print(const std::string &assignment);
  static void clear();
  static void diff(const std::string &id1, const std::string &id2);
  static void disassemble(const std::string &id);
  static void disassemble(const std::string &id,
                          std::vector<Instruction> &instructions);
  static void disassemble(const Binary &binary,
                          std::vector<Instruction> &instructions);
  static void quit();
  static void help();
  static bool assignment(const std::string &line);
  static Lookup callFunction(const std::string functionCall);
  static Lookup callFunction(const std::string &functionName,
                             const std::vector<std::string> &arguments);
  static void parseArguments(const std::string &functionCall,
                             std::vector<std::string> &argumentList);
  static size_t loadBinary(std::string path);
};

struct Singleton_Repl_Members {
  Singleton_Repl_Members() {}
  void consoleRead();
  void executeLine(const std::string &line);

private:
  std::map<std::string, Lookup> mapAssignments;
  std::vector<std::unique_ptr<Binary>> binaries;
  // Note for the file io feature we will want to turn this off.
  bool bIsInteractiveMode = true;
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
  std::string opcode = line.substr(0, 5);
  StringHelpers::trim(opcode);
  ReplActionType action = ReplLookupHelpers::ActionFind(opcode);
  if (action == ReplActionType::UNKNOWN) {
    opcode = line.substr(0, 10);
    action = ReplLookupHelpers::ActionFind(opcode);
  }
  switch (action) {
  case ReplActionType::PRINT:
    ReplActions::print(line.substr(6));
    break;
  case ReplActionType::LOADPLUGIN:
  case ReplActionType::LOADBINARY: {
    std::vector<std::string> argumentList;
    ReplActions::parseArguments(line, argumentList);
    ReplActions::callFunction(opcode, argumentList);
    break;
  }
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
    bool success = ReplActions::assignment(line);
    if (!success) {
      ReplActions::callFunction(line);
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
  ReplActions::print(getLookup(assignment));
}

Lookup &ReplActions::getLookup(const std::string &assignment) {
  auto &instance = Singleton::get();
  auto iter = instance.mapAssignments.find(assignment);
  if (iter != instance.mapAssignments.end()) {
    return iter->second;
  }
  std::stringstream sstr;
  sstr << "identifier " << assignment << " Not found!" << std::endl;
  throw std::runtime_error(sstr.str());
}

void ReplActions::print(const Lookup &lookup) {
  auto &instance = Singleton::get();
  switch (lookup.type) {
  case RuntimeTypes::BINARY:
    // std::cout << "called print on a binary with index: " << lookup.index <<
    // std::endl;
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
  StringHelpers::Split(line, assignmentExpr, '=', trim);
  if (assignmentExpr.size() == 2) {
    // std::cout << "assignmentExpr: " << assignmentExpr << std::endl;
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
  // std::cout << "functionCall: " << functionCall << std::endl;
  size_t openParenIndex = functionCall.find_first_of("(");
  std::string functionName = functionCall.substr(0, openParenIndex);
  // std::cout << "functionName: " << functionName << std::endl;

  std::vector<std::string> argumentList;
  ReplActions::parseArguments(functionCall, argumentList);
  return ReplActions::callFunction(functionName, argumentList);
}

void ReplActions::parseArguments(const std::string &functionCall,
                                 std::vector<std::string> &argumentList) {
  size_t openParenIndex = functionCall.find_last_of("(");
  size_t closeParenIndex = functionCall.find_first_of(")");
  std::string functionArguments = functionCall.substr(
      openParenIndex + 1, closeParenIndex - openParenIndex - 1);
  // std::cout << "functionArguments: " << functionArguments << std::endl;
  StringHelpers::stringFunc trim = StringHelpers::trim;
  StringHelpers::Split(functionArguments, argumentList, ',', trim);
  // std::cout << "argumentList: " << argumentList << std::endl;
}

Lookup ReplActions::callFunction(const std::string &functionName,
                                 const std::vector<std::string> &arguments) {

  Lookup lookup{RuntimeTypes::UNKNOWN, static_cast<size_t>(-1)};
  ReplActionType action = ReplLookupHelpers::ActionFind(functionName);
  switch (action) {
  case ReplActionType::PRINT:
    for (auto arg : arguments) {
      ReplActions::print(arg);
    }
    break;
  case ReplActionType::LOADBINARY:
    if (arguments.size() != 1) {
      throw std::runtime_error("loadBinary takes one argument.");
    }
    lookup.index = ReplActions::loadBinary(arguments[0]);
    lookup.type = RuntimeTypes::BINARY;
    break;
  case ReplActionType::LOADPLUGIN:
    std::cerr << "Error: " << functionName << " is not handled yet, standby"
              << std::endl;
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
  case ReplActionType::DISASM:
    if (arguments.size() != 1) {
      throw std::runtime_error("disasm takes one arguments");
    }
    ReplActions::disassemble(arguments[0]);
    break;
  case ReplActionType::DIFF:
    ReplActions::diff(arguments[0], arguments[1]);
    break;
  default:
    std::cerr << "Error: " << functionName
              << " is not a library defined function!" << std::endl;
  }
  return lookup;
}

void ReplActions::disassemble(const std::string &id) {
  std::vector<Instruction> instructions;
  disassemble(id, instructions);
  std::cout << instructions << std::endl;
}

void ReplActions::disassemble(const std::string &id,
                              std::vector<Instruction> &instructions) {
  auto &instance = Singleton::get();
  Lookup l = getLookup(id);
  if (l.type != RuntimeTypes::BINARY) {
    std::stringstream sstr;
    sstr << "identfier: " << id << " must be a binary.";
    throw std::runtime_error(sstr.str());
  }
  assert(l.index < instance.binaries.size());
  Binary *pBinary = instance.binaries[l.index].get();
  disassemble(*pBinary, instructions);
}

void ReplActions::disassemble(const Binary &binary,
                              std::vector<Instruction> &instructions) {
  Disassembler disasm(binary.Arch());
  disasm.setStartAddress(binary.getStartAddress());
  disasm.Decode(binary.Instructions().data(), binary.Instructions().size());
  disasm.moveInstructions(instructions);
}

void ReplActions::diff(const std::string &id1, const std::string &id2) {
  auto &instance = Singleton::get();
  std::vector<Instruction> inst1;
  std::vector<Instruction> inst2;
  disassemble(id1, inst1);
  disassemble(id2, inst2);
#ifndef _WIN32
  if (instance.bIsInteractiveMode) {
    std::stringstream sstr1;
    std::stringstream sstr2;
    sstr1 << inst1;
    sstr2 << inst2;
    curses::diffCurses(sstr1.str(), sstr2.str());
  }
#endif
  DiffOutput diffout = DiffTool::action(inst1, inst2);
  std::cout << diffout.first << "\n" << diffout.second;
}

size_t ReplActions::loadBinary(std::string path) {
  auto &instance = Singleton::get();
  instance.binaries.push_back(ASMParser::Parser(path));
  return instance.binaries.size() > 0 ? instance.binaries.size() - 1 : 0;
}

void Repl::run() {
  auto &instance = Singleton::get();
  Gozihr::printVersion();
  while (true) {
    try {
      instance.consoleRead();
    } catch (std::runtime_error &error) {
      std::cerr << error.what() << std::endl;
      std::cin.get();
    } catch (std::exception &error) {
      std::cerr << error.what() << std::endl;
      std::cin.get();
    }
  }
}