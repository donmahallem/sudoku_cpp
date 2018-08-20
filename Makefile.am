.PHONY: all test web
AUTOMAKE_OPTIONS = foreign
SUBDIRS = test web benchmark binSrc
CXXFLAGS = -Wall -std=gnu++11 -g $(USECLANG)

all: test web

.PHONY: web
web: Subfolder
Subfolder Mystuff:
	${MAKE} -C web