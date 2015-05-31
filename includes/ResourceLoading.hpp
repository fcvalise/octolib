/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceLoading.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 10:50:27 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 11:10:55 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCELOADING_HPP
# define RESOURCELOADING_HPP
# include "PackageReader.hpp"

# include <list>
# include <functional>

namespace octo
{
	class PackageReader;
	class IResourceListener;
	class ResourceLoadingImp;

	class ResourceLoading
	{
	public:
		typedef std::function<bool(PackageReader&, IResourceListener*)>	LoadAction;
		typedef std::list<LoadAction>									LoadActions;

		ResourceLoading();
		ResourceLoading(PackageReader&& reader, LoadActions&& actions, IResourceListener* listener);

		bool	loadOne();
		bool	isFinished()const;
	private:
		std::shared_ptr<ResourceLoadingImp>	m_imp;
	};
}

#endif
