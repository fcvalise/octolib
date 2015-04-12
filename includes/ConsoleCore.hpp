/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 18:05:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/11 21:36:31 by irabeson         ###   ########.fr       */
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
	 *
	 */
	class ConsoleCore
	{
	public:
		ConsoleCore();

		void						setListener(IConsoleListener* listener);
		void						insertChar(wchar_t c);
		void						removeCurrent();
		void						removePrevious();
		void						removeAll();
		void						moveCursor(int offset);

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
	private:
		void			emitTextChanged();
		void			emitCursorChanged();
		void			emitExecuted(std::wstring const& result);
		void			emitError(std::wstring const& error);
	private:
		ConsoleInterpreter	m_interpreter;
		std::wstring		m_buffer;
		std::wstring		m_prompt;
		unsigned int		m_cursorPosition;
		IConsoleListener*	m_listener;
	};

	template <class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, R(*function)(A...))
	{
		m_interpreter.addCommand(name, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		m_interpreter.addCommand(name, instance, function);
	}

	template <class F>
	void	ConsoleCore::addCommand(std::wstring const& name, F&& functor)
	{
		m_interpreter.addCommand(name, functor);
	}
}

#endif
