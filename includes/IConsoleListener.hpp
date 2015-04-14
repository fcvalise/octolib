/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IConsoleListener.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 19:47:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 14:01:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICONSOLELISTENER_HPP
# define ICONSOLELISTENER_HPP
# include <string>

namespace octo
{
	class IConsoleListener
	{
	public:
		virtual ~IConsoleListener() = default;

		virtual void	onTextChanged(std::wstring const& text) = 0;
		virtual void	onCursorChanged(unsigned int pos) = 0;
		virtual void	onExecuted(std::wstring const& result) = 0;
		virtual void	onError(std::wstring const& message, std::wstring const& line) = 0;
	};
}

#endif
