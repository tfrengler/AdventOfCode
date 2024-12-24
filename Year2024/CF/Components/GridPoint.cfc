<cfcomponent displayname="GridPoint" modifier="final" output="false" accessors="false" persistent="true" >

    <cfproperty name="X"        type="numeric" getter="true" setter="true" >
    <cfproperty name="Y"        type="numeric" getter="true" setter="true" >
    <cfproperty name="IsValid"  type="boolean" getter="true" setter="true" >
    <cfproperty name="Value"    type="string" getter="true" setter="true" >

    <cffunction access="public" name="Init" returntype="GridPoint" output="false">
        <cfargument name="X"        required="false" type="numeric" default="-1" />
        <cfargument name="Y"        required="false" type="numeric" default="-1" />
        <cfargument name="IsValid"  required="false" type="boolean" default="false" />
        <cfargument name="Value"    required="false" type="string" default="\0" />
        <cfscript>
            variables.X = arguments.X;
            variables.Y = arguments.Y;
            variables.IsValid = arguments.IsValid;
            variables.Value = arguments.Value;

            return this;
        </cfscript>
    </cffunction>

    <cffunction access="public" name="ValueEquals" returntype="boolean" output="false">
        <cfargument name="other" required="true" type="GridPoint" />
        <cfscript>
            return
                variables.X == other.getX() &&
                variables.Y == other.getY() &&
                variables.IsValid == other.getIsValid() &&
                variables.Value == other.getValue();
        </cfscript>
    </cffunction>
</cfcomponent>