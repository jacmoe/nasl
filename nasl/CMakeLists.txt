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

set(Headers
    include/script.h
    include/graphics.h
    include/color.h
    include/buffer.h
)

set(Sources
    src/script.c
    src/graphics.c
    src/color.c
    src/buffer.c
)

set(3rdParty_Headers
    3rd/include/my_basic.h
    3rd/include/nuklear.h
    3rd/include/nuklear_glfw_gl3.h
    3rd/include/stb_image.h
)

set(3rdParty_Source
    3rd/src/my_basic.c
)

add_library(${TARGET_NAME} STATIC
    ${Headers}
    ${Sources}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)
