/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 18:09:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 23:07:31 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleCore.hpp"
#include "IConsoleListener.hpp"
#include "IConsoleCompletionListener.hpp"
#include <algorithm>
#include <cstdlib>

namespace octo
{
	ConsoleCore::ConsoleCore() :
		m_prompt(L"$> "),
		m_cursorPosition(0),
		m_completionEnabled(false),
		m_listener(nullptr),
		m_completionListener(nullptr)
	{
	}

	void	ConsoleCore::setCompletionEnabled(bool enable)
	{
		m_completionEnabled = enable;
		emitCompletionChanged();
	}

	void	ConsoleCore::nextCompletion()
	{
		m_completion.nextCompletion();
		emitCompletionChanged();
	}

	void	ConsoleCore::prevCompletion()
	{
		m_completion.prevCompletion();
		emitCompletionChanged();
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
		emitCompletionChanged();
	}

	void	ConsoleCore::setCompletionListener(IConsoleCompletionListener* listener)
	{
		m_completionListener = listener;
		emitCompletionChanged();
	}

	/*!	Insert a character at the cursor position */
	void	ConsoleCore::insertChar(wchar_t c)
	{
		m_buffer.insert(m_cursorPosition, 1, c);
		++m_cursorPosition;
		emitTextChanged();
		emitCursorChanged();
		emitCompletionChanged();
	}

	/*!	Insert a string at the cursor position */
	void	ConsoleCore::insertString(std::wstring const& str)
	{
		m_buffer.insert(m_cursorPosition, str);
		m_cursorPosition += str.size();
		emitTextChanged();
		emitCursorChanged();
		emitCompletionChanged();
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
		emitCompletionChanged();
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
		emitCompletionChanged();
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
		emitCompletionChanged();
	}

	/*!	Replace the current buffer content */
	void	ConsoleCore::resetBuffer(std::wstring const& line)
	{
		m_buffer = line;
		m_cursorPosition = m_buffer.size();
		emitTextChanged();
		emitCursorChanged();
		emitCompletionChanged();
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
		emitCompletionChanged();
	}

	/*!	Fill the buffer with the next entry in the history */
	void	ConsoleCore::resetFromNext()
	{
		std::wstring	entry;

		if (m_history.getNextEntry(entry))
		{
			resetBuffer(entry);
			setCompletionEnabled(false);
		}
	}

	/*!	Fill the buffer with the previous entry in the history */
	void	ConsoleCore::resetFromPrevious()
	{
		std::wstring	entry;

		if (m_history.getPreviousEntry(entry))
		{
			resetBuffer(entry);
			setCompletionEnabled(false);
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
		}
		catch (ConsoleInterpreter::ArgumentTypeException const& e)
		{
			emitError(L"interpreter: invalid argument type (" + std::to_wstring(e.getArgumentIndex()) + L"), expected type: " + e.getExpectedTypeName());
		}
		catch (ConsoleInterpreter::NotEnoughArgumentException const& e)
		{
			emitError(L"interpreter: not enough arguments (expected: " + std::to_wstring(e.getExpected()) + L" provided: " + std::to_wstring(e.getProvided()) + L")");
		}
		catch (ConsoleInterpreter::TooManyArgumentException const& e)
		{
			emitError(L"interpreter: too many arguments (expected: " + std::to_wstring(e.getExpected()) + L" provided: " + std::to_wstring(e.getProvided()) + L")");
		}
		catch (ConsoleInterpreter::UnknowCommandException const& e)
		{
			emitError(L"interpreter: \'" + e.getCommandName() + L"\' is an unknow command");
		}
		catch (ConsoleInterpreter::SyntaxErrorException const& e)
		{
			emitError(L"interpreter: syntax error at " + std::to_wstring(e.getPosition()) + L": " + e.getDescription());
		}
		setCompletionEnabled(false);
		m_history.pushEntry(m_buffer);
		m_buffer.clear();
		m_cursorPosition = 0;
		emitTextChanged();
		emitCursorChanged();
		emitCompletionChanged();
	}

	/*!	Complete the current buffer */
	void	ConsoleCore::complete()
	{
		std::wstring	completion;

		if (m_completionEnabled && m_completion.hasCompletions())
		{
			m_completion.getCurrentCompletion(completion);
			insertString(completion);
			setCompletionEnabled(false);
		}
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
	
	bool	ConsoleCore::isCompletionEnabled()const
	{
		return (m_completionEnabled);
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

	void	ConsoleCore::emitCompletionChanged()
	{
		// Find the beginning of the word under the cursor
		auto						start = m_buffer.find_last_of(L" \t\r\n\"(),", m_cursorPosition);
		std::wstring				word;
		std::wstring				current;

		if (start == std::wstring::npos)
			start = 0;
		else
			++start;
		word = m_buffer.substr(start, m_buffer.size() - start);
		if (word.empty())
			m_completionEnabled = false;
		m_completion.resetBuffer(word);
		m_completion.getCurrentCompletion(current);
		if (m_completionListener)
		{
			m_completion.getCurrentCompletion(current);
			m_completionListener->onCompletionChanged(
					IConsoleCompletionListener::Changes(m_completionEnabled && m_completion.hasCompletions(),
														word,
														current,
														start));
		}
	}
}
