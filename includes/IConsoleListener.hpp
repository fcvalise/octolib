/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IConsoleListener.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 19:47:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 22:49:11 by irabeson         ###   ########.fr       */
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

		/*! Method called when the buffer content has been changed */
		virtual void	onTextChanged(std::wstring const& text) = 0;

		/*! Method called when the cursor position has been changed */
		virtual void	onCursorChanged(unsigned int pos) = 0;

		/*! Method called when the buffer content has been executed */
		virtual void	onExecuted(std::wstring const& result) = 0;

		/*! Method called when an error has been occured */
		virtual void	onError(std::wstring const& message, std::wstring const& line) = 0;
	};
}

#endif
