/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __json_helper_h__
#define __json_helper_h__

#include "interfaces/pch.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonHelper {
private:
  JsonHelper() = delete;

public:
  template <typename T> static T readJsonToObj(std::string &filepath) {
    std::ifstream file(filepath);
    json j;
    file >> j;
    return j.get<T>();
  }
};

namespace jObjects {
struct Config {
  std::string arch;
  std::string libpath;
  std::string binaryPath;
  std::string rawAsm;
};

struct ActionConfig {
  std::string action;
  std::vector<Config> configs;
};

inline void to_json(nlohmann::json &j, const Config &c) {
  if (!c.arch.empty() && !c.rawAsm.empty()) {
    j["arch"] = c.arch;
    j["rawAsm"] = c.rawAsm;
  } else {
    assert(!c.binaryPath.empty());
    j["binaryPath"] = c.binaryPath;
  }
  if (!c.libpath.empty()) {
    j["libpath"] = c.libpath;
  }
}

inline void from_json(const nlohmann::json &j, Config &c) {
  if (j.contains("arch")) {
    j.at("arch").get_to(c.arch);
  }
  if (j.contains("rawAsm")) {
    j.at("rawAsm").get_to(c.rawAsm);
  }
  if (j.contains("binaryPath")) {
    j.at("binaryPath").get_to(c.binaryPath);
  }
  if (j.contains("libpath")) {
    j.at("libpath").get_to(c.libpath);
  }
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActionConfig, action, configs);
}; // namespace jObjects

#endif // __json_helper_h__
