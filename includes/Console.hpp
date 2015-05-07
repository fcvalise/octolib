/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:29:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/07 20:13:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_HPP
# define CONSOLE_HPP
# include "NonCopyable.hpp"
# include "IConsoleListener.hpp"
# include "GraphicsListeners.hpp"
# include "ConsoleCore.hpp"
# include "ConsoleHistory.hpp"

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
		class Cursor;

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

		/*!	Define the font used to render text */
		void						setFont(sf::Font const& font, unsigned int fontSize);

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
		void						setPalette(Palette const& palette);

		/*!	Enable or disable the console
		 *
		 *	Console is displayed and can respond to text event only if enabled.
		 */
		void						setEnabled(bool enable);

		/*!	Return true if the console is enabled, otherwise false */
		bool						isEnabled()const;

		/*!	Print a message in the console */
		void						print(std::wstring const& str, sf::Color const& color);
		void						printError(std::wstring const& str);
		void						printError(std::exception const& e);
		void						printHelp(std::wstring const& str);

		/*!	Clear the console display */
		void						clear();

		/*!	Update the console logic */
		void						update(sf::Time frameTime, sf::View const& view);

		/*!	Draw the console */
		void						draw(sf::RenderTarget& render)const;

		/*!	Register a free function
		 *
		 *	\code
		 *
		 *	double	foo(int param){ ... }
		 *
		 *	...
		 *
		 *	// Register foo
		 *	console.addCommand(L"foo", &foo);
		 *	\endcode
		 */
		template <class R, class ... A>
		void						addCommand(std::wstring const& name, R(*function)(A...));

		/*!	Register a member function
		 *
		 *	\code
		 *	struct Foo
		 *	{
		 *		double	bar(int param){ ... }
		 *	};
		 *
		 *	...
		 *
		 *	Foo	fooInstance;
		 *
		 *	// Register Foo::bar()
		 *	console.addCommand(L"foobar", fooInstance, &bar);
		 *	\endcode
		 */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		/*!	Register a member function
		 *
		 *	\code
		 *	struct Foo
		 *	{
		 *		double	bar(int param){ ... }
		 *	};
		 *
		 *	...
		 *
		 *	Foo*	fooInstance = new Foo;
		 *
		 *	// Register Foo::bar()
		 *	console.addCommand(L"foobar", fooInstance, &bar);
		 *	\endcode
		 */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		/*!	Register a constant member function
		 *
		 *	\code
		 *	struct Foo
		 *	{
		 *		double	bar(int param)const{ ... }
		 *	};
		 *
		 *	...
		 *
		 *	Foo	const	fooInstance;
		 *
		 *	// Register Foo::bar()
		 *	console.addCommand(L"foobar", fooInstance, &bar);
		 *	\endcode
		 */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		/*!	Register a constant member function
		 *
		 *	\code
		 *	struct Foo
		 *	{
		 *		double	bar(int param)const{ ... }
		 *	};
		 *
		 *	...
		 *
		 *	Foo const*	fooInstance = new Foo;
		 *
		 *	// Register Foo::bar()
		 *	console.addCommand(L"foobar", fooInstance, &bar);
		 *	\endcode
		 */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		/*!	Register a functor or a lambda function
		 *
		 *	\code
		 *	struct Foo
		 *	{
		 *		double	operator()(int param){ ... }
		 *	};
		 *
		 *	...
		 *
		 *	// Register a functor
		 *	console.addCommand(L"foobar", Foo());
		 *
		 *	// Register a lambda
		 *	console.addCommand(L"lambdalala", [](int, double){ ... });
		 *	\endcode
		 */
		template <class F>
		void						addCommand(std::wstring const& name, F&& functor);

		/*!	Return the list of all registered commands keys */
		std::vector<std::wstring>	getCommandList()const;
	private:
		virtual void	onTextEntered(sf::Event::TextEvent const& event);
		virtual bool	onPressed(sf::Event::KeyEvent const& event);
		virtual bool	onReleased(sf::Event::KeyEvent const& event);
		virtual void	onTextChanged(std::wstring const& text);
		virtual void	onCursorChanged(unsigned int pos);
		virtual void	onExecuted(std::wstring const& result);
		virtual void	onError(std::wstring const& message, std::wstring const& line);

		void			nextHistoryEntry();
		void			previousHistoryEntry();
		void			execute();
	private:
		ConsoleCore					m_core;
		ConsoleHistory				m_history;
		std::shared_ptr<class Cursor>	m_cursor;
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
		Palette const*				m_palette;
	};
}

#include "Console.hxx"
#endif
