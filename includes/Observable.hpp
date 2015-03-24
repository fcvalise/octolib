/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Observable.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 17:39:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 17:46:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSERVABLE_HPP
# define OBSERVABLE_HPP
# include <vector>

namespace octo
{
	template <class ... A>
	class Observable
	{
	public:
		class AbstractObserver;

		void	addObserver(AbstractObserver* observer)
		{
			m_observers.push_back(observer);
		}

		void	removeObserver(AbstractObserver* observer)
		{
			m_observers.erase(std::find(m_observers.begin(), m_observers.end(), observer));
		}

		void	notifyAll(A const& args...)
		{
			for (auto* observer : m_observers)
			{
				observer->notified(args...);
			}
		}
	private:
		std::vector<AbstractObserver>	m_observers;
	};

	template <class ... A>
	class Observable<A...>::AbstractObserver
	{
	public:
		virtual ~AbstractObserver()
		{
		}
	private:
		virtual void	notified(A const& args...) = 0;
	};
}

#endif
