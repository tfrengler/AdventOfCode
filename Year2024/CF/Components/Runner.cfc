<cfcomponent displayname="Runner" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="DayInstance" type="Components.IDay" getter="false" setter="false" >
    <cfproperty name="Output" type="Components.Output" getter="false" setter="false" >

    <cffunction access="public" name="Init" returntype="Runner" output="false">
        <cfargument name="day" required="true" type="string" />
        <cfscript>
            variables.DayInstance = createObject("component", "Days.Day#arguments.day#").Init();
            variables.Output = new Components.Output();
            return this;
        </cfscript>
    </cffunction>

    <cffunction access="public" name="RunPart" returntype="void" output="true">
        <cfargument name="number" required="true" type="numeric" />
        <cfargument name="iterations" required="false" type="numeric" default="1" />
        <cfscript>

            if (arguments.iterations <= 0)
            {
                throw("Argument 'iterations' must be greater than 0");
            }

            if (arguments.number < 1 || arguments.number > 2)
            {
                throw("Argument 'number' must be 1 or 2");
            }

            var executionTimes = [];
            var stopwatch = new Components.Stopwatch();
            var totalStopwatch = new Components.Stopwatch().Start();

            variables.Output.WriteBlock("Running part #arguments.number#...");

            var result = 0;
            for(var index = 1; index <= arguments.iterations; index++)
            {
                stopwatch.Restart();
                result = arguments.number == 1 ? variables.DayInstance.Part01() : variables.DayInstance.Part02();
                stopwatch.Stop();
                executionTimes.append(stopwatch.ElapsedMS());
            }

            totalStopwatch.Stop();
            variables.Output.WriteBlock("Done, time taken: #numberFormat(totalStopwatch.ElapsedSeconds(), "0.00")# seconds");

            arraySort(executionTimes, "numeric", "asc");
            var averageExecutionTimeInMS = arrayAvg(executionTimes);
            var medianExecutionTimeInMS = 0;

            var arrayLen = executionTimes.len();
            if (arrayLen > 1)
            {
                if (arrayLen % 2 == 0) {
                    // For even length, average the two middle values
                    medianExecutionTimeInMS = (executionTimes[arrayLen / 2] + executionTimes[(arrayLen / 2) + 1]) / 2;
                } else {
                    // For odd length, take the middle value
                    medianExecutionTimeInMS = executionTimes[(arrayLen + 1) / 2];
                }
            } // If there's only one value then just take that one obviously
            else {
                medianExecutionTimeInMS = executionTimes[1];
            }

            Output.WriteLine("EXECUTION TIMES (over #arguments.iterations# iterations):");
            Output.WriteList(["<b>Average</b>: #numberFormat(averageExecutionTimeInMS, "0.0000")# ms", "<b>Median</b>: &nbsp;#numberFormat(medianExecutionTimeInMS, "0.0000")# ms"]);
            Output.WriteBlock("Result (final iteration): #result#");

        </cfscript>
    </cffunction>

</cfcomponent>