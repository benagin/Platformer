#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <string>

enum WindowMode {
	Windowed = 0,
	WindowedFull,
	FullScreen
};


class Window {
public:
	Window(const std::string& _title, int _width, int _height, WindowMode _mode, GLFWmonitor* _monitor);
	~Window();

	void Init();
	bool ShouldClose();
	void SetTitle(const std::string& _title);
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	GLFWwindow* GlfwWindow() { return m_window; }
	void PostQuit();

	const glm::dvec2& GetMouseLocation() { return m_mouseLocation; }
	void SetMouseLocation(const glm::dvec2& _pos);

	void SwapBuffers();
	void PollEvents();

	static Window* Init(WindowMode _mode);
	static Window* GetWindow() { return m_gameWindow; }

private:

	void SetMonitor(GLFWmonitor* _monitor) { m_monitor = _monitor; }

	int m_width;
	int m_height;
	std::string m_title;

	GLFWwindow* m_window;
	GLFWmonitor* m_monitor;
	glm::dvec2 m_mouseLocation;

	static Window* m_gameWindow; // there will only every be one window.
};



#endif // WINDOW_HPP_
