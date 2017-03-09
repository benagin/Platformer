#ifndef GAME_HPP_
#define GAME_HPP_

#include <glm/glm.hpp>

#include "Utilities/MatrixStack.hpp"
#include "Graphics/UI/Window.hpp"
#include "Graphics/UI/GUI.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"


class Game {

  public:

    Game();

    ~Game();

    void Init();
    void Run();

    enum State {
      Menu,
      Gameplay,
      GameOver
    };

    // temp
    Window* GetWindow() { return m_window; }
    void Update();

    void Render();
    void RenderMenu();
    void RenderGame();
    void RenderGameOver();

    void SetCursor(const glm::dvec2& _pos);
    void ToggleKey(unsigned int _key);

    static void InitGL();
    static void InitGlew();

  private:

    void ProcessInput();
    void QuitGame();

    MatrixStack m_matrixStack;

    Window* m_window;

    Camera m_camera;

    GUI m_menu{"../assets/XML/StartMenu.xml"};

    State m_state;
    bool m_running;
    // Once it is finished
    // GameConfig m_config;

    // Game input states, window related states are
    // stored in the window.
    bool m_keys[Key::NUM_KEYS];
    Resources* m_resources;
    InputManager* m_inputManager;
};

#endif // GAME_HPP_
