<cfcomponent displayname="Output" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="SuppressOutput" type="boolean" getter="true" setter="true" >

    <cffunction access="public" name="Init" returntype="Output" output="false">
    <cfscript>
        variables.SuppressOutput = false;
        return this;
    </cfscript>
    </cffunction>

    <cffunction access="public" name="WriteBlock" returntype="void" output="true">
        <cfargument name="input" required="true" type="string" />
        <cfscript>
            if (variables.SuppressOutput) return;
            writeOutput("<p>#arguments.input#</p>");
            cfflush();
        </cfscript>
    </cffunction>

    <cffunction access="public" name="WriteList" returntype="void" output="true">
        <cfargument name="input" required="true" type="array" />
        <cfscript>
            if (variables.SuppressOutput) return;
            writeOutput("<ul>");
            for(var output in arguments.input)
            {
                writeOutput("<li>#output#</li>");
            }
            writeOutput("</ul>");
            cfflush();
        </cfscript>
    </cffunction>

    <cffunction access="public" name="WriteLine" returntype="void" output="true">
        <cfargument name="input" required="true" type="string" />
        <cfscript>
            if (variables.SuppressOutput) return;
            writeOutput("#arguments.input#<br/>");
            cfflush();
        </cfscript>
    </cffunction>

    <cffunction access="public" name="Write" returntype="void" output="true">
        <cfargument name="input" required="true" type="string" />
        <cfscript>
            if (variables.SuppressOutput) return;
            writeOutput(arguments.input);
            cfflush();
        </cfscript>
    </cffunction>

</cfcomponent>