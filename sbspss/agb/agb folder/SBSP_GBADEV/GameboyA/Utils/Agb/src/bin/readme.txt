
Notes:

* The Development Environment
  The modules in this folder were created using Visual C++ 6.0 Enterprise Edition.  
  STL is used, so an error will result if you use any compiler before Visual C++ 
  5.0 SP2.

* Change the Visual C++ Settings
  You must use the library created for the AGB in order to compile the various 
  converters.  For this reason, you must modify Visual C++, specifying "include" 
  and "lib" found inside this folder at the very top of Option-Directory-Include 
  and Library in Visual C++.

  Regarding the compilation of prevcl, please execute nmake from the DOS prompt.

* Change Project Settings to Use the Library
  Please also make the following change to use the library created for AGB:

  1. Add libmagbx.lib to Project-Settings-Link-General-Object/Library Modules.
  