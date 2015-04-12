/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:50:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/12 14:34:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Application.hpp"
#include "GraphicsManager.hpp"

namespace octo
{
	Console::Console() :
		m_maxLogCount(10u),
		m_relativeHeight(0.33f),
		m_needUpdate(false),
		m_enabled(false),
		m_font(nullptr)
	{
		m_core.setListener(this);
	}

	void	Console::setFont(sf::Font const& font)
	{
		m_font = &font;
		m_current.setFont(font);
		for (sf::Text& text : m_log)
			text.setFont(font);
		m_needUpdate = true;
	}

	void	Console::switchEnabled()
	{
		setEnabled(!m_enabled);
	}

	void	Console::setEnabled(bool enable)
	{
		GraphicsManager&	graphics = Application::getGraphicsManager();

		if (m_enabled != enable)
		{
			m_enabled = enable;
			m_needUpdate = (m_font != nullptr);
			if (enable)
				graphics.addTextListener(this);
			else
				graphics.removeTextListener(this);
		}
	}

	bool	Console::isEnabled()const
	{
		return (m_enabled && (m_font != nullptr));
	}

	void	Console::onTextChanged(std::wstring const& text)
	{
		if (isEnabled() == false)
			return;
		m_current.setString(text);
	}

	void	Console::onCursorChanged(unsigned int pos)
	{
		if (isEnabled() == false)
			return;
		static_cast<void>(pos);
	}

	void	Console::onExecuted(std::wstring const& result)
	{
		if (isEnabled() == false)
			return;
		if (result.empty() == false)
			print(result, sf::Color::White);
	}

	void	Console::onError(std::wstring const& message)
	{
		if (isEnabled() == false)
			return;
		print(message, sf::Color::Red);
	}

	void	Console::onTextEntered(sf::Event::TextEvent const& event)
	{
		if (isEnabled() == false)
			return;
		if (m_enabled == false)
			return;
		// It should be safe...
		m_core.insertChar(event.unicode);
	}

	void	Console::update(sf::Time, sf::View const& view)
	{
		float	top = view.getSize().y - (view.getSize().y * m_relativeHeight);
		float	leftPos = (view.getCenter().y - view.getSize().y / 2.f) + 3.f;

		if (m_needUpdate && isEnabled())
		{
			m_current.setPosition(leftPos, top);
			top += m_current.getLocalBounds().height;
			for (sf::Text& text : m_log)
			{
				text.setPosition(leftPos, top);
				top += text.getLocalBounds().height;
			}
			m_needUpdate = false;
		}			
	}

	void	Console::draw(sf::RenderTarget& render)const
	{
		if (isEnabled() == false)
			return;
		render.draw(m_current);
		for (sf::Text const& text : m_log)
			render.draw(text);
	}

	void	Console::print(std::wstring const& str, sf::Color const& color)
	{
		sf::Text	text(str, *m_font, 30);

		text.setColor(color);
		if (m_log.size() == m_maxLogCount)
			m_log.pop_front();
		m_log.push_back(text);
		m_needUpdate = true;
	}
}
