/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimableProperty.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 17:10:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 15:13:58 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMABLEPROPERTY_HPP
# define ANIMABLEPROPERTY_HPP
# include <functional>

namespace octo
{
	/*!
	 *	\ingroup Animation
	 *	Define an animable property
	 *
	 *	This class is a wrapper around a function pointer which allows
	 *	to modify an arbitrary value.
	 */
	template <class T>
	class AnimableProperty
	{
	public:
		explicit AnimableProperty(void(*function)(T)) :
			m_setter(function)
		{
		}

		template <class O>
		AnimableProperty(O& object, void(O::*function)(T)) :
			m_setter(function, object)
		{
		}

		template <class F>
		explicit AnimableProperty(F&& functor) :
			m_setter(functor)
		{
		}

		AnimableProperty(AnimableProperty<T> const& other) = default;
		AnimableProperty(AnimableProperty<T>&& other) = default;
		AnimableProperty<T>& operator = (AnimableProperty<T> const& other) = default;

		inline void	setValue(T value)
		{
			m_setter(value);
		}
	private:
		std::function<void(T)>	m_setter;
	};
}

#endif
