/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAnimation.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:22:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 14:51:07 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IANIMATION_HPP
# define IANIMATION_HPP
# include <SFML/System/Time.hpp>
# include <cstdint>

namespace octo
{
	class ByteArray;

	/*!
	 *	\ingroup Animation
	 *	Loop modes
	 */
	enum class LoopMode : std::uint8_t
	{
		NoLoop,
		Loop
	};

	/*!
	 *	\ingroup Animation
	 *	Animation interface
	 */
	template <class T>
	class IAnimation
	{
	public:
		/*!	Type of values animated */
		typedef	T	ValueType;

		virtual ~IAnimation(){}

		/*!	Return the value for a time given */
		virtual T const&	value(sf::Time currentTime)const = 0;

		/*!	Return the total duration of the animation */
		virtual sf::Time	duration()const = 0;

		/*!	Return the loop mode */
		virtual LoopMode	loopMode()const = 0;

		/*!	Load animation datas from memory */
		virtual bool		loadFromMemory(ByteArray const& buffer) = 0;
	};
}

#endif
