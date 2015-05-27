/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexicalTree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:07:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 05:50:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICALTREE_HPP
# define LEXICALTREE_HPP
# include <string>
# include <vector>
# include <queue>
# include <set>
# include <map>
# include <iostream>

namespace octo
{
	template <class C, class T, T DefaultValue, T RootValue>
	class LexicalTree
	{
		class 								Node;
		typedef std::shared_ptr<Node>		NodePtr;
		typedef std::shared_ptr<Node const>	ConstNodePtr;
		typedef std::basic_string<C>		String;
	public:
		static constexpr C	NullKey = C(0);

		LexicalTree() :
			m_root(std::make_shared<Node>(C(0), RootValue))
		{
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
				++it;
			}
			if (current)
			{
				current->getWords(results);
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
	public:
		explicit Node(C key) :
			Node(key, DefaultValue)
		{
		}
		
		explicit Node(C key, T const& value) :
			m_value(value),
			m_key(key)
		{
		}

		void	getWords(std::vector<String>& results)const
		{
			struct	NodeBuffer
			{
				NodeBuffer() = default;
				NodeBuffer(String const& b, ConstNodePtr const& n) :
					buffer(b),
					node(n)
				{
				}

				String			buffer;
				ConstNodePtr	node;
			};
			std::queue<NodeBuffer>		stack;
			std::set<ConstNodePtr>		marked;
			NodeBuffer					current;
			String						buffer;

			stack.emplace(String(), this->shared_from_this());
			while (stack.empty() == false)
			{
				current = stack.front();
				stack.pop();
				if (marked.find(current.node) == marked.end())
				{
					marked.insert(current.node);
					if (current.node->getValue() != DefaultValue && current.buffer.empty() == false)
					{
						results.push_back(current.buffer);
					}
					for (auto const& pair : current.node->m_nexts)
					{
						if (marked.find(pair.second) == marked.end())
						{
							stack.emplace(current.buffer + pair.second->getKey(), pair.second);
						}
					}
				}
			}
		}

		NodePtr	getOrCreate(C key, T const& value)
		{
			auto	it = m_nexts.find(key);
			NodePtr	result;

			if (it == m_nexts.end())
			{
				result = std::make_shared<Node>(key, value);
				m_nexts.insert(std::make_pair(key, result));
			}
			else
			{
				result = it->second;
				assert (result->m_value == DefaultValue);
				result->m_value = value;
			}
			return (result);
		}

		NodePtr	getOrCreate(C key)
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

		void	putNext(C key, NodePtr node)
		{
			m_nexts[key] = node;
		}

		NodePtr	getNext(C key)const
		{
			auto	it = m_nexts.find(key);
			NodePtr	result;

			if (it != m_nexts.end())
				result = it->second;
			return (result);
		}

		C			getKey()const
		{
			return (m_key);
		}

		T const&	getValue()const
		{
			return (m_value);
		}

		bool		hasNexts()const
		{
			return (m_nexts.empty() == false);
		}
	private:
		std::map<C, NodePtr>	m_nexts;
		T						m_value;
		C						m_key;
	};	
}

#endif
