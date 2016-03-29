/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:32:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/15 15:28:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP
# include "DefaultGraphicsListeners.hpp"
# include "NonCopyable.hpp"

# include <SFML/Graphics/View.hpp>

namespace octo
{
	class GraphicsManager;

	class Camera : public DefaultWindowListener,
				   public NonCopyable
	{
		friend class GraphicsManager;
	public:
		explicit Camera();

		void					setCenter(sf::Vector2f const& center);
		void					setCenter(float x, float y);
		void					move(sf::Vector2f const& offset);
		void					move(float offsetX, float offsetY);
		void					setRotation(float angle);
		void					rotate(float angle);
		void					setZoom(float factor);

		sf::Vector2f const&		getCenter()const;
		sf::Vector2f const&		getSize()const;
		sf::FloatRect const&	getRectangle()const;
		float					getRotation()const;
		float					getZoom()const;
		sf::View const&			getView()const;
		sf::View const&			getGuiView()const;

		sf::Vector2f			mapPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2f			mapGuiPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2i			mapCoordsToPixel(sf::Vector2f const& position)const;
		sf::Vector2i			mapGuiCoordsToPixel(sf::Vector2f const& position)const;

		void					setSize(sf::Vector2f const & size);
		void					update(sf::Time frameTime);
	private:
		virtual void			onResized(sf::Event::SizeEvent const& event);
		void					setup(GraphicsManager& graphics, sf::View const & cameraView);
		void					updateRectangle();
	private:
		GraphicsManager*	m_graphicsManager;
		sf::View			m_view;
		sf::View			m_guiView;
		sf::FloatRect		m_rectangle;
		float				m_zoomFactor;
	};
}

#endif
