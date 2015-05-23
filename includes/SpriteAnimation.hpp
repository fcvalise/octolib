/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpriteAnimation.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 14:30:48 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 14:50:56 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITEANIMATION_HPP
# define SPRITEANIMATION_HPP
# include "AbstractFrameAnimation.hpp"

namespace octo
{
	class ByteArray;

	class SpriteAnimation : public octo::AbstractFrameAnimation<std::size_t>
	{
	public:
		virtual bool	loadFromMemory(ByteArray const& buffer);
	};
}

#endif
