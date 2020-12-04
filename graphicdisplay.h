#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H
#include <X11/Xlib.h>
#include <vector>
#include "observer.h"
#include "window.h"
#include "info.h"
#include "subject.h"

class GraphicDisplay: public Observer {
    const int DEAD_CELL = Xwindow::White;
    const int ALIVE_CELL = Xwindow::Black;
    
    std::vector <std::vector <int>> graphicGrid; // stores the state of the cell as int (which corresponds to colours)
    Xwindow *w = nullptr;
    int totalWidth = 500;

    public:
        GraphicDisplay(size_t n);
        ~GraphicDisplay() override;
        void notify( Subject & whoNotified ) override;  // updates graphicGrid
        void print(); // make changes the cells on the display (either turn them white or black)
        std::string getName() override;
};

#endif
