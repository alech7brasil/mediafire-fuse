/*
 * Copyright (C) 2013 Bryan Christ <bryan.christ@mediafire.com>
 *               2014 Johannes Schauer <j.schauer@email.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */


#include <stdio.h>
#include <string.h>

#include "../mfshell.h"
#include "../commands.h"
#include "../../mfapi/apicalls.h"

int
mfshell_cmd_file(mfshell_t *mfshell, int argc, char **argv)
{
    file_t      *file;
    int         len;
    int         retval;
    const char *quickkey;
    const char *name;
    const char *hash;

    if(mfshell == NULL) return -1;

    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }

    quickkey = argv[1];
    if(quickkey == NULL) return -1;

    len = strlen(quickkey);

    if(len != 11 && len != 15) return -1;

    file = file_alloc();

    retval = mfconn_api_file_get_info(mfshell->mfconn,file,(char*)quickkey);
    mfconn_update_secret_key(mfshell->mfconn);

    quickkey = file_get_key(file);
    name = file_get_name(file);
    hash = file_get_hash(file);

    if(name != NULL && name[0] != '\0')
        printf("   %-15.15s   %s\n\r",
        "filename:", name);

    if(quickkey != NULL && quickkey[0] != '\0')
        printf("   %-15.15s   %s\n\r",
        "quickkey:", quickkey);

    if(hash != NULL && hash[0] != '\0')
        printf("   %-15.15s   %s\n\r",
        "hash:", hash);

    file_free(file);

    return 0;
}
