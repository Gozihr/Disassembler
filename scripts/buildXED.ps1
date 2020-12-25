# Setup the Packages Dir (if it does not exist)
$PACKAGE_DIR = "$PSScriptRoot\..\packages"
if (!(Test-Path $PACKAGE_DIR)) {
    new-item -Path $PACKAGE_DIR -ItemType directory
}
$PACKAGE_DIR = join-path $PSScriptRoot "..\packages" -Resolve

$XED_BUILD ="$PACKAGE_DIR/xed_build"
if (!(Test-Path $XED_BUILD)) {
    new-item -Path $XED_BUILD -ItemType directory
    pushd $XED_BUILD
    git clone https://github.com/intelxed/xed.git xed
    git clone https://github.com/intelxed/mbuild.git mbuild
    mkdir build
    pushd build
    #Invoke-Expression "../xed/mfile.py --shared --limit-strings install" | Out-Null
    $proc = Start-Process -Wait -FilePath "../xed/mfile.py" -ArgumentList "--shared --limit-strings install"
    popd
    popd
}
$XED_Release ="$PACKAGE_DIR/xed"
if (!(Test-Path $XED_Release)) {
    new-item -Path $XED_Release -ItemType directory
    $XED_Install="build\kits\xed-install-base-*"
    $XED_Include="$XED_BUILD\$XED_Install\include"
    Copy-Item  -Force -Recurse  $XED_Include -Destination $XED_Release
    $XED_Lib="$XED_BUILD\$XED_Install\lib"
    Copy-Item  -Force -Recurse  $XED_Lib -Destination $XED_Release
}
