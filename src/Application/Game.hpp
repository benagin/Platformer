#ifndef GAME_HPP_
#define GAME_HPP_

#include <glm/glm.hpp>
#include <vector>

#include "Camera/Camera.hpp"
#include "Entities/Entity.hpp"
#include "Graphics/UI/Window.hpp"
#include "Graphics/Renderer2D.hpp"
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
      ActiveGame,
      GameOver
    };

    // temp
    Window* GetWindow() { return m_window; }
    void Update();
    void Render();
    void SetCursor(const glm::dvec2& _pos);
    void ToggleKey(unsigned int _key);

    static void InitGL();
    static void InitGlew();

    State GetState() const { return m_state; }

  private:
    std::vector<Entity*> m_entities;
    void ProcessInput();
    void QuitGame();
    Window* m_window;
    State m_state;
    bool m_running;
    // Once it is finished
    // GameConfig m_config;

    // Game input states, window related states are
    // stored in the window.
    bool m_keys[Key::NUM_KEYS];
    Renderer* m_renderer;
    Resources* m_resources;
    InputManager* m_inputManager;
    Camera* m_camera;
};

#endif // GAME_HPP_
