/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleAutoComplete.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 02:47:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 03:36:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLEAUTOCOMPLETE_HPP
# define CONSOLEAUTOCOMPLETE_HPP
# include <map>
# include <memory>
# include "LexicalTree.hpp"

namespace octo
{
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
		void	addWord(std::wstring const& word, Lexems lexem);
	private:
		Tree	m_tree;
	};
}

#endif
