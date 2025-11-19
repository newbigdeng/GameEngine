#include "Application.h"
namespace eng
{
	bool Application::SetNeedsToBeClosed(bool value)
	{
		m_needsToBeClosed = value;
	}
	bool Application::NeedsToBeClosed() const
	{
		return m_needsToBeClosed;
	}
}