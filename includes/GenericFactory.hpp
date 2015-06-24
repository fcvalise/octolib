/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GenericFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 04:03:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/24 05:27:36 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERICFACTORY_HPP
# define GENERICFACTORY_HPP
# include <map>
# include <stdexcept>
# include <functional>
# include <vector>

namespace octo
{
	/*!	\ingroup Core
	 *	\brief Generic factory template
	 *	\tparam K Type of key
	 *	\tparam B Type of base class
	 *	\tparam A Types passed to B constructor
	 */
	template <class K, class B, class ... A>
	class GenericFactory
	{
		typedef std::function<B*(A...)>	Creator;
	public:
		void			registerCreator(K const& key, Creator&& creator);

		template <class C>
		void			registerCreator(K const& key);

		B*				create(K const& key, A ... args)const;
		std::vector<K>	keys()const;
	private:
		std::map<K, Creator>	m_creators;
	};
}

#include "GenericFactory.hxx"
#endif
