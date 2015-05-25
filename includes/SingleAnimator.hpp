/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SingleAnimator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 14:54:40 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 15:37:32 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINGLEANIMATOR_HPP
# define SINGLEANIMATOR_HPP
# include "AbstractAnimator.hpp"
# include "IAnimation.hpp"

namespace octo
{
	template <class T>
	class SingleAnimator : public AbstractAnimator<T>
	{
	public:
		typedef IAnimation<T>	AnimationType;

		explicit SingleAnimator(AnimableProperty<T> const& property) :
			AbstractAnimator<T>(property),
			m_animation(nullptr)
		{
		}

		void	setAnimation(AnimationType const& animation)
		{
			m_animation = &animation;
		}
		
		IAnimation<T> const&	getCurrentAnimation()const
		{
			return (*m_animation);
		}
	private:
		AnimationType const*	m_animation;
	};
}

#endif
