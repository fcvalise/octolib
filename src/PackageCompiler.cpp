/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCompiler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 06:01:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 04:41:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PackageCompiler.hpp"
#include "details/PackageCommons.hpp"

#include <map>
#include <iterator>
#include <fstream>
#include <limits>

namespace octo
{
	struct PackageCompiler::FileInfo
	{
		std::string					path;
		std::string					name;
		std::uint64_t				size;
		PackageHeader::EntryType	type;
	};

	class PackageCompiler::FillHeader
	{
	public:
		explicit FillHeader(PackageHeader& header) :
			m_header(header),
			m_offset(0)
		{
		}

		void	operator()(PackageCompiler::FileInfo const& fileInfo)
		{
			m_header.addEntry(fileInfo.type, fileInfo.name,
							  m_offset, fileInfo.size);
			m_offset += fileInfo.size;
		}
	private:
		PackageHeader&	m_header;
		std::uint64_t	m_offset;
	};

	PackageCompiler::PackageCompiler() :
		m_listener(nullptr),
		m_extensions
		{
			{"ttf", PackageHeader::EntryType::Font},
			{"otf", PackageHeader::EntryType::Font},
			{"bmp", PackageHeader::EntryType::Texture},
			{"png", PackageHeader::EntryType::Texture},
			{"tga", PackageHeader::EntryType::Texture},
			{"jpg", PackageHeader::EntryType::Texture},
			{"psd", PackageHeader::EntryType::Texture},
			{"hdr", PackageHeader::EntryType::Texture},
			{"pic", PackageHeader::EntryType::Texture},
			{"ogg", PackageHeader::EntryType::Sound},
			{"wav", PackageHeader::EntryType::Sound},
			{"flac", PackageHeader::EntryType::Sound},
			{"aiff", PackageHeader::EntryType::Sound},
			{"au", PackageHeader::EntryType::Sound},
			{"raw", PackageHeader::EntryType::Sound},
			{"paf", PackageHeader::EntryType::Sound},
			{"svx", PackageHeader::EntryType::Sound},
			{"nist", PackageHeader::EntryType::Sound},
			{"voc", PackageHeader::EntryType::Sound},
			{"ircam", PackageHeader::EntryType::Sound},
			{"w64", PackageHeader::EntryType::Sound},
			{"mat4", PackageHeader::EntryType::Sound},
			{"mat5", PackageHeader::EntryType::Sound},
			{"pvf", PackageHeader::EntryType::Sound},
			{"htk", PackageHeader::EntryType::Sound},
			{"sds", PackageHeader::EntryType::Sound},
			{"caf", PackageHeader::EntryType::Sound},
			{"wve", PackageHeader::EntryType::Sound},
			{"mpc2k", PackageHeader::EntryType::Sound},
			{"rf64", PackageHeader::EntryType::Sound},
			{"txt", PackageHeader::EntryType::Text},
			{"conf", PackageHeader::EntryType::Text},
			{"json", PackageHeader::EntryType::Text},
			{"xml", PackageHeader::EntryType::Text}
		}
	{
	}

	void	PackageCompiler::setListener(IListener* listener)
	{
		m_listener = listener;
	}

	bool	PackageCompiler::compile(std::string const& outputFile,
									 std::vector<std::string> const& paths)
	{
		FileInfoArray	fileInfos;
		PackageHeader	header;

		if (getFileInfos(paths, fileInfos) == false)
			return (false);
		std::for_each(fileInfos.begin(), fileInfos.end(), FillHeader(header));
		if (writePackage(outputFile, fileInfos, header) == false)
			return (false);
		if (writeDefinitionFile(header) == false)
			return (false);
		return (true);
	}

	bool	PackageCompiler::getFileInfos(std::vector<std::string> const& paths, FileInfoArray& fileInfos)
	{
		for (auto const& path : paths)
		{
			if (checkInputFile(path))
			{
				fileInfos.emplace_back(getFileInfo(path));
			}
		}
		std::sort(fileInfos.begin(), fileInfos.end(), sortFileInfo);
		return (fileInfos.empty() == false);
	}
	
	PackageCompiler::FileInfo	PackageCompiler::getFileInfo(std::string const& path)const
	{
		FileInfo	result{path, details::getBaseName(path),
						   details::getFileSize(path), getTypeFor(path)};

		return (result);
	}

	bool	PackageCompiler::checkInputFile(std::string const& path)
	{
		std::string					baseName;
		PackageHeader::EntryType	type;

		if (details::fileExists(path) == false)
		{
			if (m_listener)
				m_listener->error("input file not found: '" + path + "'");
			return (false);
		}
		baseName = details::getBaseName(path);
		if (baseName.empty())
		{
			if (m_listener)
				m_listener->error("invalid input file: '" + path + "'");
			return (false);
		}
		type = getTypeFor(path);
		if (type == PackageHeader::EntryType::Invalid)
		{
			if (m_listener)
				m_listener->error("unsupported input file format: '" + path + "'");
			return (false);
		}
		return (true);
	}

	PackageHeader::EntryType	PackageCompiler::getTypeFor(std::string const& fileName)const
	{
		std::string	extension = details::getExtension(fileName);
		auto		it = m_extensions.find(extension);

		if (it == m_extensions.end())
			return (PackageHeader::EntryType::Invalid);
		else
			return (it->second);
	}

	bool	PackageCompiler::writePackage(std::string const& outputFile, 
							 			  FileInfoArray const& fileInfos,
							 			  PackageHeader const& header)
	{
		std::ofstream	out(outputFile.c_str(), std::ios_base::binary);
		std::size_t		i = 0;

		if (out.is_open() == false)
		{
			if (m_listener)
				m_listener->error("output file cannot be opened: '" + outputFile + "'");
			return (false);
		}
		header.write(out);
		for (auto const& fileInfo : fileInfos)
		{
			if (m_listener)
			{
				m_listener->copyingFile(fileInfo.path, i, fileInfos.size());
			}
			if (writeFile(fileInfo, header, out) == false)
				return (false);
			++i;
		}
		return (true);
	}

	bool	PackageCompiler::writeFile(FileInfo const& info, PackageHeader const& header,
									   std::ostream& out)
	{
		std::ifstream			input(info.path, std::ios_base::binary);
		std::unique_ptr<char[]>	buffer;

		if (input.is_open() == false)
		{
			if (m_listener)
				m_listener->error("input file cannot be opened: '" + info.path + "'");
			return (false);
		}
		buffer.reset(new char[info.size]);
		input.read(buffer.get(), info.size);
		if (input.gcount() != std::streamsize(info.size))
		{
			if (m_listener)
				m_listener->error("unable to read input file: '" + info.path + "'");
			return (false);
		}
		// TODO XOR buffer
		out.write(buffer.get(), info.size);
		return (true);
		static_cast<void>(header);
	}

	namespace
	{
		static std::string	makeSymbolName(std::string str)
		{
			std::for_each(std::begin(str), std::end(str), [](char& c)
				{
					if (std::isspace(c) || std::ispunct(c))
					{
						c = '_';
					}
					else
					{
						c = std::toupper(c);
					}
				});
			return (str);
		}

		static std::string	getNow()
		{
			std::chrono::time_point<std::chrono::system_clock>	now = std::chrono::system_clock::now();
			std::time_t											nowTime = std::chrono::system_clock::to_time_t(now);
			std::string											str(std::ctime(&nowTime));

			if (str.back() == '\n')
				str.pop_back();
			return (str);
		}

		static std::map<PackageHeader::EntryType, std::string> const	EntryTypeLabels
		{
			{octo::PackageHeader::EntryType::Font, "FONTS"},
			{octo::PackageHeader::EntryType::Texture, "TEXTURES"},
			{octo::PackageHeader::EntryType::Sound, "SOUNDS"},
			{octo::PackageHeader::EntryType::Text, "TEXTS"},
			{octo::PackageHeader::EntryType::Invalid, "INVALID"}
		};

		std::string	getEntryTypeLabel(PackageHeader::EntryType type)
		{
			auto it = EntryTypeLabels.find(type);

			if (it == EntryTypeLabels.end())
				return ("UNKNOWN");
			else
				return (it->second);
		}
	}

	bool	PackageCompiler::writeDefinitionFile(PackageHeader const& header)
	{
		std::ofstream										out("ResourceDefinitions.hpp");
		std::vector<std::string>							lineBegins;
		std::string											lineBegin;
		std::size_t											maxSize = 0;
		std::uint64_t										key = 0;
		PackageHeader::EntryType							lastType = PackageHeader::EntryType::Invalid;

		if (out.is_open() == false)
		{
			if (m_listener)
				m_listener->error("unable to open resource definition file: 'ResourceDefinitions.hpp'");
			return (false);
		}
		for (auto const& entry : header)
		{
			lineBegin = "static constexpr ResourceKey const\t" + makeSymbolName(entry.name) + " = ";
			if (lineBegin.size() > maxSize)
				maxSize = lineBegin.size();
			lineBegins.emplace_back(lineBegin);
		}
		// Start writing
		out << "//\n//\tFile generated at " << getNow() << "\n//\n";
		out << "#if !defined OCTO_PACKAGE_RESOURCE_DEFINITION_HPP\n";
		out << "#define OCTO_PACKAGE_RESOURCE_DEFINITION_HPP\n";
		out << "#include <cstdint>\n\n";
		out << "typedef std::uint64_t	ResourceKey;\n";
		for (key = 0; key < header.count(); ++key)
		{
			if (lastType != header.getEntryType(key))
			{
				out << "\n// " << getEntryTypeLabel(header.getEntryType(key)) << "\n";
				lastType = header.getEntryType(key);
			}
			out << lineBegins[key];
			std::fill_n(std::ostream_iterator<char>(out), maxSize - lineBegins[key].size(), ' ');
			out << key << ";\n";
		}
		out << "\n#endif // OCTO_PACKAGE_RESOURCE_DEFINITION_HPP\n";
		return (true);
	}

	bool	PackageCompiler::sortFileInfo(FileInfo const& left, FileInfo const& right)
	{
		if (left.type < right.type)
		{
			return (true);
		}
		else if (left.type == right.type)
		{
			return (left.size < right.size);
		}
		else
		{
			return (false);
		}
	}

}