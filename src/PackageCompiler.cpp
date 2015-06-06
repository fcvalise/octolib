/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageCompiler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 06:01:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/06 08:03:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PackageCompiler.hpp"
#include "details/PackageCommons.hpp"

#include <map>
#include <iterator>
#include <fstream>
#include <limits>
#include <chrono>

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

	class PackageCompiler::FindInfoByName
	{
	public:
		explicit FindInfoByName(std::string const& name) :
			m_name(details::toLower(name))
		{
		}

		bool	operator()(PackageCompiler::FileInfo const& info)const
		{
			std::string	name = details::toLower(info.name);

			return (name == m_name);
		}
	private:
		std::string const	m_name;
	};

	namespace
	{
		static std::string	extractFileName(std::string const& fileName)
		{
			std::string::size_type	pos = fileName.find_last_of("/");

			if (pos == std::string::npos)
				pos = 0;
			return (fileName.substr(pos));
		}

		static std::string	makeSymbolName(std::string str)
		{
			std::for_each(std::begin(str), std::end(str), [](char& c)
				{
					if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						c = std::toupper(c);
					}
					else
					{
						c = '_';
					}
				});
			return (str);
		}

		static std::map<PackageHeader::EntryType, std::string> const	EntryTypeLabels
		{
			{octo::PackageHeader::EntryType::Font, "FONTS"},
			{octo::PackageHeader::EntryType::Texture, "TEXTURES"},
			{octo::PackageHeader::EntryType::Sound, "SOUNDS"},
			{octo::PackageHeader::EntryType::Text, "TEXTS"},
			{octo::PackageHeader::EntryType::Palette, "PALETTES"},
			{octo::PackageHeader::EntryType::ColorWheel, "COLOR WHEELS"},
			{octo::PackageHeader::EntryType::SpriteSheet, "SPRITE SHEETS"},
			{octo::PackageHeader::EntryType::SpriteAnimation, "SPRITE ANIMATIONS"},
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
			{"aif", PackageHeader::EntryType::Sound},
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
			{"cgf", PackageHeader::EntryType::Text},
			{"json", PackageHeader::EntryType::Text},
			{"xml", PackageHeader::EntryType::Text},
			{"opa", PackageHeader::EntryType::Palette},
			{"ocw", PackageHeader::EntryType::ColorWheel},
			{"oss", PackageHeader::EntryType::SpriteSheet},
			{"osa", PackageHeader::EntryType::SpriteAnimation}
		}
	{
	}

	void	PackageCompiler::setListener(IListener* listener)
	{
		m_listener = listener;
	}

	bool	PackageCompiler::compile(std::string const& outputFile,
									 std::string const& outputHeaderFile,
									 std::vector<std::string> const& paths)
	{
		FileInfoArray	fileInfos;
		PackageHeader	header;

		if (getFileInfos(paths, fileInfos) == false)
			return (false);
		std::for_each(fileInfos.begin(), fileInfos.end(), FillHeader(header));
		if (writePackage(outputFile, fileInfos, header) == false)
			return (false);
		if (outputHeaderFile.empty() == false && writeDefinitionFile(header, outputHeaderFile) == false)
			return (false);
		if (m_listener)
			m_listener->finished(header);
		return (true);
	}

	bool	PackageCompiler::getFileInfos(std::vector<std::string> const& paths, FileInfoArray& fileInfos)
	{
		for (auto const& path : paths)
		{
			if (checkInputFile(path, fileInfos))
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

	bool	PackageCompiler::checkInputFile(std::string const& path, FileInfoArray& fileInfos)
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
		if (std::find_if(fileInfos.begin(), fileInfos.end(), FindInfoByName(baseName)) != fileInfos.end())
		{
			if (m_listener)
				m_listener->error("duplicated input file name: '" + path + "'");
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
		details::generateMask(m_encryptionMask, details::PackageEncryptionMaskSize,
							  header.byteCount());
		for (auto const& fileInfo : fileInfos)
		{
			if (m_listener)
			{
				m_listener->copyingFile(fileInfo.path, i, fileInfos.size());
			}
			if (writeFile(fileInfo, out) == false)
				return (false);
			++i;
		}
		return (true);
	}

	bool	PackageCompiler::writeFile(FileInfo const& info, std::ostream& out)
	{
		std::ifstream			input(info.path, std::ios_base::binary);

		if (input.is_open() == false)
		{
			if (m_listener)
				m_listener->error("input file cannot be opened: '" + info.path + "'");
			return (false);
		}
		if (m_buffer.read(input, info.size) == false)
		{
			if (m_listener)
				m_listener->error("unable to read input file: '" + info.path + "'");
			return (false);
		}
		details::xorEncryptDecrypt(m_buffer.begin(), m_buffer.end(), m_encryptionMask);
		m_buffer.write(out);
		return (true);
	}

	bool	PackageCompiler::writeDefinitionFile(PackageHeader const& header, std::string const& outputFilePath)
	{
		std::ofstream										out(outputFilePath);
		std::vector<std::string>							lineBegins;
		std::string											lineBegin;
		std::string											uniqueIncludeMacro;
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
		uniqueIncludeMacro = makeSymbolName("octo_" + outputFilePath);
		// Start writing
		out << "//\n//\t" << extractFileName(outputFilePath) << "\n";
		out << "#if !defined " << uniqueIncludeMacro << "\n";
		out << "#define " << uniqueIncludeMacro << "\n";
		out << "#include <cstdint>\n\n";
		out << "typedef char const*		ResourceKey;\n";
		for (key = 0; key < header.count(); ++key)
		{
			if (lastType != header.getEntryType(key))
			{
				out << "\n// " << getEntryTypeLabel(header.getEntryType(key)) << "\n";
				lastType = header.getEntryType(key);
			}
			out << lineBegins[key];
			std::fill_n(std::ostream_iterator<char>(out), maxSize - lineBegins[key].size(), ' ');
			out << "\"" << header.getEntryName(key) << "\"" << ";\n";
		}
		out << "\n#endif // " << uniqueIncludeMacro << "\n";
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
			return (left.size > right.size);
		}
		else
		{
			return (false);
		}
	}
}
