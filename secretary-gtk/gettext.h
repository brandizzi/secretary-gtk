#ifndef _SECRETARY_GTK_GETTEXT_H
# define _SECRETARY_GTK_GETTEXT_H

#import "config.h"

#include "../gettext.h"

#define _(s) (gettext(s))
#define N_(s) (gettext_noop(s))

#endif /* _SECRETARY_GTK_GETTEXT_H */
