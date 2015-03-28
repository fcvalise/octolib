# octolib
Octodyssey's core library repository.

## Organisation
The source files of the library are located in '<root>/includes/' and '<root>/src/' directories.  
This repository contains an units test program located in '<root>/tests/' directory
and somes graphics interactives test programs located in '<root>/interactive_tests/' folder.
  
Sources of theses interactives application are a good entry point to discover the library,
and they are used as examples by generated documentation.

### Modules
Octolib is separable into several modules:
- Core module  
Provides somes commons classes as containers.
 - State management module  
Provides services in order to manage the differents screens required by a game.  
 - Package module  
Provides services in order to pack multiple ressources into an unique file called
package. This module provides also a way to read datas from a package file.  
 - Resource module  
Manage and provides all the games ressources.  
Resource module use read services of packages module.  
 - Animation system  
Provides services in order to animate objects properties.  
 - Gui system  
Provides basic stuffs to create simple user interface. 

## How to build?
### Requierements
 - C++ 11 compiler
 - Doxygen for documentation
 - GNU make
 - SMFL 2.2
 - Boost (for units tests only)

### Building the library
    $> make

### Generating HTML documentation
    $> make dox

Then index page can be quickly opened under MacOS with:

	$> make open_dox

### How to rebuild all?
You can rebuild all, the library, the units and interactives tests and tools with:

	$> make complete
