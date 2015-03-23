/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultTransition.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 14:59:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 15:25:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTTRANSITION_HPP
# define DEFAULTTRANSITION_HPP
# include "AbstractTransition.hpp"

# include <SFML/Graphics/RectangleShape.hpp>

namespace octo
{
	/*!	Fade in then fade out */
	class BlackFadeTransition : public AbstractTransition
	{
	public:
		BlackFadeTransition(sf::View const& view, Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!	Black slide moving horizontally */
	class BlackHSlideTransition : public octo::AbstractTransition
	{
	public:
		BlackHSlideTransition(sf::View const& view, Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!	Black slide moving vertically */
	class BlackVSlideTransition : public octo::AbstractTransition
	{
	public:
		BlackVSlideTransition(sf::View const& view, Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition);
	private:
		sf::RectangleShape	m_shape;
	};
}

#endif
