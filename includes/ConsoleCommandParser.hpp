/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:30:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 00:02:04 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLECOMMANDPARSER_HPP
# define CONSOLECOMMANDPARSER_HPP
# include <string>
# include <vector>

// TODO: move this file into details directory
namespace octo
{
	/*!	Console command line parser */
	class ConsoleCommandParser
	{
	public:
		/*!	Parse a line of text */
		static void	parseLine(std::wstring const& line,
							  std::wstring& name,
							  std::vector<std::wstring>& arguments);
	};
}

#endif
