AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
bin_PROGRAMS = secretary runtests
secretary_SOURCES = secretary.c secretary-gtk-gettext.h \
        secretary-gtk-widget.h secretary-gtk-widget.c \
        secretary-gtk-toolbar.h secretary-gtk-toolbar.c \
        secretary-gtk-panel.h secretary-gtk-panel.c \
        secretary-gtk-project-treeview.h secretary-gtk-project-treeview.c \
        secretary-gtk-project-tree-model.c secretary-gtk-project-tree-model.h \
        secretary-gtk-task-listview.h secretary-gtk-task-listview.c \
        secretary-gtk-utils.h secretary-gtk-utils.c \
        secretary-gtk-application.h secretary-gtk-application.c \
        gettext.h
secretary_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
secretary_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@
LDADD = $(LIBINTL)

runtests_SOURCES = test/runtests.c CuTest.c CuTest.h \
        secretary-gtk-project-tree-model.c secretary-gtk-project-tree-model.h \
        test/test-secretary-gtk-project-tree-model.c \
        test/test-secretary-gtk-project-tree-model.h
runtests_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
runtests_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@

SUBDIRS = po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = config.rpath

TESTS = runtests

test: check

clean-local:
	-rm *~
