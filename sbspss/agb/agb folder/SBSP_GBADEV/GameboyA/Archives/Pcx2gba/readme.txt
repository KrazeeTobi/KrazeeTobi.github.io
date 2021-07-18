Savage PCX to Gameboy Advance Graphic Convertor         Version 1.0
-------------------------------------------------------------------
Designed and Written By Matthew Tighe.
Copyright (C)Savage Development 2001.
All Rights Reserved.

Introduction
-------------------------------------------------------------------
This graphic convertor allows you to take PCX or PCC graphic files
and convert them into a format you can use on the gameboy advance.

This programme is literally a hack just so I could get started on the
GBA.  

Currently it produces a GCC header file (.H) containing 3 pre-defined
arrays, one for the palette, one for the tile data and one for the map.
This is a bit rubbish I know, I have plans to support COFF object file
output in the future so you can link resources straight into you binaries.

Requirements
------------
Win32 Command Line.

Getting Started
-------------------------------------------------------------------
Usage
-----

PCX2GBA input.pcx array_name <options>

The PCX file is required, the array_name argument forms the base for
the array names eg:

	PCX2GBA mario.pcx mario

	marioData[] {...};	=	Tile data
	#define marioDataLen	=	Length of Tile data
	#define marioBlocks 	=	Number of blocks in data

	marioPal[]	=	Palette Data
	marioPalLen	=	guess

	marioMap[]	=	Map data
	marioMapLen	=	hmm....

Options
-------

-m	Don't remove similar tiles ( this will take up more memory in the cartridge ).
-g	Don't output the map data.
-p	Don't output the palette data.


Check out my Savage Demo for an example of how to use the files PCX2GBA
creates.

The next release in a few days will output maps as well and remove
redundant tiles.

Planned Features
-------------------------------------------------------------------

* For Next Release
- In the Future

* Tile Rationalisation for Flipped tiles
* Output to COFF object file (so you can link it into yor code).

- Better map format
- 16 colour tiles
- Compressed output

Other Utilities
-------------------------------------------------------------------

For more info and downloads see my web pages.

PCX2GB - (GBC)
Much more advanced programme to convert pcx files to Gameboy Colour graphics.
Includes many of the features planned for PCX2GBA.  Such as layered sprites,
compressed output and automatic tile rationalisation with x and y flips.

Savage Gameboy Colour Map Editor - (GBC)
Allows creation of large maps using blocks created by this programme.
Future support for compressed maps and advanced drawing facilities.

Savage PCM2GB Sound Convertor - (GBC)
Simple 8bit to 4bit sample convertor to create Gameboy Colour Wave Files.


Links
------------------------------------------------------------------

www.matt-tighe.co.uk/gba	- My Gameboy Advance website, demos, games, docs.

www.matt-tighe.co.uk/gbc	- My Gameboy colour site.

www.matt-tighe.co.uk		- My Forumla Ford Website, Check out my racing exploits!!!

www.devrs.com			- Excellent site for GBC and GBA.

www.gbadev.org			- The gameboy advance developer site loads of demos + source