# CRPG2.0
C++ console rpg

In order to compile it you'll need Visual Studio. 
Create a new Windows Console Project and attach to the Header Files folder the files preproc.h and prototype.h
Put the file firstLevel.map in the same directory with CRPG.cpp.
To link the resources (the 2 wav files and the ico) Right Click on the Resource Files folder -> 
Add Resource... *it doesn't matter which type of resource you choose, as it will be automatically changed*
-> Import -> *select the All files filter to see the files* and pick the file you want.
Automatically, a header file called resource.h will be created and it will contain the links to your resources (make sure that button-48.wav is IDR_WAVE1 and beep-03.wav is IDR_WAVE2).
