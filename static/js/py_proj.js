async function classifyMessage() {
    
    const userInput = document.getElementById("user-input-text").value;
    console.log(userInput)
    const response = await fetch("/classify_text", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({text: userInput})
    });

    const data = await response.json();
    document.getElementById("text-result").innerText = "Result: " + data.prediction;

}

async function classifyFile() {

    const fileInput = document.getElementById("user-input-file");
    fileInput.addEventListener('change', () => {
        if (fileInput.files.length === 1) {
            console.log("File selected: ", elim.files[0]);
        }
    });
    

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
window.classifyMessage = classifyMessage;
window.classifyFile = classifyFile;