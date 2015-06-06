# Packager

This utility packages multiple file into one package which
can be used with Octolib ressource system.

## How to build:

    $> make
## How to use

	    $> packager <output_file> [-h <header_file_path>] <input_files...>
		    
		Optional flag <code>-h</code> allows to define the name of the header file produced.  
		The header is not produced is <code>-h</code> is omitted.

### Exemples
		Compile a package with all files in <code>./resources/fx_textures/</code> and create or update a C++ header <code>FxTextureDefinitions.hpp</code> which defines the keys of each resources packed in <code>fx_textures.pck</code>:

		    $>  packager fx_textures.pck -h FxTextureDefinitions.hpp ./resources/fx_textures/*
