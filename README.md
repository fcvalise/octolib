# octolib
Octodyssey's core library

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
