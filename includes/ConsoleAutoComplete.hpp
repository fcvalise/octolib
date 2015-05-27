/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleAutoComplete.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 02:47:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 18:12:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLEAUTOCOMPLETE_HPP
# define CONSOLEAUTOCOMPLETE_HPP
# include <map>
# include <memory>
# include "LexicalTree.hpp"

namespace octo
{
	class ConsoleAutoCompletion
	{
	public:

	private:

	};

	class ConsoleAutoComplete
	{
		enum class	Lexems
		{
			Command,
			Parameter,
			Null,
			Root
		};

		typedef LexicalTree<wchar_t, Lexems, Lexems::Null, Lexems::Root>	Tree;
	public:
		typedef std::vector<std::wstring>				Completions;
		typedef typename Completions::const_iterator	CompletionsIterator;

		void					addWord(std::wstring const& word, Lexems lexem);
		void					resetBuffer(std::wstring const& buffer);
		bool					getCurrentCompletion(std::wstring& result);
		bool					getNextCompletion(std::wstring& result);
		bool					getPrevCompletion(std::wstring& result);
		Completions const&		getCompletions()const;
		bool					hasCompletions()const;
	private:
		Tree				m_tree;
		Completions			m_completions;
		CompletionsIterator	m_current;
		std::wstring		m_buffer;
	};
}

#endif
