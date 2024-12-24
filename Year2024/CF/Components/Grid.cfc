<cfcomponent displayname="Grid" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="Grid" type="array" getter="true" setter="false" >
    <cfproperty name="Width" type="numeric" getter="true" setter="false" >
    <cfproperty name="Height" type="numeric" getter="true" setter="false" >

    <cffunction access="public" name="Init" returntype="Grid" output="false">
        <cfargument name="inputString" required="true" type="string" />
        <cfscript>
            if (arguments.inputString.trim().len() == 0) {
                throw("Error instantiating grid. Argument 'inputString' is empty");
            }

            variables.Grid = [];

            var columns = 0;
            var row = 1;

            for(var i = 1; i <= arguments.inputString.len(); i++)
            {
                if (asc(arguments.inputString[i]) == 13 || i == arguments.inputString.len())
                {
                    grid[row] = rtrim(mid(arguments.inputString, i-columns, columns+1));
                    row++;
                    columns = 0;
                }

                columns++;
            }

            variables.Width = variables.Grid[1].len();
            variables.Height = arrayLen(Grid);

            return this;
        </cfscript>
    </cffunction>

    <!--- <cffunction access="public" name="WriteBlock" returntype="void" output="true">
        <cfargument name="input" required="true" type="string" />
        <cfscript>

        </cfscript>
    </cffunction> --->
</cfcomponent>