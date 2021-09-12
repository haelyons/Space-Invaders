# Space-Invaders
C++ Space Invaders clone built for a custom University of Leeds gamepad (NXP K64F board). Features implemented based on the original game:
- Left to right movement for the player 'canon'
- Firing mechanics for both canon and invaders (2D collision systems)
- Random firing from current invaders
- Wave based level design

Added Boss waves, featuring a single, larger sprite which fires at a faster interval than previous waves. Previously used velocity based movement but was removed due to limited screen size and unarcade-like animation. Also features menu screen for navigating options, credits and game.

Overall this project was an exercise in headers and low level, unsafe code with lots of raw pointer arithmetic. Using the [] operator regularly to refer to vectors of vectors of pointer objects, while fun to finding neat algorithmic and iteration solutions, reveals the weakness of templates and pointer referencing in C++. Not only is it daunting for those wishing to read the code, it is very difficult to keep track of while programming and causes overflow and misreferencing errors constantly. Moreover the memory allocated in the initial declarations of the vectors of vectors is never released, slowing down execution as functions from the objects pointed to were called.

In the future, storing objects in vectors will be avoided, as this is a huge memory hog. Instead values for each alien could be stored as integers and parsed on access. Matrices provide another easier way to define these 3D integer maps.

![alt text](https://raw.githubusercontent.com/haelyons/Space-Invaders/master/Gamepad.png)

![alt text](https://github.com/haelyons/Space-Invaders/blob/master/Gamepad%20Diagram.png)
