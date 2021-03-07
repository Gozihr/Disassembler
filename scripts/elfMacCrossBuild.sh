SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
pushd $SCRIPT_DIR/../packages/

if [ ! -e $SCRIPT_DIR/../packages/binutils-2.35 ]; then
    wget https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz
    tar xzf binutils-2.35.tar.gz
fi

if [ ! -e $SCRIPT_DIR/../packages/binutils-2.35/build ]; then
    cd binutils-2.35
    mkdir build && cd build
    ../configure --prefix=${HOME}/.local/binutils --target=x86_64-unknown-linux-gnu
    make -j7
    make install
fi
popd

#ASM_FILE=$1
#ASM_OBJ_FILE="${ASM_FILE%.*}.o"
#ASM_EXE="${ASM_FILE%.*}.out"
#nasm -felf64 $ASM_FILE
#$SCRIPT_DIR/../packages/binutils-2.35/build/ld/ld-new $ASM_OBJ_FILE -o $ASM_EXE
