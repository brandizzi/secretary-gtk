#ifndef _SECRETARY_GTK_GETTEXT_H
# define _SECRETARY_GTK_GETTEXT_H

#include <libintl.h>

#define _(s) (gettext(s))
#define gettext_noop(s) (s)
#define N_(s) (gettext_noop(s))

#endif /* _SECRETARY_GTK_GETTEXT_H */
