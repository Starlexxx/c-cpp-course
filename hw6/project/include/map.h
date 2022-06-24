#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <string>
#include <vector>
#include <memory>
#include "enemy.h"
#include "item.h"

typedef struct {
    int prop;
    int feat;
} value_t;

class Map {
 private:
    int N;
    int M;
    std::vector <std::vector<std::shared_ptr<Enemy>>> enemy_map;
    std::vector <std::vector<std::shared_ptr<Item>>> items_map;
 public:
    explicit Map(std::ifstream& file);
    int get_N();
    int get_M();
    std::shared_ptr<Enemy> get_enemy(position_t pos);
    std::shared_ptr<Item> get_item(position_t pos);
    void kill_element(position_t pos);
};

#endif  // PROJECT_INCLUDE_MAP_H_
