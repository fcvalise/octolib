/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCompletion.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 22:29:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 23:45:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleCompletion.hpp"

namespace octo
{
	void	ConsoleCompletion::addWord(std::wstring const& word, Lexems lexem)
	{
		if (m_tree.contains(word) == false)
		{
			m_tree.addWord(word, lexem);
		}
	}
	
	void	ConsoleCompletion::resetBuffer(std::wstring const& buffer)
	{
		if (m_buffer != buffer)
		{
			m_completions.clear();
			m_tree.completeWord(buffer, m_completions);
			m_current = m_completions.begin();
			m_buffer = buffer;
		}
	}

	bool	ConsoleCompletion::getCurrentCompletion(std::wstring& result)
	{
		bool	hasResult = false;

		if (m_current != m_completions.end())
		{
			result.assign(*m_current);
			hasResult = true;
		}
		return (hasResult);
	}

	bool	ConsoleCompletion::getNextCompletion(std::wstring & result)
	{
		bool	hasResult = false;

		if (nextCompletion())
		{
			result.assign(*m_current);
		}
		return (hasResult);
	}

	bool	ConsoleCompletion::getPrevCompletion(std::wstring & result)
	{
		bool	hasResult = false;

		if (prevCompletion())
		{
			result.assign(*m_current);
		}
		return (hasResult);
	}
	
	bool	ConsoleCompletion::nextCompletion()
	{
		bool	hasResult = false;

		if (m_current != m_completions.end() && m_current + 1 != m_completions.end())
		{
			++m_current;
			hasResult = true;
		}
		return (hasResult);
	}

	bool	ConsoleCompletion::prevCompletion()
	{
		bool	hasresult = false;

		if (m_current != m_completions.end() && m_current != m_completions.begin())
		{
			--m_current;
			hasresult = true;
		}
		return (hasresult);
	}

	ConsoleCompletion::Completions const&		ConsoleCompletion::getCompletions()const
	{
		return (m_completions);
	}

	bool		ConsoleCompletion::hasCompletions()const
	{
		return (m_completions.empty() == false);
	}
}
