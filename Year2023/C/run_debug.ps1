make clean

Write-Host -f Green "Rebuilding in debug mode"
make all BUILD=debug

Write-Host -f Green "Running binaries..."

Write-Host -f Green "DAY 01:"
./build/Day01_debug.exe
Write-Host -f Green "DAY 02:"
./build/Day02_debug.exe
Write-Host -f Green "DAY 03:"
./build/Day03_debug.exe
Write-Host -f Green "DAY 04:"
./build/Day04_debug.exe
Write-Host -f Green "DAY 05:"
./build/Day05_debug.exe
Write-Host -f Green "DAY 06:"
./build/Day06_debug.exe