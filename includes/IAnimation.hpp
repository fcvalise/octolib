/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAnimation.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:22:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 18:26:24 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IANIMATION_HPP
# define IANIMATION_HPP
# include <SFML/System/Time.hpp>

namespace octo
{
	enum class LoopMode : std::uint8_t
	{
		NoLoop,
		Loop
	};

	template <class T>
	class IAnimation
	{
	public:
		virtual ~IAnimation(){}

		virtual T const&	value(sf::Time currentTime)const = 0;
		virtual sf::Time	duration()const = 0;
		virtual LoopMode	loopMode()const = 0;
		virtual bool		loadFromMemory(char* data, std::size_t) = 0;
		virtual bool		loadFromFile(std::string const& fileName) = 0;
		virtual bool		saveToFile(std::string const& fileName)const = 0;	
	};
}

#endif
