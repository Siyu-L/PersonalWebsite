async function classifyMessage() {
    
    const userInput = document.getElementById("user-input-text").value;
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
    const file = fileInput.files[0]

    const formData = new FormData();
    formData.append("file", file);
    const response = await fetch("/classify_file", {
        method: "POST",
        body: formData
    })
    
   const data = await response.json()
   document.getElementById("file-result").innerText = "Result: " + data.prediction;

}

async function getIndicativeWords() {
    const numInput = parseInt(document.getElementById("num-words").value, 10);
    console.log(numInput)
    const response = await fetch("/indicative_word", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({num: numInput})
    })
    
    const data = await response.json()
    document.getElementById("spam-words").innerText = "Spam: " + data.spam_ind
    document.getElementById("ham-words").innerText = "Ham: " + data.ham_ind


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