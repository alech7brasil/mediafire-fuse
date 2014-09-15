#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strings.h"
#include "mfshell.h"
#include "private.h"
#include "command.h"

int
mfshell_cmd_chdir(mfshell_t *mfshell,const char *folderkey)
{
    folder_t    *folder_new;
    const char  *folder_curr;
    const char  *folder_parent;
    int         retval;

    if(mfshell == NULL) return -1;
    if(folderkey == NULL) return -1;

    // change to root
    if(strcmp(folderkey,"/") == 0) folderkey = "myfiles";

    // user wants to navigate up a level
    if(strcmp(folderkey,"..") == 0)
    {
        // do several sanity checks to see if we're already at the root
        folder_curr = folder_get_key(mfshell->folder_curr);

        if(folder_curr == NULL) return 0;
        if(strcmp(folder_curr,"myfiles") == 0) return 0;

        folder_parent = folder_get_parent(mfshell->folder_curr);

        if(folder_parent == NULL) return 0;

        // it's pretty sure that we're not at the root
        folderkey = folder_parent;
    }

    // check the lenght of the key
    if(strlen(folderkey) != 13)
    {
        // as a folder moniker, "myfiles" is an exception
        if(strcmp(folderkey,"myfiles") != 0) return -1;
    }

    // create a new folder object to store the results
    folder_new = folder_alloc();

    // navigate to root is a special case
    if(strcmp(folderkey,"myfiles") == 0)
    {
        folder_set_key(folder_new,"myfiles");
        retval = 0;
    }
    else
    {
        retval = mfshell->folder_get_info(mfshell,
            folder_new,(char*)folderkey);
        mfshell->update_secret_key(mfshell);
    }

    if(retval == 0)
    {
        if(mfshell->folder_curr != NULL)
        {
            folder_free(mfshell->folder_curr);
            mfshell->folder_curr = NULL;
        }

        mfshell->folder_curr = folder_new;
    }
    else
    {
        folder_free(folder_new);
    }

    return retval;
}


