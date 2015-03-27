/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:42:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/27 01:46:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP
# define APPLICATION_HPP
# include "StateManager.hpp"

namespace octo
{
	class GraphicsManager;
	class Options;

	class ApplicationImp;
	
	/*!	\class Application
	 *	\brief Skeleton of a game
	 *
	 *	Application provide a game state management over a SFML render.<br>
	 *	System must be initialized first with initialize() and
	 *	released with destroy().<br>
	 *	To start the main loop call run() function.<br>
	 *
	 *	The games screens must be implemented with AbstractState.<br>
	 *
	 */
	class Application
	{
	public:
		/*!	Initialize the application
		 *	\param title Window title
		 *	\param optionFilePath option file path
		 *	\param argc element count stored in array argv
		 *	\param argv command line string array
		 *
		 *	Options are loaded from text file at path \a optionFilePath<br>
		 *	Then command line is parsed and if some options directives are found they are
		 *	added to the application options.
		 */
		static void				initialize(std::string const& title,
										   std::string const& optionFilePath,
										   int argc, char **argv);

		/*!	Release the application */
		static void				destroy();

		/*!	Start the main loop */
		static void				run(StateManager::Key const& stateKey);
		static void				stop();
		static void				pause();
		static void				resume();
		static void				error(char const* message);

		static StateManager&	getStateManager();
		static GraphicsManager&	getGraphicsManager();
		static Options&			getOptions();
	private:
		static ApplicationImp*	s_instance;
	};
}

#endif
