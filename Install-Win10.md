
# Windows 10 Install (not using Visual Studio)

These are instructions for building KAI on Windows without using Visual Studio.

Normally, you can just install cmake for windows, run it, then build the resultant .sln Solution file.

These instructions are for building KAI on Windows just using the Ubuntu bash shell.

## Install Ubuntu for Windows

See here.

## Install Requirements

Try the following from a Bash shell on Windows 10:

	$ alias get='sudo apt-get install'
	$ get clang
	$ get cmake
	$ get libboost-system-dev
	$ get libboost-filesystem-dev
	$ get libboost-program-options-dev

### Problems

(First)[http://stackoverflow.com/questions/17775390/clang-3-3-in-c1y-mode-cannot-parse-cstdio-header]

And another:

/home/christian/Desktop/local/KAI/Include/KAI/Core/Type/Traits.h:3:10: fatal error: 'boost/type_index.hpp' file not
      found
.#include <boost/type_index.hpp>







