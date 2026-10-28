# Changelog

## 1.0.0 - 2026-10-28

First PSP release of Client3 with the PSP-specific rendering, memory, and networking updates.

### Added
- PSP Graphics Engine (GU) renderer for 3D triangles, toggled with `render_gu` (fallback to the software renderer)
- Half-resolution 3D scene on PSP (`render_scale = 2`), with input coordinates scaled to match
- Configurable scene radius on all platforms, `render_distance` (clamped to 8-25)
- PSP 3D scene and viewport buffers sized for the PSP memory budget
- Release packaging: `build-psp.sh` now also ships README.md and CHANGELOG.md in `dist/Client3-PSP/`

### Changed
- PSP links against `libpspgu` and `libpspge`
- Reduced 3D memory on PSP: `MODEL_MAX_DEPTH` 600, `MODEL_DEPTH_FACE_COUNT` 80, `PIX3D_POOL_COUNT` 5
- Flames disabled on PSP to save RAM
- PSP bump allocator reserves 16 MiB (lowmem) or 24 MiB instead of 32 MiB, leaving headroom for runtime and asset allocations
- Default server address for the PSP package is set in `config.ini`/`rom/config.ini` (`socketip`, `http_port = 8888`)
- PSP docs (`docs/PSP_*.md`) and the packaged README updated for the new renderer options

### Fixed
- PSP crashes caused by memory exhaustion during scene and cache setup
- Client now stops cleanly during initialization if the cache or network setup fails, rather than continuing into a crash
- Mouse/viewport input mapping on half-resolution rendering

### Upstream
- Based on Client3 (RuneScape 2 revision #225 port) from https://github.com/lesleyrs/Client3
