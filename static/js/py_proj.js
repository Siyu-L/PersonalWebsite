async function classifyMessage() {
    
    const userInput = document.getElementById("sf-input-text").value;
    const response = await fetch("/classify_text", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({text: userInput})
    });

    const data = await response.json();
    document.getElementById("text-result").innerText = "Result: " + data.prediction;

}

async function classifyFile() {

    const fileInput = document.getElementById("sf-input-file");
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
    const numInput = parseInt(document.getElementById("sf-input-num").value, 10);
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

// --- Text input auto classify --- //
const textArea = document.getElementById("sf-input-text");
textArea.addEventListener("input", ()=> {
    if (textArea.value.trim() === "") {
        document.getElementById("text-result").innerText = "";
        return;
    }
    classifyMessage();
});



// --- File input auto classify --- //

function dragOverHandler(ev) {
    ev.preventDefault()
    uploadZone.classList.add("dragover")
}
function dragLeaveHandler() {
    uploadZone.classList.remove("dragover")
}
function dropHandler(ev) {
    ev.preventDefault();
    uploadZone.classList.remove("dragover");

    if (ev.dataTransfer.items) {
        fileInput.files = ev.dataTransfer.files;
        classifyFile();

    }
}

const fileInput = document.getElementById("sf-input-file");
const uploadZone = document.getElementById("file-upload-zone");

uploadZone.addEventListener("click", () => fileInput.click());
uploadZone.addEventListener("dragover", dragOverHandler);
uploadZone.addEventListener("dragleave", dragLeaveHandler);
uploadZone.addEventListener("drop", dropHandler)

fileInput.addEventListener("change", () => {
    if (fileInput.files.length > 0) {
        classifyFile();
    }
});

// --- Page refresh ---//
document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("sf-input-text").value = "";
  document.getElementById("text-result").innerText = "";
  document.getElementById("file-result").innerText = "";
  document.getElementById("sf-input-file").value = "";
});