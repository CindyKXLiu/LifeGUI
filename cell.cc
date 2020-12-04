#include "cell.h"

Cell::Cell(size_t r, size_t c)
    : r{r}, c{c}, numAliveNeighbours{DEFAULT_ALIVE}, state{State::Dead} {}

void Cell::setLiving(){
    state = State::Alive;
}

void Cell::reset(){
    numAliveNeighbours = DEFAULT_ALIVE;
}

std::string Cell::getName(){
    std::string name = "(" + std::to_string(this->r) + "," + std::to_string(this->c) + ")";
    return name; 
}

void Cell::broadcastIfAlive(){
    if(state == State::Alive){
        notifyObservers();
    }
}

void Cell::notify( Subject & whoNotified ){
    ++numAliveNeighbours;
}

void Cell::recalculate(){
    if(numAliveNeighbours < LOWER_BOUND || numAliveNeighbours > UPPER_BOUND){
        state = State::Dead;
    }
    else if(numAliveNeighbours == REVIVAL){
        state = State::Alive;
    }
}

Info Cell::getInfo() const{
    return Info{state, r, c};
}
