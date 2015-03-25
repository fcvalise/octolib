/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCommons.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 06:09:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 17:30:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGECOMMONS_HPP
# define PACKAGECOMMONS_HPP
# include <string>
# include <fstream>

namespace octo
{
	namespace details
	{
		static inline bool fileExists(std::string const& path)
		{
			std::ifstream	is(path);

			return (is.is_open());
		}

		static inline std::uint64_t	getFileSize(std::string const& path)
		{
			std::ifstream	ifs(path.c_str());
			std::uint64_t	result = 0;

			ifs.seekg(0, std::ios_base::end);
			result = ifs.tellg();
			return (result);
		}

		static inline std::string	getExtension(std::string const& path)
		{
			std::string				result;
			std::string::size_type	dotPos = path.find_last_of(".");

			if (dotPos != std::string::npos)
			{
				result.assign(path, dotPos + 1, path.size() - (dotPos + 1));
			}
			return (result);
		}		

		static inline std::string	getBaseName(std::string const& path)
		{
			std::string				result;
			std::string::size_type	slashPos = path.find_last_of("/\\");

			if (slashPos == std::string::npos)
				slashPos = 0;
			else
				++slashPos;
			return (std::string(path, slashPos, path.size() - slashPos));
		}		
	}
}

#endif
