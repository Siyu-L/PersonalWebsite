var Module = {
    print: (text) => {
        document.getElementById("terminal").innerText += text + "\n";
    },
    printErr: (text) => {
        console.error(text);
    },
    stdin: function () {
        if (Module.inputQueue && Module.inputQueue.length > 0) {
            const value = Module.inputQueue.shift() + "\n";
            console.log("Provided input:", value);
            return value.charCodeAt(0);
        }
        return null;
    },
    inputQueue: [],
    onRunTimeInitialized: function () {
        console.log("WASM initialized — calling main with args");
        Module.callMain(['6','7','4']);
    }
};

const script = document.createElement("script");
script.src = "/static/connectn.js";
document.body.appendChild(script);
document.getElementById("terminal-input").addEventListener("keydown", (e) => {
    if (e.key === "Enter") {
        const val = e.target.value.trim();
        e.target.value = "";
        Module.inputQueue = val.split("").map(c => c);
        Module.inputQueue.push("\n");
    }
});
script.onerror = () => console.error("Failed to load connectn.js");
