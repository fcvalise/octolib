/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 18:05:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/25 23:11:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLECORE_HPP
# define CONSOLECORE_HPP
# include "ConsoleInterpreter.hpp"

namespace octo
{
	class IConsoleListener;

	/*!
	 *	\ingroup Console
	 *	\class ConsoleCore
	 *	\brief Core of console
	 *	
	 *	The core store current line into a buffer and can start execution
	 *	with an interpreter.<br>
	 *	The core is rendering agnostic. Any class who implements IConsoleListener
	 *	interface will be receives all events requiered to render this console
	 *	system.<br>
	 *	The IConsoleListener instance defined by setListener() is
	 *	notified when a command is executed, on syntax error, etc....<br>
	 *
	 */
	class ConsoleCore
	{
	public:
		ConsoleCore();

		/*!	Define the unique listener */
		void						setListener(IConsoleListener* listener);

		/*!	Insert a character at the cursor position */
		void						insertChar(wchar_t c);

		/*!	Remove the character at the cursor position */
		void						removeCurrent();

		/*!	Remove the character before the cursor position */
		void						removePrevious();

		/*!	Clear the buffer */
		void						removeAll();

		/*!	Replace the current buffer content */
		void						resetBuffer(std::wstring const& line);

		/*!	Return the current line */
		std::wstring const&			getBuffer()const;

		/*! Move the cursor */
		void						moveCursor(int offset);

		/*! Force to notify the listener of a text change */
		void						updateText();

		/*!	Execute the current command stored in the buffer */
		void						execute();

		template <class R, class ... A>
		void						addCommand(std::wstring const& name, R(*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		template <class F>
		void						addCommand(std::wstring const& name, F&& functor);

		unsigned int				getPromptSize()const;
		std::vector<std::wstring>	getCommandList()const;
	private:
		void						emitTextChanged();
		void						emitCursorChanged();
		void						emitExecuted(std::wstring const& result);
		void						emitError(std::wstring const& error);
	private:
		ConsoleInterpreter	m_interpreter;
		std::wstring		m_buffer;
		std::wstring		m_prompt;
		unsigned int		m_cursorPosition;
		IConsoleListener*	m_listener;
	};
}

#include "ConsoleCore.hxx"
#endif
