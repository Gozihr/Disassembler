#!/bin/bash
export CODECOV_TOKEN="d9c30fc8-86aa-42df-9194-25dfe3f9a408"
find src plugins \( -name \*.h -o -name \*.cpp \) -exec gcov -style=file -i build/{} \;
bash <(curl -s https://codecov.io/bash)