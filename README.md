# Space-Invaders
C++ Space Invaders clone built for a custom University of Leeds gamepad (NXP K64F board). Features implemented based on the original game:
- Left to right movement for the player 'canon'
- Firing mechanics for both canon and invaders (2D collision systems)
- Random firing from current invaders
- Wave based level design

Added Boss waves, featuring a single, larger sprite which fires at a faster interval than previous waves. Previously used velocity based movement but have removed due to limited screen size and unarcade-like animation, pending implementation of step based movement.

TODO:
- Step based movement
- Ride of the Valkyries 8bit to C code – file size
- Not recognising wave end
