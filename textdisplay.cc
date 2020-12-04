#include "textdisplay.h"

TextDisplay::TextDisplay(size_t n){
    std::vector<char> row;

    // making one row of n dead cells
    for(int i = 0; i < n; ++i){
        row.push_back(DEAD_CELL);
    }

    // making a n by n grid of dead cells
    for (int i = 0; i < n; ++i){
        theDisplay.push_back(row);
    }
}

void TextDisplay::notify( Subject & whoNotified ){
    Info whoNotifiedInfo = whoNotified.getInfo();

    if(whoNotifiedInfo.state == State::Alive){
        theDisplay[whoNotifiedInfo.row][whoNotifiedInfo.col] = ALIVE_CELL;
    }
    else{
        theDisplay[whoNotifiedInfo.row][whoNotifiedInfo.col] = DEAD_CELL;
    }
}

std::string TextDisplay::getName(){
    return END;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for(auto row: td.theDisplay){
        for(auto c: row){
            out << c;
        }

        out << std::endl;
    }
}
