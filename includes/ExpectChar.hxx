/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpectChar.hxx                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 17:54:19 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 17:01:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	/*!
		\class BasicExceptChar
		\brief Change the state of the input stream if the char readed is not expected.
		\code
		// Expect an integer surrounded by []
		int	x = 0;

		std::cin >> ExpectChar('[') >> x >> ExpectChar(']');
		\endcode
	*/

	/*!	Construct an instance with defining the expected char */
	template <class C>
	BasicExceptChar<C>::BasicExceptChar(C c) :
		m_char(c)
	{
	}

	template <class C>
	void	BasicExceptChar<C>::read(std::istream& is)const
	{
		C	temp = C(0);

		is >> temp;
		if (temp != m_char)
		{
			is.setstate(std::ios_base::failbit);
		}
	}

	template <class C, class Traits>
	std::basic_istream<C, Traits> &operator >> (std::basic_istream<C, Traits>& is, BasicExceptChar<C>&& ec)
	{
		typename std::basic_istream<C, Traits>::sentry init(is);

		if (init)
		{
			ec.read(is);
		}
		return (is);
	}
}
