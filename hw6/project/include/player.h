#ifndef PROJECT_INCLUDE_PLAYER_H_
#define PROJECT_INCLUDE_PLAYER_H_

#include <set>
#include <string>
#include <memory>
#include "enemy.h"
#include "item.h"

class Player : public Essence {
 private:
    int max_WGT;
    int WGT;
    int ARM;
    std::set <std::shared_ptr<Item>> items = {};
 public:
    explicit Player(position_t position = {x:0, y:0}, int health = 100, int damage = 1,
        int max_wgt = 20, int wgt = 0, int arm = 0): Essence(position, health, damage),
        max_WGT(max_wgt), WGT(wgt), ARM(arm) {}
    void move_player(position_t new_pos);
    void fight(std::shared_ptr<Enemy> enemy);
    int get_max_WGT();
    int get_ARM();
    int get_WGT();
    void add_item(std::shared_ptr<Item> new_item);
    void throw_item(std::shared_ptr<Item> old_item);
    std::set <std::shared_ptr<Item>> get_items();
};

#endif  // PROJECT_INCLUDE_PLAYER_H_
