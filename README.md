"# Snake-Game" 
You can install libraries either from the Ubuntu software center or from command line.
To install libraries:
1. Simply run the terminal and go to directory which contains the file downloaded file
“install-libraries.sh”.
2. Run the command $: bash install-libraries.sh
3. Provide the password and wait for the libraries to be installed. If you get an error that
libglew1.6-dev cannot be found, try installing an older version, such as libglew1.5-dev by
issuing following on command line $: sudo apt-get install libglew1.5-dev
4. If you have any other flavour of Linux. You can follow similar procedure to install
“OpenGL” libraries.

COMPILING
each time you need to compile and link your program (game)
you will be simply calling the “make” utility in the game directory on the terminal to perform the
compilation and linking.$: make
if there are no errors this will create an exe. file
named game-release
Run that game-release file to run your game by $: ./game-release
