/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:29:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 19:50:16 by irabeson         ###   ########.fr       */
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
# include <SFML/Graphics/RectangleShape.hpp>

# include <string>
# include <list>

namespace octo
{
	/*!
	 *	\ingroup Console
	 *	\class Console
	 *	\brief In-game console
	 *
	 *	This console is displayed on screen over the game.
	 *	On enabled, the console takes the keyboard's focus.
	 */
	class Console : public IConsoleListener,
					public ITextListener,
					public IKeyboardListener
	{
		class Cursor;
	public:
		static sf::Color const	BackgroundColor;
		static sf::Color const	InputColor;
		static sf::Color const	CursorColor;
		static sf::Color const	QuoteColor;
		static sf::Color const	ResultColor;
		static sf::Color const	ErrorColor;
		static sf::Color const	HelpColor;

		Console();

		void			setFont(sf::Font const& font);
		void			setEnabled(bool enable);
		void			print(std::wstring const& str, sf::Color const& color);
		void			clear();

		virtual void	onTextEntered(sf::Event::TextEvent const& event);
		virtual bool	onPressed(sf::Event::KeyEvent const& event);
		virtual bool	onReleased(sf::Event::KeyEvent const& event);
		virtual void	onTextChanged(std::wstring const& text);
		virtual void	onCursorChanged(unsigned int pos);
		virtual void	onExecuted(std::wstring const& result);
		virtual void	onError(std::wstring const& message, std::wstring const& line);
		void			update(sf::Time frameTime, sf::View const& view);
		void			draw(sf::RenderTarget& render)const;

		template <class R, class ... A>
		void			addCommand(std::wstring const& name, R(*function)(A...));

		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		template <class F>
		void			addCommand(std::wstring const& name, F&& functor);
	private:
		bool			isEnabled()const;
	private:
		ConsoleCore					m_core;
		std::shared_ptr<Cursor>		m_cursor;
		std::list<sf::Text>			m_log;
		sf::Text					m_current;
		sf::RectangleShape			m_rectangle;
		std::size_t					m_maxLogCount;
		unsigned int				m_fontSize;
		float						m_relativeHeight;
		float						m_lineSpacing;
		float						m_leftPadding;
		float						m_topPadding;
		bool						m_needUpdate;
		bool						m_enabled;
		sf::Font const*				m_font;
	};
}

#include "Console.hxx"
#endif
