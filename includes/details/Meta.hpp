/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Meta.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 07:49:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 12:51:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_HPP
# define META_HPP

namespace octo
{
	namespace details
	{
		template <class H, class ... T>
		struct	TotalSizeofImp
		{
			static constexpr std::size_t const	Value = sizeof(H) + TotalSizeofImp<T...>::Value;
		};

		template <class H>
		struct	TotalSizeofImp<H>
		{
			static constexpr std::size_t const	Value = sizeof(H);
		};

		template <class ... T>
		static constexpr inline std::size_t totalSizeOf()
		{
			return (TotalSizeofImp<T...>::Value);
		}

		/*!
		 *	\struct IndexOf
		 *	\brief Get index of a type in a list of types
		 *	\tparam T Searched type
		 *	\tparam Head First type of type list
		 *	\tparam Tail Types remaining in the type list
		 *
		 *	\code
		 *	std::cout << IndexOf<int, char, double, int, std::string>::Value << std:endl;
		 *
		 *	\endcode
		 */
		template <class T, class Head, class ... Tail>
		struct	IndexOf
		{
			static constexpr std::size_t	Value = 1u + IndexOf<T, Tail...>::Value;
		};

		template <class T, class ... Tail>
		struct	IndexOf<T, T, Tail...>
		{
			static constexpr std::size_t	Value = 0u;
		};
	}
}

#endif
