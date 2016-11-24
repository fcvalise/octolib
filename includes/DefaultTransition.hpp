/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultTransition.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 14:59:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:36:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTTRANSITION_HPP
# define DEFAULTTRANSITION_HPP
# include "AbstractTransition.hpp"

# include <SFML/Graphics/RectangleShape.hpp>

namespace octo
{
	/*!
	 *	\ingroup GameState
	 *	Fade in then fade out
	 */
	class BlackFadeTransition : public AbstractTransition
	{
	public:
		explicit BlackFadeTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!
	 *	\ingroup GameState
	 *	Fade in then fade out
	 */
	class WhiteFadeTransition : public AbstractTransition
	{
	public:
		explicit WhiteFadeTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!
	 *	\ingroup GameState
	 *	Fade in then fade out
	 */
	class RedFadeTransition : public AbstractTransition
	{
	public:
		explicit RedFadeTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!
	 *	\ingroup GameState
	 *	Fade in then fade out
	 */
	class BlueFadeTransition : public AbstractTransition
	{
	public:
		explicit BlueFadeTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!
	 *	\ingroup GameState
	 *	Black slide moving horizontally
	 */
	class BlackHSlideTransition : public octo::AbstractTransition
	{
	public:
		explicit BlackHSlideTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};

	/*!
	 *	\ingroup GameState
	 *	Black slide moving vertically
	 */
	class BlackVSlideTransition : public octo::AbstractTransition
	{
	public:
		explicit BlackVSlideTransition(Action action);

		virtual void	draw(sf::RenderTarget& render)const;
	private:
		virtual void	updateTransition(sf::Time, float timePosition, sf::View const& view);
	private:
		sf::RectangleShape	m_shape;
	};
}

#endif
