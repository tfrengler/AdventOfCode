<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AOC - Index</title>

    <style>
        #Output {
            width: 100%;
            height: 70vh;
            overflow: scroll;
            background-color: aliceblue
        }

        section {
            display: inline-block;
            width: fit-content;
            border: solid 0.1rem lightgray;
            padding: 0.5rem;
            margin: 0.5rem;
            vertical-align: top;
        }
    </style>

    <script src="index.js"></script>
</head>
<body>

<fieldset>
    <legend>Advent of Code - Coldfusion Edition</legend>
    <p>
        <label for="DayPart1">Run part 1?</label>
        <input type="checkbox" id="DayPart1" name="DayPart" checked />
    <p>
    </p>
        <label for="DayPart2">Run part 2?</label>
        <input type="checkbox" id="DayPart2" name="DayPart" />
    </p>
    <p>
        <label for="Iterations">How many iterations?</label>
        <input type="number" value="1" step="1" name="Iterations" />
    </p>
    <p>
        <input type="button" value="Execute" name="Execute" />
    </p>
</fieldset>

<fieldset>
    <legend>DAYS</legend>
    <cfscript>
        // runner = new Components.Runner("09");
        // runner.RunPart(2, 30);

        DayComponents = directoryList(
            path=expandPath("Days"),
            recurse=false,
            listInfo="name",
            sort="asc",
            filter="Day*.cfc"
        );

        // DayComponents.append("Day11.cfc");
        // DayComponents.append("Day12.cfc");
        // DayComponents.append("Day13.cfc");
        // DayComponents.append("Day14.cfc");
        // DayComponents.append("Day15.cfc");
        // DayComponents.append("Day16.cfc");
        // DayComponents.append("Day17.cfc");
        // DayComponents.append("Day18.cfc");
        // DayComponents.append("Day19.cfc");

        sectionStartIndex = 0;
        for(index = 1; index <= DayComponents.len(); index++)
        {
            if ((index-1) % 5 == 0) {
                writeOutput("<section>");
                sectionStartIndex = index-1;
            }

            dayNumber = DayComponents[index].mid(4,2);

            writeOutput("
            <div>
                <label for='Day#dayNumber#'>Day #dayNumber#</label>
                <input type='radio' value='#dayNumber#' id='Day#dayNumber#' name='DayChoice' />
            </div>");

            if ((sectionStartIndex + index) % 5 == 0 || index == DayComponents.len()) {
                writeOutput("</section>");
            }
        }
    </cfscript>
</fieldset>

<fieldset>
    <legend>OUTPUT</legend>
    <div id="Output" disabled></div>
</fieldset>

</body>
</html>