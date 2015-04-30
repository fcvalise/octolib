/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleHistory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 15:29:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 16:25:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLEHISTORY_HPP
# define CONSOLEHISTORY_HPP
# include <algorithm>
# include <string>
# include <deque>

namespace octo
{
	class ConsoleHistory
	{
		static constexpr std::size_t const	InvalidPosition = std::numeric_limits<std::size_t>::max(); 
	public:
		ConsoleHistory();

		void			pushEntry(std::wstring const& entry);
		bool			isEmpty()const;
		bool			getNextEntry(std::wstring& entry);
		bool			getPreviousEntry(std::wstring& entry);
	private:
		typedef std::deque<std::wstring>		Entries;

		Entries			m_entries;
		std::size_t		m_maxEntries;
		std::size_t		m_current;
	};
}

#endif
