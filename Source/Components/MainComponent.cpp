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
    Alien::unloadImages();
    CloseWindow();
}

void MainComponent::prepare()
{
    SetTargetFPS (60);
    spaceship.prepare();
    
    obstacles = createObstacles();
    
    aliens = createAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
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

std::vector<Alien> MainComponent::createAliens()
{
    std::vector<Alien> aliens;
    
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alienType;
            
            if (row == 0)
                alienType = 3;
            else if (row == 1 || row == 2)
                alienType = 2;
            else
                alienType = 1;
            
            float x = 75 + column * 55;
            float y = 110 + row * 55;
            
            aliens.push_back (Alien (alienType, { x, y }));
        }
    }
    
    return aliens;
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
    
    for (auto& alien : aliens)
        alien.draw();
    
    for (auto& laser : alienLasers)
        laser.draw();
    
    EndDrawing();
}

void MainComponent::drawBackground()
{
    ClearBackground (Colours::Grey);
}

void MainComponent::moveAliens()
{
    for (auto& alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth())
        {
            aliensDirection = -1;
            moveDownAliens (4);
        }
        
        if (alien.position.x < 0)
        {
            aliensDirection = 1;
            moveDownAliens (4);
        }
            
        alien.update (aliensDirection);
    }
}

void MainComponent::alienShootLaser()
{
    double currentTime = GetTime();
    
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomIndex = GetRandomValue (0, (int) (aliens.size() - 1));
        Alien& alien = aliens[randomIndex];
        
        alienLasers.push_back (Laser ({ alien.position.x + alien.alienImages[alien.type - 1].width/2,
                                        alien.position.y + alien.alienImages[alien.type - 1].height/2 }, 6));
        
        timeLastAlienFired = GetTime();
    }
}

void MainComponent::moveDownAliens (int distance)
{
    for (auto& alien : aliens)
    {
        alien.position.y += distance;
    }
}

void MainComponent::update()
{
    for (auto& laser : spaceship.lasers)
        laser.update();
    
    moveAliens();
    
    alienShootLaser();
    
    for (auto& laser : alienLasers)
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
    
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
            it = alienLasers.erase (it);
        else
            ++it;
    }
}
