
#ifndef __helper_h__
#define __helper_h__

#include <vector>
#include <string>
#include <sstream>

class StringHelpers {
   public:
    static void Split(const std::string &input, std::vector<std::string> &result) {
       result.clear();
       std::stringstream s_stream(input); //create string stream from the string
       while(s_stream.good()) {
          std::string substr;
          getline(s_stream, substr, ','); //get first string delimited by comma
          result.push_back(substr);
       }
    }
    private:
      StringHelpers() = delete;
};
#endif // __helper_h__