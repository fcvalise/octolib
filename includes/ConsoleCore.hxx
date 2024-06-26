/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCore.hxx                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:42:24 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 22:30:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, R(*function)(A...))
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleCore::addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, instance, function);
	}

	template <class F>
	void	ConsoleCore::addCommand(std::wstring const& name, F&& functor)
	{
		m_completion.addWord(name, ConsoleCompletion::Lexems::Command);
		m_interpreter.addCommand(name, functor);
	}
}
