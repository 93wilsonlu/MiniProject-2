#ifndef CENTAURONEMY_HPP
#define CENTAURONEMY_HPP
#include "Enemy.hpp"

class CentauroEnemy : public Enemy {
public:
	CentauroEnemy(int x, int y);
	void Hit(float damage);
};
#endif // CENTAURONEMY_HPP
