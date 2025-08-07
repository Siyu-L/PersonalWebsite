let cols, rows;
let spacing = 30;
let zoff = 0;

function setup() {
    createCanvas(windowWidth, windowHeight);
    cols = floor(width / spacing) + 1;
    rows = floor(height / spacing) + 1;
    stroke(100);
    noFill()
}

function draw() {
    background(0)
    let yoff = 0
    for(let y = 0; y < rows; y++) {
        for(let x = 0; x < cols; x++) {
            let x1 = x*spacing
            let y1 = y*spacing + sin((x + frameCount*0.02)) * 20;
            let x2 = (x+1) * spacing
            let y2 = y * spacing + sin((x + 1 + frameCount*0.02)) * 20;
            line(x1, y1, x2, y2)
        }

    }

}