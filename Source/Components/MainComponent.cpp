#include "MainComponent.h"
#include "iostream"

MainComponent::MainComponent()
{
    InitWindow (Sizes::WIDTH + Sizes::OFFSET, Sizes::HEIGHT + 2 * Sizes::OFFSET, "Space Invaders");
    SetTargetFPS (60);
    
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
    spaceship.prepare();
    
    obstacles = createObstacles();
    
    aliens = createAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    
    mysteryShip.prepare();
    mysteryShipSpawnInterval = GetRandomValue (10, 20);
    timeLastSpawn = 0.0f;
    
    lives = 3;
    run = true;
    SpaceshipImage = LoadTexture ("../../Assets/spaceship.png");
    
    score = 0;
    highScore = 0;
}

std::vector<Obstacle> MainComponent::createObstacles()
{
    int obstacleWidth = (int) (Obstacle::grid[0].size() * 3);
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;
    
    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back (Obstacle({offset_x, (float) (GetScreenHeight() - 200) }));
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
    
    mysteryShip.draw();
    
    EndDrawing();
}

void MainComponent::drawBackground()
{
    ClearBackground (Colours::Grey);
    DrawRectangleRoundedLinesEx ({ 10, 10, 780, 780 }, 0.18f, 20.0f, 2.0f, Colours::Yellow);
    DrawLineEx ({ 25, 730 }, { 775, 730 }, 3, Colours::Yellow);
    
    if (run)
        DrawTextEx (Fonts::font, "LEVEL 01", { 570, 740 }, 34, 2, Colours::Yellow);
    else
        DrawTextEx (Fonts::font, "GAME OVER", { 570, 740 }, 34, 2, Colours::Yellow);
    
    float x = 50.0f;
    for (int i = 0; i < lives; i++)
    {
        DrawTextureV (SpaceshipImage, { x, 745 }, WHITE);
        x += 50.0f;
    }
    
    DrawTextEx (Fonts::font, "SCORE", { 60, 25 }, 34, 2, Colours::Yellow);
    std::string scoreText = FormatWithLeadingZeros (score, 5);
    DrawTextEx (Fonts::font, scoreText.c_str(), { 60, 50 }, 34, 2, Colours::Yellow);
    
    DrawTextEx (Fonts::font, "HIGH SCORE", { 540, 25 }, 34, 2, Colours::Yellow);
    std::string highScoreText = FormatWithLeadingZeros (highScore, 5);
    DrawTextEx (Fonts::font, highScoreText.c_str(), { 625, 50 }, 34, 2, Colours::Yellow);
}

void MainComponent::moveAliens()
{
    for (auto& alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            moveDownAliens (4);
        }
        
        if (alien.position.x < 25)
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
    if (run)
    {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryShip.spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue (10, 20);
        }
        
        for (auto& laser : spaceship.lasers)
            laser.update();
        
        moveAliens();
        
        alienShootLaser();
        
        for (auto& laser : alienLasers)
            laser.update();
        
        deleteInactiveLasers();
        
        mysteryShip.update();
        
        checkForCollisions();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            reset();
            prepare();
        }
    }
}

void MainComponent::handleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
            spaceship.moveLeft();
        
        else if (IsKeyDown(KEY_RIGHT))
            spaceship.moveRight();
        
        else if (IsKeyDown(KEY_SPACE))
            spaceship.fireLaser();
    }
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

void MainComponent::checkForCollisions()
{
    // Spacship lasers
    for (auto& laser : spaceship.lasers)
    {
        auto it = aliens.begin();
        
        while (it != aliens.end())
        {
            if (CheckCollisionRecs (it->getRect(), laser.getRect()))
            {
                if (it -> type == 1)
                    score += 100;
                
                if (it -> type == 2)
                    score += 200;
                
                if (it -> type == 3)
                    score += 300;
                    
                checkForHighScore();
                it = aliens.erase (it);
                laser.active = false;
            }
            else
                ++it;
        }
        
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs (it->getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase (it);
                    laser.active = false;
                }
                else
                    ++it;
            }
        }
        
        if (CheckCollisionRecs (mysteryShip.getRect(), laser.getRect()))
        {
            mysteryShip.alive = false;
            laser.active = false;
            score += 500;
            checkForHighScore();
        }
    }
    
    // Alien lasers
    for (auto& laser : alienLasers)
    {
        if (CheckCollisionRecs (laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            lives--;
            
            if (lives == 0)
                gameOver();
        }
        
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs (it->getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase (it);
                    laser.active = false;
                }
                else
                    ++it;
            }
        }
    }
    
    // Alien collision with obstacle
    for (auto& alien : aliens)
    {
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs (it->getRect(), alien.getRect()))
                    it = obstacle.blocks.erase (it);
                else
                    it++;
            }
        }
        
        if (CheckCollisionRecs (alien.getRect(), spaceship.getRect()))
            gameOver();
    }
    
}

void MainComponent::gameOver()
{
    std::cout << "Game over" << std::endl;
    run = false;
}

void MainComponent::reset()
{
    spaceship.reset();
    
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void MainComponent::checkForHighScore()
{
    if (score > highScore)
    {
        highScore = score;
    }
}
