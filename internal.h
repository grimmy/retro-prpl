/**
 * @file internal.h Internal definitions and includes
 * @ingroup core
 */

/* purple
 *
 * Purple is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */
#ifndef _PURPLE_INTERNAL_H_
#define _PURPLE_INTERNAL_H_

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* for SIOCGIFCONF  in SKYOS */
#ifdef SKYOS
#include <net/sockios.h>
#endif

#ifdef HAVE_ENDIAN_H
# include <endian.h>
#endif

#define MSG_LEN 2048
/* The above should normally be the same as BUF_LEN,
 * but just so we're explicitly asking for the max message
 * length. */
#define BUF_LEN MSG_LEN
#define BUF_LONG BUF_LEN * 2

#include <sys/stat.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/time.h>
#endif
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HAVE_ICONV
#include <iconv.h>
#endif

#ifdef HAVE_LANGINFO_CODESET
#include <langinfo.h>
#endif

#ifdef PURPLE_PLUGINS
# ifdef HAVE_DLFCN_H
#  include <dlfcn.h>
# endif
#endif

#ifndef _WIN32
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/un.h>
# include <sys/utsname.h>
# include <netdb.h>
# include <signal.h>
# include <unistd.h>
#endif

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 255
#endif

#include <glib.h>

#include "glibcompat.h"

#include <glib/gstdio.h>

#ifdef _WIN32
#include "win32dep.h"
#endif

#ifdef HAVE_CONFIG_H
#if SIZEOF_TIME_T == 4
#	define PURPLE_TIME_T_MODIFIER "lu"
#elif SIZEOF_TIME_T == 8
#	define PURPLE_TIME_T_MODIFIER "zu"
#else
#error Unknown size of time_t
#endif
#endif

#include <glib-object.h>

#ifdef __COVERITY__

/* avoid TAINTED_SCALAR warning */
#undef g_utf8_next_char
#define g_utf8_next_char(p) (char *)((p) + 1)

#endif

/* Safer ways to work with static buffers. When using non-static
 * buffers, either use g_strdup_* functions (preferred) or use
 * g_strlcpy/g_strlcpy directly. */
#define purple_strlcpy(dest, src) g_strlcpy(dest, src, sizeof(dest))
#define purple_strlcat(dest, src) g_strlcat(dest, src, sizeof(dest))

typedef union
{
	struct sockaddr sa;
	struct sockaddr_in in;
	struct sockaddr_in6 in6;
	struct sockaddr_storage storage;
} common_sockaddr_t;

#define PURPLE_WEBSITE "https://pidgin.im/"
#define PURPLE_DEVEL_WEBSITE "https://pidgin.im/development/"


/* INTERNAL FUNCTIONS */

#include "account.h"
#include "connection.h"

/* This is for the accounts code to notify the buddy icon code that
 * it's done loading.  We may want to replace this with a signal. */
void
_purple_buddy_icons_account_loaded_cb(void);

/* This is for the buddy list to notify the buddy icon code that
 * it's done loading.  We may want to replace this with a signal. */
void
_purple_buddy_icons_blist_loaded_cb(void);

/* This is for the purple_core_migrate() code to tell the buddy
 * icon subsystem about the old icons directory so it can
 * migrate any icons in use. */
void
_purple_buddy_icon_set_old_icons_dir(const char *dirname);

/**
 * Creates a connection to the specified account and either connects
 * or attempts to register a new account.  If you are logging in,
 * the connection uses the current active status for this account.
 * So if you want to sign on as "away," for example, you need to
 * have called purple_account_set_status(account, "away").
 * (And this will call purple_account_connect() automatically).
 *
 * @note This function should only be called by purple_account_connect()
 *       in account.c.  If you're trying to sign on an account, use that
 *       function instead.
 *
 * @param account  The account the connection should be connecting to.
 * @param regist   Whether we are registering a new account or just
 *                 trying to do a normal signon.
 * @param password The password to use.
 */
void _purple_connection_new(PurpleAccount *account, gboolean regist,
                            const char *password);
/**
 * Tries to unregister the account on the server. If the account is not
 * connected, also creates a new connection.
 *
 * @note This function should only be called by purple_account_unregister()
 *       in account.c.
 *
 * @param account  The account to unregister
 * @param password The password to use.
 * @param cb Optional callback to be called when unregistration is complete
 * @param user_data user data to pass to the callback
 */
void _purple_connection_new_unregister(PurpleAccount *account, const char *password,
                                       PurpleAccountUnregistrationCb cb, void *user_data);
/**
 * Disconnects and destroys a PurpleConnection.
 *
 * @note This function should only be called by purple_account_disconnect()
 *        in account.c.  If you're trying to sign off an account, use that
 *        function instead.
 *
 * @param gc The purple connection to destroy.
 */
void _purple_connection_destroy(PurpleConnection *gc);

/**
 * Sets most commonly used socket flags: O_NONBLOCK and FD_CLOEXEC.
 *
 * @param fd The file descriptor for the socket.
 *
 * @return TRUE if succeeded, FALSE otherwise.
 */
gboolean
_purple_network_set_common_socket_flags(int fd);

#endif /* _PURPLE_INTERNAL_H_ */
