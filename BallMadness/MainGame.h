#pragma once
#include <InfernoEngine/Camera2D.h>
#include <InfernoEngine/SpriteBatch.h>
#include <InfernoEngine/InputManager.h>
#include <InfernoEngine/Window.h>
#include <InfernoEngine/GLSLProgram.h>
#include <InfernoEngine/Timing.h>
#include <InfernoEngine/SpriteFont.h>
#include "Grid.h"
#include "BallController.h"
#include "BallRenderer.h"
#include <memory>


// TODO:
// Visualize momentum with color
// Visualize velocity with color
// Visualize position with color

enum class GameState { RUNNING, EXIT };

const int CELL_SIZE = 12;

class MainGame {
public:
    ~MainGame();
    void run();


private:
    void init();
    void initRenderers();
    void initBalls();
    void update(float deltaTime);
    void draw();
    void drawHud();
    void processInput();

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    std::vector<Ball> m_balls; ///< All the balls 
    std::unique_ptr<Grid> m_grid; ///< Grid for spatial partitioning for collision

    uint32_t m_currentRenderer = 0;
    std::vector<BallRenderer*> m_ballRenderers;

  

    BallController m_ballController; ///< Controls balls

    Inferno::Window m_window; ///< The main window
    Inferno::SpriteBatch m_spriteBatch; ///< Renders all the balls
    std::unique_ptr<Inferno::SpriteFont> m_spriteFont; ///< For font rendering
    Inferno::Camera2D m_camera; ///< Renders the scene
    Inferno::InputManager m_inputManager; ///< Handles input
    Inferno::GLSLProgram m_textureProgram; ///< Shader for textures]

    Inferno::FPSLimiter m_fpsLimiter; ///< Limits and calculates fps
    float m_fps = 0.0f;

    GameState m_gameState = GameState::RUNNING; ///< The state of the game
};

