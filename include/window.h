
#ifndef __VC_WINDOW__
#define __VC_WINDOW__ 1

#include <platform_types.h>
#include "imgui.h"

namespace VC {

	class Window {

	public:
		enum VC_KEY
		{
			kVC_KEY_UNKNOWN = -1,
			kVC_KEY_SPACE = 32,
			kVC_KEY_APOSTROPHE = 39, /* ' */
			kVC_KEY_COMMA = 44, /* , */
			kVC_KEY_MINUS = 45, /* - */
			kVC_KEY_PERIOD = 46, /* . */
			kVC_KEY_SLASH = 47, /* / */
			kVC_KEY_0 = 48,
			kVC_KEY_1 = 49,
			kVC_KEY_2 = 50,
			kVC_KEY_3 = 51,
			kVC_KEY_4 = 52,
			kVC_KEY_5 = 53,
			kVC_KEY_6 = 54,
			kVC_KEY_7 = 55,
			kVC_KEY_8 = 56,
			kVC_KEY_9 = 57,
			kVC_KEY_SEMICOLON = 59, /* ; */
			kVC_KEY_EQUAL = 61, /* = */
			kVC_KEY_A = 65,
			kVC_KEY_B = 66,
			kVC_KEY_C = 67,
			kVC_KEY_D = 68,
			kVC_KEY_E = 69,
			kVC_KEY_F = 70,
			kVC_KEY_G = 71,
			kVC_KEY_H = 72,
			kVC_KEY_I = 73,
			kVC_KEY_J = 74,
			kVC_KEY_K = 75,
			kVC_KEY_L = 76,
			kVC_KEY_M = 77,
			kVC_KEY_N = 78,
			kVC_KEY_O = 79,
			kVC_KEY_P = 80,
			kVC_KEY_Q = 81,
			kVC_KEY_R = 82,
			kVC_KEY_S = 83,
			kVC_KEY_T = 84,
			kVC_KEY_U = 85,
			kVC_KEY_V = 86,
			kVC_KEY_W = 87,
			kVC_KEY_X = 88,
			kVC_KEY_Y = 89,
			kVC_KEY_Z = 90,
			kVC_KEY_LEFT_BRACKET = 91, /* [ */
			kVC_KEY_BACKSLASH = 92, /* \ */
			kVC_KEY_RIGHT_BRACKET = 93, /* ] */
			kVC_KEY_GRAVE_ACCENT = 96, /* ` */
			kVC_KEY_WORLD_1 = 161, /* non-US #1 */
			kVC_KEY_WORLD_2 = 162, /* non-US #2 */
			kVC_KEY_ESCAPE = 256,
			kVC_KEY_ENTER = 257,
			kVC_KEY_TAB = 258,
			kVC_KEY_BACKSPACE = 259,
			kVC_KEY_INSERT = 260,
			kVC_KEY_DELETE = 261,
			kVC_KEY_RIGHT = 262,
			kVC_KEY_LEFT = 263,
			kVC_KEY_DOWN = 264,
			kVC_KEY_UP = 265,
			kVC_KEY_PAGE_UP = 266,
			kVC_KEY_PAGE_DOWN = 267,
			kVC_KEY_HOME = 268,
			kVC_KEY_END = 269,
			kVC_KEY_CAPS_LOCK = 280,
			kVC_KEY_SCROLL_LOCK = 281,
			kVC_KEY_NUM_LOCK = 282,
			kVC_KEY_PRINT_SCREEN = 283,
			kVC_KEY_PAUSE = 284,
			kVC_KEY_F1 = 290,
			kVC_KEY_F2 = 291,
			kVC_KEY_F3 = 292,
			kVC_KEY_F4 = 293,
			kVC_KEY_F5 = 294,
			kVC_KEY_F6 = 295,
			kVC_KEY_F7 = 296,
			kVC_KEY_F8 = 297,
			kVC_KEY_F9 = 298,
			kVC_KEY_F10 = 299,
			kVC_KEY_F11 = 300,
			kVC_KEY_F12 = 301,
			kVC_KEY_F13 = 302,
			kVC_KEY_F14 = 303,
			kVC_KEY_F15 = 304,
			kVC_KEY_F16 = 305,
			kVC_KEY_F17 = 306,
			kVC_KEY_F18 = 307,
			kVC_KEY_F19 = 308,
			kVC_KEY_F20 = 309,
			kVC_KEY_F21 = 310,
			kVC_KEY_F22 = 311,
			kVC_KEY_F23 = 312,
			kVC_KEY_F24 = 313,
			kVC_KEY_F25 = 314,
			kVC_KEY_KP_0 = 320,
			kVC_KEY_KP_1 = 321,
			kVC_KEY_KP_2 = 322,
			kVC_KEY_KP_3 = 323,
			kVC_KEY_KP_4 = 324,
			kVC_KEY_KP_5 = 325,
			kVC_KEY_KP_6 = 326,
			kVC_KEY_KP_7 = 327,
			kVC_KEY_KP_8 = 328,
			kVC_KEY_KP_9 = 329,
			kVC_KEY_KP_DECIMAL = 330,
			kVC_KEY_KP_DIVIDE = 331,
			kVC_KEY_KP_MULTIPLY = 332,
			kVC_KEY_KP_SUBTRACT = 333,
			kVC_KEY_KP_ADD = 334,
			kVC_KEY_KP_ENTER = 335,
			kVC_KEY_KP_EQUAL = 336,
			kVC_KEY_LEFT_SHIFT = 340,
			kVC_KEY_LEFT_CONTROL = 341,
			kVC_KEY_LEFT_ALT = 342,
			kVC_KEY_LEFT_SUPER = 343,
			kVC_KEY_RIGHT_SHIFT = 344,
			kVC_KEY_RIGHT_CONTROL = 345,
			kVC_KEY_RIGHT_ALT = 346,
			kVC_KEY_RIGHT_SUPER = 347,
			kVC_KEY_MENU = 348,
		};
		enum VC_MOUSE_KEY {
			KVC_MOUSE_KEY_RIGTH = 0,
			KVC_MOUSE_KEY_LEFT = 1
		};
		s8 Init();
		void CreateWindow(u32 width, u32 height, const char* title);

		bool GetMousePressed(VC_MOUSE_KEY key);
		void GetMousePosition();
		void PollEvents();
		void SwapBuffers();
		s32 ShouldClose();
		void MakeCurrentContext();
		s8 Terminate();
		bool getKeyPressed(VC_KEY key);
		//RENDER
		void ClearColor(float r, float g, float b, float a);
		void Clear();

		double xMouse;
		double yMouse;
	private:

	};

}

#endif