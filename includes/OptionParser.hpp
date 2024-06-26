/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:28:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 11:32:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONPARSER_HPP
# define OPTIONPARSER_HPP
# include <string>

namespace octo
{
	/*!	\ingroup Core
	 *	\brief Option parser
	 */
	class OptionParser
	{
	public:
		static void	parseLine(std::string const& line, std::string& key, std::string& value);

		class SyntaxErrorException
		{
		public:
			explicit SyntaxErrorException(std::string const& message);

			std::string const&	what()const;
		private:
			std::string	m_message;
		};
	};
}

#endif
