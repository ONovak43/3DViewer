#pragma once

namespace VL
{
	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;
		void setHandled(bool handled) { m_handled = handled; }
		bool isHandled() const { return m_handled; }
	protected:
		bool m_handled = false;
	};
}