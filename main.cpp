#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_render.h"

#include <SDL.h>

#include "src/board/board.cpp"
#include "SDL_video.h"
#include "vector_3d.hpp"

#include "src/render/line.cpp"

#include "src/render/camera.cpp"
class Framework{
public:
    Framework(int height_, int width_): height(height_), width(width_) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
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

    void draw_cube(Cube c, Camera &camera, int direction) {
        const Vec3d p1 = c.pos;
        const Vec3d p2 = c.pos + Vec3d{10, 0, 0};
        const Vec3d p3 = c.pos + Vec3d{10, 10, 0};
        const Vec3d p4 = c.pos + Vec3d{0, 10 ,0};

        const Vec3d p5 = c.pos + Vec3d{0, 0, 10};
        const Vec3d p6 = c.pos + Vec3d{10, 0, 10};
        const Vec3d p7 = c.pos + Vec3d{10, 10, 10};
        const Vec3d p8 = c.pos + Vec3d{0, 10, 10};

        std::vector<Line> lines = {
            Line(p1, p2),
            Line(p2, p3),
            Line(p3, p4),
            Line(p4, p1),

            Line(p5, p6),
            Line(p6, p7),
            Line(p7, p8),
            Line(p8, p5),

            Line(p1, p5),
            Line(p2, p6),
            Line(p3, p7),
            Line(p4, p8),
        };

        for (auto &l : lines) {
            draw_line(l, camera, direction);
        }
    }


    void draw_line(Line &l, Camera &c, int direction) {
        float d = 500.f;
        Vec3d cameraPos = c.getPos(direction);
        int offset = c.getOffset();

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

        int offsetX;
        int offsetY;

        if (direction == 0) {
            offsetX = -offset * 2;
            offsetY = -offset * 2;
        }
        else if (direction == 1) {
            offsetX = offset * 2;
            offsetY = -offset * 2;
        }
        else if (direction == 2) {
            offsetX = offset * 2;
            offsetY = offset * 2;
        }
        else if (direction == 3) {
            offsetX = -offset * 2;
            offsetY = offset * 2;
        }
        else {
            offsetX = -offset * 2;
            offsetY = -offset * 2;
        }

        SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
    }

    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
private:
    int height;
    int width;
};



int main() {

    std::vector<Line> lines;
    
    Board b;

    Cube cube(Color(255, 255, 255), {0,0,0});

    b.addCube(0, 0, 0, cube);

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
                c.changeHeight(1);
            }
            if (event.wheel.y < 0) {
                c.changeHeight(-1);
            }
        }

        // if (event.type == SDL_MOUSEMOTION) {
        //     SDL_SetWindowTitle(
        //         fw.window, 
        //         (std::to_string(event.motion.x ) + 
        //                " " + std::to_string(event.motion.y))
        //                .c_str()
        //     );
        //     // std::cout << "move";
        // }

        if (keys[SDLK_UP] || keys[SDLK_w]) {
            std::cout << "up\n";
            c.changeOffset(1);
        }
        if (keys[SDLK_DOWN] || keys[SDLK_s]) {
            std::cout << "down\n";
            c.changeOffset(-1);
        }

        SDL_SetRenderDrawColor(fw.renderer, 0, 0, 0, 0);
        SDL_RenderClear(fw.renderer);

        SDL_SetRenderDrawColor(fw.renderer, 255, 255, 255, 255);

        for (int i = 0; i < lines.size(); i++) {
            fw.draw_line(lines[i], c, cameraPos);
        }

        fw.draw_cube(cube, c, cameraPos);

        SDL_RenderPresent(fw.renderer);

        SDL_PollEvent(&event);
    }

    return 0;
}
