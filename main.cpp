#include <iostream>
#include "SDL_render.h"

#include <SDL.h>

class Framework{
public:
    Framework(int height_, int width_): height(height_), width(width_) {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    ~Framework() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_square(int x, int y, int w, int h) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for (int i = x; i < w+x; i++) {
            for (int j = y; j < y+h; j++) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }

        SDL_RenderPresent(renderer);
    }

private:
    int height;
    int width;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
};


#include "pieces/z_piece.hpp"

int main() {
    Framework fw(800, 800);

    fw.draw_square(200, 100, 50, 50);

    SDL_Event event;

    z_piece t = z_piece();

    t.log();

    // while(!(event.type == SDL_QUIT)){
    //     SDL_Delay(10);
    //     SDL_PollEvent(&event);  // Catching the poll event.
    // }

    return 0;
}
