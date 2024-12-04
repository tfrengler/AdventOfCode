$BuildMode  = "debug"

# if ($args.Length -eq 0)
# {
#     # Write-Host -f Red "ERROR: Expected at least one cmdline-argument but found none"
#     $BuildMode = "debug"
# }

if ($args -Contains "--release")
{
    $BuildMode = "release"
}

Write-Host -f Yellow "BUILD MODE: ${BuildMode}"

if ($args -NotContains "--noclean")
{
    make clean_all
}

Write-Host -f Green "DAY 01:"
make Day NR=01 BUILD=${BuildMode}
& "./build/Day01_${BuildMode}.exe"

Write-Host -f Green "DAY 02:"
make Day NR=02 BUILD=${BuildMode}
& "./build/Day02_${BuildMode}.exe"

Write-Host -f Green "DAY 03:"
make Day NR=03 BUILD=${BuildMode}
& "./build/Day03_${BuildMode}.exe"