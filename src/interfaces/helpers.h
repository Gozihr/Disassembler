
#ifndef __helper_h__
#define __helper_h__

#include <vector>
#include <string>
#include<sstream>

namespace Helpers {
    std::vector<std::string> Split(std::string input) {
       std::vector<std::string> result;
       std::stringstream s_stream(input); //create string stream from the string
       while(s_stream.good()) {
          std::string substr;
          getline(s_stream, substr, ','); //get first string delimited by comma
          result.push_back(substr);
       }
       return result;
    }
}
#endif // __helper_h__