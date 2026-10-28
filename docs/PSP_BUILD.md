# PSP Build

This repository already contains an upstream PSPSDK target in `psp.mk`.
Release: 1.0.0 (2026-10-28)

## Requirements

- PSPSDK installed, with `psp-gcc`, `psp-config`, `mksfoex`, and `pack-pbp` on `PATH`
- `zip`
- Runtime data in `rom/`

The build script defaults `PSPDEV` to `/usr/local/pspdev`; override it if your
toolchain lives elsewhere (for example `PSPDEV=/home/nigel/pspdev`).

## Build And Package

From the repository root:

```sh
./build-psp.sh
```

or build manually:

```sh
make -f psp.mk clean
make -f psp.mk -j$(nproc)
```

Output:

```text
dist/Client3-PSP.zip
dist/Client3-PSP/EBOOT.PBP
dist/Client3-PSP/config.ini
dist/Client3-PSP/rom/
dist/Client3-PSP/README.txt
dist/Client3-PSP/README.md
dist/Client3-PSP/CHANGELOG.md
```

Copy `Client3-PSP` to:

```text
/PSP/GAME/Client3-PSP/
```

## PC-Hosted Server

The PSP client reads `config.ini` from the same directory as `EBOOT.PBP`. The
package also keeps the repository's `rom/config.ini` copy. For a server running
on a PC on the same LAN, set this in both files:

```ini
socketip = your.pc.lan.ip
http_port = 8888
```

The package defaults to `lowmem = 1` for stability. Keep the PSP and the server
PC on the same network.

## Rendering Options

```ini
render_distance = 16   # scene radius in tiles (8-25), lower is faster
render_scale    = 2    # 2 = half-resolution scene, 1 = full resolution
render_gu       = 1    # 1 = PSP Graphics Engine, 0 = software triangles
```

If the client crashes, first try `render_gu = 0` and lower `render_distance`.
