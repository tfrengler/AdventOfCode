<cfcomponent displayname="Day10" modifier="final" output="false" accessors="false" persistent="true" extends="Components.Day" implements="Components.IDay">

    <cffunction access="public" name="Init" returntype="Day10" output="false">
        <cfscript>
            var ReturnData = super.Init("Day10");
            variables.Output.SetSuppressOutput(false);
            return ReturnData;
        </cfscript>
    </cffunction>

    <cffunction access="public" name="Part01" returntype="numeric" output="false">
    <cfscript>
        var partAnswer = 0;
        application.assert(partAnswer == 0, "Expected part answer to be 0 but it was #partAnswer#");
        return partAnswer;
    </cfscript>
    </cffunction>

    <cffunction access="public" name="Part02" returntype="numeric" output="false">
    <cfscript>
        var partAnswer = 0;
        application.assert(partAnswer == 0, "Expected part answer to be 0 but it was #partAnswer#");
        return partAnswer;
    </cfscript>
    </cffunction>

</cfcomponent>