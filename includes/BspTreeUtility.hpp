/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspTreeUtility.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 11:34:55 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:53:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPTREEUTILITY_HPP
# define BSPTREEUTILITY_HPP
# include <ostream>

namespace octo
{
	class BspTree;

	void	printDot(BspTree const& tree, std::ostream& os);
}

#endif
