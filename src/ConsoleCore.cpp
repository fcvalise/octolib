/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 18:09:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 01:44:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleCore.hpp"
#include "IConsoleListener.hpp"
#include <algorithm>
#include <cstdlib>

namespace octo
{
	ConsoleCore::ConsoleCore() :
		m_prompt(L"$> "),
		m_cursorPosition(0)
	{
	}

	/*! Force to notify the listener of a text change */
	void	ConsoleCore::updateText()
	{
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Define the unique listener */
	void	ConsoleCore::setListener(IConsoleListener* listener)
	{
		m_listener = listener;
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Insert a character at the cursor position */
	void	ConsoleCore::insertChar(wchar_t c)
	{
		m_buffer.insert(m_cursorPosition, 1, c);
		++m_cursorPosition;
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Remove the character at the cursor position */
	void	ConsoleCore::removeCurrent()
	{
		if (m_buffer.empty() || m_cursorPosition == m_buffer.size())
			return;
		m_buffer.erase(m_cursorPosition, 1);
		m_cursorPosition = std::min<unsigned int>(m_cursorPosition, m_buffer.size());
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Remove the character before the cursor position */
	void	ConsoleCore::removePrevious()
	{
		if (m_buffer.empty() || m_cursorPosition == 0u)
			return;
		--m_cursorPosition;
		m_buffer.erase(m_cursorPosition, 1);
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Clear the buffer */
	void	ConsoleCore::removeAll()
	{
		if (m_buffer.empty())
			return;
		m_buffer.clear();
		m_cursorPosition = 0;
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Replace the current buffer content */
	void	ConsoleCore::resetBuffer(std::wstring const& line)
	{
		m_buffer = line;
		m_cursorPosition = m_buffer.size();
		emitTextChanged();
		emitCursorChanged();
	}

	/*! Move the cursor */
	void	ConsoleCore::moveCursor(int offset)
	{
		if (m_buffer.empty())
			return;
		if (offset < 0)
		{
			if (m_cursorPosition >= static_cast<unsigned int>(std::abs(offset)))
				m_cursorPosition += offset;
			else
				m_cursorPosition = 0;
		}
		else if (offset > 0)
		{
			m_cursorPosition = std::min<unsigned int>(m_cursorPosition + offset, m_buffer.size());
		}
		emitCursorChanged();
	}

	/*!	Fill the buffer with the next entry in the history */
	void	ConsoleCore::resetFromNext()
	{
		std::wstring	entry;

		if (m_history.getNextEntry(entry))
		{
			resetBuffer(entry);
		}
	}

	/*!	Fill the buffer with the preivous entry in the history */
	void	ConsoleCore::resetFromPrevious()
	{
		std::wstring	entry;

		if (m_history.getPreviousEntry(entry))
		{
			resetBuffer(entry);
		}
	}

	/*!	Execute the current command stored in the buffer */
	void	ConsoleCore::execute()
	{
		std::wstring	result;

		if (m_buffer.empty())
			return;
		try
		{
			result = m_interpreter.execute(m_buffer);
			emitExecuted(result);
			m_history.pushEntry(m_buffer);
		}
		catch (ConsoleInterpreter::ArgumentTypeException const& e)
		{
			emitError(L"invalid argument type (" + std::to_wstring(e.getArgumentIndex()) + L"), expected type: " + e.getExpectedTypeName());
		}
		catch (ConsoleInterpreter::NotEnoughArgumentException const& e)
		{
			emitError(L"not enough arguments");
		}
		catch (ConsoleInterpreter::TooManyArgumentException const& e)
		{
			emitError(L"too many arguments");
		}
		catch (ConsoleInterpreter::UnknowCommandException const& e)
		{
			emitError(L"\'" + e.getCommandName() + L"\' is an unknow command");
		}
		catch (ConsoleInterpreter::SyntaxErrorException const& e)
		{
			emitError(L"syntax error at " + std::to_wstring(e.getPosition()) + L": " + e.getDescription());
		}
		m_buffer.clear();
		m_cursorPosition = 0;
		emitTextChanged();
		emitCursorChanged();
	}

	/*!	Return the current line */
	std::wstring const&	ConsoleCore::getBuffer()const
	{
		return (m_buffer);
	}

	unsigned int	ConsoleCore::getPromptSize()const
	{
		return (m_prompt.size());
	}
	
	std::vector<std::wstring>	ConsoleCore::getCommandList()const
	{
		return (m_interpreter.getCommandList());
	}
	
	void	ConsoleCore::emitTextChanged()
	{
		if (m_listener)
			m_listener->onTextChanged(m_prompt + m_buffer);
	}

	void	ConsoleCore::emitCursorChanged()
	{
		if (m_listener)
			m_listener->onCursorChanged(m_cursorPosition + m_prompt.size());
	}

	void	ConsoleCore::emitExecuted(std::wstring const& result)
	{
		if (m_listener)
			m_listener->onExecuted(result);
	}

	void	ConsoleCore::emitError(std::wstring const& message)
	{
		if (m_listener)
			m_listener->onError(message, m_buffer);
	}
}
