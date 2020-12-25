
$path=$args[0]
$tarfile=$args[1]
$zipFolderRoot=[System.IO.Path]::GetFileNameWithoutExtension(${tarfile})
$regexzipFolderRoot = Get-ChildItem $path | Where-Object { $_.Name.StartsWith($zipFolderRoot)}
$unpackedDir="${path}\${regexzipFolderRoot}"
Write-Host "unpackedDir: $unpackedDir"
if (Test-Path $unpackedDir) {
    Write-Host "Moving Contents of: $unpackedDir"
    Move-Item -Path "${unpackedDir}\*" -Destination ${path}
    Remove-Item $unpackedDir
}


