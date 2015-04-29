/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:50:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/29 17:51:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Application.hpp"
#include "GraphicsManager.hpp"
#include <iostream>

namespace octo
{
	sf::Color const	Console::BackgroundColor{0, 0, 0, 140};
	sf::Color const	Console::InputColor{0, 255, 0};
	sf::Color const	Console::CursorColor{0, 200, 0};
	sf::Color const	Console::QuoteColor{180, 180, 180};
	sf::Color const	Console::ResultColor{0, 128, 255};
	sf::Color const	Console::ErrorColor{255, 0, 0};
	sf::Color const	Console::HelpColor{255, 255, 102};

	class Console::Cursor
	{
	public:
		Cursor()
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
		m_font(nullptr)
	{
		m_cursor.reset(new Cursor);
		m_core.setListener(this);
		m_current.setColor(InputColor);
		m_rectangle.setFillColor(BackgroundColor);
	}

	void	Console::setFont(sf::Font const& font)
	{
		m_font = &font;
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
		m_cursor->setColor(CursorColor);
		m_needUpdate = true;
	}

	void	Console::setEnabled(bool enable)
	{
		if (m_font == nullptr)
			return;
		if (m_enabled != enable)
		{
			m_enabled = enable;
			m_core.updateText();
			m_needUpdate = true;
		}
	}

	bool	Console::isEnabled()const
	{
		return (m_enabled && (m_font != nullptr));
	}
	
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
			print(result, ResultColor);
	}

	void	Console::onError(std::wstring const& message, std::wstring const& line)
	{
		if (isEnabled() == false)
			return;
		print(L"\t" + message, ErrorColor);
		print(line, QuoteColor);
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

	void	Console::update(sf::Time, sf::View const& view)
	{
		sf::Vector2f	viewSize	= view.getSize();
		float			top = viewSize.y * m_relativeHeight * 0.5f + view.getCenter().y;
		float			left = viewSize.x * -0.5f + view.getCenter().x;
		float			leftPadded = left + m_leftPadding;

		if (m_needUpdate && isEnabled())
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
			m_needUpdate = false;
		}			
	}

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

	void	Console::print(std::wstring const& str, sf::Color const& color)
	{
		sf::Text	text(str, *m_font, m_fontSize);

		text.setColor(color);
		if (m_log.size() == m_maxLogCount)
			m_log.pop_back();
		m_log.push_front(text);
		m_needUpdate = true;
	}
	
	std::vector<std::wstring>	Console::getCommandList()const
	{
		return (m_core.getCommandList());
	}
}
