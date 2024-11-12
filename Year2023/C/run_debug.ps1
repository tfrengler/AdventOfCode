make clean

Write-Host -f Green "Rebuilding in debug mode"
make all BUILD=debug -j 8

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
Write-Host -f Green "DAY 07:"
./build/Day07_debug.exe
Write-Host -f Green "DAY 08:"
./build/Day08_debug.exe
Write-Host -f Green "DAY 09:"
./build/Day09_debug.exe
Write-Host -f Green "DAY 10:"
./build/Day10_debug.exe