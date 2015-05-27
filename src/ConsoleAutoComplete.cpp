/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleAutoComplete.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:15:35 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 03:17:26 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleAutoComplete.hpp"

namespace octo
{
	void	ConsoleAutoComplete::addWord(std::wstring const& word, Lexems lexem)
	{
		m_tree.addWord(word, lexem);
	}
}
