/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:50:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 01:48:49 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Application.hpp"
#include "GraphicsManager.hpp"
#include "Palette.hpp"
#include "StringUtils.hpp"
#include <iostream>

namespace octo
{
	class Console::Cursor
	{
	public:
		Cursor() :
			m_yPos(0.f)
		{
		}

		void	setCursorWidth(float width)
		{
			sf::Vector2f	size = m_shape.getSize();

			size.x = width;
			m_shape.setSize(size);
		}

		void	setCursorHeight(float height)
		{
			sf::Vector2f	size = m_shape.getSize();

			size.y = height;
			m_shape.setSize(size);
		}

		void	setBaseLine(float pos)
		{
			m_yPos = pos;
		}

		void	setColor(sf::Color const& color)
		{
			m_shape.setFillColor(color);
		}

		void	onTextChanged(sf::Text const& text)
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

		void	setCursorPosition(unsigned int cursorPos)
		{
			if (cursorPos >= m_offsets.size())
				return;
			float			offset = m_offsets.at(cursorPos);
			sf::Vector2f	pos;
			
			pos.x = offset;
			pos.y = m_yPos;
			m_shape.setPosition(pos);
		}

		void	draw(sf::RenderTarget& render, sf::Transform const& parent)const
		{
			sf::RenderStates	states;

			states.transform = parent;
			states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::DstColor, sf::BlendMode::Subtract);
			render.draw(m_shape, states);
		}
	private:
		std::vector<float>	m_offsets;
		std::vector<float>	m_widths;
		sf::RectangleShape	m_shape;
		float				m_yPos;
	};

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
		m_cursor.reset(new class Cursor);
		m_core.setListener(this);
	}

	/*!	Define the font used to render text */
	void	Console::setFont(sf::Font const& font, unsigned int fontSize)
	{
		m_font = &font;
		m_fontSize = fontSize;
		m_current.setFont(font);
		m_current.setCharacterSize(m_fontSize);
		for (sf::Text& text : m_log)
		{
			text.setFont(font);
			text.setCharacterSize(m_fontSize);
		}
		m_cursor->setCursorWidth(font.getGlyph('X', m_fontSize, false).advance);
		m_cursor->setCursorHeight(font.getLineSpacing(m_fontSize));
		m_cursor->setBaseLine(0);
		m_cursor->setColor(m_palette->getColor(Cursor));
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
		m_current.setColor(m_palette->getColor(Input));
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

	void	Console::onTextChanged(std::wstring const& text)
	{
		if (isEnabled() == false)
			return;
		m_current.setString(text);
		m_cursor->onTextChanged(m_current);
	}

	void	Console::onCursorChanged(unsigned int pos)
	{
		if (isEnabled() == false)
			return;
		m_cursor->setCursorPosition(pos);
	}

	void	Console::onExecuted(std::wstring const& result)
	{
		if (isEnabled() == false)
			return;
		if (result.empty() == false)
			print(result, m_palette->getColor(Result));
	}

	void	Console::onError(std::wstring const& message, std::wstring const& line)
	{
		if (isEnabled() == false)
			return;
		print(L"\t" + message, m_palette->getColor(Error));
		print(line, m_palette->getColor(Quote));
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
			// Delete do nothing because currently you can move
			// the cursor into the line
			case 127:
				m_core.removeCurrent();
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
					m_core.moveCursor(-1);
					break;
				case sf::Keyboard::Right:
					m_core.moveCursor(1);
					break;
				case sf::Keyboard::Up:
					m_core.resetFromNext();
					break;
				case sf::Keyboard::Down:
					m_core.resetFromPrevious();
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
					setEnabled(false);
					break;
				default:
					break;
			}
		}
		return (m_enabled == false);
	}

	/*!	Update the console logic */
	void	Console::update(sf::Time, sf::View const& view)
	{
		sf::Vector2f const&	viewSize = view.getSize();
		sf::Vector2f const&	viewCenter = view.getCenter();
		float				top = viewSize.y * m_relativeHeight * 0.5f + viewCenter.y;
		float				left = viewSize.x * -0.5f + viewCenter.x;
		float				leftPadded = left + m_leftPadding;

		if (isEnabled())
		{
			m_rectangle.setSize(sf::Vector2f(viewSize.x, viewSize.y * m_relativeHeight));
			m_rectangle.setPosition(sf::Vector2f(left, top));
			m_current.setPosition(leftPadded, top + m_topPadding);
			top += m_font->getLineSpacing(m_fontSize) + m_lineSpacing + m_topPadding;
			for (sf::Text& text : m_log)
			{
				text.setPosition(leftPadded, top);
				top += m_font->getLineSpacing(m_fontSize) + m_lineSpacing;
			}
		}			
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
		m_cursor->draw(render, m_current.getTransform());
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

		text.setColor(color);
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
}
