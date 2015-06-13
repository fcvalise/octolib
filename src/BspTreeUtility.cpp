/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspTreeUtility.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 11:38:54 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:54:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BspTreeUtility.hpp"
#include "BspTree.hpp"
#include "BspNode.hpp"

#include <map>
#include <string>
#include <sstream>

namespace octo
{
	typedef std::map<BspNode const*, std::string> NodeIdMap;

	class MakeMap
	{
	public:
		explicit MakeMap(NodeIdMap& map) :
			m_map(map),
			m_nextId(0)
		{
		}

		void	operator()(BspNode const* node)
		{
			std::ostringstream	oss;

			oss << m_nextId++;
			m_map.insert(std::make_pair(node, oss.str()));
		}
	private:
		NodeIdMap&		m_map;
		unsigned int	m_nextId;
	};

	/*!	Imprime un arbre au format dot sur un flux de sortie */
	void	printDot(BspTree const& tree, std::ostream& os)
	{
		NodeIdMap		map;
		BspNode const*	current = nullptr;
		BspNode const*	front = nullptr;
		BspNode const*	back = nullptr;

		tree.forEach<BspTree::VisitorMode::Prefix>(MakeMap(map));
		os << "digraph bsp" << std::endl << "{" << std::endl << "\tgraph [ordering=\"out\"];" << std::endl;
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			os << "\t" << it->second << " [label=\"" << it->second << "\"];" << std::endl;
		}
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			current = it->first;
			front = current->front();
			back = current->back();
			if (front)
				os << "\t" << it->second << " -> " << map.at(front) << ";" << std::endl;
			if (back)
				os << "\t" << it->second << " -> " << map.at(back) << ";" << std::endl;
		}
		os << "}" << std::endl;
	}
}
