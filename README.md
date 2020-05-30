# Space-Invaders
C++ Space Invaders clone built for a custom University of Leeds gamepad (NXP K64F board). The features implemented based on the original game:
- Left to right movement for the player 'canon'
- A fixed amount of player lives
- Firing mechanics for both canon and invaders (hence 2D collision systems)
- Random firing from remaining invaders
- Wave based level design

Added Boss waves, featuring a single, larger sprite which fires at a faster interval than previous waves. Previously used velocity based movement but have removed the system due to limited screen size, pending implementation of step based movement.

TODO:
- Incremental movement
- Ride of the Valkyries 8bit to C code – file upload
- Not recognising wave end
