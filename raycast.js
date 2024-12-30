const TILE_SIZE = 32;
const MAP_ROWS = 11;
const MAP_COLS = 15;

const WINDOW_WIDTH = TILE_SIZE * MAP_COLS;
const WINDOW_HEIGHT = TILE_SIZE * MAP_ROWS;

class Map {
    constructor () {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1],
            [1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1],
            [1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        ]
    }

    isPlayerAtWall (x, y)
    {
        if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
            return true;
        let mapGridIndexX = Math.floor(x / TILE_SIZE);
        let mapGridIndexY = Math.floor(y / TILE_SIZE);
        return (this.grid[mapGridIndexY][mapGridIndexX]);
    }

    render ()
    {
        for (let i = 0; i < MAP_ROWS; i++)
        {
            for (let j = 0; j < MAP_COLS; j++)
                {
                    let tileX = j * TILE_SIZE;
                    let tileY = i * TILE_SIZE;
                    let tile_color = (this.grid[i][j] == 1) ? "#222" : "#fff";
                    stroke("#222");
                    fill(tile_color);
                    rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
                }
        }
    }
}

class Player {
    constructor () {
        this.x = WINDOW_WIDTH / 2;
        this.y = WINDOW_HEIGHT / 2;
        this.radius = 10;
        this.turnDirection = 0;
        this.walkDirections = 0;
        this.rotationAngle = Math.PI / 2;
        this.moveSpeed = 2.0;
        this.rotationSpeed = 2 * (Math.PI / 180);

    }
    update ()
    {
        // update player position based on turnDirection amd walkDirection
        this.rotationAngle += this.turnDirection * this.rotationSpeed;
        let moveStep = this.walkDirections * this.moveSpeed;
        let newPositionX = this.x + Math.cos(this.rotationAngle) * moveStep;
        let newPositionY  = this.y + Math.sin(this.rotationAngle) * moveStep;
        if (!grid.isPlayerAtWall(newPositionX, newPositionY))
        {
            this.x = newPositionX;
            this.y = newPositionY;
        }
    }
    render ()
    {
        noStroke();
        fill ("red");
        circle(this.x, this.y, this.radius);
        stroke("red");
        line (
            this.x,
            this.y,
            this.x + Math.cos(this.rotationAngle) * 30,
            this.y + Math.sin(this.rotationAngle) * 30
        );
    }

}

let grid = new Map();
let player = new Player();

function keyPressed ()
{
    if (keyCode == UP_ARROW)
        player.walkDirections += 1;
    else if (keyCode == DOWN_ARROW)
        player.walkDirections -= 1;  
    else if (keyCode == RIGHT_ARROW)
        player.turnDirection += 1;
    else if (keyCode == LEFT_ARROW)
        player.turnDirection -= 1;    
}
function keyReleased ()
{
    if (keyCode == UP_ARROW)
        player.walkDirections = 0;
    else if (keyCode == DOWN_ARROW)
        player.walkDirections = 0;
    else if (keyCode == RIGHT_ARROW)
        player.turnDirection = 0;
    else if (keyCode == LEFT_ARROW)
        player.turnDirection = 0;    
}

function setup()
{
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update()
{
    player.update();
}

function draw()
{
    update();
    grid.render();
    player.render();
}

