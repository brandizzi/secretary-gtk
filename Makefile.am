AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
bin_PROGRAMS = secretary runtests
secretary_module_srcs =	secretary-gtk/widget.h widget.c \
	secretary-gtk/toolbar.h toolbar.c \
	secretary-gtk/panel.h panel.c \
	secretary-gtk/project-treeview.h project-treeview.c \
	project-tree-model.c secretary-gtk/project-tree-model.h \
	secretary-gtk/task-listview.h task-listview.c \
	secretary-gtk/task-tree-model.h task-tree-model.c \
	secretary-gtk/utils.h utils.c \
	secretary-gtk/application.h application.c \
	secretary-gtk/new-task-dialog.h new-task-dialog.c \
	gettext.h
secretary_SOURCES = secretary.c \
	$(secretary_module_srcs)

secretary_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
secretary_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@
LDADD = $(LIBINTL)

runtests_SOURCES = test/runtests.c CuTest.c CuTest.h \
	$(secretary_module_srcs) \
	test/test-project-tree-model.c test/test-secretary-gtk/project-tree-model.h \
	test/test-application.c test/test-secretary-gtk/application.h \
	test/test-new-task-dialog.c test/test-secretary-gtk/new-task-dialog.h \
	test/test-utils.c test/test-secretary-gtk/test-utils.h
runtests_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
runtests_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@

SUBDIRS = po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = config.rpath

TESTS = runtests

test: check

clean-local:
	-find -name '*~' -o -name '*.bkp' | xargs rm
