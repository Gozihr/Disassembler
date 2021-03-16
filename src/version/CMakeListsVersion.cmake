# this file is intended to be included by other project CMakeLists.txt files
# in order to make the following Gozihr version variables available
#   GOZIHR_MAJOR : Integer major number (e.g. 0, 1, 2)
#   GOZIHR_MINOR : Integer minor number (e.g. 0, 1, 2)
#   GOZIHR_PATCH : Integer patch number (e.g. 0, 1, 2)
#   GOZIHR_VERSION : Full GOZIHR verion string as MAJOR.MINOR.PATCH+BUILD (e.g. 1.0.5+255)

file (READ ${CMAKE_CURRENT_LIST_DIR}/Version.txt VERSION NEWLINE_CONSUME)
string (REPLACE "." ";" VERSION "${VERSION}")
string (REPLACE "\n" ";" VERSION "${VERSION}")
string (REPLACE "\r" ";" VERSION "${VERSION}")
list (GET VERSION 0 GOZIHR_MAJOR)
list (GET VERSION 1 GOZIHR_MINOR)
list (GET VERSION 2 GOZIHR_PATCH)

file (READ ${CMAKE_CURRENT_LIST_DIR}/AppName.txt GOZIHR_NAME)


set (GOZIHR_VERSION "${GOZIHR_MAJOR}.${GOZIHR_MINOR}.${GOZIHR_PATCH}")