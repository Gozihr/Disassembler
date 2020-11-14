#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
if [ ! -e $SCRIPT_DIR/../packages/ ]; then
mkdir $SCRIPT_DIR/../packages/
fi
if [ ! -e $SCRIPT_DIR/../packages/xed_build ]; then
pushd $SCRIPT_DIR/../packages/
mkdir xed_build
pushd xed_build
git clone https://github.com/intelxed/xed.git xed
git clone https://github.com/intelxed/mbuild.git mbuild
mkdir build
pushd build
../xed/mfile.py --shared --limit-strings install
popd
popd
mkdir xed
cp -r xed_build/build/kits/xed-install-base-*/include xed/
cp -r xed_build/build/kits/xed-install-base-*/lib xed/
popd
fi