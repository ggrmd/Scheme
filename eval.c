
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "list.h"
#include "environnement.h"


object sfs_eval( object input )
{ 
    /* OBJET AUTOEVALUANT */
    if ( input-> type != SFS_PAIR && input-> type != SFS_SYMBOL)
    {   
        return input;
    }
    if (input->type == SFS_PRIMITIVE)
    {
	return sfs_eval_primitive(input);
    }

    /* SYMBOLE */
    if (input->type == SFS_SYMBOL)
    {
        if(get_variable_value_list_env(list_env, input) == NULL)
        {
            return input;
        }


        return retourner_valeur_symbole_env(input,envt_courant(list_env));
	

    }

    /* LISTE */
    if(input->type == SFS_PAIR)
    {
	return sfs_eval_pair(input);
    }
} 
  


object sfs_eval_pair(object input)
{
	object proc;
/* quote */
	if (car(input)->type==SFS_PAIR)
	{
		proc=sfs_eval_pair(car(input));
		if (proc->type==SFS_COMPOUND)
		{
			return sfs_eval_proc(proc,cdr(input));
		}
		else
		{
			WARNING_MSG("Not a procedure!");
			return NULL;
		}
	}
        if ( isquote(car(input)) == 0 )
        {
            if ( cddr(input) != nil)
            {
               WARNING_MSG("Quote takes 1 argument !");
            }
            return cadr(input);
        }
        /* define */
        if ( isdefine(car(input)) == 0 )
        {
            if (cdr(input)->type == SFS_NIL || cddr(input)->type==SFS_NIL || cdddr(input) != nil)
            {
               WARNING_MSG("define takes 2 arguments!");
            }
	    
	    if (is_reserved(cadr(input)->this.symbol)==1)
            {
            	WARNING_MSG("Symbol used is reserved to scheme");
            	return NULL;
            }


            object symbole = cadr(input);
            object val = sfs_eval(caddr(input));
	    object binding=make_pair(symbole,val);
            ajouter_binding_list_env(binding,&list_env);
            return symbole ;
        }

        /* set! */
        if ( is_set(car(input)) == 0 )
        {
            if (cdr(input)->type == SFS_NIL || cddr(input)->type==SFS_NIL || cdddr(input) != nil)
            {
                WARNING_MSG("Set takes 2 arguments !");
		return NULL;
            }

            if (get_variable_value_list_env(list_env, cadr(input)) == NULL)
            {
                WARNING_MSG (" Undefined variable !");
		return nil;
            }

	    if (is_reserved(cadr(input)->this.symbol)==1)
            {
            	WARNING_MSG("Symbol used is reserved to scheme");
            	return NULL;
            }

            object symbole = cadr(input);
            object new_val = caddr(input);
	    object couple_actuel = get_variable_value_list_env(list_env, cadr(input));

            object old_val = cdr(couple_actuel);
            memcpy(old_val,cdr(couple_actuel),sizeof(*old_val));
            
            memcpy(cdr(couple_actuel),new_val,sizeof(*new_val));
           
            return symbole;

        }

        /* and */
        if ( is_and(car(input)) == 0 )
        {   input = cdr(input) ;
            while ( input != nil)
            {   if ( input->type != SFS_PAIR)
                {
                    return NULL;
                    WARNING_MSG("Not a pair !");
                }
                if ( sfs_eval(car(input))== faux)
                {
                    return faux;
                }
                input = cdr(input);
            }

            return vrai;
        }

        /* or */
        if ( is_or(car(input)) == 0 )
        {   input = cdr(input) ;
            while ( input != nil)
            {   if ( input->type != SFS_PAIR)
                {
                    return NULL;
                    WARNING_MSG("Not a pair !");
                }
                if ( sfs_eval(car(input))!= faux)
                {
                    return vrai;
                }
                input = cdr(input);
            }

            return faux;

        }

        /* if */
        if ( is_if(car(input)) == 0 )
        {   if ( sfs_eval(cadr(input)) != faux)
            {
                return sfs_eval(caddr(input));
            }
            else
            {
                input = car(cdddr(input));
                if (input != nil)
                {
                    return sfs_eval(input);
                }
                else
                {
                    return faux;
                }
            }

        }

	if ( is_lambda(car(input)) == 0 )
	{	
		return sfs_eval_lambda(input);
	}


	if (car(input)->type == SFS_SYMBOL)
    	{
		object value;
		if (get_variable_value_list_env(list_env , car(input))==NULL)
		{
			WARNING_MSG("Unknown symbol");
        		return NULL;
   		}
		else
		{
			value =retourner_valeur_symbole_env(car(input),car(list_env));
        	}
        	switch(value->type)
    		{
        		case SFS_PRIMITIVE :
        		return sfs_eval_primitive(input);
        		break;
 
        		/*case SFS_COMPOUND:
        		return sfs_eval_proc(value,cdr(input));            
        		break;*/
 
        		default:
                	WARNING_MSG("Syntax error");
                	return NULL;
           
   		}
        }
    
 
 
    WARNING_MSG("Syntax error");
    return NULL;
 

}


object sfs_eval_primitive(object input)
{
    object binding = get_variable_value_list_env(list_env,car(input));
    object o_prim = cdr(binding);
    if (binding == NULL || o_prim->type != SFS_PRIMITIVE )
    {
        WARNING_MSG("Unknown primitive");
        return NULL;
    }
    else
    {
        return o_prim->this.primitive(cdr(input));
    }
        
        
}





/* @fn : int isquote (object o)
   @brief : verifie que o est "quote" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */
int isquote (object o)
{  /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if ( o->type == SFS_NIL )
    {
        ERROR_MSG("Nil !");
    }
    if (strcmp(o->this.symbol,"quote") == 0)
    {
        return 0;
    }

    return 1;

}

/* @fn : int isdefine (object o)
   @brief : verifie que o est "define" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */

int isdefine (object o)
{      
   /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"define") == 0)
    {
        return 0;
    }

    return 1;

}

/* @fn : int is_set (object o)
   @brief : verifie que o est "set" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */

int is_set (object o)
{  /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"set!") == 0)
    {
        return 0;
    }

    return 1;
}

/* @fn : int is_if (object o)
   @brief : verifie que o est "if" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */

int is_if (object o)
{  /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"if") == 0)
    {
        return 0;
    }
    return 1;
}

/* @fn : int is_and (object o)
   @brief : verifie que o est "and" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */

int is_and (object o)
{  /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"and") == 0)
    {
        return 0;
    }
    return 1;
}

/* @fn : int is_or (object o)
   @brief : verifie que o est "or" et retourne 0 si c'est le cas, 1 sinon.
   @pre: o doit être un symbole  */

int is_or (object o)
{

 /*   if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"or") == 0)
    {
        return 0;
    }
    return 1;
}


/*
 @fn int is_reserved(string word)
 
 @brief renvoie 1 si word est un mot reservé du scheme(forme, primitives,..), 0 sinon.

A completer dans l'increment 3
 */


int is_reserved(string word)
{
    if (strcmp(word,"define")==0)
        return 1;
    if (strcmp(word,"if")==0)
        return 1;
    if (strcmp(word,"and")==0)
        return 1;
    if (strcmp(word,"or")==0)
        return 1;
    if (strcmp(word,"car")==0)
        return 1;
    if (strcmp(word,"cdr")==0)
        return 1;
    if (strcmp(word,"+")==0)
        return 1;
    if (strcmp(word,"-")==0)
        return 1;
    if (strcmp(word,"*")==0)
        return 1;
    if (strcmp(word,"/")==0)
        return 1;
    else
        return 0;
}


int is_lambda (object o)
{  /* if ( o->type != SFS_SYMBOL )
    {
        WARNING_MSG("Not a symbol !");
    }*/
    if (strcmp(o->this.symbol,"lambda") == 0)
    {
        return 0;
    }
    return 1;
}

object sfs_eval_lambda(object input){
	if (cdr(input)==nil)
	{
		WARNING_MSG("Compound syntax error : right syntax is (lambda (parm) (body))");
		return NULL;
	}
	if (car(cdr(input))->type!=SFS_PAIR)
	{
		WARNING_MSG("Compound syntax error : parameters must be in a list");
		return NULL;
	}
	if (cdr(cdr(input))==nil)
	{
		WARNING_MSG("Compound syntax error : right syntax is (lambda (parm) (body))");
		return NULL;
	}
	object param=car(cdr(input));
	object body=car(cdr(cdr(input)));
	object compound=make_compound(param,body,list_env);
	return compound;
}

object sfs_eval_proc(object proc,object values)
{
	object env_courant=list_env;
	object retour;
	object param=proc->this.compound.parms;
	object body=proc->this.compound.body;
	object binding;
	if (proc->type!=SFS_COMPOUND)
	{
		WARNING_MSG("Not a compound!");
		return NULL;	
	}
	list_env=proc->this.compound.env;
	object env_temp=make_pair(list_env,nil);
	list_env=env_temp;

	while (param!=nil && values!=nil)
	{
		binding=make_pair(car(param),make_pair(car(values),nil));
		param=cdr(param);
		values=cdr(values);
		list_env->this.pair.cdr = make_pair(list_env->this.pair.cdr,binding);
	}
	
	retour=sfs_eval(body);
	list_env=env_courant;
	return retour;
}
























