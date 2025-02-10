SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = tergo_sofle/rev1
SWAP_HANDS_ENABLE = yes
CONVERT_TO=rp2040_ce

ifeq ($(strip $(USE_LAYOUT_ABNT2)),yes)
    OPT_DEFS += -DUSE_LAYOUT_ABNT2
endif
