Client3 reads startup and login configuration from:

  config.ini

The package also keeps a copy at rom/config.ini because the upstream repository
stores its example console config there. Keep both copies in sync if you edit
settings.

For a PC-hosted single-player/private server, edit config.ini and set socketip
to your PC's LAN IP address. Keep lowmem = 1 for the conservative profile, or
set lowmem = 0 on PSP-2000+ to enable the 24 MiB scene allocator and higher-
memory client features.
