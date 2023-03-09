#include <iostream>
#include "src/renderer.cpp"
#include "include/sphere.h"

#include <SDL.h>

class Framework{
public:
    // Contructor which initialize the parameters.
    Framework(int height_, int width_): height(height_), width(width_){
        SDL_Init(SDL_INIT_VIDEO);       // Initializing SDL as Video
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);      // setting draw color
        SDL_RenderClear(renderer);      // Clear the newly created window
        SDL_RenderPresent(renderer);    // Reflects the changes done in the
                                        //  window.
    }

    // Destructor
    ~Framework(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_circle(int center_x, int center_y, int radius_){
        // Setting the color to be RED with 100% opaque (0% trasparent).
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Drawing circle
        for(int x=center_x-radius_; x<=center_x+radius_; x++){
            for(int y=center_y-radius_; y<=center_y+radius_; y++){
                if((std::pow(center_y-y,2)+std::pow(center_x-x,2)) <= 
                    std::pow(radius_,2)){
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        // Show the change on the screen
        SDL_RenderPresent(renderer);
    }

private:
    int height;     // Height of the window
    int width;      // Width of the window
    SDL_Renderer *renderer = NULL;      // Pointer for the renderer
    SDL_Window *window = NULL;      // Pointer for the window
};




// void renderPointEzra(sf::RenderWindow& window, Sphere s) {
//   sf::CircleShape shape(20.0f);
//   shape.setFillColor(s.getColor());
// }

int main() {
    Framework fw(200, 400);

    fw.draw_circle(200, 100, 50);

    SDL_Event event;    // Event variable

    while(!(event.type == SDL_QUIT)){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }

    return 0;
}
