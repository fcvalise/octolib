/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspTree.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 11:31:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:47:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <BspTree::VisitorMode M, class V>
	void	BspTree::visit(V& visitor)
	{
		VisitorPolicy<BspNode, V&, M>::visit(m_root.get(), visitor);
	}

	template <BspTree::VisitorMode M, class V>
	void	BspTree::visit(V& visitor)const
	{
		VisitorPolicy<BspNode const, V&, M>::visit(m_root.get(), visitor);
	}

	template <BspTree::VisitorMode M, class V>
	void	BspTree::forEach(V visitor)
	{
		VisitorPolicy<BspNode, V, M>::visit(m_root.get(), visitor);
	}

	template <BspTree::VisitorMode M, class V>
	void	BspTree::forEach(V visitor)const
	{
		VisitorPolicy<BspNode const, V, M>::visit(m_root.get(), visitor);
	}

	template <class N, class V>
	struct	BspTree::VisitorPolicy<N, V, BspTree::VisitorMode::Infix>
	{
		static inline void visit(N* root, V& visitor)
		{
			if (root->front())
				visit(root->front(), visitor);
			visitor(root);
			if (root->back())
				visit(root->back(), visitor);
		}
	};

	template <class N, class V>
	struct	BspTree::VisitorPolicy<N, V, BspTree::VisitorMode::Prefix>
	{
		static inline void visit(N* root, V& visitor)
		{
			visitor(root);
			if (root->front())
				visit(root->front(), visitor);
			if (root->back())
				visit(root->back(), visitor);
		}
	};

	template <class N, class V>
	struct	BspTree::VisitorPolicy<N, V, BspTree::VisitorMode::Postfix>
	{
		static inline void visit(N* root, V& visitor)
		{
			if (root->front())
				visit(root->front(), visitor);
			if (root->back())
				visit(root->back(), visitor);
			visitor(root);
		}
	};
}
