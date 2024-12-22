<cfcomponent output="false">

    <cfset this.name="AdventOfCode" />
    <cfset this.applicationtimeout = CreateTimeSpan(1,0,0,0) />

    <cfset this.sessionmanagement = true />
    <cfset this.setClientCookies = true />
    <cfset this.sessioncookie.secure = true />
    <cfset this.sessiontimeout = CreateTimeSpan(0,1,0,0) />
    <cfset this.sessionType = "cfml" />
    <cfset this.loginstorage = "session" />

    <cfset this.scriptProtect = "all" />
    <cfset this.invokeImplicitAccessor = false />

    <cfset this.appRoot = getDirectoryFromPath(getCurrentTemplatePath()) />
    <cfset this.mappings = {} />
    <cfset this.mappings["/Components"] = this.appRoot & "Components" />
    <cfset this.mappings["/Days"] = this.appRoot & "Days" />
    <cfset this.mappings["/Input"] = this.appRoot & "Input" />

    <cffunction name="onApplicationStart" returnType="boolean" output="true">
    <cfscript>
        application.rootDir = this.appRoot;
        application.assert = (required bool expression, string message = "") => {
            if (arguments.expression) return;
            throw("Assertion failed!" & arguments.message.len() > 0 ? " #arguments.message#" : "<no message>");
        };

        return true;
    </cfscript>
    </cffunction>

    <cffunction name="onRequestStart" returnType="boolean" output="false" >
        <cfargument type="string" name="targetPage" required="true" />
        <!--- Otherwise the webserver might buffer the proxied response from Lucee and cfflush won't emit anything--->
        <!--- <cfheader name="X-Accel-Buffering" value="no" /> --->

        <cfif structKeyExists(URL, "Reset") >
            <cfset onSessionEnd(session, application) />
            <cflocation url=#listFirst(cgi.REQUEST_URL, "?")# />
        </cfif>

        <!--- For testing purposes, this nukes the session and restarts the application --->
        <cfif structKeyExists(URL, "Restart") >
            <cfset onSessionEnd(session, application) />
            <cfset applicationStop() />
            <cflocation url=#listFirst(cgi.REQUEST_URL, "?")# />
        </cfif>

        <cfreturn true />
    </cffunction>

    <cffunction name="onSessionEnd" returntype="void" output="false">
        <cfargument name="sessionScope" type="struct" required="true" />
        <cfargument name="applicationScope" type="struct" required="true" />

        <cfset sessionInvalidate() />
    </cffunction>

</cfcomponent>