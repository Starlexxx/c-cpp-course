#include "essence.h"

int Essence::get_HP() {
    return HP;
}

int Essence::kick() {
    return DMG;
}

void Essence::get_kicked(int dmg) {
    HP -= dmg;
}

position_t Essence::get_position() {
    return position;
}
