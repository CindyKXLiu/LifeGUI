#include "graphicdisplay.h"

GraphicDisplay::GraphicDisplay(size_t n){
    // making the display
    if(n > totalWidth){
        w = new Xwindow(n);
        totalWidth = n;
    }
    else{
        w = new Xwindow();
    }

    // making one row of n dead cells
    std::vector<int> row;
    for(int i = 0; i < n; ++i){
        row.push_back(DEAD_CELL);
    }

    // making a n by n grid of dead cells
    for (int i = 0; i < n; ++i){
        graphicGrid.push_back(row);
    }
}

GraphicDisplay::~GraphicDisplay(){
    delete w;
}

void GraphicDisplay::notify(Subject & whoNotified){
    Info whoNotifiedInfo = whoNotified.getInfo();

    if(whoNotifiedInfo.state == State::Alive){
        graphicGrid[whoNotifiedInfo.row][whoNotifiedInfo.col] = ALIVE_CELL;
    }
    else{
        graphicGrid[whoNotifiedInfo.row][whoNotifiedInfo.col] = DEAD_CELL;
    }
}

void GraphicDisplay::print(){
    int dimension = totalWidth/graphicGrid.size();

    for(int r = 0; r < graphicGrid.size(); ++r){
        for(int c = 0; c < graphicGrid.size(); ++c){
            w->fillRectangle(dimension * r, dimension * c, dimension, dimension, graphicGrid[r][c]);
        }
    }
}

std::string GraphicDisplay::getName(){}
