#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "generator.hpp"
#include <iostream>
#include <vector>

using namespace std;

// 1. Define the game states (Scenes)
enum class AppState { MENU, KEY_HUNTER, DUNGEON, DUAL_ROBOT, CHERRY, PERMUTATION, SUDOKU };

// Helper struct for clickable menu cards
struct MenuCard {
    sf::FloatRect bounds;
    AppState targetState;
};

int main() {
    // Setup wider window to fit the 3x2 grid
    sf::RenderWindow window(sf::VideoMode({1024, 768}), "Brain Tester - C++ Native");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        cerr << "Error: Place arial.ttf in the same folder!" << endl;
        return -1;
    }

    AppState currentState = AppState::MENU;
    SudokuPuzzle currentSudoku; 
    KeyHunterPuzzle currentKeyHunter;
    // You will add the struct instances for the other 4 games here later:
    // DungeonPuzzle currentDungeon; ...

    // Menu layout math
    vector<MenuCard> menuCards;
    vector<sf::RectangleShape> cardShapes;
    vector<sf::Text> cardTitles;
    
    string titles[6] = {"Key Hunter", "Dungeon Survival", "Dual Robot", "Cherry Expedition", "Permutation Puzzle", "Sudoku Master"};
    AppState states[6] = {AppState::KEY_HUNTER, AppState::DUNGEON, AppState::DUAL_ROBOT, AppState::CHERRY, AppState::PERMUTATION, AppState::SUDOKU};
    
    float cardW = 280.0f, cardH = 180.0f;
    float startX = 60.0f, startY = 200.0f, pad = 30.0f;

    for (int i = 0; i < 6; i++) {
        int row = i / 3;
        int col = i % 3;
        float x = startX + col * (cardW + pad);
        float y = startY + row * (cardH + pad);

        sf::RectangleShape card({cardW, cardH});
        card.setPosition({x, y});
        card.setFillColor(sf::Color(20, 30, 60)); // Dark UI card color
        card.setOutlineThickness(2.0f);
        card.setOutlineColor(sf::Color(100, 120, 180, 100));

        sf::Text title(font, titles[i], 22);
        title.setPosition({x + 20.0f, y + 20.0f});
        title.setFillColor(sf::Color::White);

        cardShapes.push_back(card);
        cardTitles.push_back(title);
        menuCards.push_back({card.getGlobalBounds(), states[i]});
    }

    // Main Game Loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Mouse Click Detection
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseBtn->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(mouseBtn->position.x, mouseBtn->position.y);

                    if (currentState == AppState::MENU) {
                        // Check if a card was clicked
                        for (const auto& card : menuCards) {
                            if (card.bounds.contains(mousePos)) {
                                currentState = card.targetState; // Switch Scene
                                
                                // Initialize the backend data for the chosen game
                                if (currentState == AppState::SUDOKU) {
                                    currentSudoku = generateSudoku(EASY);
                                } else if (currentState == AppState::KEY_HUNTER) {
                                    currentKeyHunter = generateKeyHunter(EASY);
                                }
                                // ... initialize others here
                            }
                        }
                    }
                }
            }

            // Return to Menu (Press Escape)
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    currentState = AppState::MENU;
                }
            }
        }

        // ==========================================
        // RENDERING PIPELINE
        // ==========================================
        window.clear(sf::Color(11, 16, 34)); // Main background color

        if (currentState == AppState::MENU) {
            // Draw Header
            sf::Text header(font, "Brain Tester", 48);
            header.setPosition({350.0f, 60.0f});
            header.setFillColor(sf::Color::White);
            window.draw(header);

            // Draw Cards
            for (int i = 0; i < 6; i++) {
                window.draw(cardShapes[i]);
                window.draw(cardTitles[i]);
            }
        } 
        else if (currentState == AppState::SUDOKU) {
            float cellSize = 50.0f;
            float offsetX = 300.0f, offsetY = 150.0f;

            for (int r = 0; r < 9; r++) {
                for (int c = 0; c < 9; c++) {
                    sf::RectangleShape cell({cellSize - 2.0f, cellSize - 2.0f});
                    cell.setPosition({offsetX + c * cellSize, offsetY + r * cellSize});
                    cell.setFillColor(sf::Color(255, 255, 255, 200));
                    window.draw(cell);

                    int val = currentSudoku.puzzle[r][c];
                    if (val != 0) {
                        sf::Text text(font, to_string(val), 24);
                        text.setFillColor(sf::Color::Black);
                        text.setPosition({offsetX + c * cellSize + 15.0f, offsetY + r * cellSize + 10.0f});
                        window.draw(text);
                    }
                }
            }
        }
        else if (currentState == AppState::KEY_HUNTER) {
            float cellSize = 60.0f;
            int R = currentKeyHunter.R;
            int C = currentKeyHunter.C;
            
            // Center the dynamic grid on the 1024x768 screen
            float offsetX = (1024.0f - (C * cellSize)) / 2.0f;
            float offsetY = (768.0f - (R * cellSize)) / 2.0f;

            for (int r = 0; r < R; r++) {
                for (int c = 0; c < C; c++) {
                    sf::RectangleShape cell({cellSize - 2.0f, cellSize - 2.0f});
                    cell.setPosition({offsetX + c * cellSize, offsetY + r * cellSize});
                    
                    char tile = currentKeyHunter.grid[r][c];
                    sf::Color fillColor = sf::Color(40, 53, 72); // Default floor
                    string icon = "";

                    if (tile == '#') {
                        fillColor = sf::Color(10, 14, 26); // Wall
                    } else if (tile == '@') {
                        icon = "P"; // Player
                        fillColor = sf::Color(124, 58, 237, 100);
                    } else if (tile >= 'a' && tile <= 'f') {
                        icon = "K"; // Key
                        fillColor = sf::Color(245, 158, 11, 80);
                    } else if (tile >= 'A' && tile <= 'F') {
                        icon = "D"; // Door / Lock
                        fillColor = sf::Color(244, 63, 94, 80);
                    }

                    cell.setFillColor(fillColor);
                    window.draw(cell);

                    if (!icon.empty()) {
                        sf::Text text(font, icon, 28);
                        text.setFillColor(sf::Color::White);
                        text.setPosition({offsetX + c * cellSize + 20.0f, offsetY + r * cellSize + 10.0f});
                        window.draw(text);
                    }
                }
            }
        }
        // ... (Add render blocks for Dungeon, Robot, Cherry, Permutation)

        window.display();
    }

    return 0;
}