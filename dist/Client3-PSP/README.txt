Client3 PSP
===========

Install:
Copy this whole folder to:

  /PSP/GAME/Client3-PSP/

The final path on the Memory Stick should look like:

  /PSP/GAME/Client3-PSP/EBOOT.PBP
  /PSP/GAME/Client3-PSP/config.ini
  /PSP/GAME/Client3-PSP/rom/config.ini
  /PSP/GAME/Client3-PSP/rom/cache/...

Server/config:
This is a PSP client build. To connect to a server running on your PC, edit
config.ini and set socketip to the PC's LAN IP address. The default config keeps
lowmem = 1 for stability. On a PSP-2000 or newer, set lowmem = 0 to use the
24 MiB scene allocator and enable higher-memory client features.

Controls:
Analog nub        Move cursor
D-pad             Arrow keys
Circle            Left click
Cross             Right click
Triangle          Control key
Square            Login using username/password from rom/config.ini
Select            Toggle performance overlay
L trigger         Reset view
R trigger + nub   Move cursor faster
HOME              Exit

Notes:
This package uses the upstream Client3 PSPSDK target and the redistributable
runtime files included in this repository. Audio is stubbed in the PSP platform
layer. Real hardware should be PSP-2000 or newer; PSP-3000 is the intended test
device.
