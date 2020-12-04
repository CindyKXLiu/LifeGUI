#include "grid.h" 

// private functions
void Grid::addNeighbours(Cell &cell, const int r, const int c, const int upperBound){
    if (r >= 0 && r < upperBound && c >=0 && c < upperBound){
        cell.attach(&(theGrid[r][c]));
    }
}

bool Grid::inRange(const int r, const int c){
    return r >= 0 && r < theGrid.size() && c >=0 && c < theGrid.size();
}

// public functions
Grid::~Grid(){
    delete td;
}

void Grid::printCellNeighbours(){
    for(auto row : theGrid){
        for(auto cell : row){
            std::cout << cell.getName() << ": " << cell.getObserverNames() << std::endl;
        }
    }
}

void Grid::init(int n){ 
    if(n < 1){
        throw std::invalid_argument{GRID_SIZE_ERR};
    }

    // set up graphic
    delete graphic;
    graphic = new GraphicDisplay{n};

    // set up an n x n grid
    delete td;
    td = new TextDisplay{n};

    // delete all current cells on theGrid
    theGrid.clear();

    // make new cells
    for(int r = 0; r < n; ++r){
        std::vector<Cell> row;
       
        // making a row of cells
        for(int c = 0; c < n; ++c){
            Cell cell{r,c};
            row.push_back(cell);
        }

        theGrid.push_back(row);
    }

    // attach observers (neighbours and textdisplay) to each cell
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            theGrid[r][c].attach(td);
            theGrid[r][c].attach(graphic);
            addNeighbours(theGrid[r][c], r+1, c+1, n);
            addNeighbours(theGrid[r][c], r+1, c-1, n);
            addNeighbours(theGrid[r][c], r-1, c+1, n);
            addNeighbours(theGrid[r][c], r-1, c-1, n);
            addNeighbours(theGrid[r][c], r, c-1, n);
            addNeighbours(theGrid[r][c], r, c+1, n);
            addNeighbours(theGrid[r][c], r-1, c, n);
            addNeighbours(theGrid[r][c], r+1, c, n);
        }
    }
}

void Grid::turnOn( int r, int c ){
    if(inRange(r,c)){
        theGrid[r][c].setLiving();
        td->notify(theGrid[r][c]);
        graphic->notify(theGrid[r][c]);
    }
    else{
        std::string ERROR_MSG = "ERROR: coordinates (" + std::to_string(r) + "," + std::to_string(c) 
            + ") are not in the range 0 to " + std::to_string(theGrid.size()-1);
        throw std::invalid_argument{ERROR_MSG};
    }
}

void Grid::tick(){
    for(int r = 0; r < theGrid.size(); ++r){
        for(int c = 0; c < theGrid.size(); ++c){
            theGrid[r][c].broadcastIfAlive();
        }
    }

    for(int r = 0; r < theGrid.size(); ++r){
        for(int c = 0; c < theGrid.size(); ++c){
            theGrid[r][c].recalculate();
            td->notify(theGrid[r][c]);
            graphic->notify(theGrid[r][c]);
        }
    }

    for(int r = 0; r < theGrid.size(); ++r){
        for(int c = 0; c < theGrid.size(); ++c){
            theGrid[r][c].reset();
        }
    }
}

std::ostream & operator<<( std::ostream & out, const Grid & g ){
    out << *(g.td);
    g.graphic->print();
}
