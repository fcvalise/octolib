/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:29:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/28 01:28:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_HPP
# define CONSOLE_HPP
# include "NonCopyable.hpp"
# include "IConsoleListener.hpp"
# include "IConsoleCompletionListener.hpp"
# include "GraphicsListeners.hpp"
# include "ConsoleCore.hpp"

# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/Graphics/RectangleShape.hpp>
# include <SFML/Graphics/View.hpp>

# include <string>
# include <list>

namespace octo
{
	class Palette;

	/*!
	 *	\ingroup Console
	 *	\class Console
	 *	\brief In-game console
	 *
	 *	This console is displayed on screen over the game.<br>
	 *	On enabled, the console takes the keyboard's focus.<br>
	 *
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
	 */
	class Console :	public NonCopyable,
					public IConsoleListener,
					public ITextListener,
					public IKeyboardListener
	{
		enum	Colors
		{
			Background = 0,
			Input,
			Cursor,
			Quote,
			Result,
			Error,
			Help
		};
	public:
		Console();

		void						setFont(sf::Font const& font, unsigned int fontSize);
		void						setPalette(Palette const& palette);
		void						setEnabled(bool enable);
		bool						isEnabled()const;

		void						addWord(std::wstring const& word, ConsoleCompletion::Lexems lexem);
		void						addWord(std::string const& word, ConsoleCompletion::Lexems lexem);
		void						addWords(std::vector<std::wstring> const& words, ConsoleCompletion::Lexems lexem);
		void						addWords(std::vector<std::string> const& words, ConsoleCompletion::Lexems lexem);

		void						print(std::wstring const& str, sf::Color const& color);
		void						printError(std::wstring const& str);
		void						printError(std::exception const& e);
		void						printHelp(std::wstring const& str);
		void						clear();

		void						update(sf::Time frameTime, sf::View const& view);
		void						draw(sf::RenderTarget& render)const;

		template <class R, class ... A>
		void						addCommand(std::wstring const& name, R(*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		template <class F>
		void						addCommand(std::wstring const& name, F&& functor);

		std::vector<std::wstring>	getCommandList()const;
	private:
		virtual void				onTextEntered(sf::Event::TextEvent const& event);
		virtual bool				onPressed(sf::Event::KeyEvent const& event);
		virtual bool				onReleased(sf::Event::KeyEvent const& event);
		virtual void				onTextChanged(std::wstring const& text);
		virtual void				onCursorChanged(unsigned int pos);
		virtual void				onExecuted(std::wstring const& result);
		virtual void				onError(std::wstring const& message, std::wstring const& line);
	private:
		class GraphicsCompletion : public sf::Drawable,
								   public IConsoleCompletionListener
		{
		public:	
			GraphicsCompletion();
			void			setColors(sf::Color const& textColor, sf::Color const& bgColor);
			void			setFont(sf::Font const& font, unsigned int charSize);
			void			updatePosition(float top, float lineMargin);
			virtual void	draw(sf::RenderTarget& target, sf::RenderStates states)const;
			virtual void	onCompletionChanged(Changes const& changes);
		private:
			sf::Text						m_text;
			sf::RectangleShape				m_background;
			std::wstring					m_word;
			std::wstring::size_type			m_wordStart;
			std::wstring					m_completion;
			bool							m_enabled;
			float							m_padding;
			sf::Font const*					m_font;
		};

		class GraphicsCursor
		{
		public:
			GraphicsCursor();

			void					setCursorWidth(float width);
			void					setCursorHeight(float height);
			void					setBaseLine(float pos);
			void					setColor(sf::Color const& color);
			void					onTextChanged(sf::Text const& text);
			void					setCursorPosition(unsigned int cursorPos);
			void					draw(sf::RenderTarget& render, sf::Transform const& parent)const;
			sf::Transform const&	getTransform()const;
		private:
			std::vector<float>	m_offsets;
			std::vector<float>	m_widths;
			sf::RectangleShape	m_shape;
			float				m_yPos;
		};

		ConsoleCore						m_core;
		GraphicsCursor					m_cursor;
		GraphicsCompletion				m_completion;
		std::list<sf::Text>				m_log;
		sf::Text						m_current;
		sf::RectangleShape				m_rectangle;
		std::size_t						m_maxLogCount;
		unsigned int					m_fontSize;
		float							m_relativeHeight;
		float							m_lineSpacing;
		float							m_leftPadding;
		float							m_topPadding;
		bool							m_needUpdate;
		bool							m_enabled;
		sf::Font const*					m_font;
		Palette const*					m_palette;
	};
}

#include "Console.hxx"
#endif
