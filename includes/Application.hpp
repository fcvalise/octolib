/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:42:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 19:28:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP
# define APPLICATION_HPP
# include "StateManager.hpp"
# include "NonCopyable.hpp"

namespace octo
{
	class ResourceManager;
	class GraphicsManager;
	class Options;
	class Console;

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
	 *	Some commands are provided by default:
	 *	<TABLE>
	 *	<TR>
	 *		<TH>Name</TH>
	 *		<TH>Parameters</TH>
	 *		<TH>Description</TH>
	 *	</TR>
	 *	<TR>
	 *		<TD>console.list_commands()</TD>
	 *		<TD></TD>
	 *		<TD>List in your terminal all availables commands</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>console.close()</TD>
	 *		<TD></TD>
	 *		<TD>Close the console</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>console.clear()</TD>
	 *		<TD></TD>
	 *		<TD>Clear the console</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>console.quit()</TD>
	 *		<TD></TD>
	 *		<TD>Close the application</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>render.screenshot(bool includeConsole)</TD>
	 *		<TD>includeConsole: define if the console is taken with the screenshot</TD>
	 *		<TD>Take a screenshot of the screen</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>system.change_state(std::string stateKey)</TD>
	 *		<TD><UL><LI>stateKey: define the state to start</LI></UL></TD>
	 *		<TD>Change the current state(see StateManager::changeState()</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>system.show_fps_counter(bool)</TD>
	 *		<TD>bool visible: show or hide</TD>
	 *		<TD>Show or hide the FPS counter display</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>system.list_states()</TD>
	 *		<TD></TD>
	 *		<TD>List the availables states</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>system.list_transitions()</TD>
	 *		<TD></TD>
	 *		<TD>List the availables transitions</TD>
	 *	</TR>
	 *	</TABLE>
	 */
	class Application : public NonCopyable
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
		 *	<TR>
		 *		<TD>console_font</TD>
		 *		<TD>string</TD>
		 *		<TD>Define the font file name used by the console</TD>
		 *		<TD>if this key is not specified the console is disabled</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>fps_counter_enabled</TD>
		 *		<TD>bool</TD>
		 *		<TD>Define if the FPS counter is enabled</TD>
		 *		<TD>if this key is not specified the FPS counter is disabled</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>fps_counter_palette</TD>
		 *		<TD>string</TD>
		 *		<TD>Define the FPS counter's palette</TD>
		 *		<TD>if this key is not specified the FPS counter is disabled</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>fps_counter_font</TD>
		 *		<TD>string</TD>
		 *		<TD>Define the FPS counter's font</TD>
		 *		<TD>if this key is not specified the FPS counter is disabled</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>fps_counter_font_size</TD>
		 *		<TD>unsigned int</TD>
		 *		<TD>Define the FPS counter's font size</TD>
		 *		<TD>12</TD>
		 *	</TR>
		 *	<TR>
		 *		<TD>fps_counter_samples</TD>
		 *		<TD>unsigned int</TD>
		 *		<TD>Define the count of samples displayed by the FPS counter</TD>
		 *		<TD>8</TD>
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

		/*!	Stop the main loop and close the application */
		static void				stop();

		/*!	Pauses the application
		 *
		 *	Pause the application that the game is no longer updated but only drawn.
		 */
		static void				pause();

		/*!	Resumes the application
		 */
		static void				resume();
	
		/*!	Display an error message and closes application */
		static void				error(char const* message);

		/*!	Takes a screenshot */
		static std::string		screenshot(bool captureConsole);

		static StateManager&	getStateManager();
		static GraphicsManager&	getGraphicsManager();
		static ResourceManager&	getResourceManager();
		static Options&			getOptions();
		static Console&			getConsole();
	private:
		static ApplicationImp*	s_instance;
	};
}

#endif
