/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterAnimation.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:21:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/20 16:07:55 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTERANIMATION_HPP
# define CHARACTERANIMATION_HPP
# include "AbstractFrameAnimation.hpp"
# include "CharacterFrame.hpp"

namespace octo
{
	class ByteArray;

	class CharacterAnimation : public AbstractFrameAnimation<CharacterFrame>
	{
	public:
		bool 	loadFromMemory(ByteArray const &buffer);		
	};	
}

#endif
