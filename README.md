# octolib [![Build Status](https://magnum.travis-ci.com/IohannRabeson/octolib.svg?token=oSgYDG8ZHmxB1gxGNZxP&branch=master)](https://magnum.travis-ci.com/IohannRabeson/octolib)  

Octodyssey's core library repository.

## How to report problems?
Please do it using this [issue tracker](https://github.com/IohannRabeson/octolib/issues).

## Organisation
The source files of the library are located in <code>includes/</code> and <code>src/</code> directories.  
This repository contains an units test program located in <code>tests/</code>' directory
and somes graphics interactives test programs located in <code>interactive_tests/</code> folder.  
Somes modules provides tools applications which are located in <code>tools/</code> directory.
  
Sources of theses interactives application are a good entry point to discover the library,
and they are used as examples by generated documentation.

Tools can be found in <code>tools/<tool_name></code>.  
 - Packager: <code>tools/packager</code>
 - Package reader: <code>tools/package_reader</code>
 - Editors: <code>tools/editors</code>

Documentation files are located in <code>doc/</code>

## How to build?
### Requierements
 - C++ 11 compiler (clang 6, g++ 4.8 or higher)
 - Doxygen for documentation (with Dot if you wants cutes graphs)
 - GNU make
 - SFML 2.2 or higher
 - Qt 5 framework
 - Boost test library

### Building the library
Produces the library <code>libocto.a</code> into the root directory:

    $> git clone git@github.com:IohannRabeson/octolib.git
    $> cd octolib
    $> make complete

Generate the documentation:

    $> make doc
    
Builds are made in <code>builds/</code> folder.
### Updating the library

    $> git pull origin master
    $> git submodule update
    $> make complete
    
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

## Documentation

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


