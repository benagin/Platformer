#ifndef KEY_EVENT_HPP_
#define KEY_EVENT_HPP_

#include "Event.hpp"

enum Key {
	Key_Unknown = GLFW_KEY_UNKNOWN,
	Key_Space = GLFW_KEY_SPACE,
	Key_Apostrophe = GLFW_KEY_APOSTROPHE,
	Key_Comma = GLFW_KEY_COMMA,
	Key_Minus = GLFW_KEY_MINUS,
	Key_Period = GLFW_KEY_PERIOD,
	Key_Slash = GLFW_KEY_SLASH,
	Key_0 = GLFW_KEY_0,
	Key_1 = GLFW_KEY_1,
	Key_2 = GLFW_KEY_2,
	Key_3 = GLFW_KEY_3,
	Key_4 = GLFW_KEY_4,
	Key_5 = GLFW_KEY_5,
	Key_6 = GLFW_KEY_6,
	Key_7 = GLFW_KEY_7,
	Key_8 = GLFW_KEY_8,
	Key_9 = GLFW_KEY_9,
	Key_SemiColon = GLFW_KEY_SEMICOLON,
	Key_Equal = GLFW_KEY_EQUAL,
	Key_A = GLFW_KEY_A,
	Key_B = GLFW_KEY_B,
	Key_C = GLFW_KEY_C,
	Key_D = GLFW_KEY_D,
	Key_E = GLFW_KEY_E,
	Key_F = GLFW_KEY_F,
	Key_G = GLFW_KEY_G,
	Key_H = GLFW_KEY_H,
	Key_I = GLFW_KEY_I,
	Key_J = GLFW_KEY_J,
	Key_K = GLFW_KEY_K,
	Key_L = GLFW_KEY_L,
	Key_M = GLFW_KEY_M,
	Key_N = GLFW_KEY_N,
	Key_O = GLFW_KEY_O,
	Key_P = GLFW_KEY_P,
	Key_Q = GLFW_KEY_Q,
	Key_R = GLFW_KEY_R,
	Key_S = GLFW_KEY_S,
	Key_T = GLFW_KEY_T,
	Key_U = GLFW_KEY_U,
	Key_V = GLFW_KEY_V,
	Key_W = GLFW_KEY_W,
	Key_X = GLFW_KEY_X,
	Key_Y = GLFW_KEY_Y,
	Key_Z = GLFW_KEY_Z,
	Key_Left_Bracket = GLFW_KEY_LEFT_BRACKET,
	Key_BackSlash = GLFW_KEY_BACKSLASH,
	Key_Right_Bracket = GLFW_KEY_RIGHT_BRACKET,
	Key_Accent = GLFW_KEY_GRAVE_ACCENT,
	Key_World_1 = GLFW_KEY_WORLD_1,
	Key_World_2 = GLFW_KEY_WORLD_2,
	Key_ESC = GLFW_KEY_ESCAPE,
	Key_Enter = GLFW_KEY_ENTER,
	Key_Tab = GLFW_KEY_TAB,
	Key_BackSpace = GLFW_KEY_BACKSPACE,
	Key_Insert = GLFW_KEY_INSERT,
	Key_Delete = GLFW_KEY_DELETE,
	Key_Right = GLFW_KEY_RIGHT,
	Key_Left = GLFW_KEY_LEFT,
	Key_Down = GLFW_KEY_DOWN,
	Key_Up = GLFW_KEY_UP,
	Key_Page_Up = GLFW_KEY_PAGE_UP,
	Key_Page_Down = GLFW_KEY_PAGE_DOWN,
	Key_Home = GLFW_KEY_HOME,
	Key_End = GLFW_KEY_END,
	Key_Caps_Lock = GLFW_KEY_CAPS_LOCK,
	Key_Scroll_Lock = GLFW_KEY_SCROLL_LOCK,
	Key_Num_Lock = GLFW_KEY_NUM_LOCK,
	Key_Print_Screen = GLFW_KEY_PRINT_SCREEN,
	Key_Pause = GLFW_KEY_PAUSE,
	Key_F1 = GLFW_KEY_F1,
	Key_F2 = GLFW_KEY_F2,
	Key_F3 = GLFW_KEY_F3,
	Key_F4 = GLFW_KEY_F4,
	Key_F5 = GLFW_KEY_F5,
	Key_F6 = GLFW_KEY_F6,
	Key_F7 = GLFW_KEY_F7,
	Key_F8= GLFW_KEY_F8,
	Key_F9 = GLFW_KEY_F9,
	Key_F10 = GLFW_KEY_F10,
	Key_F11 = GLFW_KEY_F11,
	Key_F12 = GLFW_KEY_F12,
	Key_F13 = GLFW_KEY_F13,
	Key_F14 = GLFW_KEY_F14,
	Key_F15 = GLFW_KEY_F15,
	Key_F16 = GLFW_KEY_F16,
	Key_F17 = GLFW_KEY_F17,
	Key_F18 = GLFW_KEY_F18,
	Key_F19 = GLFW_KEY_F19,
	Key_F20 = GLFW_KEY_F20,
	Key_F21 = GLFW_KEY_F21,
	Key_F22 = GLFW_KEY_F22,
	Key_F23 = GLFW_KEY_F23,
	Key_F24 = GLFW_KEY_F24,
	Key_F25 = GLFW_KEY_F25,
	Key_K0 = GLFW_KEY_KP_0,
	Key_K1 = GLFW_KEY_KP_1,
	Key_K2 = GLFW_KEY_KP_2,
	Key_K3 = GLFW_KEY_KP_3,
	Key_K4 = GLFW_KEY_KP_4,
	Key_K5 = GLFW_KEY_KP_5,
	Key_K6 = GLFW_KEY_KP_6,
	Key_K7 = GLFW_KEY_KP_7,
	Key_K8 = GLFW_KEY_KP_8,
	Key_K9 = GLFW_KEY_KP_9,
	Key_KDecimal = GLFW_KEY_KP_DECIMAL,
	Key_KDivide = GLFW_KEY_KP_DIVIDE,
	Key_KMultiply = GLFW_KEY_KP_MULTIPLY,
	Key_KSubtract = GLFW_KEY_KP_SUBTRACT,
	Key_KAdd = GLFW_KEY_KP_ADD,
	Key_KEnter = GLFW_KEY_KP_ENTER,
	Key_KEQ = GLFW_KEY_KP_EQUAL,
	Key_Left_Shift = GLFW_KEY_LEFT_SHIFT,
	Key_Left_Control = GLFW_KEY_LEFT_CONTROL,
	Key_Left_Alt = GLFW_KEY_LEFT_ALT,
	Key_Left_Super = GLFW_KEY_LEFT_SUPER,
	Key_Right_Shift = GLFW_KEY_RIGHT_SHIFT,
	Key_Right_Control = GLFW_KEY_RIGHT_CONTROL,
	Key_Right_Alt = GLFW_KEY_RIGHT_ALT,
	Key_Right_Super = GLFW_KEY_RIGHT_SUPER,
	Key_Menu = GLFW_KEY_MENU,
	NUM_KEYS
};

enum Mod {
	Mod_None = 0x0,
	Mod_Shift = GLFW_MOD_SHIFT,
	Mod_Control = GLFW_MOD_CONTROL,
	Mod_Alt = GLFW_MOD_ALT,
	Mod_Super = GLFW_MOD_SUPER
};

enum Action {
	Action_Release = GLFW_RELEASE,
	Action_Press = GLFW_PRESS,
	Action_Repeat = GLFW_REPEAT
};


class KeyEvent: public Event {
public:
	KeyEvent(Window* _window, Key _key, Mod _mod, Action _action);
	Key GetKey();
	Mod GetMod();
	Action GetAction();
private:
	Key m_key;
	Mod m_mod;
	Action m_action;
};


#endif // KEY_EVENT_HPP_
