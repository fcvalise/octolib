/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GenericFactory.hxx                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:11:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/11 16:35:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <type_traits>

namespace octo
{
	template <class K, class B, class ... A>
	void		GenericFactory<K, B, A...>::registerCreator(K const& key, Creator&& creator)
	{
		m_creators.emplace(key, creator);
	}

	template <class K, class B, class ... A>
	template <class C>
	void		GenericFactory<K, B, A...>::registerCreator(K const& key)
	{
		static_assert(std::is_base_of<B, C>::value, "C must be derived from B");

		registerCreator(key, [](A ... args)
			{
				return (new C(std::forward<A>(args)...));
			});
	}

	template <class K, class B, class ... A>
	B*			GenericFactory<K, B, A...>::create(K const& key, A ... args)const
	{
		auto	it = m_creators.find(key);

		if (it == m_creators.end())
			throw std::range_error("generic factory: key not found");
		return (it->second(std::forward<A>(args)...));
	}

	template <class K, class B, class ... A>
	std::vector<K>	GenericFactory<K, B, A...>::keys()const
	{
		std::vector<K>	results;

		results.reserve(m_creators.size());
		for (auto const& pair : m_creators)
			results.push_back(pair.first);
		return (results);
	}
}
