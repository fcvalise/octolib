/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:29:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/12 14:34:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_HPP
# define CONSOLE_HPP
# include "IConsoleListener.hpp"
# include "GraphicsManager.hpp"
# include "ConsoleCore.hpp"

# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Text.hpp>

# include <string>
# include <list>

namespace octo
{
	class Console : public IConsoleListener,
					public ITextListener
	{
	public:
		Console();

		void			setFont(sf::Font const& font);

		void			switchEnabled();
		void			setEnabled(bool enable);

		virtual void	onTextChanged(std::wstring const& text);
		virtual void	onCursorChanged(unsigned int pos);
		virtual void	onExecuted(std::wstring const& result);
		virtual void	onError(std::wstring const& message);
		virtual void	onTextEntered(sf::Event::TextEvent const& event);
		void			update(sf::Time frameTime, sf::View const& view);
		void			draw(sf::RenderTarget& render)const;
	private:
		void			print(std::wstring const& str, sf::Color const& color);
		bool			isEnabled()const;
	private:
		ConsoleCore			m_core;
		std::list<sf::Text>	m_log;
		sf::Text			m_current;
		sf::Vector2f		m_charSize;
		std::size_t			m_maxLogCount;
		float				m_relativeHeight;
		bool				m_needUpdate;
		bool				m_enabled;
		sf::Font const*		m_font;
	};
}

#endif
