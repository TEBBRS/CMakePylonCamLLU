# CMakePylonCamLLU
An application for connecting to the wolfram engine with a pylon camera

Main purpose:
The intend of this application is to collect data from a Pylon Camera. Send the image to a running Wolfram Engine. Let some vision algorithm loos on the picture
and display the changed picture in a window.

Actual state:
At this moment i don't understand howto communicate with the Wolfram kernel. So the program is far from finished.

What did I do to come to this point:

PREREQUISITES
=============
First yo need to download the Library Link Utilities (LLU) from https://github.com/WolframResearch/LibraryLinkUtilities
I've cloned it locally and opened it into Visual Studio 2022. To compile the library I needed to add the following directive to CMake:
-DWolframLanguage_INSTALL_DIR="C:\Program Files\Wolfram Research\Wolfram Engine\13.3" otherwise WSTP couldn't be found.

Compilation
===========
Compiling this application is pretty straight forward. With find_package you include the LLU library into you're application.
I also needed to add the following directive to CMake:
-DWolframLanguage_INSTALL_DIR="C:\Program Files\Wolfram Research\Wolfram Engine\13.3" but after rechecking I found this shouldn't be necessary.

RUNNING THE APPLICATION
=======================
To run the application I needed to copy the wstp64i64.dll next to where the executable is.
It looks like this:

