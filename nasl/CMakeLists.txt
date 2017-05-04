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
project(nasl_lib)

set(TARGET_NAME nasl)

set(Headers
    include/nasl_script.h
    include/nasl_graphics.h
    include/nasl_color.h
    include/nasl_buffer.h
)

set(Sources
    src/nasl_script.c
    src/nasl_graphics.c
    src/nasl_color.c
    src/nasl_buffer.c
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

include_directories(
    include
    3rd/include
)

add_library(${TARGET_NAME} STATIC
    ${Headers}
    ${Sources}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)
