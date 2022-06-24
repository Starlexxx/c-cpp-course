#ifndef PROJECT_INCLUDE_ITEM_H_
#define PROJECT_INCLUDE_ITEM_H_

#include <string>
#include "essence.h"

class Item {
 private:
    std::string name;
    int WGT;
    int ARM;
    position_t position;
 public:
    explicit Item(std::string str, position_t pos, int weight, int armor): name(str), WGT(weight), ARM(armor), position(pos) {}
    int get_WGT();
    int get_ARM();
    std::string get_name();
    position_t get_position();
};

#endif  // PROJECT_INCLUDE_ITEM_H_
