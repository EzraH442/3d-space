#include <iostream>
#include <vector>
#include <unordered_map>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_render.h"

#include <SDL.h>

#include "vector_3d.hpp"

#include "src/render/line.cpp"

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

    void draw_line(Line &l, Vec3d cameraPos) {
        // std::cout << "draw line";
        // get start position
        
        float d = 500.f;

        Vec3d startTransformed = l.start - cameraPos;
        Vec3d endTransformed = l.end - cameraPos;

        // std::cout << "line from " << startTransformed << " to " << endTransformed;

        float scaleStart = d / startTransformed.z;
        float scaleEnd = d / endTransformed.z;

        float x1 = startTransformed.x * scaleStart + 300;
        float y1 = startTransformed.y * scaleStart + 300;

        float x2 = endTransformed.x * scaleEnd + 300;
        float y2 = endTransformed.y * scaleEnd + 300;

        // std::cout << " projected to (" << x1 << ", " << y1 << ") -->" << "(" << x2 << ", " << y2 << ")" << "\n";

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    SDL_Renderer *renderer = NULL;
private:
    int height;
    int width;
    SDL_Window *window = NULL;
};


#include "src/render/camera.cpp"

int main() {

    std::vector<Line> lines;
    
    int cameraPos = 0;
    Camera c;

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


    std::unordered_map<int, bool> keys;
    std::unordered_map<int, bool> mouse;

    SDL_Event event;

    while(!(event.type == SDL_QUIT)){
        SDL_Delay(50);

        if (event.type == SDL_KEYDOWN) {
            keys[event.key.keysym.sym] = true;
        }
        if (event.type == SDL_KEYUP) {
            keys[event.key.keysym.sym] = false;

            int key = event.key.keysym.sym; 
            if (key == SDLK_RIGHT || key == SDLK_d) {
                cameraPos = (cameraPos + 1) % 4;
            }
            if (key == SDLK_LEFT || key == SDLK_a) {
                cameraPos = (cameraPos + 3) % 4;
            }
        }

        if (event.type == SDL_MOUSEWHEEL) {
            if (event.wheel.y > 0) {
                c.changeHeight(10);
            }
            if (event.wheel.y < 0) {
                c.changeHeight(-10);
            }
        }

        if (keys[SDLK_UP] || keys[SDLK_w]) {
            std::cout << "up\n";
            c.changeOffset(10);
        }
        if (keys[SDLK_DOWN] || keys[SDLK_s]) {
            std::cout << "down\n";
            c.changeOffset(-10);
        }

        SDL_SetRenderDrawColor(fw.renderer, 0, 0, 0, 0);
        SDL_RenderClear(fw.renderer);

        SDL_SetRenderDrawColor(fw.renderer, 255, 255, 255, 255);

        for (int i = 0; i < lines.size(); i++) {
            fw.draw_line(lines[i], c.getPos(cameraPos));
        }

        SDL_RenderPresent(fw.renderer);

        SDL_PollEvent(&event);
    }

    return 0;
}
