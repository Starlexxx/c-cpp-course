#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "map.h"
#define BEGIN 0

class Game {
 private:
    std::shared_ptr<Map> cur_map;
    std::shared_ptr<Player> player;
    int state;
    int version;

 public:
    Game(std::shared_ptr<Map> map, std::shared_ptr<Player> play, int ver): cur_map(map), player(play), state(BEGIN), version(ver) {}
    std::vector<std::string> print_instructions();
    int get_action(std::vector<std::string> supported_actions);
    int start_moving(std::string action);
    int start_fighting();
    int pick_item(position_t pos);
    void start();
};

#endif  // PROJECT_INCLUDE_GAME_H_
