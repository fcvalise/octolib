# Package reader

This utility display informations about a package.  
This program can also extract packaged file.

## Usage

	$> package_reader <package_file> <command> [args...]

### --info
Display general informations about package file:

    $> package_reader my_package.pack --info

### --list
Display a detailed list of item contained by the package file:

    $> package_reader my_package.pack --list
    
### --extract <key> <output_file>
Extract packaged data into a new file:

    $> package_reader my_package.pack --extract 123 my_awesome_texture.png
