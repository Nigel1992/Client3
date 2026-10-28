# PSP Port Status

Source base: Client3 upstream PSP target, built with PSPSDK via `psp.mk`.
Release: 1.0.0 (2026-10-28)

| Area | Status | Notes |
| --- | --- | --- |
| Startup | Working | PSP module info, exit callback, main thread, and 333 MHz clock setup are implemented in `src/platform/psp.c`. Cache and network failures abort cleanly instead of continuing into a crash. |
| Display | Working | 480x272 framebuffer written to PSP VRAM. The 3D scene can use the PSP Graphics Engine (`render_gu = 1`) or the software rasterizer, at full or half scene resolution (`render_scale`). |
| Input | Working | Analog cursor, click buttons, D-pad keys, viewport pan/reset, login shortcut, and HOME exit are wired. Input is scaled correctly for half-resolution rendering. |
| Filesystem/runtime data | Working | Package includes `rom/`, including `rom/config.ini`, cache files, fonts, soundfont, and map data from the repository. |
| Configuration | Working | `config.ini` next to `EBOOT.PBP` supplies startup/login/server/renderer options. `lowmem = 1` is the default for stability. |
| Networking | Working | PSP network init exists and connects through the configured PSP access point. A PC-hosted server requires `socketip` set to the PC LAN IP and both devices on the same network. |
| Audio | Missing/optional | PSP platform audio functions are stubs. |
| Timing | Working | Uses PSP system time and callback-friendly delay calls. |
| Memory | Working | Reduced 3D model depth, face count, and pix3d pool count; flames disabled. Default half-resolution scene and 16-tile render distance to stay within PSP memory. |
| Packaging | Working | `build-psp.sh` creates `dist/Client3-PSP.zip` ready for `/PSP/GAME/Client3-PSP/`. |

Real hardware testing is recommended on a PSP-2000/3000. If a crash occurs,
try `render_gu = 0`, `render_scale = 1` (or keep `2`), and a lower
`render_distance` before reporting the issue.
