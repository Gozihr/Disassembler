ASM_FILE=$1
ASM_OBJ_FILE="${ASM_FILE%.*}.o"
ASM_EXE="${ASM_FILE%.*}.out"
nasm -fmacho64 $ASM_FILE && ld -macosx_version_min 10.13 -lSystem $ASM_OBJ_FILE -o $ASM_EXE && ./$ASM_EXE