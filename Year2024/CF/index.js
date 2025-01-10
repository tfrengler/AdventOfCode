"use strict";

const Elements = Object.freeze({
    Execute: () => document.querySelector("[name='Execute']"),
    Output: () => document.querySelector("#Output"),
    DayPart1: () => document.querySelector("#DayPart1"),
    DayPart2: () => document.querySelector("#DayPart2"),
    DayChoice: () => Array.from(document.querySelectorAll("[name='DayChoice']")).filter(x => x.checked)[0] || null,
    Iterations: () => document.querySelector("[name='Iterations']")
});

// U+231B

window.onload = function () {
    Elements.Execute().addEventListener("click", OnExecute);
}

const OnExecute = async function () {
    console.log("OnExecute START");

    Elements.Execute().disabled = true;
    // Elements.Execute().value = "EXECUTE &#x231B";
    Elements.Output().innerHTML = "";

    const RequestURL = "Runner.cfm"
    + `?Iterations=${ Elements.Iterations().value }`
    + `&Day=${ Elements.DayChoice().value }`
    + `&Part1=${ Elements.DayPart1().checked }`
    + `&Part2=${ Elements.DayPart1().checked }`;

    const data = await fetch(RequestURL)
        .then(response => response.text());

    Elements.Execute().disabled = false;
    // Elements.Execute().value = "EXECUTE";
    Elements.Output().innerHTML = data;

    console.log("OnExecute END");
}