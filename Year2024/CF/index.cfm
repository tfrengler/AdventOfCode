<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AOC - Index</title>
</head>
<body>
<cfscript>

    fileContent = fileRead(expandPath("Input") & "/Day10.txt");
    grid = new Components.Grid(fileContent);

    writeDump(grid);

    // day = "Day09";
    // test = createObject("component", "Days.#day#").init();
    // writeDump(test);
    // writeDump(test.Part01());
    // writeDump(var=variables, expand=false);

    //test = directoryList(expandPath("Days"), false, "path", "Day*.cfc");
    // writeDump(test);

    // writeOutput("<table><thead><th>Day/Part</th><th>Run</th><th>Result</th></thead>");

    /*for(i = 1; i <= test.len(); i++) {
        data = getComponentMetadata(test[i]);
        // writeDump(data);
        writeOutput("<li>#data.fullName#</li>");
    }*/
</cfscript>
</body>
</html>