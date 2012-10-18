AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
bin_PROGRAMS = secretary runtests
secretary_module_srcs =	secretary-gtk/widget.h widget.c \
	secretary-gtk/toolbar.h toolbar.c \
	secretary-gtk/panel.h panel.c \
	secretary-gtk/perspective-tree-view.h perspective-tree-view.c \
	perspective-tree-model.c secretary-gtk/perspective-tree-model.h \
    project-tree-model.c secretary-gtk/project-tree-model.h \
	secretary-gtk/task-tree-view.h task-tree-view.c \
	secretary-gtk/task-tree-model.h task-tree-model.c \
	secretary-gtk/utils.h utils.c \
	secretary-gtk/application.h application.c \
	secretary-gtk/new-task-dialog.h new-task-dialog.c \
	secretary-gtk/_internal/new-task-dialog.h \
	secretary-gtk/new-project-dialog.h new-project-dialog.c \
	secretary-gtk/_internal/new-project-dialog.h \
	secretary-gtk/date-entry.h date-entry.c \
	secretary-gtk/_internal/date-entry.h \
	secretary-gtk/date-cell-renderer.h date-cell-renderer.c \
	secretary-gtk/_internal/date-cell-renderer.h \
	gettext.h secretary-gtk/gettext.h
secretary_SOURCES = secretary.c \
	$(secretary_module_srcs)

secretary_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
secretary_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@
LDADD = $(LIBINTL)

runtests_SOURCES = test/runtests.c CuTest.c CuTest.h \
	$(secretary_module_srcs) \
	test/test-perspective-tree-model.c \
	test/test-secretary-gtk/perspective-tree-model.h \
	test/test-task-tree-model.c \
	test/test-secretary-gtk/task-tree-model.h \
	test/test-project-tree-model.c \
	test/test-secretary-gtk/task-tree-view.h \
	test/test-task-tree-view.c \
	test/test-secretary-gtk/project-tree-model.h \
	test/test-application.c test/test-secretary-gtk/application.h \
	test/test-new-task-dialog.c test/test-secretary-gtk/new-task-dialog.h \
	test/test-new-project-dialog.c test/test-secretary-gtk/new-project-dialog.h \
	test/test-utils.c test/test-secretary-gtk/test-utils.h \
	test/test-date-entry.c test/test-secretary-gtk/date-entry.h\
	test/test-date-cell-renderer.c test/test-secretary-gtk/date-cell-renderer.h
runtests_CFLAGS = @GTK_CFLAGS@ @SECRETARY_CFLAGS@
runtests_LDADD = @GTK_LIBS@ @SECRETARY_LIBS@

SUBDIRS = po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = config.rpath

TESTS = runtests

test: check

clean-local:
	-find -name '*~' -o -name '*.bkp' -o -name '*.orig' | xargs rm
