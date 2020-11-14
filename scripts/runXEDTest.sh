SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
XED_LIB_PATH="$(dirname $SCRIPT_DIR)/packages/xed/lib"
XED_TEST="$(dirname $SCRIPT_DIR)/build/plugins/xedPlugin/test/XED_TEST"
if [ "$(uname)" == "Darwin" ]; then
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$XED_LIB_PATH
    $XED_TEST
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XED_LIB_PATH
    $XED_TEST
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] ||
     [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ] ||
     [ "$(expr substr $(uname -s) 1 9)"  == "CYGWIN_NT"  ]; then
     echo "Windows is not currently supported!"
fi