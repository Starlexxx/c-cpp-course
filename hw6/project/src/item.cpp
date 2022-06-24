#include "item.h"

int Item::get_WGT() {
    return WGT;
}

int Item::get_ARM() {
    return ARM;
}

std::string Item::get_name() {
    return name;
}

position_t Item::get_position() {
    return position;
}
