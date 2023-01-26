# ----------------------------
# Makefile Options
# ----------------------------

NAME = FPQS
ICON = icon.png
DESCRIPTION = "Get all possible zeros for a polynomial"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
