<cfcomponent displayname="Runner" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="SuppressOutput" type="boolean" getter="true" setter="true" >

    <cffunction access="public" name="Init" returntype="Runner" output="false">
    <cfscript>
        variables.SuppressOutput = false;
        return this;
    </cfscript>
    </cffunction>

    <cffunction access="public" name="xxx" returntype="void" output="true">
        <cfargument name="xxx" required="true" type="string" />
        <cfscript>

        </cfscript>
    </cffunction>

</cfcomponent>