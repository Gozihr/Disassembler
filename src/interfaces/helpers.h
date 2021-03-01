
#ifndef __helper_h__
#define __helper_h__

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

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

private:
  StringHelpers() = delete;
};
#endif // __helper_h__