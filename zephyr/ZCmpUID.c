/* This file is part of the Project Athena Zephyr Notification System.
 * It contains source for the ZCompareUID function.
 *
 *	Created by:	Robert French
 *
 *	Copyright (c) 1987 by the Massachusetts Institute of Technology.
 *	For copying and distribution information, see the file
 *	"mit-copyright.h".
 */

#include "zephyrlib_internal.h"

int
ZCompareUID(ZUnique_Id_t *uid1, ZUnique_Id_t *uid2)
{
    return (!memcmp((char *)uid1, (char *)uid2, sizeof (*uid1)));
}
