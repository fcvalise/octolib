/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpectChar.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 17:54:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 20:11:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPECTCHAR_HPP
# define EXPECTCHAR_HPP
# include <iostream>

namespace octo
{
	template <class C>
	struct	BasicExceptChar
	{
		explicit BasicExceptChar(C c);

		void	read(std::basic_istream<C>& is)const;
	private:
		C const	m_char;
	};

	template <class C, class Traits>
	std::basic_istream<C, Traits> &operator >> (std::basic_istream<C, Traits>& is, BasicExceptChar<C>&& ec);

	typedef BasicExceptChar<char>		ExpectChar;
	typedef BasicExceptChar<wchar_t>	WExpectChar;
}

#include "ExpectChar.hxx"
#endif
