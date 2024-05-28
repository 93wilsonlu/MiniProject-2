#include "ScoreboardScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

void ScoreboardScene::Initialize() {
    index = 0;
    changePage = 1;
    Update(0);
}

std::string ScoreboardScene::time2str(const time_t& time) {
    tm* ltm = localtime(&time);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    return std::to_string(year) + "/" + std::to_string(month) + "/" +
           std::to_string(day) + " " + std::to_string(hour) + ":" +
           std::to_string(minute);
}

void ScoreboardScene::Update(float deltaTime) {
    if (changePage) {
        Clear();
        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int halfW = w / 2;
        int halfH = h / 2;

        AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 48, halfW,
                                       halfH - 350, 8, 200, 2, 255, 0.5, 0.5));

        Engine::ImageButton* btn;

        btn = new Engine::ImageButton("stage-select/dirt.png",
                                      "stage-select/floor.png", halfW - 650,
                                      halfH + 300 - 50, 400, 100);
        btn->SetOnClickCallback(
            std::bind(&ScoreboardScene::PrevOnClick, this, 1));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48,
                                       halfW - 450, halfH + 300, 0, 0, 0, 255,
                                       0.5, 0.5));

        btn = new Engine::ImageButton("stage-select/dirt.png",
                                      "stage-select/floor.png", halfW - 200,
                                      halfH + 300 - 50, 400, 100);
        btn->SetOnClickCallback(
            std::bind(&ScoreboardScene::BackOnClick, this, 2));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW,
                                       halfH + 300, 0, 0, 0, 255, 0.5, 0.5));

        btn = new Engine::ImageButton("stage-select/dirt.png",
                                      "stage-select/floor.png", halfW + 250,
                                      halfH + 300 - 50, 400, 100);
        btn->SetOnClickCallback(
            std::bind(&ScoreboardScene::NextOnClick, this, 3));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48,
                                       halfW + 450, halfH + 300, 0, 0, 0, 255,
                                       0.5, 0.5));

        auto& scoreboard = Engine::GameEngine::GetInstance().scoreboard;
        int scoreboard_len = scoreboard.size();
        for (int i = 0; i < 10 && index * 10 + i < scoreboard_len; i++) {
            AddNewObject(new Engine::Label(
                scoreboard[index * 10 + i].name, "pirulen.ttf", 32, halfW - 200,
                halfH - 300 + i * 50, 8, 200, 2, 255, 0.5, 0.5));
            AddNewObject(new Engine::Label(
                std::to_string(scoreboard[index * 10 + i].score), "pirulen.ttf",
                32, halfW, halfH - 300 + i * 50, 8, 200, 2, 255, 0.5, 0.5));
            AddNewObject(new Engine::Label(
                time2str(scoreboard[index * 10 + i].time), "pirulen.ttf", 32,
                halfW + 300, halfH - 300 + i * 50, 8, 200, 2, 255, 0.5, 0.5));
        }
        changePage = 0;
    }
}

void ScoreboardScene::Terminate() {
    IScene::Terminate();
}

void ScoreboardScene::NextOnClick(int stage) {
    int scoreboard_len = Engine::GameEngine::GetInstance().scoreboard.size();
    if ((index + 1) * 10 < scoreboard_len) {
        index++;
        changePage = 1;
    }
}

void ScoreboardScene::PrevOnClick(int stage) {
    if (index) {
        index--;
        changePage = 1;
    }
}

void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}