/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCompletion.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 22:28:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 23:48:53 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLECOMPLETION_HPP
# define CONSOLECOMPLETION_HPP
# include "LexicalTree.hpp"

# include <map>
# include <memory>

namespace octo
{
	class ConsoleCompletion
	{
	public:
		enum class	Lexems
		{
			Command,
			Parameter,
			Null,
			Root
		};

		typedef std::vector<std::wstring>				Completions;
		typedef typename Completions::const_iterator	CompletionsIterator;

		void					addWord(std::wstring const& word, Lexems lexem);
		void					resetBuffer(std::wstring const& buffer);
		bool					getCurrentCompletion(std::wstring& result);
		bool					getNextCompletion(std::wstring& result);
		bool					getPrevCompletion(std::wstring& result);
		bool					nextCompletion();
		bool					prevCompletion();
		Completions const&		getCompletions()const;
		bool					hasCompletions()const;
	private:
		typedef LexicalTree<wchar_t, Lexems, Lexems::Null, Lexems::Root>	Tree;

		Tree						m_tree;
		Completions					m_completions;
		CompletionsIterator			m_current;
		std::wstring				m_buffer;
	};
}


#endif
