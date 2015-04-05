/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:30:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/03 09:20:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLECOMMANDPARSER_HPP
# define CONSOLECOMMANDPARSER_HPP
# include <string>
# include <vector>

namespace octo
{
	class ConsoleCommandParser
	{
	public:
		static bool	parseLine(std::wstring const& line,
							  std::wstring& name,
							  std::vector<std::wstring>& arguments);
	};
}

#endif
