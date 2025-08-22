async function classifyMessage() {
    const userInput = document.getElementById("user-input").value;

    const response = await fetch("https://localhost:5000/classify", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({text: userInput})
    });

    const data = await response.json();
    document.getElementById("result").innerText = "Result: " + data.prediction;

}


function openProj(evt, projId, projTitle) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++)
    {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }    

    document.getElementById(projId).style.display = "block";
    evt.currentTarget.className += " active"

    document.getElementById("proj-header").innerHTML = projTitle;

}

window.openProj = openProj;