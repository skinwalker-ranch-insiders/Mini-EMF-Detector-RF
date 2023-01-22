This project requires the Manchester libraries for Arduino Software.
I am using Arduino 1.8.57.0 from the Windows 11 App Store.
I was told the Manchester libraries do not work in the newer version of the Arduino softrware.

Create a folder called arduino-libs-manchester-master under your Documents\Arduino\libraries folder.
Copy the following files to it:
	keywords		(It gives you a list of commands that can be used when call man. commands)
	library
	Manchester.cpp
	Machester.h		(#include <Manchester.h> in the ino files)
	README.markdown
