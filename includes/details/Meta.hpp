/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Meta.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 07:49:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 08:49:44 by irabeson         ###   ########.fr       */
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
	}
}

#endif
