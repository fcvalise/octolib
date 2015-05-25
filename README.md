# octolib [![Build Status](https://magnum.travis-ci.com/IohannRabeson/octolib.svg?token=oSgYDG8ZHmxB1gxGNZxP&branch=master)](https://magnum.travis-ci.com/IohannRabeson/octolib)  

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
 - Qt 5 framework
 - Boost (for units tests only)

### Building the library
    $> make

### Building editors and tools

All tools are located at <octolib_root>/tools/.

## Makefile
### Rules

 - make complete: rebuilds the library then build tools and unit tests
 - make doc: generate documentation
 - make open_doc: open documentation in your web browser (OSX only)
 - make run_tests: builds unit tests
 - make tests: builds unit tests
 - make application_tests: builds interactives tests
 - make tools: builds tools

### Debug/Release switch

By default the Makefile builds in release mode.  
You can switch this mode to debug using MODE variable.  
Exemple to run make re in debug mode:
	
	make re MODE=debug

