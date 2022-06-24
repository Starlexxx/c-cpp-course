#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "essence.h"
#include "player.h"
#include "map.h"
#include "game.h"
#define ERROR -1


int main(int argc, const char** argv) {
    if (argc < 2) {
        return ERROR;
    }
    int j = 0;
    int ver = 0;
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "--map") {
            j = i;
        }
        if (std::string(argv[i]) == "--view-armor") {
            ver = 1;
        }
    }
    std::ifstream file(argv[j+1]);
    if (file.bad()) {
        return ERROR;
    }

    std::shared_ptr<Map> map = std::make_shared<Map>(file);
    file.close();

    std::shared_ptr<Player> player = std::make_shared<Player>();
    std::shared_ptr<Game> game = std::make_shared<Game>(map, player, ver);
    game->start();

    return 0;
}
