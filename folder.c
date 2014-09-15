/*
 * Copyright (C) 2013 Bryan Christ <bryan.christ@mediafire.com>
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


#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "private.h"

#ifndef folder_t
#define folder_t    _folder_t
#endif

folder_t*
folder_alloc(void)
{
    folder_t    *folder;

    folder = (folder_t*)calloc(1,sizeof(folder_t));

    return folder;
}

void
folder_free(folder_t *folder)
{
    if(folder == NULL) return;

    free(folder);

    return;
}

int
folder_set_key(folder_t *folder,const char *key)
{
    if(folder == NULL) return -1;
    if(key == NULL) return -1;

    if(strlen(key) != 13) return -1;

    memset(folder->folderkey,0,sizeof(folder->folderkey));
    strncpy(folder->folderkey,key,sizeof(folder->folderkey) - 1);

    return 0;
}

const char*
folder_get_key(folder_t *folder)
{
    if(folder == NULL) return NULL;

    return folder->folderkey;
}

int
folder_set_parent(folder_t *folder,const char *parent_key)
{
    if(folder == NULL) return -1;
    if(parent_key == NULL) return -1;

    if(strlen(parent_key) != 13)
    {
        if(strcmp(parent_key,"myfiles") != 0) return -1;
    }

    memset(folder->parent,0,sizeof(folder->parent));
    strncpy(folder->parent,parent_key,sizeof(folder->parent) -1);

    return 0;
}

const char*
folder_get_parent(folder_t *folder)
{
    if(folder == NULL) return NULL;

    return folder->parent;
}

int
folder_set_name(folder_t *folder,const char *name)
{
    if(folder == NULL) return -1;
    if(name == NULL) return -1;

    if(strlen(name) > 40) return -1;

    memset(folder->name,0,sizeof(folder->name));
    strncpy(folder->name,name,sizeof(folder->name) - 1);

    return 0;
}

const char*
folder_get_name(folder_t *folder)
{
    if(folder == NULL) return NULL;

    return folder->name;
}

