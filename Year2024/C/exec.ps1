$BuildMode  = "debug"
$Day = $args[0];

if ($args.Count -eq 0)
{
    Write-Host -f Red "No args passed"
    exit
}

if ($args -Contains "--r")
{
    $BuildMode = "release"
}

if ($Day -eq "Debug") {
    & make Debug BUILD=${BuildMode}
    & .\build\Debug_${BuildMode}.exe
    exit
}

& make Day NR=${Day} BUILD=${BuildMode}
& .\build\Day${Day}_${BuildMode}.exe