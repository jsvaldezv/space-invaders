#include "MainComponent.h"

MainComponent::MainComponent()
{
    InitWindow (Sizes::WIDTH, Sizes::HEIGHT, "Space Invaders!");
    SetTargetFPS (60);

    prepare();
    process();
}

MainComponent::~MainComponent()
{
    CloseWindow();
}

void MainComponent::prepare()
{
}

void MainComponent::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        draw();
        EndDrawing();
    }
}

void MainComponent::draw()
{
    drawBackground();
    
    spaceship.Draw();
}

void MainComponent::drawBackground()
{
    ClearBackground (Colours::Grey);
}
