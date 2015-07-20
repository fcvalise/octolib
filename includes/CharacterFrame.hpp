/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterFrame.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:20:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/20 17:17:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTERFRAME_HPP
# define CHARACTERFRAME_HPP
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Rect.hpp>

namespace octo
{
	class BinaryInputStream;

	class CharacterFrame
	{
	public:
		void					loadFromMemory(BinaryInputStream& is);

		sf::FloatRect const&	getBox()const;
		sf::Vector2f const&		getHotPoint()const;
		std::size_t				getTextureRectangleId()const;
	
		friend bool				operator != (CharacterFrame const& left, CharacterFrame const& right);
	private:
		sf::FloatRect	m_box;
		sf::Vector2f	m_hotPoint;
		std::size_t		m_textureRectangleId;
	};

	inline bool	operator != (CharacterFrame const& left, CharacterFrame const& right)
	{
		return (left.m_box != right.m_box ||
				left.m_hotPoint != right.m_hotPoint ||
				left.m_textureRectangleId != right.m_textureRectangleId);
	}
}

#endif
