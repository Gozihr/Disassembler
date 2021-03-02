/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */


#ifndef __helper_h__
#define __helper_h__

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include "pch.h"

class StringHelpers {
public:
  typedef std::function<void(std::string &s)> stringFunc;
  static void Split(const std::string &input, std::vector<std::string> &result,
                    std::function<void(std::string &s)> fn = doNothing) {
    result.clear();
    std::stringstream s_stream(input); // create string stream from the string
    while (s_stream.good()) {
      std::string substr;
      getline(s_stream, substr, ','); // get first string delimited by comma
      fn(substr);
      result.push_back(substr);
    }
  }
  static inline void doNothing(std::string &) {}

  // trim from start (in place)
  static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
              return !std::isspace(ch);
            }));
  }

  // trim from end (in place)
  static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }

  // trim from both ends (in place)
  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  static std::vector<unsigned char> HexToBytes(const std::string &hex) {
    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
      std::string byteStr = hex.substr(i, 2);
      unsigned char byte =
          static_cast<unsigned char>(strtol(byteStr.c_str(), nullptr, 16));
      bytes.push_back(byte);
    }

    return bytes;
  }

  static std::vector<unsigned char> HexToBytesFormat(const std::string &hex) {
    std::string hexStr(hex);
    hexStr.erase(std::remove(hexStr.begin(), hexStr.end(), ' '), hexStr.end());
    if (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) {
      hexStr = hexStr.substr(2, hexStr.size() - 2);
    }
    return HexToBytes(hexStr);
  }

private:
  StringHelpers() = delete;
};
#endif // __helper_h__