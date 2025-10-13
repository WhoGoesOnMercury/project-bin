var intRand = Math.floor(Math.random() * 255);
document.getElementById('randomNumber').textContent = intRand;

const intRandBinary = [0, 0, 0, 0, 0, 0, 0, 0];

function intToBinary() {
    var i = 0;
    while (intRand != 0 && i != 8) {
        if (intRand - 128 >= 0) {
            intRand -= 128;
            intRandBinary[0] = 1;
        } else if (intRand - 64 >= 0) {
            intRand -= 64;
            intRandBinary[1] = 1;
        } else if (intRand - 32 >= 0) {
            intRand -= 32;
            intRandBinary[2] = 1;
        } else if (intRand - 16 >= 0) {
            intRand -= 16;
            intRandBinary[3] = 1;
        } else if (intRand - 8 >= 0) {
            intRand -= 8;
            intRandBinary[4] = 1;
        } else if (intRand - 4 >= 0) {
            intRand -= 4;
            intRandBinary[5] = 1;
        } else if (intRand - 2 >= 0) {
            intRand -= 2;
            intRandBinary[6] = 1;
        } else if (intRand - 1 >= 0) {
            intRand -= 1;
            intRandBinary[7] = 1;
        }
        i++;
    }
}

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const cellSize = 5;
const numRows = canvas.height / cellSize;
const numCols = canvas.width / cellSize;
let cells = [[]];
cells[0][Math.floor(numCols / 2)] = 1;
let generation = 0;

function drawCells() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = "#f8f8f8";
    for (let row = 0; row < generation; row++) {
        for (let col = 0; col < numCols; col++) {
            if (cells[row][col]) {
                ctx.fillRect(col * cellSize, row * cellSize, cellSize, cellSize);
            }
        }
    }
}

function updateCells() {
    cells.push(new Array(numCols).fill(0));
    for (let i = 0; i < numCols; i++) {
        let left = cells[generation][i - 1] || 0;
        let center = cells[generation][i] || 0;
        let right = cells[generation][i + 1] || 0;
        cells[generation + 1][i] = applyRule(left, center, right);
    }
    generation++;
}

function applyRule(left, center, right) {
    if (left === 1 && center === 1 && right === 1) return intRandBinary[0];
    if (left === 1 && center === 1 && right === 0) return intRandBinary[1];
    if (left === 1 && center === 0 && right === 1) return intRandBinary[2];
    if (left === 1 && center === 0 && right === 0) return intRandBinary[3];
    if (left === 0 && center === 1 && right === 1) return intRandBinary[4];
    if (left === 0 && center === 1 && right === 0) return intRandBinary[5];
    if (left === 0 && center === 0 && right === 1) return intRandBinary[6];
    if (left === 0 && center === 0 && right === 0) return intRandBinary[7];
}

function runSimulation() {
    updateCells();
    drawCells();
    requestAnimationFrame(runSimulation);
}

intToBinary();
document.getElementById('binaryRepresentation').textContent = intRandBinary.join('');
runSimulation();
