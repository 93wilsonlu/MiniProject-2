#include <functional>
#include <string>

#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "WinScene.hpp"

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0,
                                   0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW,
                                   halfH / 4 - 10, 255, 255, 255, 255, 0.5,
                                   0.5));
    Engine::TextInput* name =
        new Engine::TextInput("", "pirulen.ttf", 32, halfW, halfH / 4 + 50,
                              500, 60, 255, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(name);
    name->SetOnValueChangedCallback(std::bind(&WinScene::winnerOnValueChanged, this, std::placeholders::_1));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200,
                                  halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW,
                                   halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
}

void WinScene::winnerOnValueChanged(int keyCode) {
    if (keyCode == ALLEGRO_KEY_BACKSPACE && winner_name.size() > 0) {
        winner_name.pop_back();
    } else if (winner_name.size() <= 15) {
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
            winner_name.push_back('a' + keyCode - ALLEGRO_KEY_A);
        } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
            winner_name.push_back('0' + keyCode - ALLEGRO_KEY_0);
        }
    }
}

void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}

void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene*>(
            Engine::GameEngine::GetInstance().GetScene("play"))
                ->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    if (!winner_name.empty()) {
        Engine::GameEngine::GetInstance().updateScoreboard(winner_name);
        winner_name.clear();
    }
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
