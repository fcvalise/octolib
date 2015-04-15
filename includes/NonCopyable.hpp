/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NonCopyable.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 18:20:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 18:23:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NONCOPYABLE_HPP
# define NONCOPYABLE_HPP

namespace octo
{
	struct	NonCopyable
	{
		NonCopyable() = default;
		NonCopyable(NonCopyable const&) = delete;
		NonCopyable&	operator = (NonCopyable const&) = delete;
	};
}

#endif
