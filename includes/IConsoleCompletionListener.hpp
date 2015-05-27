/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IConsoleCompletionListener.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 22:33:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 22:59:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICONSOLECOMPLETIONLISTENER_HPP
# define ICONSOLECOMPLETIONLISTENER_HPP
# include "ConsoleCompletion.hpp"

namespace octo
{
	class IConsoleCompletionListener
	{
	public:
		class	Changes;

		virtual ~IConsoleCompletionListener(){}

		virtual void	onCompletionChanged(Changes const& changes) = 0;
	};
	
	class	IConsoleCompletionListener::Changes
	{
	public:
		Changes(bool enabled,
				std::wstring const& word,
				std::wstring const& completion,
				std::wstring::size_type wordStart) :
			m_enabled(enabled),
			m_word(word),
			m_completion(completion),
			m_wordStart(wordStart)
		{
		}

		bool					getEnabled()const
		{
			return (m_enabled);
		}

		std::wstring const&		getWord()const
		{
			return (m_word);
		}

		std::wstring const&		getCompletion()const
		{
			return (m_completion);
		}

		std::wstring::size_type	getWordStart()const
		{
			return (m_wordStart);
		}
	private:
		bool 						m_enabled;
		std::wstring const&			m_word;
		std::wstring const&			m_completion;
		std::wstring::size_type		m_wordStart;
	};
	
}

#endif
