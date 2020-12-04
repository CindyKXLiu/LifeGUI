#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream> 
#include <vector>
#include "observer.h"
#include "subject.h"
#include "info.h"

class Cell;

class TextDisplay: public Observer {
    const char DEAD_CELL = '_';
    const char ALIVE_CELL = 'X';
    const std::string END = "TD";

    // Grid of characters representing state of the cells. '_' => dead, 'X' => alive
    std::vector<std::vector<char>> theDisplay;

 public: 
    explicit TextDisplay( size_t n );

    // Cell/Grid tells text display that status for a Cell has changed and needs to be updated.
    virtual void notify( Subject & whoNotified ) override;

    // Returns the string "TD".
    virtual std::string getName() override;

    // Outputs the grid of characters.
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
