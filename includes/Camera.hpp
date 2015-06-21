/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:32:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/21 02:53:26 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP
# include "DefaultGraphicsListeners.hpp"
# include "ListenerHelpers.hpp"

# include <SFML/Graphics/View.hpp>

namespace octo
{
	class GraphicsManager;

	class ICameraListener
	{
	public:
		virtual ~ICameraListener() = default;
		virtual void	onCenterChanged(sf::Vector2f const& newCenter) = 0;
		virtual void	onRotationChanged(float newRotation) = 0;
		virtual void	onZoomChanged(float newFactor) = 0;
		virtual void	onSizeChanged(sf::Vector2f const& newSize) = 0;
	};

	class Camera : public DefaultWindowListener
	{
		friend class GraphicsManager;
	public:
		explicit Camera();

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
		sf::FloatRect		getRectangle()const;
		sf::View const&		getView()const;
		sf::View const&		getGuiView()const;

		sf::Vector2f		mapPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2f		mapGuiPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2i		mapCoordsToPixel(sf::Vector2f const& position)const;
		sf::Vector2i		mapGuiCoordsToPixel(sf::Vector2f const& position)const;

		void				update(sf::Time frameTime);
		void				addListener(ICameraListener* listener);
		void				removeListener(ICameraListener* listener);
	private:
		virtual void		onResized(sf::Event::SizeEvent const& event);
		void				setup(GraphicsManager& graphics);
	private:
		GraphicsManager*				m_graphicsManager;
		sf::View						m_view;
		sf::View						m_guiView;
		float							m_zoomFactor;
		ListenerArray<ICameraListener>	m_listeners;
	};
}

#endif
