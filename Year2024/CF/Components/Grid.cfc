<cfcomponent displayname="Grid" modifier="final" output="false" accessors="false" persistent="true">

    <cfproperty name="Grid" type="array" getter="true" setter="false" >
    <cfproperty name="Width" type="numeric" getter="true" setter="false" >
    <cfproperty name="Height" type="numeric" getter="true" setter="false" >
    <cfproperty name="BoundaryCrossIsFatal" type="boolean" getter="true" setter="true" >

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
                    grid[row] = trim(mid(arguments.inputString, i-columns, columns+1));
                    row++;
                    columns = 0;
                }

                columns++;
            }

            variables.Width = variables.Grid[1].len();
            variables.Height = arrayLen(Grid);
            variables.BoundaryCrossIsFatal = false;

            return this;
        </cfscript>
    </cffunction>

    <!---
        Column size: 5
        Array size: 15
        ROW |01 02 03 04 05 06 07 08 09 10 11 12 13 14 15|
            |A  B  C  D  E  F  G  H  I  J  L  M  N  O  P |
        COL |1--------------2-----------3----------------|

        Given X is row and Y is col
        And Y is 2 and X is 3
        Let result be (Y mod array size)+ column width + X:
            2 mod 15 + 5 + 3 = H
    --->
    <cffunction access="public" name="GetPoint" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>

            if (arguments.X < 1 || arguments.X > variables.Width) {
                if (variables.BoundaryCrossIsFatal is true) {
                    throw("Error when getting grid point. X (#arguments.X#) is beyond the width of the grid (#variables.Width#)");
                }
                return new GridPoint(-1, -1, false, "");
            }

            if (arguments.Y < 1 || arguments.Y > variables.Height) {
                if (variables.BoundaryCrossIsFatal is true) {
                    throw("Error when getting grid point. Y (#arguments.Y#) is beyond the height of the grid (#variables.Height#)");
                }
                return new GridPoint(-1, -1, false, "");
            }

            // var gridPosition = (arguments.Y mod arrayLen(variables.Grid)) + variables.Width + arguments.X;
            // return new GridPoint(arguments.X, arguments.Y, true, variables.Grid[gridPosition]);

            return new GridPoint(arguments.X, arguments.Y, true, variables.Grid[arguments.Y][arguments.X]);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetNorth" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X, arguments.Y - 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetNorthEast" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X + 1, arguments.Y - 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetEast" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X + 1, arguments.Y);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetSouthEast" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X + 1, arguments.Y + 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetSouth" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X, arguments.Y + 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetSouthWest" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X - 1, arguments.Y + 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetWest" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X - 1, arguments.Y);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetNorthWest" returntype="GridPoint" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return GetPoint(arguments.X - 1, arguments.Y - 1);
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetStar" returntype="array" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return [
                GetNorthEast(arguments.X, arguments.Y),
                GetSouthEast(arguments.X, arguments.Y),
                GetSouthWest(arguments.X, arguments.Y),
                GetNorthWest(arguments.X, arguments.Y)
            ];
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetCross" returntype="array" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return [
                GetNorth(arguments.X, arguments.Y),
                GetEast(arguments.X, arguments.Y),
                GetSouth(arguments.X, arguments.Y),
                GetWest(arguments.X, arguments.Y)
            ];
        </cfscript>
    </cffunction>

    <cffunction access="public" name="GetBox" returntype="array" output="false">
        <cfargument name="X" required="true" type="numeric" />
        <cfargument name="Y" required="true" type="numeric" />
        <cfscript>
            return [
                GetNorth(arguments.X, arguments.Y),
                GetNorthEast(arguments.X, arguments.Y),
                GetEast(arguments.X, arguments.Y),
                GetSouthEast(arguments.X, arguments.Y),
                GetSouth(arguments.X, arguments.Y),
                GetSouthWest(arguments.X, arguments.Y),
                GetWest(arguments.X, arguments.Y),
                GetNorthWest(arguments.X, arguments.Y),
            ];
        </cfscript>
    </cffunction>
</cfcomponent>