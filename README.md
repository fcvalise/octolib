# octolib
Octodyssey's core library

## How to build?
### Requierements
 - C++ 11 compiler
 - Doxygen for documentation
 - GNU make

### Building the library
    $> make

### Generating HTML documentation
    $> make dox

Then index page can be quickly opened under MacOS with:

	$> make open_dox

### Building the tests
They are units tests in tests/ directory and graphics interactives
tests in graphics_tests/ directory.  

Each graphics tests have his own Makefile to build it.
