/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultTransition.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 14:59:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 19:58:24 by irabeson         ###   ########.fr       */
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
		explicit BlackFadeTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!	Black slide moving horizontally */
	class BlackHSlideTransition : public octo::AbstractTransition
	{
	public:
		explicit BlackHSlideTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!	Black slide moving vertically */
	class BlackVSlideTransition : public octo::AbstractTransition
	{
	public:
		explicit BlackVSlideTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(float, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};
}

#endif
