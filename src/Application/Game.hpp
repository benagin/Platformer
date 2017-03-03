#ifndef GAME_HPP_
#define GAME_HPP_

#include <glm/glm.hpp>

#include "Graphics/UI/Window.hpp"
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
private:
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
	Resources* m_resources;
	InputManager* m_inputManager;	
};

#endif // GAME_HPP_
