/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleAutoComplete.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:15:35 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 18:13:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleAutoComplete.hpp"

namespace octo
{
	void	ConsoleAutoComplete::addWord(std::wstring const& word, Lexems lexem)
	{
		m_tree.addWord(word, lexem);
	}
	
	void	ConsoleAutoComplete::resetBuffer(std::wstring const& buffer)
	{
		if (m_buffer != buffer)
		{
			m_completions.clear();
			m_tree.completeWord(buffer, m_completions);
			m_current = m_completions.begin();
			m_buffer = buffer;
		}
	}

	bool	ConsoleAutoComplete::getCurrentCompletion(std::wstring& result)
	{
		bool	hasResult = false;

		if (m_current != m_completions.end())
		{
			result.assign(*m_current);
			hasResult = true;
		}
		return (hasResult);
	}

	bool	ConsoleAutoComplete::getNextCompletion(std::wstring & result)
	{
		bool	hasResult = false;

		if (m_current != m_completions.end() && m_current + 1 != m_completions.end())
		{
			++m_current;
			result.assign(*m_current);
			hasResult = true;
		}
		return (hasResult);
	}

	bool	ConsoleAutoComplete::getPrevCompletion(std::wstring & buffer)
	{
		bool	hasResult = false;

		if (m_current != m_completions.end() && m_current - 1 != m_completions.end())
		{
			--m_current;
			buffer.assign(*m_current);
			hasResult = true;
		}
		return (hasResult);
	}
	
	ConsoleAutoComplete::Completions const&		ConsoleAutoComplete::getCompletions()const
	{
		return (m_completions);
	}

	bool		ConsoleAutoComplete::hasCompletions()const
	{
		return (m_completions.empty() == false);
	}
}
