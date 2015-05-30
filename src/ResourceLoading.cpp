/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceLoading.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 10:54:26 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 15:30:57 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceLoading.hpp"
#include "IResourceListener.hpp"

namespace octo
{
	class ResourceLoadingImp
	{
	public:
		ResourceLoadingImp() :
			m_listener(nullptr)
		{
		}

		ResourceLoadingImp(PackageReader&& reader, ResourceLoading::LoadActions&& actions, IResourceListener* listener) :
			m_reader(std::move(reader)),
			m_actions(std::move(actions)),
			m_listener(listener)
		{
		}

		bool	loadOne()
		{
			auto	it = m_actions.begin();
			bool	result = false;

			if (it != m_actions.end())
			{
				result = (*it)(m_reader, m_listener);
				m_actions.erase(it);
			}
			if (m_actions.empty() && m_listener)
			{
				m_listener->finished();
			}
			return (result);
		}

		bool	isFinished()const
		{
			return (m_actions.empty());
		}
	private:
		PackageReader					m_reader;
		ResourceLoading::LoadActions	m_actions;
		IResourceListener*				m_listener;
	};

	ResourceLoading::ResourceLoading()
	{
	}

	ResourceLoading::ResourceLoading(PackageReader&& reader, LoadActions&& actions, IResourceListener* listener) :
		m_imp(new ResourceLoadingImp(std::move(reader), std::move(actions), listener))
	{
	}

	bool	ResourceLoading::loadOne()
	{
		if (m_imp == nullptr)
			return (false);
		return (m_imp->loadOne());
	}

	bool	ResourceLoading::isFinished()const
	{
		return (m_imp == nullptr || m_imp->isFinished());
	}
}
