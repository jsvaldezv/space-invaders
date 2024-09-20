#include "MainComponent.h"

MainComponent::MainComponent()
{
    InitWindow (Sizes::WIDTH, Sizes::HEIGHT, "Space Invaders!");
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
}

void MainComponent::process()
{
    while (!WindowShouldClose())
    {
        handleInput();

        BeginDrawing();
        draw();
        EndDrawing();
    }
}

void MainComponent::draw()
{
    drawBackground();
    spaceship.draw();
}

void MainComponent::drawBackground()
{
    ClearBackground (Colours::Grey);
}

void MainComponent::update()
{
    
}

void MainComponent::handleInput()
{
    if (IsKeyDown(KEY_LEFT))
        spaceship.moveLeft();
    
    else if (IsKeyDown(KEY_RIGHT))
        spaceship.moveRight();
}
