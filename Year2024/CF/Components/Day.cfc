<cfcomponent displayname="Day" modifier="abstract" output="false" accessors="false" persistent="true">

    <cfproperty name="Input" type="string" getter="true" setter="false" >
    <cfproperty name="Output" type="Components.Output" getter="false" setter="false" >

    <cffunction access="public" name="Init" returntype="Day" output="false">
        <cfargument name="input" required="true" type="string" />
        <cfscript>
            if (arguments.input.len() == 0) {
                throw("Cannot instantiate day. Argument 'input' is empty");
            }
            variables.input = fileRead( expandPath("Input/") & arguments.input & ".txt" );

            application.assert(variables.input.len() > 0);
            variables.Output = new Components.Output();

            return this;
        </cfscript>
    </cffunction>

</cfcomponent>