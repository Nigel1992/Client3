#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

export PSPDEV="${PSPDEV:-/home/nigel/pspdev}"
export PATH="$PATH:$PSPDEV/bin"

need_tool() {
    if ! command -v "$1" >/dev/null 2>&1; then
        echo "missing required tool: $1" >&2
        exit 1
    fi
}

need_tool psp-gcc
need_tool psp-config
need_tool mksfoex
need_tool pack-pbp
need_tool zip

if [ ! -d rom ]; then
    echo "missing rom/ runtime data directory" >&2
    exit 1
fi

jobs="${JOBS:-$(nproc)}"

make -f psp.mk clean >/dev/null 2>&1 || true
make -f psp.mk -j"$jobs" -B

if [ ! -f EBOOT.PBP ]; then
    echo "PSP build finished without EBOOT.PBP" >&2
    exit 1
fi

pkg_root="dist/Client3-PSP"
rm -rf dist
mkdir -p "$pkg_root/config"

cp EBOOT.PBP "$pkg_root/EBOOT.PBP"
cp -R rom "$pkg_root/rom"
cp rom/config.ini "$pkg_root/config.ini"

cat > "$pkg_root/config/README.txt" <<'EOF'
Client3 reads startup and login configuration from:

  config.ini

The package also keeps a copy at rom/config.ini because the upstream repository
stores its example console config there. Keep both copies in sync if you edit
settings.

For a PC-hosted single-player/private server, edit config.ini and set socketip
to your PC's LAN IP address. Keep lowmem = 1 for the conservative profile, or
set lowmem = 0 on PSP-2000+ to enable the 24 MiB scene allocator and higher-
memory client features.
EOF

cp README.md "$pkg_root/README.md"
cp CHANGELOG.md "$pkg_root/CHANGELOG.md"
cp PSP_README.txt "$pkg_root/README.txt"

(
    cd dist
    zip -qr Client3-PSP.zip Client3-PSP
)

echo "Built dist/Client3-PSP.zip"
du -h dist/Client3-PSP.zip
