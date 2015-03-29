/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/29 04:18:04 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:24:53 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTANIMATOR_HPP
# define ABSTRACTANIMATOR_HPP

namespace octo
{
	template <class T>
	class AbstractAnimator
	{
	public:
		void	update(sf::Time frameTime)
		{
			if (m_run)
			{
				m_elapsed += frameTime;
			}
		}
	private:
		float	m_elapsed;
	};
}

#endif
