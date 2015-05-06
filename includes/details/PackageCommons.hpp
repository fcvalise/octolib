/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCommons.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 06:09:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 12:01:55 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGECOMMONS_HPP
# define PACKAGECOMMONS_HPP
# include <string>
# include <fstream>
# include <random>
# include "ByteArray.hpp"

namespace octo
{
	namespace details
	{
		static constexpr std::size_t const		PackageEncryptionMaskSize = 1024;

		static inline std::string toLower(std::string str)
		{
			std::for_each(str.begin(), str.end(), [](char& c){c = std::tolower(c);});
			return (str);
		}

		/*!	Check if a file exists */
		static inline bool fileExists(std::string const& path)
		{
			std::ifstream	is(path);

			return (is.is_open());
		}

		/*!	Compute file size in bytes */
		static inline std::uint64_t	getFileSize(std::string const& path)
		{
			std::ifstream	ifs(path.c_str());
			std::uint64_t	result = 0;

			ifs.seekg(0, std::ios_base::end);
			result = ifs.tellg();
			return (result);
		}

		/*!	Get file extension from a complete file path */
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

		/*!	Get base name from a complete file path */
		static inline std::string	getBaseName(std::string const& path)
		{
			std::string::size_type	slashPos = path.find_last_of("/\\");

			if (slashPos == std::string::npos)
				slashPos = 0;
			else
				++slashPos;
			return (std::string(path, slashPos, path.size() - slashPos));
		}

		/*!	Generate a pseudo random series of bytes */
		static void	generateMask(ByteArray& mask, std::size_t size, std::size_t seed)
		{
			std::mt19937						engine(seed);
			std::uniform_int_distribution<char>	distribution(std::numeric_limits<char>::min(),
															 std::numeric_limits<char>::max());

			mask.resize(size);
			std::generate(mask.begin(), mask.end(), std::bind(distribution, engine));
		}

		/*!	Perform a simple xor encryption
		 *	\param beginBytes
		 */
		template <class I>
		static void	xorEncryptDecrypt(I beginBytes, I endBytes,
									  ByteArray const& mask)
		{
			std::size_t	i = 0;

			while (beginBytes != endBytes)
			{
				*beginBytes = *beginBytes xor mask[i % mask.size()];
				++i;
				++beginBytes;
			}
		}
	}
}

#endif
