
$path=$args[0]
$tarfile=$args[1]

$bname=(Split-Path $path -Leaf)
$zipFolderRootBName=[System.IO.Path]::GetFileNameWithoutExtension(${tarfile})
$zipFolderRootDir=(Get-Item $tarfile ).DirectoryName
$zipFolderRoot="${zipFolderRootDir}\${zipFolderRootBName}"

Write-Host "bname: $bname"
Write-Host "zipFolderRoot: $zipFolderRoot"
Write-Host "zipFolderRoot exists: $(Test-Path $zipFolderRoot)"
Write-Host "zipFolderRootBName: $zipFolderRootBName"
Write-Host "Does bname equals zipFolderRootBName: $(-not ($bname -eq $zipFolderRootBName))"
if ( (Test-Path $zipFolderRoot) -and (-not ($bname -eq $zipFolderRootBName))) {
    Rename-Item $zipFolderRoot $bname
    #Move-Item -Path "${zipFolderRoot}\*" -Destination ${path}
    #Remove-Item $zipFolderRoot
} else {
    Write-Host "No rename necessary for $bname"
}
