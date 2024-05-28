#ifndef GHOSTTURRET_HPP
#define GHOSTTURRET_HPP
#include "Turret.hpp"

class GhostTurret: public Turret {
public:
	static const int Price;
    GhostTurret(float x, float y);
    void CreateBullet() override;
};
#endif // GHOSTTURRET_HPP
