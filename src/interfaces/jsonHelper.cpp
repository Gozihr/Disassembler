#include "jsonHelper.h"

/*void Config::to_json(json &j, const Config &c) {
  if (!c.arch.empty() && !c.rawAsm.empty()) {
    j["arch"] = c.arch;
    j["rawAsm"] = c.rawAsm;
    // j = json{{"arch", c.arch}, {"rawAsm", c.rawAsm}, {"binaryPath", ""}};
  } else {
    assert(!c.binaryPath.empty());
    j["binaryPath"] = c.binaryPath;
  }
  if (!c.libpath.empty()) {
    j["libpath"] = c.libpath;
  }
}

void Config::from_json(const json &j, Config &c) {
  j.at("arch").get_to(c.arch);
  j.at("rawAsm").get_to(c.rawAsm);
  j.at("binaryPath").get_to(c.binaryPath);
  j.at("libpath").get_to(c.libpath);
}*/

/*void to_json(json &j, const ActionConfig &c) {
  j["action"] = c.action;
  j["configs"] = c.configs;
}

void from_json(const json &j, ActionConfig &c) {}*/