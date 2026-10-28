Client3 PSP
===========

Version 1.0.0 (2026-10-28)

Install:
Copy this whole folder to:

  /PSP/GAME/Client3-PSP/

The final path on the Memory Stick should look like:

  /PSP/GAME/Client3-PSP/EBOOT.PBP
  /PSP/GAME/Client3-PSP/config.ini
  /PSP/GAME/Client3-PSP/rom/config.ini
  /PSP/GAME/Client3-PSP/rom/cache/...
  /PSP/GAME/Client3-PSP/README.md
  /PSP/GAME/Client3-PSP/CHANGELOG.md

Server/config:
This is a PSP client build. To connect to a server running on your PC, edit
config.ini (and rom/config.ini) and set socketip to the PC's LAN IP address.
The default config keeps lowmem = 1 for stability.

Rendering options in config.ini:
  render_distance = 16   Scene radius in tiles (8-25). Lower is faster.
  render_scale    = 2    Scene at half resolution (1 = full resolution).
  render_gu       = 1    Use the PSP Graphics Engine for 3D triangles.

If the game still crashes, try render_gu = 0 or a lower render_distance.

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
device. The PSP and the server PC must be on the same network.
