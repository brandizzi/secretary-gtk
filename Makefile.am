AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
bin_PROGRAMS = secretary
secretary_SOURCES = secretary.c secretary-gtk-gettext.h \
        secretary-gtk-widget.h secretary-gtk-widget.c \
        secretary-gtk-toolbar.h secretary-gtk-toolbar.c \
        secretary-gtk-utils.h secretary-gtk-utils.c \
        gettext.h
secretary_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
secretary_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@
LDADD = $(LIBINTL)


SUBDIRS = po

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath
