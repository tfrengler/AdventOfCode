<cfscript>
    if (structIsEmpty(URL)) {
        throw("Nothing passed");
    }

    cfparam(name="URL.Day", type="string");
    cfparam(name="URL.Part1", type="boolean");
    cfparam(name="URL.Part2", type="boolean");
    cfparam(name="URL.Iterations", type="numeric");

    // writeDump(URL);abort;

    Runner = new Components.Runner(URL.Day);

    if (URL.Part1) {
        Runner.RunPart(1, URL.Iterations);
    }

    if (URL.Part2) {
        Runner.RunPart(2, URL.Iterations);
    }
</cfscript>