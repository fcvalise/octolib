/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexicalTree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:07:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 17:39:58 by irabeson         ###   ########.fr       */
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

		static void		exportDotLabel(ConstNodePtr node, OStream& os)
		{
			os << reinterpret_cast<std::size_t>(node->get()) << " [label = \"";
			if (node->isRoot() == RootValue)
				os << "root";
			else
				os << node->getKey();
			os << "\"";
			if (node->getValue() != DefaultValue && node->getValue() != RootValue)
				os << ",style=filled,fillcolor=\"palegreen\"";
			os << "];\n";
		}
	public:
		static constexpr C	NullKey = C(0);

		LexicalTree() :
			m_root(std::make_shared<Node>(C(0), RootValue))
		{
		}

		~LexicalTree()
		{
		}

		void	exportDot(OStream& os, String const& graphName)const
		{
			std::set<ConstNodePtr>	nodes;

			os << "digraph " << graphName << "\n{\n";
			m_root->exportDot(os, nodes);
			for (auto node : nodes)
			{
				exportDotLabel(node, os);
			}
			os << "}\n";
		}

		void	addWord(String const& word, T const& value)
		{
			if (word.empty())
				return;
			auto	it = word.cbegin();
			NodePtr	current = m_root;

			while (current && it != word.cend())
			{
				if (it + 1 == word.cend())
					current = addLetter(current, *it, value);
				else
					current = addLetter(current, *it);
				++it;
			}
		}

		void	completeWord(String const& beginStr, std::vector<String>& results)const
		{
			ConstNodePtr	current = m_root;
			auto			it = beginStr.begin();
			
			while (current && it != beginStr.end())
			{
				current = current->getNext(*it);
				if (current == nullptr || current->getKey() != *it)
					return;
				++it;
			}
			if (current && it == beginStr.end())
			{
				for (auto p : *current)
				{
					p.second->getWords(results);
				}
			}
		}

		void	getWords(std::vector<String>& results)const
		{
			m_root->getWords(results);
		}
	private:
		static NodePtr	addLetter(NodePtr& current, C letter, T const& value)
		{
			NodePtr	next;

			if (current != nullptr)
			{
				next = current->getOrCreate(letter, value);
			}
			return (next);
		}

		static NodePtr	addLetter(NodePtr& current, C letter)
		{
			NodePtr	next;

			if (current != nullptr)
			{
				next = current->getOrCreate(letter);
			}
			return (next);
		}

	private:
		NodePtr	m_root;
	};

	template <class C, class T, T DefaultValue, T RootValue>
	class 	LexicalTree<C, T, DefaultValue, RootValue>::Node : public std::enable_shared_from_this<Node>
	{
		static String	formatDotNodeName(ConstNodePtr node)
		{
			std::basic_ostringstream<C>	os;

			os << reinterpret_cast<std::size_t>(node.get());
			return (os.str());
		}

		static void		getWordsImp(ConstNodePtr const& node, String buffer, std::vector<String>& results)
		{
			C			key = node->getKey();

			if (key != NullKey)
				buffer.push_back(key);
			if (node->getValue() != DefaultValue && buffer.empty() == false)
				results.push_back(buffer);
			if (node->hasNexts())
			{
				auto		it = node->begin();

				getWordsImp(it->second, buffer, results);
				++it;
				while (it != node->end())
				{
					getWordsImp(it->second, buffer, results);
					++it;
				}
			}
		}
	public:
		typedef typename std::map<C, NodePtr>::iterator			ChildIterator;
		typedef typename std::map<C, NodePtr>::const_iterator	ChildConstIterator;

		explicit Node(C key) :
			Node(key, DefaultValue)
		{
		}
		
		explicit Node(C key, T const& value) :
			m_value(value),
			m_key(key)
		{
		}

		void				getWords(std::vector<String>& results)const
		{
			getWordsImp(this->shared_from_this(), String(), results);
		}

		NodePtr				getOrCreate(C key, T const& value)
		{
			auto	it = m_nexts.find(key);
			NodePtr	result;

			if (it == m_nexts.end())
			{
				result = std::make_shared<Node>(key, value);
				m_nexts.insert(std::make_pair(key, result));
			}
			else if (it->second->getValue() == DefaultValue)
			{
				result = it->second;
				result->m_value = value;
			}
			else
			{
				throw std::runtime_error("lexical tree: duplicated entry");
			}
			return (result);
		}

		NodePtr				getOrCreate(C key)
		{
			auto	it = m_nexts.find(key);
			NodePtr	result;

			if (it == m_nexts.end())
			{
				result = std::make_shared<Node>(key, DefaultValue);
				m_nexts.insert(std::make_pair(key, result));
			}
			else
			{
				result = it->second;
			}
			return (result);
		}

		void				exportDot(OStream& os, std::set<ConstNodePtr>& nodes)
		{
			nodes.insert(this->shared_from_this());
			for (auto const& p : m_nexts)
			{
				os << formatDotNodeName(this->shared_from_this()) << " -> " <<
					  formatDotNodeName(p.second) << ";\n";
				p.second->exportDot(os, nodes);
			}
		}

		NodePtr				getNext(C key)const
		{
			auto	it = m_nexts.find(key);
			NodePtr	result;

			if (it != m_nexts.end())
				result = it->second;
			return (result);
		}

		C					getKey()const
		{
			return (m_key);
		}

		T const&			getValue()const
		{
			return (m_value);
		}

		bool				hasNexts()const
		{
			return (m_nexts.empty() == false);
		}

		bool				isRoot()const
		{
			return (m_value == RootValue);
		}

		ChildIterator		begin()
		{
			return (m_nexts.begin());
		}

		ChildIterator		end()
		{
			return (m_nexts.end());
		}

		ChildConstIterator	begin()const
		{
			return (m_nexts.begin());
		}

		ChildConstIterator	end()const
		{
			return (m_nexts.end());
		}
	private:
		std::map<C, NodePtr>	m_nexts;
		T						m_value;
		C						m_key;
	};	
}

#endif
