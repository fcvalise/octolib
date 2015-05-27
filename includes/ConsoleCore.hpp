/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 18:05:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 02:20:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLECORE_HPP
# define CONSOLECORE_HPP
# include "ConsoleInterpreter.hpp"
# include "ConsoleHistory.hpp"

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

		void						setListener(IConsoleListener* listener);

		void						resetBuffer(std::wstring const& line);
		void						insertChar(wchar_t c);
		void						removeCurrent();
		void						removePrevious();
		void						removeAll();
		void						resetFromPrevious();
		void						resetFromNext();

		void						moveCursor(int offset);
		void						updateText();

		void						execute();

		std::wstring const&			getBuffer()const;
		unsigned int				getPromptSize()const;
		std::vector<std::wstring>	getCommandList()const;

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
	private:
		void						emitTextChanged();
		void						emitCursorChanged();
		void						emitExecuted(std::wstring const& result);
		void						emitError(std::wstring const& error);
	private:
		ConsoleInterpreter	m_interpreter;
		ConsoleHistory		m_history;
		std::wstring		m_buffer;
		std::wstring		m_prompt;
		unsigned int		m_cursorPosition;
		IConsoleListener*	m_listener;
	};
}

#include "ConsoleCore.hxx"
#endif
