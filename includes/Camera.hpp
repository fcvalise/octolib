/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:32:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/08 16:49:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP
# include "DefaultGraphicsListeners.hpp"

# include <SFML/Graphics/View.hpp>

namespace octo
{
	class GraphicsManager;

	/*!
	 *	\ingroup Graphics
	 *	\class Camera
	 *	\brief Camera
	 *
	 *	Camera provides unified view controls.
	 */
	class Camera : public DefaultWindowListener
	{
	public:
		explicit Camera();

		void				setup(GraphicsManager& graphics);
		void				setCenter(sf::Vector2f const& center);
		void				setCenter(float x, float y);
		void				move(sf::Vector2f const& offset);
		void				move(float offsetX, float offsetY);
		void				setRotation(float angle);
		void				rotate(float angle);
		void				setZoom(float factor);

		sf::Vector2f const&	getCenter()const;
		sf::Vector2f const&	getSize()const;
		float				getRotation()const;
		float				getZoom()const;
		sf::View const&		getView()const;
		sf::View const&		getGuiView()const;

		sf::Vector2f		mapPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2f		mapGuiPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2i		mapCoordsToPixel(sf::Vector2f const& position)const;
		sf::Vector2i		mapGuiCoordsToPixel(sf::Vector2f const& position)const;

		void				update(sf::Time frameTime);
		virtual void		onResized(sf::Event::SizeEvent const& event);
	private:
		GraphicsManager*	m_graphicsManager;
		sf::View			m_view;
		sf::View			m_guiView;
		float				m_zoomFactor;
	};
}

#endif
