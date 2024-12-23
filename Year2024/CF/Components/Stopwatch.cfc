<cfcomponent displayname="Stopwatch" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="Begin" type="numeric" getter="false" setter="false" >
    <cfproperty name="End" type="numeric" getter="false" setter="false" >

    <cffunction access="public" name="Init" returntype="Stopwatch" output="false">
    <cfscript>
        variables.Begin = 0;
        variables.End = 0;
        return this;
    </cfscript>
    </cffunction>

    <cffunction access="public" name="Start" returntype="Stopwatch" output="false">
        <cfscript>
            variables.Begin = createObject("java", "java.lang.System").nanoTime();
            return this;
        </cfscript>
    </cffunction>

    <cffunction access="public" name="Stop" returntype="Stopwatch" output="false">
        <cfscript>
            variables.End = createObject("java", "java.lang.System").nanoTime();
            return this;
        </cfscript>
    </cffunction>

    <cffunction access="public" name="ElapsedMS" returntype="numeric" output="false">
        <cfscript>
            return (variables.End - variables.Begin) * 1.0E-6;
        </cfscript>
    </cffunction>

</cfcomponent>