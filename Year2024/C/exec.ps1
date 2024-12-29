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

& make Day NR=${Day} BUILD=${BuildMode}
& .\build\Day${Day}_${BuildMode}.exe