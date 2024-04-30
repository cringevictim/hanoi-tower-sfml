#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <vector>
#include <random>


struct Disk {
    sf::RectangleShape rect;
    int size;
};

int num_disks = 4; // default

std::vector<std::stack<Disk>> pegs(3);
int selected_peg = -1;
Disk held_disk;
bool is_holding_disk = false;
bool game_won = false;
bool show_menu = true;


sf::Font font;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 255);

void autoSolve(sf::RenderWindow& window);

Disk create_disk(int size) {
    Disk d;
    d.size = size;
    d.rect.setSize(sf::Vector2f(20.f * size, 20.f));
    d.rect.setFillColor(sf::Color(distrib(gen), distrib(gen), distrib(gen)));
    d.rect.setOrigin(d.rect.getSize().x / 2, d.rect.getSize().y / 2);
    return d;
}


void log(std::string text) {
    std::cout << "LOG: " << text << std::endl;
}

void log_num(std::string text, int num) {
    std::cout << "LOG: " << text << num << std::endl;
}

bool check_win_condition() {
    return pegs[0].empty() && pegs[1].empty() && pegs[2].size() == num_disks;
}


sf::Text create_text(const std::string& str, int font_size, float x, float y) {
    sf::Text text(str, font, font_size);
    text.setPosition(x, y);
    return text;
}


void reset_game() {
    pegs = std::vector<std::stack<Disk>>(3);
    for (int i = num_disks; i > 0; --i) {
        pegs[0].push(create_disk(i));
    }
    is_holding_disk = false;
}

void add_game_buttons(sf::RenderWindow& window) {
    sf::RectangleShape menu(sf::Vector2f(213.f, 65.f));
    menu.setPosition(45.f, 445.f);
    menu.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(menu);

    std::string buttons[] = { "Auto (Console Output)", "Back" };
    for (int i = 0; i < 2; i++) {
        sf::Text text = create_text(buttons[i], 20, 50.f, 450.f + i * 30);
        window.draw(text);
    }
}



void handle_game_button_clicks(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if (mouse_pos.x >= 45 && mouse_pos.x <= 260) {
        if (mouse_pos.y >= 450 && mouse_pos.y <= 470) { // "Tip"
            log("[Auto] button was triggered");
            if (!is_holding_disk && pegs[0].size() == num_disks) autoSolve(window);
        }
        else if (mouse_pos.y >= 480 && mouse_pos.y <= 500) { // "Auto"
            log("[Back] button was triggered");
            show_menu = true;
            game_won = false;
            reset_game();
        }
    }
}

void handle_menu_clicks(sf::RenderWindow& window, const sf::Event& event) {
    if (!show_menu) return;

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int start_x = 310, start_y = 210;
    int height = 50;
    for (int i = 0; i < 2; ++i) {
        if (mouse_pos.x >= start_x && mouse_pos.x <= start_x + 180 &&
            mouse_pos.y >= start_y + i * height && mouse_pos.y <= start_y + (i + 1) * height) {
            switch (i) {
            case 0: // Start
                log("[Start] button was triggered");
                game_won = false;
                show_menu = false;
                reset_game();
                break;
            case 1: // Exit
                log("[Exit] button was triggered");
                window.close();
                break;
            }
        }
    }


    if (mouse_pos.x >= start_x && mouse_pos.x <= start_x + 180) {
        if (mouse_pos.y >= 360 && mouse_pos.y <= 410) { // "+ Disks"
            if (num_disks < 6) num_disks++;
            log("[+ Disks] button was triggered");
        }
        else if (mouse_pos.y >= 410 && mouse_pos.y <= 460) { // "- Disks"
            if (num_disks > 3) num_disks--;
            log("[- Disks] button was triggered");
        }
    }
}



void draw_menu(sf::RenderWindow& window) {
    if (!show_menu) return;

    sf::RectangleShape menu(sf::Vector2f(200.f, 250.f));
    menu.setPosition(300.f, 200.f);
    menu.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(menu);

    sf::RectangleShape disk_control_panel(sf::Vector2f(180.f, 100.f));
    disk_control_panel.setPosition(310.f, 310.f);
    disk_control_panel.setFillColor(sf::Color(100, 100, 100, 150));
    window.draw(disk_control_panel);

    std::string button_labels[] = { "Start", "Exit", "+ Disks", "- Disks" };
    for (int i = 0; i < 2; i++) {
        sf::Text text = create_text(button_labels[i], 20, 310.f, 210.f + i * 50);
        window.draw(text);
    }


    sf::Text plus_text = create_text("+ Disks", 20, 310.f, 360.f);
    sf::Text minus_text = create_text("- Disks", 20, 310.f, 410.f);
    window.draw(plus_text);
    window.draw(minus_text);


    sf::Text disk_count_text = create_text("Disks: " + std::to_string(num_disks), 20, 310.f, 310.f);
    window.draw(disk_count_text);
}


void draw(sf::RenderWindow& window) {
    if (show_menu) {
        draw_menu(window);
    }
    else {
        add_game_buttons(window);

        sf::RectangleShape base(sf::Vector2f(410.f, 10.f));
        base.setFillColor(sf::Color::Black);
        base.setPosition(190.f, 350.f);
        window.draw(base);

        for (int i = 0; i < 3; ++i) {
            sf::RectangleShape peg(sf::Vector2f(10.f, 150.f));
            peg.setFillColor(sf::Color::Black);
            peg.setPosition(190.f + i * 200.f, 200.f);
            window.draw(peg);

            std::stack<Disk> temp_stack;
            while (!pegs[i].empty()) {
                temp_stack.push(pegs[i].top());
                pegs[i].pop();
            }

            int count = 0;
            while (!temp_stack.empty()) {
                Disk& d = temp_stack.top();
                d.rect.setPosition(195.f + i * 200.f, 340.f - count * 30.f);
                window.draw(d.rect);
                pegs[i].push(d);
                temp_stack.pop();
                count++;
            }
        }

        if (is_holding_disk) {
            held_disk.rect.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            window.draw(held_disk.rect);
        }
    }
    // Ensure buttons are always drawn over the game scene
}

void moveDisk(int n, int from_peg, int to_peg, int aux_peg, sf::RenderWindow& window, std::vector<std::stack<Disk>>& pegs_local) {
    if (n == 1) {
        std::cout << "Move disk 1 from peg " << from_peg << " to peg " << to_peg << std::endl;
        pegs_local[to_peg].push(pegs_local[from_peg].top());
        pegs_local[from_peg].pop();
        return;
    }
    moveDisk(n - 1, from_peg, aux_peg, to_peg, window, pegs_local);
    std::cout << "Move disk " << n << " from peg " << from_peg << " to peg " << to_peg << std::endl;
    pegs_local[to_peg].push(pegs_local[from_peg].top());
    pegs_local[from_peg].pop();
    moveDisk(n - 1, aux_peg, to_peg, from_peg, window, pegs_local);
}

// Integration with SFML (assume this function is called when "Auto" button is pressed)
void autoSolve(sf::RenderWindow& window) {
    std::vector<std::stack<Disk>> pegs_local = pegs;
    moveDisk(num_disks, 0, 2, 1, window, pegs_local); // Move disks from peg 0 to peg 2 using peg 1 as auxiliary
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower of Hanoi");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    reset_game();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (show_menu) {
                    handle_menu_clicks(window, event);
                }
                else {
                    handle_game_button_clicks(window, event);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !game_won && !show_menu && event.mouseButton.y < 400) {
                    int x = event.mouseButton.x;
                    int peg_index = (x - 150) / 200;
                    if (peg_index >= 0 && peg_index < 3) {
                        if (!is_holding_disk && !pegs[peg_index].empty()) {
                            held_disk = pegs[peg_index].top();
                            pegs[peg_index].pop();
                            is_holding_disk = true;
                            log_num("Disk was picked up from peg ", peg_index);
                            selected_peg = peg_index;
                        }
                        else if (is_holding_disk) {
                            if (pegs[peg_index].empty() || held_disk.size < pegs[peg_index].top().size) {
                                pegs[peg_index].push(held_disk);
                                log_num("Disk was putt down on peg ", peg_index);
                                is_holding_disk = false;
                                if (check_win_condition()) {
                                    reset_game();
                                    game_won = true;
                                    show_menu = true;
                                }
                            }
                            else {
                                pegs[selected_peg].push(held_disk);
                                is_holding_disk = false;
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