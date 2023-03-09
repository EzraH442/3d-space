#include <iostream>
#include "SDL_render.h"

#include <SDL.h>
#include <vector>

#include "vector_3d.hpp"

#include "src/render/line.cpp"

int height = 500;
int length = 100;
int offset = 50;

Vec3d cameraPosNW = {length + offset, length + offset, height};
Vec3d cameraPosNE = {0 - offset, length + offset, height};
Vec3d cameraPosSE = {0 - offset, 0 - offset, height};
Vec3d cameraPosSW = {length + offset, 0 - offset, height};

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

    void draw_line(Line &l) {
        std::cout << "draw line";
        // get start position
        
        float d = 500.f;

        Vec3d startTransformed = l.start - cameraPosSE;
        Vec3d endTransformed = l.end - cameraPosSE;

        std::cout << "line from " << startTransformed << " to " << endTransformed;

        float scaleStart = d / startTransformed.z;
        float scaleEnd = d / endTransformed.z;

        float x1 = startTransformed.x * scaleStart + 300;
        float y1 = startTransformed.y * scaleStart + 300;

        float x2 = endTransformed.x * scaleEnd + 300;
        float y2 = endTransformed.y * scaleEnd + 300;

        std::cout << " projected to (" << x1 << ", " << y1 << ") -->" << "(" << x2 << ", " << y2 << ")" << "\n";

        //draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderPresent(renderer);
    }

private:
    int height;
    int width;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
};

int main() {

    std::vector<Line> lines;

    for (int i = 0; i < 11; i++) {
        lines.push_back(Line({0,i*10,0}, {100,i*10,0}));
    }

    for (int i = 0; i < 11; i++) {
        lines.push_back(Line({i*10, 0 ,0}, {i*10, 100, 0}));
    }

    int boardHeight = 200;
    lines.push_back(Line({0,0,0}, {0,0,boardHeight}));
    lines.push_back(Line({100,0,0}, {100,0,boardHeight}));
    lines.push_back(Line({0,100,0}, {0,100,boardHeight}));
    lines.push_back(Line({100,100,0}, {100,100,boardHeight}));

    Framework fw(800, 800);

    for (int i = 0; i < lines.size(); i++) {
        std::cout << i << " ";
        fw.draw_line(lines[i]);
    }

    SDL_Event event;

    while(!(event.type == SDL_QUIT)){
        std::cout << "";
        SDL_Delay(10);
        SDL_PollEvent(&event);  // Catching the poll event.
    }

    return 0;
}
