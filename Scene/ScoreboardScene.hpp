//
// Created by Hsuan on 2024/4/10.
//

#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class ScoreboardScene final : public Engine::IScene {
   private:
    int index = 0;
    bool changePage = 0;
    std::string time2str(const time_t &time);

   public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void NextOnClick(int stage);
    void PrevOnClick(int stage);
    void BackOnClick(int stage);
};
#endif  // ScoreboardScene_HPP
