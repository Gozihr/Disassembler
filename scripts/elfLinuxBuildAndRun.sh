ASM_FILE=$1
ASM_OBJ_FILE="${ASM_FILE%.*}.o"
ASM_EXE="${ASM_FILE%.*}.out"
nasm -felf64 $ASM_FILE && ld $ASM_OBJ_FILE -o $ASM_EXE && ./$ASM_EXE