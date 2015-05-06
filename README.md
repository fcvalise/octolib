# octolib
Octodyssey's core library repository.

## How to report problems?
Please do it using this [issue tracker](https://github.com/IohannRabeson/octolib/issues).

## Organisation
The source files of the library are located in '<root>/includes/' and '<root>/src/' directories.  
This repository contains an units test program located in '<root>/tests/' directory
and somes graphics interactives test programs located in '<root>/interactive_tests/' folder.  
Somes modules provides tools applications which are located in '<root>/tools/directory.
  
Sources of theses interactives application are a good entry point to discover the library,
and they are used as examples by generated documentation.

### Modules

Octolib is separable into several modules:  
#### Core module  
Provides commons stuff.

#### State management module  
Provides services to manage the differents screens required by a game.

#### Package module  
Provides services to pack multiple ressources into an unique file called
package. This module provides also a way to read datas from a package file.

#### Resource module  
Manage all the games ressources such textures, fonts, sound. 
Resource module use read services of packages module.

#### Animation system  
Provides services to animate objects properties.

#### Graphics
Provides services to render stuff

#### Audio engine
Provides classes to play music composed in real-time.

#### Gui system  
Provides basic stuffs to create simple user interface.

## How to build?
### Requierements
 - C++ 11 compiler
 - Doxygen for documentation (with Dot if you wants cutes graphs)
 - GNU make
 - SFML 2.2
 - Boost (for units tests only)

### Building the library
    $> make

### Building examples
	$> cd interactive_tests/<test_directory>; make

### Generating HTML documentation
    $> make dox

Then index page can be quickly opened under MacOS with:

	$> make open_dox

### How to rebuild all?
You can rebuild all, the library, the units and interactives tests and tools with:

	$> make complete
