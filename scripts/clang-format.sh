find src/ \( -name \*.h -o -name \*.cpp \) -exec clang-format -style=file -i {} \;
find plugins/ \( -name \*.h -o -name \*.cpp \) -exec clang-format -style=file -i {} \;