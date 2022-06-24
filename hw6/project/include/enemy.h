#ifndef PROJECT_INCLUDE_ENEMY_H_
#define PROJECT_INCLUDE_ENEMY_H_

#include <string>
#include "essence.h"

class Enemy : public Essence {
 private:
    std::string name;

 public:
    explicit Enemy(std::string s, position_t position, int hp, int dmg): Essence(position, hp, dmg), name(s) {}
    std::string get_name();
};

#endif  // PROJECT_INCLUDE_ENEMY_H_
