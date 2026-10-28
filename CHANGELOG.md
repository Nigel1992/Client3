# Changelog

## [Unreleased/PSP Build] - 2026-10-28

### Added
- PSP GU renderer path for 3D triangles (toggle via `render_gu`) with fallback to software renderer
- Config options for PSP: `render_distance` (8-25), `render_scale` (1=full, 2=half), `render_gu` (0/1)
- PSP low memory defaults and stability improvements
- Half-resolution scene rendering support on PSP with proper mouse/input scaling
- Performance overlay toggle support on PSP

### Changed
- Updated PSP build to link against `libpspgu` and `libpspge`
- Lowered memory usage on PSP/low-end targets: reduced `MODEL_MAX_DEPTH`, `MODEL_DEPTH_FACE_COUNT`, `PIX3D_POOL_COUNT`
- Disabled flames on PSP
- Switched to half-resolution scene rendering by default on PSP for stability
- Updated default server IP to `192.168.178.186:8888` for local network play
- Increased scene allocator headroom on PSP for the lower resolution path
- Improved PSP startup stability with better error handling for cache/network initialization

### Fixed
- PSP crashes during startup/gameplay through reduced memory footprint and safer initialization
- GUI/input coordinate scaling for half-resolution rendering

## Upstream
- Based on Client3 (RuneScape 2 revision #225 port) from https://github.com/lesleyrs/Client3
