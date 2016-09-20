
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
    if (o->type == SFS_INTEGER)
    {
    	printf("%d",o->this.integer);
    }
    if (o->type == SFS_CHARACTER)
    {	
    	printf("%c",o->this.character);
    }
    if (o->type == SFS_STRING)
    {
    	printf("%s",o->this.string);
    }
	
    return;
}

void sfs_print_pair( object o ) {

    return;
}

void sfs_print( object o ) {

    if ( SFS_PAIR == o->type ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }

}
