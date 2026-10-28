# PSP Controls

These are the controls implemented in `src/platform/psp.c`.

The PSP build uses a native-pixel fullscreen viewport for readability. It fills
the PSP screen without shrinking the RuneScape UI, so only part of the full
client is visible at once and you pan around when needed.

| PSP input | Client action |
| --- | --- |
| Analog nub | Move cursor |
| D-pad | Arrow keys |
| Circle | Left click |
| Cross | Right click |
| Triangle | Control key |
| Square | Login using `username` and `password` from `rom/config.ini` |
| Select | Toggle performance overlay |
| L trigger | Reset the view |
| R trigger + analog nub | Move the cursor faster |
| HOME | Exit through the PSP callback |

There is no PSP on-screen keyboard in this port. Set login details and server
address in `config.ini` before copying the folder to the Memory Stick.
