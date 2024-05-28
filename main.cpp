// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/WinScene.hpp"

int main(int argc, char** argv) {
    Engine::LOG::SetConfig(true);
    Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // TODO: [HACKATHON-1-SCENE] (3/4): Register Scenes here
    game.AddNewScene("settings", new SettingsScene());
    game.AddNewScene("play", new PlayScene());
    game.AddNewScene("lose-scene", new LoseScene());
    game.AddNewScene("win", new WinScene());
    game.AddNewScene("start", new StartScene());
    game.AddNewScene("stage-select", new StageSelectScene());
    game.AddNewScene("scoreboard-scene", new ScoreboardScene());

    // TODO: [HACKATHON-1-SCENE] (4/4): Change the start scene
    game.Start("start", 60, 1600, 832);
    return 0;
}