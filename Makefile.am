AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
bin_PROGRAMS = secretary runtests
secretary_SOURCES = secretary.c gettext.h \
        widget.h widget.c \
        toolbar.h toolbar.c \
        panel.h panel.c \
        project-treeview.h project-treeview.c \
        project-tree-model.c project-tree-model.h \
        task-listview.h task-listview.c \
        utils.h utils.c \
        application.h application.c \
        gettext.h
secretary_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
secretary_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@
LDADD = $(LIBINTL)

runtests_SOURCES = test/runtests.c CuTest.c CuTest.h \
        project-tree-model.c project-tree-model.h \
        test/test-project-tree-model.c \
        test/test-project-tree-model.h
runtests_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
runtests_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@

SUBDIRS = po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = config.rpath

TESTS = runtests

test: check

clean-local:
	-find -name '*~' -o -name '*.bkp' | xargs rm
