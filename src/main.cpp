#include "SDL2/SDL_main.h"
#include "SDL2/SDL.h"
#include <vector>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 10;

class GameOfLife {
public:
    GameOfLife(int width, int height) : width(width), height(height) {
        grid.resize(height / CELL_SIZE, std::vector<bool>(width / CELL_SIZE, false));
    }

    void toggleCell(int x, int y) {
        grid[y][x] = !grid[y][x];
    }

    void update() {
        std::vector<std::vector<bool>> newGrid = grid;
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[y].size(); ++x) {
                int aliveNeighbors = countAliveNeighbors(x, y);
                if (grid[y][x]) {
                    newGrid[y][x] = (aliveNeighbors == 2 || aliveNeighbors == 3);
                }
                else {
                    newGrid[y][x] = (aliveNeighbors == 3);
                }
            }
        }
        grid = newGrid;
    }

    void draw(SDL_Renderer* renderer) {
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x]) {
                    SDL_Rect rect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }

private:
    int width, height;
    std::vector<std::vector<bool>> grid;

    int countAliveNeighbors(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < grid[0].size() && ny >= 0 && ny < grid.size() && grid[ny][nx]) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GameOfLife game(WIDTH, HEIGHT);
    bool running = true;
    bool paused = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x / CELL_SIZE;
                int y = event.button.y / CELL_SIZE;
                game.toggleCell(x, y);
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                paused = !paused; // Переключение паузы
            }
        }

        if (!paused) {
            game.update(); // Обновление состояния игры
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Очистка экрана
        SDL_RenderClear(renderer);
        game.draw(renderer); // Отрисовка игрового поля
        SDL_RenderPresent(renderer); // Обновление экрана

        SDL_Delay(100); // Задержка для управления скоростью игры
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

