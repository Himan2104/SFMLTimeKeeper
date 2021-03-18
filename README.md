# SFMLTimeKeeper
Timekeeper is a header only utility class/library aimed towards better and easy handling of time in SFML.
This code is free to use, share and modify and comes with no warranty what so ever.
Let me know of any improvements or issues. 

## Features
- timescale: Can be used to speed up, slow down or pause game. Also affects the dynamic clock.
- deltatime: Can be used for timestep fixing.
- static clock: A clock unaffected by the changes in timescale. It will always return the time elapsed since start or last reset.
- dynamic clock: A clock that is affected directly by the timescale.

Please see the _src/demo.cpp_ file to understand the library a bit better.

Consider giving it a Star if you found it useful. Thanks :)
