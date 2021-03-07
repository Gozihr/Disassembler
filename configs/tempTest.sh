#!/bin/bash

# Note until we have a test harness this will have to do.

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
XED_LIB_PATH="$(dirname $SCRIPT_DIR)/packages/xed/lib"
XED_TEST="$(dirname $SCRIPT_DIR)/build/plugins/xedPlugin/test/XED_TEST"

./build/src/cli/disasm -c configs/rawConfig.json
./build/src/cli/disasm -c configs/linuxBinaryConfig.json
./build/src/cli/disasm -c configs/winBinaryConfig.json
./build/src/cli/disasm -c configs/winGCCBinaryConfig.json
./build/src/cli/disasm -c configs/windiffConfig.json


if [ "$(uname)" == "Darwin" ]; then
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$XED_LIB_PATH
    # Note see if we can get hello.macos.out to crossbuild for linux/windows.
    ./build/src/cli/disasm -c configs/macBinaryConfig.json
    ./build/src/cli/disasm -c configs/macXedBinaryConfig.json
    ./build/src/cli/disasm -c configs/macXedLinuxBinaryConfig.json
    ./build/src/cli/disasm -c configs/macXedRawConfig.json
    ./build/src/cli/disasm -c configs/macDiffConfig.json
    ./build/src/cli/disasm -c configs/macXedDiffConfig.json
    ./build/src/cli/disasm -c configs/diffConfig.json

elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XED_LIB_PATH
     ./build/src/cli/disasm -c configs/linuxXedBinaryConfig.json
     ./build/src/cli/disasm -c configs/linuxXedRawConfig.json

elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] ||
     [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ] ||
     [ "$(expr substr $(uname -s) 1 9)"  == "CYGWIN_NT"  ]; then
     echo "Windows is not currently supported!"
fi