#define SDL_MAIN_HANDLED
#include "../inc/Window.hpp"
#include <stdio.h>

int main( int argc, char* args[] ){
    Window window;
    window.loop();
    return 0;
}