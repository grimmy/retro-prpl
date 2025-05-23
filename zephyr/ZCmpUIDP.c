/* This file is part of the Project Athena Zephyr Notification System.
 * It contains source for the ZCompareUIDPred function.
 *
 *	Created by:	Robert French
 *
 *	Copyright (c) 1987 by the Massachusetts Institute of Technology.
 *	For copying and distribution information, see the file
 *	"mit-copyright.h".
 */

#include "zephyrlib_internal.h"

int
ZCompareUIDPred(ZNotice_t *notice, void *uid)
{
    return (ZCompareUID(&notice->z_uid, (ZUnique_Id_t *) uid));
}

int
ZCompareMultiUIDPred(ZNotice_t *notice, void *uid)
{
    return (ZCompareUID(&notice->z_multiuid, (ZUnique_Id_t *) uid));
}
