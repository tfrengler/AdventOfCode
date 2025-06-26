$BuildMode  = "debug"

if ($args -Contains "--release")
{
    $BuildMode = "release"
}

Write-Host -f Yellow "BUILD MODE: ${BuildMode}"

if ($args -NotContains "--noclean")
{
    make clean
}

$Days = "01", "02", "03", "04", "05", "06", "07", "09", "10"

foreach ($day in $Days)
{
    Write-Host -f Green "DAY ${day}:"
    make Day NR=${day} BUILD=${BuildMode}
    & "./build/Day${day}_${BuildMode}.exe"
}
