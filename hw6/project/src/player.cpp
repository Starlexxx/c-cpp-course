#include "player.h"
#define ARMOR_ABSORBE 1

void Player::move_player(position_t new_pos) {
    position.x += new_pos.x;
    position.y += new_pos.y;
}

void Player::fight(std::shared_ptr<Enemy> enemy) {
    enemy->get_kicked(kick());
    if (enemy->get_HP() > 0) {
        if (enemy->kick() <= ARM) {
            get_kicked(ARMOR_ABSORBE);
        } else {
            get_kicked(enemy->kick() - ARM);
        }
    }
}

int Player::get_max_WGT() {
    return max_WGT;
}

int Player::get_ARM() {
    return ARM;
}

int Player::get_WGT() {
    return WGT;
}

std::set<std::shared_ptr<Item>> Player::get_items() {
    return items;
}

void Player::add_item(std::shared_ptr<Item> new_item) {
    items.insert(new_item);
    WGT += new_item->get_WGT();
    ARM += new_item->get_ARM();
}

void Player::throw_item(std::shared_ptr<Item> old_item) {
    items.erase(old_item);
    WGT -= old_item->get_WGT();
    ARM -= old_item->get_ARM();
}
