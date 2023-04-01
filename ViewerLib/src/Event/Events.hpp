#pragma once
#include "Event.hpp"
#include <cstdint>

namespace VL
{
	class WindowCloseEvent :
		public Event
	{
		public:
			WindowCloseEvent() = default;
	};

	class WindowResizeEvent :
		public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_width(width), m_height(height)
		{
		}

		[[nodiscard]] inline uint32_t getWidth() const { return m_width; }
		[[nodiscard]] inline uint32_t getHeight() const { return m_height; }
	private:
		uint32_t m_width;
		uint32_t m_height;
	};

	class WindowMoveEvent
		: public Event
	{
	public:
		WindowMoveEvent(int32_t x, int32_t y)
			: m_x(x), m_y(y)
		{
		}
	private:
		int32_t m_x;
		int32_t m_y;
	};

	class KeyboardEvent :
		public Event
	{
	public:
		enum class KEY_CODES
		{
			NONE = 0,
			SPACE = 32,
			APOSTROHPE = 39,
			COMMA = 44,
			MINUS = 45,
			PERIOD = 46,
			SLASH = 47,
			D0 = 48,
			D1 = 49,
			D2 = 50,
			D3 = 51,
			D4 = 52,
			D5 = 53,
			D6 = 54,
			D7 = 55,
			D8 = 56,
			D9 = 57,
			SEMICOLON = 59,
			EQUAL = 61,
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			LEFT_BRACKET = 91,
			BACKSLASH = 92,
			RIGHT_BRACKET = 93,
			GRAVE_ACCENT = 96,
			WORLD_1 = 161,
			WORLD_2 = 162,
			ESCAPE = 256,
			ENTER = 257,
			TAB = 258,
			BACKSPACE = 259,
			INSERT = 260,
			DELETE = 261,
			RIGHT = 262,
			LEFT = 263,
			DOWN = 264,
			UP = 265,
			PAGE_UP = 266,
			PAGE_DOWN = 267,
			HOME = 268,
			END = 269,
			CAPS_LOCK = 280,
			SCROLL_LOCK = 281,
			NUM_LOCK = 282,
			PRINT_SCREENT = 283,
			PAUSE = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KP_DECIMAL = 330,
			KP_DIVIDE = 331,
			KP_MULTIPLY = 332,
			KP_SUBTRACT = 333,
			KP_ADD = 334,
			KP_ENTER = 335,
			KP_EQUAL = 336,
			LEFT_SHIFT = 340,
			LEFT_CONSTROL = 341,
			LEFT_ALT = 342,
			LEFT_SUPER = 343,
			RIGHT_SHIFT = 344,
			RIGHT_CONTROL = 345,
			RIGHT_ALT = 346,
			RIGHT_SUPER = 347,
			MENU = 348
		};
		public:
			KeyboardEvent(KEY_CODES key)
				: Event(), m_keyCode(key)
			{
			};
			inline KEY_CODES getKeyCode() const 
			{ 
				return m_keyCode; 
			};
		protected:
			KEY_CODES m_keyCode = KEY_CODES::NONE;
	};	

	class KeyPressEvent :
		public KeyboardEvent
	{
	public:
		KeyPressEvent(KEY_CODES key)
			: KeyboardEvent(key)
		{
		}
	};

	class KeyReleaseEvent :
		public KeyboardEvent
	{
	public:
	KeyReleaseEvent(KEY_CODES key)
			: KeyboardEvent(key)
		{
		}
	};;
}
