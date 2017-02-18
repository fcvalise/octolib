/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:50:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/20 16:32:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Application.hpp"
#include "GraphicsManager.hpp"
#include "Palette.hpp"
#include "StringUtils.hpp"
#include <iostream>
#include <fstream>

namespace octo
{
	//
	//	Console::GraphicsCompletion;
	//
	Console::GraphicsCompletion::GraphicsCompletion() :
		m_wordStart(std::wstring::npos),
		m_enabled(false),
		m_padding(4.f)
	{
	}

	void	Console::GraphicsCompletion::setColors(sf::Color const& textColor,
												   sf::Color const& bgColor)
	{
		m_text.setFillColor(textColor);
		m_background.setFillColor(bgColor);
	}

	void	Console::GraphicsCompletion::setFont(sf::Font const& font, unsigned int fontSize)
	{
		m_text.setFont(font);
		m_text.setCharacterSize(fontSize);
		m_font = &font;
	}

	void	Console::GraphicsCompletion::draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		if (m_enabled)
		{
			target.draw(m_background, states);
			target.draw(m_text, states);
		}
	}

	static sf::Vector2f	textSize(sf::String const& str, sf::Font const* font, unsigned int fontSize)
	{
		sf::Vector2f	size;

		for (auto c : str)
		{
			sf::Glyph const&	glyph = font->getGlyph(c, fontSize, false);

			size.x += glyph.advance;
		}
		size.y = font->getLineSpacing(fontSize);
		return (size);
	}

	void	Console::GraphicsCompletion::updatePosition(float top, float lineMargin)
	{
		sf::Vector2f	wordSize = textSize(m_word, m_font, m_text.getCharacterSize());
		sf::Vector2f	completeSize = textSize(m_text.getString(), m_font, m_text.getCharacterSize());

		completeSize.x += m_padding * 2;
		completeSize.y += lineMargin;
		m_text.setPosition(-wordSize.x, top);
		m_background.setPosition(-(wordSize.x + m_padding), top);
		m_background.setSize(completeSize);
	}

	void	Console::GraphicsCompletion::onCompletionChanged(Changes const& changes)
	{
		m_enabled = changes.getEnabled();
		m_word = changes.getWord();
		m_completion = changes.getCompletion();
		m_wordStart = changes.getWordStart();
		m_text.setString(m_word + m_completion +
						 L" [" + std::to_wstring(changes.getCurrentPosition()) +
						 L"/" + std::to_wstring(changes.getCompletionCount()) +  
						 L"]");
	}

	//
	//	Console::Cursor
	//
	Console::GraphicsCursor::GraphicsCursor() :
		m_yPos(0.f)
	{
	}

	void	Console::GraphicsCursor::setCursorWidth(float width)
	{
		sf::Vector2f	size = m_shape.getSize();

		size.x = width;
		m_shape.setSize(size);
	}

	void	Console::GraphicsCursor::setCursorHeight(float height)
	{
		sf::Vector2f	size = m_shape.getSize();

		size.y = height;
		m_shape.setSize(size);
	}

	void	Console::GraphicsCursor::setBaseLine(float pos)
	{
		m_yPos = pos;
	}

	void	Console::GraphicsCursor::setColor(sf::Color const& color)
	{
		m_shape.setFillColor(color);
	}

	void	Console::GraphicsCursor::onTextChanged(sf::Text const& text)
	{
		sf::String const&	str = text.getString();
		sf::Font const*		font = text.getFont();
		float				current = 0;
		std::size_t			i = 0;

		m_offsets.resize(str.getSize() + 1);
		while (i < str.getSize())
		{
			sf::Glyph const&	glyph = font->getGlyph(str[i], text.getCharacterSize(), false);

			m_offsets.at(i) = current;
			current += glyph.advance;
			++i;
		}
		m_offsets.at(i) = current;
	}

	void	Console::GraphicsCursor::setCursorPosition(unsigned int cursorPos)
	{
		if (cursorPos >= m_offsets.size())
			return;
		float			offset = m_offsets.at(cursorPos);
		sf::Vector2f	pos;
		
		pos.x = offset;
		pos.y = m_yPos;
		m_shape.setPosition(pos);
	}

	void	Console::GraphicsCursor::draw(sf::RenderTarget& render, sf::Transform const& parent)const
	{
		sf::RenderStates	states;

		states.transform = parent;
		states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::DstColor, sf::BlendMode::Subtract);
		render.draw(m_shape, states);
	}

	sf::Transform const& Console::GraphicsCursor::getTransform()const
	{
		return (m_shape.getTransform());
	}

	//
	//	Console
	//

	/*!
	 *	\ingroup Console
	 *	\class Console
	 *	\brief In-game console
	 *
	 *	This console is displayed on screen over the game.<br>
	 *	On enabled, the console takes the keyboard's focus.<br>
	 *
	 *	<h3>Command registration</h3>
	 *	Registering a command must be done by using addCommand methods.<br>
	 *	You can register any C++ function or methods, but overloads are
	 *	not supported, use a lambda to explicitly specifing the overload
	 *	to call.<br>
	 *	Currently these type are supported as parameter and return of command:
	 *	<ul>
	 *		<li>All native types such bool, int, float, double </li>
	 *		<li>std::string</li>
	 *		<li>std::wstring</li>
	 *		<li>sf::Vector2</li>
	 *		<li>sf::Vector3</li>
	 *		<li>sf::Rect</li>
	 *		<li>sf::Color</li>
	 *		<li>sf::VideoMode</li>
	 *	</ul>
	 *	<h3>History</h3>
	 *	Keys UP and DOWN recall respectivly the previous and the next user entry.<br>
	 *	<h3>Auto completion</h3>
	 *	Press TAB to active the completion mode.
	 *	In this mode, TAB and SHIFT+TAB allows
	 *	to select a particular completion if they are multiple.<br>
	 *	Press LEFT to complete or ESC to close completion panel.<br>
	 *	<br>
	 *	All commands names registered are added to the completion dictionnary but
	 *	you can add words yourself using addWord methods.
	 */

	/*!	Construct a default console */
	Console::Console() :
		m_maxLogCount(20u),
		m_fontSize(24),
		m_relativeHeight(0.33f),
		m_lineSpacing(8.f),
		m_leftPadding(10.f),
		m_topPadding(4.f),
		m_needUpdate(true),
		m_enabled(false),
		m_font(nullptr),
		m_palette(nullptr)
	{
		m_core.setListener(this);
		m_core.setCompletionListener(&m_completion);
	}

	/*!	Define the font used to render text */
	void	Console::setFont(sf::Font const& font, unsigned int fontSize)
	{
		m_font = &font;
		m_fontSize = fontSize;
		m_current.setFont(font);
		m_current.setCharacterSize(m_fontSize);
		m_completion.setFont(font, m_fontSize);
		for (sf::Text& text : m_log)
		{
			text.setFont(font);
			text.setCharacterSize(m_fontSize);
		}
		m_cursor.setCursorWidth(font.getGlyph('X', m_fontSize, false).advance);
		m_cursor.setCursorHeight(font.getLineSpacing(m_fontSize));
		m_cursor.setBaseLine(0);
		m_cursor.setColor(m_palette->getColor(Cursor));
		m_needUpdate = true;
	}

	/*!	Define the palette used.
	 *
	 *	Palette must contains at least 7 colors:
	 *	- Background
	 *	- Input
	 *	- Cursor
	 *	- Quote
	 *	- Result
	 *	- Error
	 *	- Help
	 */
	void	Console::setPalette(Palette const& palette)
	{
		m_palette = &palette;
		m_needUpdate = true;
		m_current.setFillColor(m_palette->getColor(Input));
		m_completion.setColors(m_palette->getColor(Quote), m_palette->getColor(Background));
		m_rectangle.setFillColor(m_palette->getColor(Background));
	}

	/*!	Enable or disable the console
	 *
	 *	Console is displayed and can respond to text event only if enabled.
	 */
	void	Console::setEnabled(bool enable)
	{
		if (m_font == nullptr || m_palette == nullptr)
			return;
		if (m_enabled != enable)
		{
			m_enabled = enable;
			m_core.updateText();
			m_needUpdate = true;
		}
	}

	/*!	Return true if the console is enabled, otherwise false */
	bool	Console::isEnabled()const
	{
		return (m_enabled && (m_font != nullptr));
	}
	
	/*!	Clear the console display */
	void	Console::clear()
	{
		m_core.removeAll();
		m_log.clear();
		m_needUpdate = true;
	}

	/*!	Update the console logic */
	void	Console::update(sf::Time, sf::View const& view)
	{
		if (isEnabled() == false)
			return;
		sf::Vector2f const&	viewSize = view.getSize();
		sf::Vector2f const&	viewCenter = view.getCenter();
		float const			lineHeight = m_font->getLineSpacing(m_fontSize) + m_lineSpacing;
		float const			top = viewSize.y * m_relativeHeight * 0.5f + viewCenter.y;
		float				y = 0.f;
		float				left = viewSize.x * -0.5f + viewCenter.x;
		float				leftPadded = left + m_leftPadding;

		m_rectangle.setSize(sf::Vector2f(viewSize.x, viewSize.y * m_relativeHeight));
		m_rectangle.setPosition(sf::Vector2f(left, top));
		m_current.setPosition(leftPadded, top + m_topPadding);
		y = top + lineHeight + m_topPadding;
		for (sf::Text& text : m_log)
		{
			text.setPosition(leftPadded, y);
			y += lineHeight;
		}
		m_completion.updatePosition(-(lineHeight + m_topPadding), m_lineSpacing);
	}

	/*!	Draw the console */
	void	Console::draw(sf::RenderTarget& render)const
	{
		if (isEnabled() == false)
			return;
		render.draw(m_rectangle);
		render.draw(m_current);
		for (sf::Text const& text : m_log)
			render.draw(text);
		render.draw(m_completion, m_cursor.getTransform() * m_current.getTransform());
		m_cursor.draw(render, m_current.getTransform());
	}

	/*!	Run a list of commands readed from a file */
	void	Console::run(std::string const& fileName)
	{
		std::wfstream	file;

		file.open(fileName, std::ios_base::in);
		if (file.is_open())
		{
			m_core.executeStream(file);
		}
		else
		{
			printError(std::wstring(L"Unable to open '") + stringToWide(fileName) + L"'");
		}
	}

	/*!	Register a word to completion dictionnary */
	void	Console::addWord(std::wstring const& word, ConsoleCompletion::Lexems lexem)
	{
		m_core.addWord(word, lexem);
	}

	/*!	Register a word to completion dictionnary */
	void	Console::addWord(std::string const& word, ConsoleCompletion::Lexems lexem)
	{
		m_core.addWord(stringToWide(word), lexem);
	}

	/*!	Register a word to completion dictionnary */
	void	Console::addWords(std::vector<std::wstring> const& words, ConsoleCompletion::Lexems lexem)
	{
		for (std::wstring const& word : words)
			m_core.addWord(word, lexem);
	}

	/*!	Register a word to completion dictionnary */
	void	Console::addWords(std::vector<std::string> const& words, ConsoleCompletion::Lexems lexem)
	{
		for (std::string const& word : words)
		{
			m_core.addWord(stringToWide(word), lexem);
		}
	}

	/*!	Print a message in the console
	 *	\param str String displayed
	 *	\param color Color of string displayed
	 */
	void	Console::print(std::wstring const& str, sf::Color const& color)
	{
		if (isEnabled() == false)
			return;
		sf::Text					text("", *m_font, m_fontSize);
		std::vector<std::wstring>	lines;

		text.setFillColor(color);
		splits(str, L'\n', lines);
		std::reverse(lines.begin(), lines.end());
		for (std::wstring const& line : lines)
		{
			text.setString(line);
			if (m_log.size() == m_maxLogCount)
				m_log.pop_back();
			m_log.push_front(text);
		}
		m_needUpdate = true;
	}
	
	/*!	Print an error message in the console
	 *	\param str String displayed
	 */
	void	Console::printError(std::wstring const& str)
	{
		if (isEnabled() == false)
			return;
		print(str, m_palette->getColor(Error));
	}
	/*!	Print the message of an exception in the console
	 *	\param str String displayed
	 */
	void						Console::printError(std::exception const& e)
	{
		if (isEnabled() == false)
			return;
		printError(L"exception: " + stringToWide(e.what()));
	}

	/*!	Print a help message */
	void						Console::printHelp(std::wstring const& str)
	{
		if (isEnabled() == false)
			return;
		print(str, m_palette->getColor(Help));
	}

	/*!	Return the list of all registered commands keys */
	std::vector<std::wstring>	Console::getCommandList()const
	{
		return (m_core.getCommandList());
	}

	void	Console::onTextChanged(std::wstring const& text)
	{
		if (isEnabled() == false)
			return;
		m_current.setString(text);
		m_cursor.onTextChanged(m_current);
	}

	void	Console::onCursorChanged(unsigned int pos)
	{
		if (isEnabled() == false)
			return;
		m_cursor.setCursorPosition(pos);
	}

	void	Console::onExecuted(std::wstring const& result)
	{
		if (isEnabled() == false)
			return;
		if (result.empty() == false)
			print(result, m_palette->getColor(Result));
	}

	void	Console::onError(std::wstring const& message, std::wstring const&)
	{
		if (isEnabled() == false)
			return;
		print(L"\t" + message, m_palette->getColor(Error));
	}

	void	Console::onTextEntered(sf::Event::TextEvent const& event)
	{
		if (isEnabled() == false)
			return;
		switch (event.unicode)
		{
			// Backspace
			case 8:
				m_core.removePrevious();
				break;
			// Enter
			case 10:
			case 13:
				m_core.execute();
				break;
			// Delete
			case 127:
				m_core.removeCurrent();
				break;
			// Theses keys triggers the completions before
			// if completion is visible
			case '\"':
			case '(':
			case ')':
				if (m_core.isCompletionActive())
					m_core.complete();
				m_core.insertChar(event.unicode);
				break;
			// Tab is disabled because we needs to handle Shift key
			case '\t':
				break;
			default:
				m_core.insertChar(event.unicode);
				break;
		}
	}

	bool	Console::onPressed(sf::Event::KeyEvent const& event)
	{
		if (m_enabled)
		{
			switch (event.code)
			{
				case sf::Keyboard::Left:
					if (m_core.isCompletionActive())
						m_core.setCompletionActive(false);
					m_core.moveCursor(-1);
					break;
				case sf::Keyboard::Right:
					if (m_core.isCompletionActive())
						m_core.complete();
					else
						m_core.moveCursor(1);
					break;
				case sf::Keyboard::Up:
					m_core.resetFromNext();
					break;
				case sf::Keyboard::Down:
					m_core.resetFromPrevious();
					break;
				case sf::Keyboard::Tab:
					if (m_core.isCompletionActive())
					{
						if (m_core.getCompletionCount() == 1)
							m_core.complete();
						else if (event.shift)
							m_core.prevCompletion();
						else
							m_core.nextCompletion();
					}
					else
					{
						m_core.setCompletionActive(true);
					}
					break;
				default:
					break;
			}
		}
		return (m_enabled == false);
	}

	bool	Console::onReleased(sf::Event::KeyEvent const& event)
	{
		if (m_enabled)
		{
			switch (event.code)
			{
				case sf::Keyboard::Escape:
					if (m_core.isCompletionActive())
						m_core.setCompletionActive(false);
					else
						setEnabled(false);
					break;
				default:
					break;
			}
		}
		return (m_enabled == false);
	}

}
