#
#   This file is part of the
# ███╗   ██╗ █████╗ ███████╗██╗     
# ████╗  ██║██╔══██╗██╔════╝██║     
# ██╔██╗ ██║███████║███████╗██║     
# ██║╚██╗██║██╔══██║╚════██║██║     
# ██║ ╚████║██║  ██║███████║███████╗
# ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚══════╝
#   project : https://github.com/jacmoe/nasl
#
#   Copyright 2017 Jacob Moen
#
#

# Paths
# -----

set(TARGET_NAME nasl)

set(Sources
    nasl/script.h
    nasl/script.c
    nasl/graphics.h
    nasl/graphics.c
    nasl/color.h
    nasl/color.c
    nasl/buffer.h
    nasl/buffer.c
)


set(3rdParty_Headers
    3rd/my_basic.h
    3rd/nuklear.h
    3rd/nuklear_glfw_gl3.h
    3rd/stb_image.h
)

set(3rdParty_Source
    3rd/my_basic.c
)

add_library(${TARGET_NAME} STATIC
    ${Sources}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)
