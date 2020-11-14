#!/bin/sh
# Download PIN & set it up.
PIN_VERSION="3.16-98275"
PIN_GITHASH="ge0db48c31"
PIN=pin-$PIN_VERSION-$PIN_GITHASH
IS_WIN=false
if [ "$(uname)" == "Darwin" ]; then
   PIN=$PIN-clang-mac
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    PIN=$PIN-gcc-linux
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] ||
     [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ] ||
     [ "$(expr substr $(uname -s) 1 9)"  == "CYGWIN_NT"  ]; then
    PIN=$PIN-msvc-windows
    IS_WIN=true
fi

PIN_ARCHIVE=$PIN.tar.gz
if [ "$IS_WIN" = true ] ; then
    PIN_ARCHIVE=$PIN.zip
fi
PIN_URL=https://software.intel.com/sites/landingpage/pintool/downloads/$PIN_ARCHIVE

UNPACK="tar -xzf"

# Only download it if we don't already have it.
if [ ! -e $PIN_ARCHIVE ]; then
  echo === DOWNLOADING ARCHIVE ===
  wget $PIN_URL --no-check-certificate
fi

echo === UNPACKING PIN ARCHIVE ===
$UNPACK $PIN_ARCHIVE
echo === DONE ===