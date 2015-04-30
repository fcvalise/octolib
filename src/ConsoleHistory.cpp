/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleHistory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 15:33:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 16:20:06 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleHistory.hpp"

namespace octo
{
	ConsoleHistory::ConsoleHistory() :
		m_maxEntries(2000),
		m_current(InvalidPosition)
	{
	}

	void	ConsoleHistory::pushEntry(std::wstring const& entry)
	{
		if (entry.empty() == false && (m_entries.empty() || m_entries.front() != entry))
		{
			if (m_entries.size() == m_maxEntries)
			{
				m_entries.pop_back();
			}
			m_entries.push_front(entry);
		}
		m_current = InvalidPosition;
	}

	bool	ConsoleHistory::getNextEntry(std::wstring& entry)
	{
		if (isEmpty() || (m_current != InvalidPosition && m_current + 1u == m_entries.size()))
			return (false);
		if (m_current == InvalidPosition)
		{
			m_current = 0u;
		}
		else
		{
			++m_current;
		}
		entry = m_entries.at(m_current);
		return (true);
	}

	bool	ConsoleHistory::getPreviousEntry(std::wstring& entry)
	{
		if (isEmpty() || m_current == InvalidPosition)
			return (false);
		if (m_current == 0u)
		{
			entry = L"";
			m_current = InvalidPosition;
		}
		else
		{
			--m_current;
			entry = m_entries.at(m_current);
		}
		return (true);
	}

	bool	ConsoleHistory::isEmpty()const
	{
		return (m_entries.empty());
	}
}
