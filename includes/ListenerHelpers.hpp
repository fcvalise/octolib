/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenerHelpers.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 18:13:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 12:09:32 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENERHELPERS_HPP
# define LISTENERHELPERS_HPP
# include <vector>

namespace octo
{
	template <class T>
	using ListenerArray = std::vector<T*>;

	template <class T>
	static void	appendListener(T* listener, ListenerArray<T>& container)
	{
		if (std::find(container.begin(), container.end(), listener) == container.end())
			container.push_back(listener);
	}

	template <class T>
	static void	removeListener(T* listener, ListenerArray<T>& container)
	{
		container.erase(std::find(container.begin(), container.end(), listener));
	}
}

#endif
