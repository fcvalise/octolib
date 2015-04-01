/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCompiler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 04:59:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/01 11:19:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGECOMPILER_HPP
# define PACKAGECOMPILER_HPP
# include "PackageHeader.hpp"
# include "ByteArray.hpp"

# include <vector>
# include <map>
# include <ostream>

namespace octo
{
	/*!
	 *	\ingroup Package
	 *	\class PackageCompiler
	 *	\brief Package file compiler
	 *
	 *	This class archive ressource files into one unique file called
	 *	package.<br>
	 *
	 *	A package file is an archive structured in 2 parts.<br>
	 *	\code
	 *	|-------------------------------------------------------|
	 *	|     HEADER DATAS     |          PACKED DATAS          |
	 *	|-------------------------------------------------------|
	 *	                        ^
	 *                          First byte of packed datas
	 *	\endcode
	 *
	 *	The first part called header is a table containing information about packed files data.<br>
	 *	More precisely, the base name (the name and extension of the file without the rest of the path), the
	 *	size (in byte), the type (Texture, Font, etc, see PackageHeader::EntryType), and the position offset.<br>
	 *	Position offset is the position of the first byte of a packaged file.<br> This position is relative
	 *	to the end of header datas so the first file packed is stored at offset 0, but his
	 *	real offset is the offset added to the bytes count of the header datas.<br>
	 *	<br>
	 *	The second part is the packed file datas one after the other.<br>
	 *	Datas packaged is trivialy encrypted to prevent the possibility of reading texts that can be present
	 *	in the packed data. The encoding is a simple XOR cipher and should not be used hoping to secure
	 *	datas.<br><br>
	 *	
	 */
	class PackageCompiler
	{
		struct FileInfo;
		class FillHeader;
		class FindInfoByName;

		typedef std::vector<FileInfo>							FileInfoArray;
		typedef std::map<std::string, PackageHeader::EntryType>	ExtensionMap;
	public:
		class IListener;

		PackageCompiler();

		/*!	Set a compilation listener
		 *
		 *	\param listener Pointer on a listener instance. The memory ownership of this 
		 *	is leaved to the user.
		 *
		 *	\code
		 *	class MyCompilationListener : public PackageCompiler::IListener
		 *	{
		 *		// Implement here the IListener interface...
		 *	};
		 *
		 *	PackageCompiler			compiler;
		 *	MyCompilationListener	listener;
		 *
		 *	compiler.setListener(&listener);
		 *	compiler.compile(...);
		 *
		 *	\endcode
		 */
		void						setListener(IListener* listener);

		/*!	Pack serveral files into one package file
		 *
		 *	Progress of compilation can be followed with an instance of IListener.<br>
		 *	When a file is packed, his resource type is defined from the file extension. For example
		 *	.png files gets type Texture, .ttf files gets type Font, .txt files gets type Text...<br>
		 *	For now a table of extension/type mapping is stored by the compiler and you can't change it
		 *	but in the future I probably implements somes setters to extend this table without
		 *	rebuilding the library.
		 *
		 *	\see PackageCompiler::IListener
		 */
		bool						compile(std::string const& outputFile,
											std::vector<std::string> const& paths);
	private:
		bool						getFileInfos(std::vector<std::string> const& paths,
												 FileInfoArray& fileInfos);
		FileInfo					getFileInfo(std::string const& path)const;
		bool						checkInputFile(std::string const& path,
												   FileInfoArray& fileInfos);
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
		IListener*		m_listener;
		ExtensionMap	m_extensions;
		ByteArray		m_encryptionMask;
		ByteArray		m_buffer;
	};
	
	/*!	Interface of compiler listener
	 *
	 *	This listener type is notified when the differents steps of compilation
	 *	are done or when errors occurs.
	 */
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
