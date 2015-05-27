/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexicalTree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:07:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 23:38:46 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICALTREE_HPP
# define LEXICALTREE_HPP
# include <string>
# include <vector>
# include <queue>
# include <set>
# include <map>
# include <cassert>
# include <ostream>

namespace octo
{
	template <class C, class T, T DefaultValue, T RootValue>
	class LexicalTree
	{
		class 								Node;
		typedef std::shared_ptr<Node>		NodePtr;
		typedef std::shared_ptr<Node const>	ConstNodePtr;
		typedef std::basic_string<C>		String;
		typedef std::basic_ostream<C>		OStream;

		static void		exportDotLabel(ConstNodePtr node, OStream& os);
	public:
		static constexpr C	NullKey = C(0);

		LexicalTree();
		~LexicalTree();

		void	exportDot(OStream& os, String const& graphName)const;
		void	addWord(String const& word, T const& value);
		void	completeWord(String const& beginStr, std::vector<String>& results)const;
		void	getWords(std::vector<String>& results)const;
		bool	contains(String const& word)const;
	private:
		static NodePtr	addLetter(NodePtr& current, C letter, T const& value);
		static NodePtr	addLetter(NodePtr& current, C letter);

	private:
		NodePtr	m_root;
	};
}

#include "LexicalTree.hxx"
#endif
