/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractResourceLoadingState.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 15:31:08 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 15:56:52 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTRESOURCELOADINGSTATE_HPP
# define ABSTRACTRESOURCELOADINGSTATE_HPP
# include "AbstractState.hpp"
# include "IResourceListener.hpp"
# include "ResourceLoading.hpp"

# include <list>

namespace octo
{
	class AbstractResourceLoadingState : public AbstractState,
										 public IResourceListener
	{
	public:
		AbstractResourceLoadingState();

	private:
		virtual void		progress(std::string const& itemName,
									 PackageHeader::EntryType itemType,
									 std::uint64_t current,
									 std::uint64_t total);
		virtual void		error(std::string const& message);
		virtual void		finished();
	protected:
		void				pushLoading(std::string packageFileName);
		virtual void		start();
		virtual void		pause();
		virtual void		resume();
		virtual void		stop();
		virtual void		update(sf::Time frameTime);
		virtual void		onNoMoreLoading() = 0;

		std::string const	getCurrentKeyLoaded()const;
		std::string const	getCurrentTypeLoaded()const;
		std::uint64_t		getCurrentStep()const;
		std::uint64_t		getTotalSteps()const;
	private:
		std::list<ResourceLoading>	m_loadings;
		std::list<ResourceLoading>::iterator	m_currentLoading;
		std::list<std::string>		m_messages;
		std::string					m_currentKeyLoaded;
		std::string					m_currentTypeLoaded;
		std::uint64_t				m_currentStep;
		std::uint64_t				m_totalSteps;
		std::string					m_error;
	};
}

#endif
