/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimableProperty.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 17:10:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 17:10:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMABLEPROPERTY_HPP
# define ANIMABLEPROPERTY_HPP

namespace octo
{
	template <class T>
	class AnimableProperty
	{
	public:
		explicit AnimableProperty(void(*function)(T)) :
			m_setter(function)
		{
		}

		template <class O>
		explicit AnimableProperty(O& object, void(O::*function)(T)) :
			m_setter(function)
		{
		}

		template <class F>
		explicit AnimableProperty(F&& functor) :
			m_setter(functor)
		{
		}

		AnimableProperty(AnimableProperty<T> const& other) = default;
		AnimableProperty(AnimableProperty<T>&& other) = default;

		AnimableProperty<T>& operator = (AnimableProperty<T> const& other)
		{
			std::swap(m_setter, other.m_setter);
			return (*this);
		}

		void	setValue(T value)
		{
			m_setter(value);
		}
	private:
		std::function<void(T)>	m_setter;
	};
}

#endif
