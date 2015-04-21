/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:32:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/21 17:16:28 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class R, class ... A>
	void	Console::addCommand(std::wstring const& name, R(*function)(A...))
	{
		m_core.addCommand(name, function);
	}

	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		m_core.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		m_core.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		m_core.addCommand(name, instance, function);
	}

	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		m_core.addCommand(name, instance, function);
	}

	template <class F>
	void	Console::addCommand(std::wstring const& name, F&& functor)
	{
		m_core.addCommand(name, functor);
	}
}
