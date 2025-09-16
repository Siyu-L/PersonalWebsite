function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function openProj(evt, projId, projTitle) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }

    document.getElementById(projId).style.display = "block";
    evt.currentTarget.className += " active"

    document.getElementById("proj-header").innerHTML = projTitle;

}


/* --- Grid Navigation --- */
let scene = [];
let mode = null;
let start = null;
let end = null;

const arrowMap = {
    "-1,0": "↑",   // up
    "1,0": "↓",    // down
    "0,-1": "←",   // left
    "0,1": "→",    // right
    "-1,-1": "↖",  // up-left
    "-1,1": "↗",   // up-right
    "1,-1": "↙",   // down-left
    "1,1": "↘"     // down-right
};

async function initScene(row, col) {

    const res = await fetch("/init_scene", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ row: row, col: col })
    });
    const data = await res.json();
    scene = data.scene;
    renderGrid();

}

async function setScene() {
    row = parseInt(document.getElementById("grid-rows").value, 10);
    col = parseInt(document.getElementById("grid-cols").value, 10);
    if (row > 8) { row = 8 }
    if (row < 2) { row = 2 }
    if (col > 8) { col = 8 }
    if (col < 2) { col = 2 }
    initScene(row, col)
}

function renderGrid() {
    const gridDiv = document.getElementById("grid-scene");
    gridDiv.innerHTML = "";

    gridDiv.style.display = "grid";
    gridDiv.style.gridTemplateColumns = `repeat(${scene[0].length}, 7rem)`;
    gridDiv.style.gridTemplateRows = `repeat(${scene.length}, 7rem)`;
    gridDiv.style.gap = "5px";

    for (let r = 0; r < scene.length; r++) {
        for (let c = 0; c < scene[0].length; c++) {
            const tile = document.createElement("div");
            tile.classList.add("grid-tile");
            tile.dataset.row = r;
            tile.dataset.col = c;
            tile.onclick = () => handleTileClick(r, c, tile);
            gridDiv.appendChild(tile);
        }
    }
}


function setMode(evt, newMode) {
    modeButtons = document.getElementsByClassName("mode-button")
    for (i = 0; i < modeButtons.length; i++) {
        modeButtons[i].className = modeButtons[i].className.replace(" active", "");
    }

    evt.currentTarget.className += " active"    

    mode = newMode;
}

function handleTileClick(r, c, tile) {
    if (mode === "start") {
        if (start) document.querySelector(".grid-tile.start").classList.remove("start");
        start = [r, c];
        tile.classList.add("start");
    } else if (mode === "end") {
        if (end) document.querySelector(".grid-tile.end").classList.remove("end");
        end = [r, c];
        tile.classList.add("end");
    } else if (mode === "obstacle") {
        const isObstacle = scene[r][c];
        scene[r][c] = !isObstacle;
        tile.classList.toggle("obstacle", !isObstacle);
    }
}


async function solvePath() {
    const response = await fetch("/find_route", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ start, end, scene })
    });

    const data = await response.json();
    if (data.path) {
        document.getElementById("path-result").innerText = "Path: " + JSON.stringify(data.path);
    }
    else {
        document.getElementById("path-result").innerText = "No valid path";
    }
    animatePath(data.path);
}

async function animatePath(path) {
    document.querySelectorAll(".grid-tile").forEach(tile => {
        tile.innerText = "";
    });    
    
    for (let i = 0; i < path.length - 1; i++) {
        const [r1, c1] = path[i];
        const [r2, c2] = path[i+1];

        const dr = r2 - r1;
        const dc = c2 - c1;
        const arrow = arrowMap[`${dr},${dc}`];
        const tile = document.querySelector(`.grid-tile[data-row="${r1}"][data-col="${c1}"]`);
        
        tile.innerText = arrow;

        await sleep(300);
    }
    const [rf, cf] = path[path.length - 1]
    const final_tile = document.querySelector(`.grid-tile[data-row="${rf}"][data-col="${cf}"]`);
    final_tile.innerText = "X";

}

/* --- Tile Puzzle --- */
let board = []

async function initBoard(row, col) {
    const res = await fetch("/init_board", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ row: row, col: col })
    });
    const data = await res.json();
    board = data.board;
    renderBoard();
}

async function setBoard() {
    row = parseInt(document.getElementById("tile-rows").value, 10);
    col = parseInt(document.getElementById("tile-cols").value, 10);
    if (row > 8) { row = 8 }
    if (row < 2) { row = 2 }
    if (col > 8) { col = 8 }
    if (col < 2) { col = 2 }
    initBoard(row, col)
}

async function scrambleBoard() {
    const res = await fetch("/scramble_board");
    const data = await res.json();
    board = data.board;
    renderBoard();
}


async function fetchBoard() {
    const res = await fetch("/get_board");
    const data = await res.json();
    board = data.board;
    renderBoard();
}

function renderBoard() {
    const boardDiv = document.getElementById("board");
    boardDiv.innerHTML = "";

    boardDiv.style.display = "grid";
    boardDiv.style.gridTemplateColumns = `repeat(${board[0].length}, 7rem)`;
    boardDiv.style.gridTemplateRows = `repeat(${board.length}, 7rem)`;
    boardDiv.style.gap = "5px";

    for (let r = 0; r < board.length; r++) {
        for (let c = 0; c < board[0].length; c++) {
            const tile = document.createElement("div");
            tile.classList.add("tile");
            if (board[r][c] === 0) {
                tile.classList.add("empty");
                tile.innerText = "";
            }
            else {
                tile.innerText = board[r][c];
            }
            boardDiv.appendChild(tile);
        }
    }
}

async function makeMove(direction) {
    const res = await fetch("/move", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ direction })
    });
    const data = await res.json();
    if (data.success) {
        board = data.board;
        renderBoard();
    }

}

async function solve_iddfs() {
    const res = await fetch("/solve_iddfs", {
        method: "POST",
        headers: { "Content-Type": "application/json" }
    });
    const data = await res.json();
    moves = data.solution[0];
    for (let i = 0; i < moves.length; i++) {
        makeMove(moves[i])
        await sleep(500)
    }
    document.getElementById("solution-box").innerText = "Solution: " + data.solution.join(", ");
}

async function solve_a_star() {
    const res = await fetch("/solve_a_star", {
        method: "POST",
        headers: { "Content-Type": "application/json" }
    });
    const data = await res.json();
    console.log(data);
    moves = data.solution;
    for (let i = 0; i < moves.length; i++) {
        makeMove(moves[i])
        await sleep(500)
    }
    document.getElementById("solution-box").innerText = "Solution: " + data.solution.join(", ");
}

document.addEventListener("keydown", e => {
    if (e.key === "ArrowUp") makeMove("up");
    if (e.key === "ArrowDown") makeMove("down");
    if (e.key === "ArrowLeft") makeMove("left");
    if (e.key === "ArrowRight") makeMove("right");
});

fetchBoard();


/* --- Spam Filter --- */

async function classifyMessage() {

    const userInput = document.getElementById("sf-input-text").value;
    const response = await fetch("/classify_text", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ text: userInput })
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
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ num: numInput })
    })

    const data = await response.json()
    document.getElementById("spam-words").innerText = "Spam: " + data.spam_ind
    document.getElementById("ham-words").innerText = "Ham: " + data.ham_ind


}

window.openProj = openProj;
window.classifyMessage = classifyMessage;
window.classifyFile = classifyFile;

// --- Text input auto classify --- //
const textArea = document.getElementById("sf-input-text");
textArea.addEventListener("input", () => {
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
    initBoard(3, 3);
    initScene(3, 3);

});
