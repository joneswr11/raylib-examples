Working example with raylib on windows (used visual studio)

key things to note: 
- download the release for the appropriate os and build env (for exmaple windows visual studio vs mingw)
- add the include and lib folder in the project
- make sure you compile against those lib files
- if using textures, audio etc. you need to have the resources folder in the same folder as the executable
- add '-Wl,--subsystem,windows' to LDFLAGS to hide console window and printing out all the openGL information such as gpu info, texture loading/unloading etc.