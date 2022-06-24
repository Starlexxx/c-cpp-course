#include <iostream>
#include <algorithm>

#include "game.h"

#define MOVE 0
#define FIGHT 1
#define THROW 2
#define PICK 3
#define FINISH -1

int Game::start_moving(std::string action) {
    cur_map->kill_element(player->get_position());

    if (action == "move left") {
        player->move_player({x:-1, y:0});
    }
    if (action == "move right") {
        player->move_player({x:1, y:0});
    }
    if (action == "move down") {
        player->move_player({x:0, y:-1});
    }
    if (action == "move up") {
        player->move_player({x:0, y:1});
    }

    if (cur_map->get_enemy(player->get_position()) == NULL && cur_map->get_item(player->get_position()) == NULL) {
        std::cout << "moved\n";
        return MOVE;
    }

    if (cur_map->get_enemy(player->get_position()) != NULL) {
        std::shared_ptr<Enemy> enemy = cur_map->get_enemy(player->get_position());
        std::cout << enemy->get_name() << " found, " << enemy->get_HP() << " hp" << std::endl;
        return FIGHT;
    } else {
        std::shared_ptr<Item> item = cur_map->get_item(player->get_position());
        std::cout << item->get_name() << " found" << std::endl;
        return PICK;
    }
}

int Game::pick_item(position_t pos) {
    std::shared_ptr<Item> ptr = cur_map->get_item(pos);
    std::shared_ptr<Item> item  = std::make_shared<Item>(ptr->get_name(), ptr->get_position(), ptr->get_WGT(), ptr->get_ARM());
    if (item->get_WGT() <= (player->get_max_WGT() - player->get_WGT())) {
        player->add_item(item);
        cur_map->kill_element(pos);
        std::cout << "clothes worn" << std::endl;
        return MOVE;
    }
    return FINISH;
}

int Game::start_fighting() {
    std::shared_ptr<Enemy> enemy = cur_map->get_enemy(player->get_position());
    player->fight(enemy);
    if (player->get_HP() <= 0) {
        return FINISH;
    }

    if (enemy->get_HP() <= 0) {
        std::cout << "enemy killed" << std::endl;
        cur_map->kill_element(enemy->get_position());
        return MOVE;
    }
    std::cout << "enemy kicked. Enemy hp: " << enemy->get_HP() << std::endl;
    return FIGHT;
}

int Game::get_action(std::vector<std::string> supported_actions) {
    std::string action = "";
    std::getline(std::cin, action);
    if (action == "") {
        state = FINISH;
        return FINISH;
    }
    std::cout << std::endl;

    if (std::find(supported_actions.begin(), supported_actions.end(), action) == supported_actions.end()) {
        std::cout << "Invalid action. Try again:\n > ";
        return get_action(supported_actions);
    }

    if (action == "kick enemy") {
        return start_fighting();
    }
    if (action.find("pick") != std::string::npos) {
        return pick_item(player->get_position());
    }
    if (action.find("throw") != std::string::npos) {
        std::set <std::shared_ptr<Item>> items = player->get_items();
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (action.find((*it)->get_name()) != std::string::npos) {
                std::cout << "the " << (*it)->get_name() << " is thrown out" << std::endl;
                player->throw_item(*it);
                break;
            }
        }
        return THROW;
    }
    return start_moving(action);
}

std::vector<std::string> Game::print_instructions() {
    std::vector<std::string> supported_actions;
    position_t pos = player->get_position();
    std::cout << "Supported actions:\n";
    if (state == FIGHT) {
        std::cout << " * kick enemy\n";
        if (version) {
            std::cout << pos.x << " x " << pos.y << ", hp: " << player->get_HP() << ", armor: " << player->get_ARM() << " > ";
        } else {
            std::cout << pos.x << " x " << pos.y << ", hp: " << player->get_HP() << " > ";
        }
        supported_actions.push_back("kick enemy");
        return supported_actions;
    }

    if (pos.x > 0) {
        std::cout << " * move left\n";
        supported_actions.push_back("move left");
    }
    if (pos.x < cur_map->get_M()-1) {
        std::cout << " * move right\n";
        supported_actions.push_back("move right");
    }
    if (pos.y > 0) {
        std::cout << " * move down\n";
        supported_actions.push_back("move down");
    }
    if (pos.y < cur_map->get_N()-1) {
        std::cout << " * move up\n";
        supported_actions.push_back("move up");
    }

    if (state == PICK || state == THROW) {
        std::set <std::shared_ptr<Item>> items = player->get_items();
        std::shared_ptr<Item> item = cur_map->get_item(player->get_position());
        bool own_item = false;
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->get_name() == item->get_name()) {
                own_item = true;
                break;
            }
        }

        if (!own_item) {
            std::cout << " * pick " << item->get_name() << std::endl;
            supported_actions.push_back("pick " + item->get_name());
        }
        std::set<std::string> names = {};
        for (auto it = items.begin(); it != items.end(); ++it) {
            names.insert((*it)->get_name());
        }
        for (auto it = names.begin(); it != names.end(); ++it) {
            std::cout << " * throw " << *it << std::endl;
            supported_actions.push_back("throw " + *it);
        }
    }
    if (supported_actions.size() == 0) {
        std::cout << std::endl;
    }

    if (version) {
        std::cout << pos.x << " x " << pos.y << ", hp: " << player->get_HP() << ", armor: " << player->get_ARM() << " > ";
    } else {
        std::cout << pos.x << " x " << pos.y << ", hp: " << player->get_HP() << " > ";
    }

    return supported_actions;
}

void Game::start() {
    while (player->get_HP() > 0) {
        std::vector<std::string> supported =  print_instructions();
        state = get_action(supported);
        if (player->get_HP() <= 0) {
            std::cout << "player died\n";
            break;
        }
        if (state == FINISH) {
            break;
        }
    }
}
