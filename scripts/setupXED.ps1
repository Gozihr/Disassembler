# Setup the Packages Dir (if it does not exist)
$PACKAGE_DIR = "$PSScriptRoot\..\packages"
if (!(Test-Path $PACKAGE_DIR)) {
    new-item -Path $PACKAGE_DIR -ItemType directory
}
$PACKAGE_DIR = join-path $PSScriptRoot "..\packages" -Resolve
Write-Host "PACKAGE_DIR is $PACKAGE_DIR"

# Fetch and decompress pintool
$PIN_VERSION="3.16-98275"
$PIN_GITHASH="ge0db48c31"
$PIN_DIRNAME="pin-$PIN_VERSION-$PIN_GITHASH-msvc-windows"
$PIN_ARCHIVE="$PIN_DIRNAME.zip"
$PIN_URL="https://software.intel.com/sites/landingpage/pintool/downloads/$PIN_ARCHIVE"
$PINTOOL_ZIP="$PACKAGE_DIR\$PIN_ARCHIVE"
$PIN_EXTRACT_DIR="$PACKAGE_DIR\pin"
$PINFULLDIR="$PIN_EXTRACT_DIR\$PIN_DIRNAME"

if (!(Test-Path $PINTOOL_ZIP)) {
    Write-Host "Fetching pintool from: $PIN_URL"
    Invoke-WebRequest $PIN_URL -OutFile $PINTOOL_ZIP
}
if (!(Test-Path $PINFULLDIR)) {
    Write-Host "Extracting: $PINTOOL_ZIP"
    Expand-Archive -LiteralPath $PINTOOL_ZIP -DestinationPath $PIN_EXTRACT_DIR
}

# XED Specific section
$TARGET_ARCH="intel64"
if( $env:PROCESSOR_ARCHITECTURE -eq "x86") {
    if( $env:PROCESSOR_ARCHITEW6432 -ne "AMD64") {
         $TARGET_ARCH="ia32"
    }
}

$XED="xed-$TARGET_ARCH"
$XED_DIR="$PACKAGE_DIR\xed"
if (!(Test-Path $XED_DIR)) {
    new-item -Path $PACKAGE_DIR -Name "xed" -ItemType directory
    
    # can add -Verbose to check file copies
    $xedpinDir="$PINFULLDIR\extras\$XED\*"
    Copy-Item  -Force -Recurse  $xedpinDir -Destination $XED_DIR
    
    $pincrtDir="$PINFULLDIR\$TARGET_ARCH\runtime\pincrt\*"
    $XED_LIB_DIR="$XED_DIR\lib\"
    Copy-item -Force -Recurse $pincrtDir -Destination $XED_LIB_DIR
}