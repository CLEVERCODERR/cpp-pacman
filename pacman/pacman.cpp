#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int HEIGHT = 10;
const int WIDTH = 20;

class Game {
private:
    vector<string> map;
    int pacmanX, pacmanY;
    int ghostX, ghostY;
    int score;
    bool running;

public:
    Game() {
        map = {
            "####################",
            "#........#.........#",
            "#.####...#...####...#",
            "#.................G#",
            "#.####.#.#####.#...#",
            "#......#.....#....#",
            "#.####.#####.#.#####" ,
            "#........#.........#",
            "#P.................#",
            "####################"
        };

        score = 0;
        running = true;

        // Find initial positions
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (map[y][x] == 'P') {
                    pacmanX = x;
                    pacmanY = y;
                }
                if (map[y][x] == 'G') {
                    ghostX = x;
                    ghostY = y;
                }
            }
        }

        srand(time(nullptr));
    }

    void draw() {
        system("clear"); // use "cls" on Windows
        for (const auto& row : map) {
            cout << row << endl;
        }
        cout << "Score: " << score << endl;
        cout << "Controls: W A S D | Q to quit" << endl;
    }

    void movePacman(char input) {
        int newX = pacmanX;
        int newY = pacmanY;

        if (input == 'w') newY--;
        if (input == 's') newY++;
        if (input == 'a') newX--;
        if (input == 'd') newX++;

        if (map[newY][newX] != '#') {
            if (map[newY][newX] == '.') {
                score += 10;
            }

            map[pacmanY][pacmanX] = ' ';
            pacmanX = newX;
            pacmanY = newY;
            map[pacmanY][pacmanX] = 'P';
        }
    }

    void moveGhost() {
        int direction = rand() % 4;
        int newX = ghostX;
        int newY = ghostY;

        if (direction == 0) newY--;
        if (direction == 1) newY++;
        if (direction == 2) newX--;
        if (direction == 3) newX++;

        if (map[newY][newX] != '#') {
            map[ghostY][ghostX] = ' ';
            ghostX = newX;
            ghostY = newY;
            map[ghostY][ghostX] = 'G';
        }
    }

    void checkCollision() {
        if (pacmanX == ghostX && pacmanY == ghostY) {
            running = false;
        }
    }

    void run() {
        while (running) {
            draw();

            char input;
            cin >> input;
            input = tolower(input);

            if (input == 'q') break;

            movePacman(input);
            moveGhost();
            checkCollision();
        }

        system("clear");
        cout << "GAME OVER!" << endl;
        cout << "Final Score: " << score << endl;
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
