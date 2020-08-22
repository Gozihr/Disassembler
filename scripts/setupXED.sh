arch=$(uname -m)
TARGET_ARCH=$1
if [ "$TARGET_ARCH" != "ia32" ] && [ "$TARGET_ARCH" != "intel64" ];
then
    if [ $arch = "i686" ]
    then
      TARGET_ARCH="ia32"
    else
            if [ $arch = "x86_64" ]
            then
                    TARGET_ARCH="intel64"
            fi
    fi
fi
XED=xed-$TARGET_ARCH
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ ! -e $SCRIPT_DIR/../packages/xed ]; then
  . $SCRIPT_DIR/fetchpintool.sh

  echo === MOVING XED ===
  mv $PIN/extras/$XED/ $SCRIPT_DIR/../packages/xed
  rm -rf $PIN
  rm -r $PIN_ARCHIVE
fi
echo === DONE ===