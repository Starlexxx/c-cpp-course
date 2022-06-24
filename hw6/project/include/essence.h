#ifndef PROJECT_INCLUDE_ESSENCE_H_
#define PROJECT_INCLUDE_ESSENCE_H_

#include <string>

typedef struct {
    int x;
    int y;
} position_t;

class Essence {
 protected:
    int HP;
    int DMG;
    position_t position;

 public:
    explicit Essence(position_t pos = {0, 0}, int health = 100, int damage = 1):
    HP(health), DMG(damage), position(pos) {}
    int get_HP();
    int kick();
    void get_kicked(int dmg);
    position_t get_position();
};

#endif  // PROJECT_INCLUDE_ESSENCE_H_
