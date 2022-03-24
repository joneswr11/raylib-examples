Working example with raylib on windows (used visual studio)

key things to note: 
- download the release for the appropriate os and build env (for exmaple windows visual studio vs mingw)
- add the include and lib folder in the project
- make sure you compile against those lib files
- if using textures, audio etc. you need to have the resources folder in the same folder as the executable
- add '-Wl,--subsystem,windows' to LDFLAGS to hide console window and printing out all the openGL information such as gpu info, texture loading/unloading etc.

- rather than adding a bunch of textures, either load one and stretch it out, multiplying how many you want by it's width
- if you only want one texture, as a background, have a file or some way to store where the points of collision are, and store them in array of rectangles and
do your collision checking against that array