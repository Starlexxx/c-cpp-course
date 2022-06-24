#include <fstream>
#include <map>
#include "map.h"

#define ERROR -1

Map::Map(std::ifstream& file) {
    std::map <std::string, value_t> values = { {"dog", {3, 5}},
                                               {"wolf", {6, 10}},
                                               {"rat", {2, 3}},
                                               {"armor", {3, 3}},
                                               {"helmet", {2, 3}},
                                               {"shield", {7, 5}},
                                               {"pants", {1, 1}},
                                               {"T-Shirt", {1, 1}} };
    if (file.bad()) {
        exit(ERROR);
    }

    file >> M >> N;
    if (file.fail()) {
        exit(ERROR);
    }

    enemy_map.assign(M, std::vector<std::shared_ptr<Enemy>> (N, NULL));
    items_map.assign(M, std::vector<std::shared_ptr<Item>> (N, NULL));

    position_t pos = { x:0, y:0 };
    std::string str = "";

    while (file) {
        file >> pos.x;

        if (file.eof()) {
            break;
        }

        file >> pos.y >> str;
        if (file.fail()) {
            exit(ERROR);
        }

        if (str == "dog" || str == "rat" || str == "wolf") {
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(str, pos, values[str].prop, values[str].feat+1);
            enemy_map[pos.x][pos.y] = enemy;
        } else {
            std::shared_ptr<Item> item = std::make_shared<Item>(str, pos, values[str].prop, values[str].feat);
            items_map[pos.x][pos.y] = item;
        }
    }
}

int Map::get_N() {
    return N;
}

int Map::get_M() {
    return M;
}

std::shared_ptr<Enemy> Map::get_enemy(position_t pos) {
    return enemy_map[pos.x][pos.y];
}

std::shared_ptr<Item> Map::get_item(position_t pos) {
    return items_map[pos.x][pos.y];
}

void Map::kill_element(position_t pos) {
    if (items_map[pos.x][pos.y] != NULL) {
        items_map[pos.x][pos.y] = NULL;
    }
    if (enemy_map[pos.x][pos.y] != NULL) {
        enemy_map[pos.x][pos.y] = NULL;
    }
}
