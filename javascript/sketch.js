let cols, rows;
let spacing = 30;
let zoff = 0;

function setup() {
    createCanvas(windowWidth, windowHeight);
    cols = floor(width / spacing);
    rows = floor(height / spacing);
    stroke(100);
    noFill()
}

function draw() {
    background(0)
    let yoff = 0
    for(let y = 0; y < rows-1; y++) {
        let xoff = 0
        for(let x = 0; x < cols; x++) {
            // generate grid, draw two triangles
            // top left corner
            let x1 = x * spacing
            let y1 = y * spacing + noise(xoff, yoff, zoff)*50;

            // top right corner
            let x2 = (x+1) * spacing;
            let y2 = y * spacing + noise(xoff+0.1, yoff, zoff)*50;

            // bottom left corner
            let x3 = x * spacing;
            let y3 = (y+1) * spacing + noise(xoff, yoff+0.1, zoff)*50;

            // bottom right corner
            let x4 = (x+1) * spacing;
            let y4 = (y+1) * spacing + noise(xoff + 0.1, yoff+0.1, zoff)*50;

            // draw two triangles, forming quad
            triangle(x1, y1, x2, y2, x4, y4);
            triangle(x1, y1, x4, y4, x3, y3);
            xoff += 0.15;
        }
        yoff += 15;
    }
    zoff += 0.01;
}