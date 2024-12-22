<cfcomponent displayname="Day09" modifier="final" output="false" accessors="false" persistent="true" extends="Components.Day" implements="Components.IDay">

    <cffunction access="public" name="Init" returntype="Day09" output="false">
        <cfscript>
            return super.Init("Day09");
        </cfscript>
    </cffunction>

    <cffunction access="public" name="Part01" returntype="numeric" output="true">
    <cfscript>
        var files = [];
        var fileIndex = 1;
        var fileId = 0;

        for (var i = 1; i <= variables.Input.len(); i = i+2) {

            files.append({
                id: fileId,
                size: val(variables.Input[i]),
                free: i == variables.Input.len() ? 0 : val(variables.Input[i + 1])
            });

            fileIndex++;
            fileId++;
        }
        writeOutput("<p>Files processed (count: #files.len()#)</p>");
        cfflush();

        // Creating the disk with the files and free space
        var disk = [];
        for (var i = 1; i <= files.len(); i++) {

            current = files[i];
            for (x = 1; x <= current.size; x++) {
                disk.append(current);
            }

            for (x = 1; x <= current.free; x++) {
                disk.append(null);
            }
        }

        writeOutput("<p>Disk created (size: #disk.len()#)</p>");
        cfflush();

        // Part 1
        var freeIndex = 1;
        var updateFreeIndex = () => {
            for (var i = freeIndex; i <= disk.len(); i++) {
                if (!isStruct(disk[i])) {
                    return i;
                }
            }
            return -1;
        }

        writeOutput("<p>Running...</p>");
        cfflush();


        cftimer(label="Part 1 time taken", type="inline")
        {
            var freeIndex = updateFreeIndex();

            try {
                for (var i = disk.len(); i != 0; i--) {

                    if (!isStruct(disk[i])) {
                        continue;
                    }

                    disk[freeIndex] = disk[i];
                    disk[i] = 0;
                    freeIndex = updateFreeIndex();

                    if (freeIndex >= i || freeIndex == -1) {
                        break;
                    }
                }
            }
            catch (error) {
                writeDump(label="catch: i", var=i);
                writeDump(label="catch: freeIndex", var=freeIndex);
                rethrow;
            }

            var partAnswer = 0;
            for (var i = 1; i <= disk.len(); i++) {
                if (!isStruct(disk[i])) continue;
                partAnswer += (disk[i].id * (i - 1));
            }
        }

        writeDump(label="Part 1 answer", var=partAnswer);
        application.assert(partAnswer == 6331212425418, "Expected part answer to be 6331212425418 but it was #partAnswer#");

        return partAnswer;
    </cfscript>
    </cffunction>

    <cffunction access="public" name="Part02" returntype="numeric" output="true">
    <cfscript>
        var exampleDiskMap      = "00...111...2...333.44.5555.6666.777.888899";
        var exampleSolutions    = "00992111777.44.333....5555.6666.....8888..";
        var files = [];
        var freeBlocks = [];
        var diskIndex = 1;
        var fileId = 0;

        // variables.Input = "2333133121414131402";
        // variables.Input = "1313165";
        /* = 169
        0...1...2......33333
        0...1...233333......
        02..1....33333......
        021......33333......
        */

        for (var fileIndex = 1; fileIndex <= variables.Input.len(); fileIndex = fileIndex+2) {

            var newFile = {
                position: diskIndex,
                id: fileId,
                size: val(variables.Input[fileIndex])
            };

            files.append(newFile);
            diskIndex = diskIndex + newFile.size;
            fileId++;

            var freeblocksCount = (fileIndex >= variables.Input.len() ? 0 : val(variables.Input[fileIndex + 1]));
            if (freeblocksCount == 0) continue;

            var newFreeBlock = {
                position: diskIndex,
                size: freeblocksCount
            };
            freeBlocks.append(newFreeBlock);
            diskIndex = diskIndex + newFreeBlock.size;
        }

        writeOutput("<p>Files and freeblocks processed (files: #files.len()#, free blocks: #freeBlocks.len()#)</p>");
        cfflush();
        // abort;

        writeOutput("<p>Running...</p>");
        cfflush();

        cftimer(label="Part time taken", type="inline")
        {
            for (var i = files.len(); i != 0; i--) {
                var currentFile = files[i];
                var sizeToMatch = currentFile.size;

                // writeOutput("<p>Find freeblock for file #currentFile.id# at position #currentFile.position# with size #sizeToMatch#</p>");
                for (var x = 1; !(x > freeBlocks.len()); x++) {

                    var freeBlock = freeBlocks[x];
                    if (freeBlock.position >= currentFile.position) {
                        // writeOutput("<p>Freeblock position (#freeBlock.position#) exceeds file position, cannot move file</p>");
                        break;
                    }

                    if (freeBlock.size < sizeToMatch) {
                        // writeOutput("<p>Freeblock size less file size (#freeBlock.size#), cannot move file</p>");
                        continue;
                    }

                    // writeOutput("<p>SUCCESS: Found freeblock at position #freeBlock.position# with size #freeBlock.size#</p>");

                    currentFile.position = freeBlock.position;
                    if (freeBlock.size == sizeToMatch) {
                        // writeOutput("<p>Freeblock was exact size</p>");
                        freeBlock.position = 0;
                        freeBlock.size = 0;
                        break;
                    }

                    // writeOutput("<p>File size was less than freeblock size, adjusting size and position. Was = size : #freeBlock.size# | position: #freeBlock.position#.</p>");
                    freeBlock.size -= sizeToMatch;
                    freeBlock.position += sizeToMatch;
                    // writeOutput("<p>After = size #freeBlock.size# | position: #freeBlock.position#</p>");
                    break;
                }
            }
        }

        writeOutput("<p>");
        cftimer(label="Sorting files and calculating answer", type="inline")
        {
            arraySort(files, (item1, item2) => {
                if (item2.position < item1.position) return 1;
                if (item2.position > item1.position) return -1;
                return 0;
            });

            var partAnswer = 0;

            for (var i = 1; i <= files.len(); i++) {
                var currentFile = files[i];
                for (var x = 0; x < currentFile.size; x++) {
                    partAnswer += currentFile.id * ((currentFile.position-1) + x);
                }
            }
        }
        writeOutput("</p>");

        // writeDump(label="Files", var=files);
        writeDump(label="Part 2 answer", var=partAnswer);
        application.assert(partAnswer == 6363268339304, "Expected part answer to be 6363268339304 but it was #partAnswer#");
        return partAnswer;
    </cfscript>
    </cffunction>

</cfcomponent>