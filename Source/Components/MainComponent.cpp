#include "MainComponent.h"
#include "iostream"

MainComponent::MainComponent()
{
    InitWindow (Sizes::WIDTH, Sizes::HEIGHT, "Space Invaders");
    prepare();
    process();
}

MainComponent::~MainComponent()
{
    CloseWindow();
}

void MainComponent::prepare()
{
    SetTargetFPS (60);
    spaceship.prepare();
    obstacles = createObstacles();
}

std::vector<Obstacle> MainComponent::createObstacles()
{
    int obstacleWidth = (int) (Obstacle::grid[0].size() * 3);
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;
    
    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back (Obstacle({offset_x, (float) (GetScreenHeight() - 100) }));
    }
    
    return obstacles;
}

void MainComponent::process()
{
    while (!WindowShouldClose())
    {
        handleInput();
        update();
        draw();
    }
}

void MainComponent::draw()
{
    BeginDrawing();
    
    drawBackground();
    spaceship.draw();
    
    for (auto& laser : spaceship.lasers)
        laser.draw();
    
    for (auto& obstacle : obstacles)
        obstacle.draw();
    
    EndDrawing();
}

void MainComponent::drawBackground()
{
    ClearBackground (Colours::Grey);
}

void MainComponent::update()
{
    for (auto& laser : spaceship.lasers)
        laser.update();
    
    deleteInactiveLasers();
}

void MainComponent::handleInput()
{
    if (IsKeyDown(KEY_LEFT))
        spaceship.moveLeft();
    
    else if (IsKeyDown(KEY_RIGHT))
        spaceship.moveRight();
    
    else if (IsKeyDown(KEY_SPACE))
        spaceship.fireLaser();
}

void MainComponent::deleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
            it = spaceship.lasers.erase (it);
        else
            ++it;
    }
}
