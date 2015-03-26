/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCompiler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 04:59:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 20:42:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGECOMPILER_HPP
# define PACKAGECOMPILER_HPP
# include "PackageHeader.hpp"

# include <vector>
# include <map>
# include <ostream>

namespace octo
{
	/*!	Package file compiler
	 *
	 *	This class archive ressource files into one unique file called
	 *	package.<br>
	 *	Progress of compilation can be followed with defining a listener
	 *	from PackageCompiler::IListener.
	 */
	class PackageCompiler
	{
		struct FileInfo;
		class FillHeader;

		typedef std::vector<FileInfo>							FileInfoArray;
		typedef std::map<std::string, PackageHeader::EntryType>	ExtensionMap;
	public:
		class IListener;

		PackageCompiler();

		void						setListener(IListener* listener);
		bool						compile(std::string const& outputFile,
											std::vector<std::string> const& paths);
	private:
		bool						getFileInfos(std::vector<std::string> const& paths,
												 FileInfoArray& fileInfos);
		FileInfo					getFileInfo(std::string const& path)const;
		bool						checkInputFile(std::string const& path);
		PackageHeader::EntryType	getTypeFor(std::string const& fileName)const;
		bool						writePackage(std::string const& outputFile, 
								 				 FileInfoArray const& fileInfos,
								 				 PackageHeader const& header);
		bool						writeFile(FileInfo const& info,
							  				  PackageHeader const& header,
							  				  std::ostream& out);
		bool						writeDefinitionFile(PackageHeader const& header);
		static bool					sortFileInfo(FileInfo const& left,
												 FileInfo const& right);
	private:
		typedef std::vector<char>	Mask;

		IListener*		m_listener;
		ExtensionMap	m_extensions;
		Mask			m_encryptionMask;
	};
	
	class PackageCompiler::IListener
	{
	public:
		virtual ~IListener(){}
		virtual void	headerBuilded(PackageHeader const& header) = 0;
		virtual void	copyingFile(std::string const& filePath,
									std::size_t current,
									std::size_t total) = 0;
		virtual void	finished(PackageHeader const& header) = 0;
		virtual void	error(std::string const& message) = 0;
	};
}

#endif
