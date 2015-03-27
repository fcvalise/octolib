/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceListener.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:14:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/27 23:09:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELISTENER_HPP
# define IRESOURCELISTENER_HPP
# include "PackageHeader.hpp"

namespace octo
{
	class IResourceListener
	{
	public:
		virtual ~IResourceListener(){}

		virtual void	progress(std::string const& name,
								 PackageHeader::EntryType type,
								 std::uint64_t current,
								 std::uint64_t total) = 0;
		virtual void	error(std::string const& message) = 0;
	};
}

#endif
