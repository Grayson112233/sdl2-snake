#include "graphics.h"

// STATIC MEMBERS

const int Graphics::WIDTH = SQUARE_SIZE * GRID_SIZE;
const int Graphics::HEIGHT = WIDTH;

// PRIVATE HELPER FUNCTIONS

bool Graphics::init_sdl() {

    // Initialize SDL_video
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("Error: Failed to init SDL2: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL Window
    window = SDL_CreateWindow(
        "SDL2 Game",                  // window title
        SDL_WINDOWPOS_UNDEFINED,      // initial x position
        SDL_WINDOWPOS_UNDEFINED,      // initial y position
        WIDTH,                        // width, in pixels
        HEIGHT,                       // height, in pixels
        SDL_WINDOW_OPENGL             // flags - see below
    );
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }

    // Initialize renderer with flags
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("Could not init renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;

}

// Type: 0 = snake, 1 = apple
void Graphics::render_square(int x, int y, int type) {

    SDL_Rect rect = {x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};

    if (type == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);    
    } else if (type == 1) {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    }

    SDL_RenderFillRect(renderer, &rect);

    if (type == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    } else if (type == 1) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    }

    SDL_RenderDrawRect(renderer, &rect);

}

// PUBLIC FUNCTIONS

Graphics::Graphics() {

	init_sdl();

}

void Graphics::clear_screen() {

    // Clear the screen with a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

};

void Graphics::present_renderer() {

    SDL_RenderPresent(renderer);

}

void Graphics::render_segments(segment head, segment *tail, int num_segments) {

    render_square(head.x, head.y, 0);
    for(int i = 0; i < num_segments; i++) {
        render_square(tail[i].x, tail[i].y, 0);
    }

}

void Graphics::render_apple(segment apple) {
    render_square(apple.x, apple.y, 1);
}

int Graphics::get_width() {
    return WIDTH;
}

int Graphics::get_height() {
    return HEIGHT;
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
}