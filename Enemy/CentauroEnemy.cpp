#include <string>
#include <random>
#include <iostream>

#include "CentauroEnemy.hpp"

CentauroEnemy::CentauroEnemy(int x, int y)
    : Enemy("play/enemy-7.png", x, y, 16, 200, 50, 300) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect
    // collision can be implemented quite easily, and efficiently if we use AABB
    // collision detection first, and then pixel-perfect collision.
}

void CentauroEnemy::Hit(float damage) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dis(0, 1);

    if (dis(rng) <= 0.1) {
        Enemy::Hit(damage);
    }
}
