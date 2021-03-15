
/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __repl_types_h__
#define __repl_types_h__

#include <unordered_map>

enum class ReplActionType {
  PRINT,
  LOADPLUGIN,
  LOADBINARY,
  QUIT,
  HELP,
  CLEAR,
  DIFF,
  DISASM,
  UNKNOWN
};

static const std::unordered_map<std::string, ReplActionType> ReplActionTypeMap =
    {

        {"print", ReplActionType::PRINT},
        {"loadPlugin", ReplActionType::LOADPLUGIN},
        {"loadBinary", ReplActionType::LOADBINARY},
        {"help", ReplActionType::HELP},
        {"quit", ReplActionType::QUIT},
        {"diff", ReplActionType::DIFF},
        {"disasm", ReplActionType::DISASM},
        {"clear", ReplActionType::CLEAR}

};

static const std::unordered_map<std::string, std::string>
    ReplActionDescriptionMap = {

        {"print", "prints the variable."},
        {"loadPlugin", "loads a plugin."},
        {"loadBinary", "loads a binary."},
        {"help", "prints a list of actions."},
        {"quit", "quits the REPL."},
        {"disasm", "disassembles a binary."},
        {"diff", "diffs two binaries."},
        {"clear", "clears the screen."}

};

static const std::unordered_map<ReplActionType, std::string> ReplActionStrMap =
    {{ReplActionType::PRINT, "print"},
     {ReplActionType::LOADPLUGIN, "loadPlugin"},
     {ReplActionType::LOADBINARY, "loadBinary"},
     {ReplActionType::HELP, "help"},
     {ReplActionType::QUIT, "quit"},
     {ReplActionType::DIFF, "diff"},
     {ReplActionType::DISASM, "disasm"},
     {ReplActionType::CLEAR, "clear"},
     {ReplActionType::UNKNOWN, "unknown"}

};

typedef std::unordered_map<std::string, ReplActionType>::const_iterator
    Repl_Action_iterator;
typedef std::unordered_map<ReplActionType, std::string>::const_iterator
    Repl_Action_Str_iterator;

class ReplLookupHelpers {
  ReplLookupHelpers() = delete;

public:
  static ReplActionType ActionFind(std::string action) {
    Repl_Action_iterator actionFound = ReplActionTypeMap.find(action);
    if (actionFound == ReplActionTypeMap.end()) {
      return ReplActionType::UNKNOWN;
    }
    return actionFound->second;
  }
};

inline std::ostream &operator<<(std::ostream &out, const ReplActionType r) {
  out << ReplActionStrMap.at(r);
  return out;
}

#endif // __repl_types_h__
