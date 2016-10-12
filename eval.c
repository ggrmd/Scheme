
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

object sfs_eval( object input ) {

    if (input->type!=SFS_PAIR && input->type!=SFS_SYMBOL)
    {
	return input;
    }

   /* if (input->type==SFS_PAIR)
    {
	if (isquote(car(input))==0)
	{
		return cdr(input);
	}
    */
    

    return input;
}

int isquote( object o){
	if (o->type==SFS_SYMBOL)
	{
		if (strcmp(o->this.symbol,"quote")==0)
		{
			return 0;
		}
	}
	
	return 1;
}
