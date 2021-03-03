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
  // static void to_json(json &j, const Config &c);
  // static void from_json(const json &j, Config &c);
};

struct ActionConfig {
  std::string action;
  std::vector<Config> configs;
  // static void to_json(json &j, const ActionConfig &c);
  // static void from_json(const json &j, ActionConfig &c);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, arch, libpath, binaryPath, rawAsm);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActionConfig, action,configs);
}; // namespace jObjects

#endif // __json_helper_h__