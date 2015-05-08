/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:32:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/08 15:26:24 by irabeson         ###   ########.fr       */
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

		void				update(sf::Time frameTime);
		virtual void		onResized(sf::Event::SizeEvent const& event);
	private:
		sf::View			m_view;
		sf::View			m_guiView;
		float				m_zoomFactor;
	};
}

#endif
