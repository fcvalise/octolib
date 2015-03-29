/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:42:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 10:15:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP
# define APPLICATION_HPP
# include "StateManager.hpp"

namespace octo
{
	class ResourceManager;
	class GraphicsManager;
	class Options;

	class ApplicationImp;
	
	/*!	\class Application
	 *	\brief Manage all systems requiered by a game
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
		 *
		 *	They are serveral keys used to parameters the application when it started.<BR>
		 *	The table below lists each of theses keys and describes it:
		 *
		 *	<TABLE>
		 *	<TR>
		 *		<TH>key</TH>
		 *		<TH>value type</TH>
		 *		<TH>description</TH>
		 *		<TH>default value</TH>
		 *	</TR>
		 *	<TR>
		 *		<TD>fullscreen</TD>
		 *		<TD>boolean</TD>
		 *		<TD>Enable or disable fullscreen render</TD>
		 *		<TD>false</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>vsync</TD>
		 *		<TD>boolean</TD>
		 *		<TD>Enable or disable vertical syncronization</TD>
		 *		<TD>false</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>resolution</TD>
		 *		<TD>VideoMode</TD>
		 *		<TD>Define render resolution. 
		 *		The format is: <width>x<height>-<bits_per_pixel></TD>
		 *		<TD>greatest fullscreen mode available</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>start_state</TD>
		 *		<TD>string</TD>
		 *		<TD>Define the first state started when the application begin</TD>
		 *		<TD>key passed to Application::run() is used by default</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>package</TD>
		 *		<TD>string</TD>
		 *		<TD>Define the package file path loaded at application start</TD>
		 *		<TD>if this key is not specified no package is loaded</TD>
		 *	</TR>
		 *	</TABLE>
		 *
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
		static ResourceManager&	getResourceManager();
		static Options&			getOptions();
	private:
		static ApplicationImp*	s_instance;
	};
}

#endif
