#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

void drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY,
                int32_t radius);

void drawSmileyMouth(SDL_Renderer *renderer, int32_t centerX, int32_t centerY, int32_t radius) ;
int main() {
  // Grab the window
  SDL_Window *window{nullptr};
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized: " << SDL_GetError() << '\n';
  } else {
    std::cout << "SDL video system is ready to go." << '\n';
  }

  // Create Window
  window =
      SDL_CreateWindow("Drawing shapes", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // renderer
  SDL_Renderer *renderer{nullptr};
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Create Rectangle
  SDL_Rect rectangle{100, 100, 200, 200}; // x, y, w, h

  // Filled rect
  SDL_Rect filledRect = {400, 100, 200, 150}; // x, y, width, height

  bool gameIsRunning{true};

  while (gameIsRunning) {
    SDL_Event event;

    // start event loop
    while (SDL_PollEvent(&event)) {
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escaped key pressed\n";
      }
    }

    // clear the screen and change the screen background color
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do drawing here

    // // Draw rectangle
    // This block sets the render draw color to red and draws a rectangle
    // outline
    SDL_SetRenderDrawColor(renderer, 255, 238, 3, 255);
    // SDL_RenderDrawRect(renderer, &rectangle);
    drawCircle(renderer, 400, 300,  100);

    SDL_SetRenderDrawColor(renderer, 255, 238, 3, 255);
    drawCircle(renderer, 370, 270,  20);
    // SDL_RenderFillRect(renderer, &filledRect);
    SDL_SetRenderDrawColor(renderer, 255, 238, 3, 255);
    drawCircle(renderer, 430, 270,  20);

    // Draw circle
    SDL_SetRenderDrawColor(renderer, 255, 238, 0, 255);
    // drawCircle(renderer, 400, 400, 100);
    drawSmileyMouth(renderer,400,320,60);


    SDL_RenderPresent(renderer);
  }

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY,
                int32_t radius) {
  const int32_t diameter{radius * 2};

  // choosing the right most circumference to draw circle
  int32_t x{radius - 1};
  int32_t y{0};
  int32_t tx{1};
  int32_t ty{1};
  int32_t error{tx - diameter};

  while (x >= y) {
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }
    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void drawSmileyMouth(SDL_Renderer *renderer, int32_t centerX, int32_t centerY, int32_t radius) {
    // Draw a curved line representing the mouth
    for (int32_t x = -radius; x <= radius; ++x) {
        // Calculate the corresponding y-coordinate using a quadratic equation
        int32_t y = static_cast<int32_t>(0.6 * sqrt(radius * radius - x * x));

        // Draw the point if it's within the bounds of the mouth
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    }
}
