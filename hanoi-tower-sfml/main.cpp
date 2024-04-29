#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <vector>

struct Disk {
    sf::RectangleShape rect;
    int size;
};


std::vector<std::stack<Disk>> pegs(3);
int selectedPeg = -1;
Disk heldDisk;
bool isHoldingDisk = false;
bool gameWon = false;
bool showMenu = true;

sf::Font font;


Disk createDisk(int size, sf::Color color) {
    Disk d;
    d.size = size;
    d.rect.setSize(sf::Vector2f(20.f * size, 20.f));
    d.rect.setFillColor(color);
    d.rect.setOrigin(d.rect.getSize().x / 2, d.rect.getSize().y / 2);
    return d;
}


bool checkWinCondition() {
    return pegs[0].empty() && pegs[1].empty() && pegs[2].size() == 4;
}


sf::Text createText(const std::string& str, int fontSize, float x, float y) {
    sf::Text text(str, font, fontSize);
    text.setPosition(x, y);
    return text;
}


void resetGame() {
    pegs = std::vector<std::stack<Disk>>(3);
    pegs[0].push(createDisk(4, sf::Color::Red));
    pegs[0].push(createDisk(3, sf::Color::Green));
    pegs[0].push(createDisk(2, sf::Color::Blue));
    pegs[0].push(createDisk(1, sf::Color::Cyan));
    isHoldingDisk = false;
}


void handleMenuClicks(sf::RenderWindow& window, const sf::Event& event) {
    if (!showMenu) return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int startX = 310, startY = 210;
    int height = 50;
    for (int i = 0; i < 3; ++i) {
        if (mousePos.x >= startX && mousePos.x <= startX + 180 &&
            mousePos.y >= startY + i * height && mousePos.y <= startY + (i + 1) * height) {
            switch (i) {
            case 0: // Start
                gameWon = false;
                showMenu = false;
                resetGame();
                break;
            case 1: // Exit
                window.close();
                break;
            }
        }
    }
}


void drawMenu(sf::RenderWindow& window) {
    if (!showMenu) return;

    sf::RectangleShape menu(sf::Vector2f(200.f, 100.f));
    menu.setPosition(300.f, 200.f);
    menu.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(menu);

    std::string buttonLabels[3] = { "Start", "Exit" };
    for (int i = 0; i < 3; i++) {
        sf::Text text = createText(buttonLabels[i], 20, 310.f, 210.f + i * 50);
        window.draw(text);
    }
}


void draw(sf::RenderWindow& window) {
    if (showMenu) {
        drawMenu(window);
    }
    else {
        sf::RectangleShape base(sf::Vector2f(410.f, 10.f));
        base.setFillColor(sf::Color::Black);
        base.setPosition(190.f, 350.f);
        window.draw(base);

        for (int i = 0; i < 3; ++i) {
            sf::RectangleShape peg(sf::Vector2f(10.f, 150.f));
            peg.setFillColor(sf::Color::Black);
            peg.setPosition(190.f + i * 200.f, 200.f);
            window.draw(peg);

            std::stack<Disk> tempStack;
            while (!pegs[i].empty()) {
                tempStack.push(pegs[i].top());
                pegs[i].pop();
            }

            int count = 0;
            while (!tempStack.empty()) {
                Disk& d = tempStack.top();
                d.rect.setPosition(195.f + i * 200.f, 340.f - count * 30.f);
                window.draw(d.rect);
                pegs[i].push(d);
                tempStack.pop();
                count++;
            }
        }

        if (isHoldingDisk) {
            heldDisk.rect.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            window.draw(heldDisk.rect);
        }
    }
}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower of Hanoi");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    resetGame();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (showMenu) {
                    handleMenuClicks(window, event);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !gameWon) {
                    int x = event.mouseButton.x;
                    int pegIndex = (x - 150) / 200; 
                    if (pegIndex >= 0 && pegIndex < 3) { 
                        if (!isHoldingDisk && !pegs[pegIndex].empty()) {
                            heldDisk = pegs[pegIndex].top();
                            pegs[pegIndex].pop();
                            isHoldingDisk = true;
                            selectedPeg = pegIndex;
                        }
                        else if (isHoldingDisk) {
                            if (pegs[pegIndex].empty() || heldDisk.size < pegs[pegIndex].top().size) {
                                pegs[pegIndex].push(heldDisk);
                                isHoldingDisk = false;
                                if (checkWinCondition()) {
                                    resetGame();
                                    gameWon = true;
                                    showMenu = true;
                                }
                            }
                            else {
                                pegs[selectedPeg].push(heldDisk);
                                isHoldingDisk = false;
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        draw(window);
        window.display();
    }

    return 0;
}
