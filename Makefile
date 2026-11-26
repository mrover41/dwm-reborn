# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRCDIR = src
BUILDDIR = build

SRC = $(shell find $(SRCDIR) -type f -name "*.c" ! -name "transient.c" | sort)
OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))
TARGET = $(BUILDDIR)/dwm

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c config.h config.mk
	@mkdir -p $(dir $@)
	${CC} -c ${CFLAGS} $< -o $@

#config.h:
#	cp config.def.h $@

$(TARGET): ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -rf $(BUILDDIR) dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.mk config.h include src \
		dwm.1 dwm.png dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f $(TARGET) ${DESTDIR}${PREFIX}/bin/dwm
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all clean dist install uninstall
