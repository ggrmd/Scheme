
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

object make_nil( void ) {

    object t = make_object( SFS_NIL );

    t->this.special = t;

    return t;
}

object make_character(char caractere){
	object t=make_object(SFS_CHARACTER);
	t->this.character=caractere;
	return t;
}


object make_string(char * str ){
	object t=make_object(SFS_STRING);
	strcpy(t->this.string, str);
	return t;
}


object make_bool(void) {
	object t=make_object(SFS_BOOLEAN);
	t->this.special = t;
	return t;
}

object make_integer(int number) {
	object t=make_object(SFS_INTEGER);
	t->this.integer=number;
	return t;
}	

object make_pair(object car,object cdr){
	object t=make_object(SFS_PAIR);
	t->this.pair.car=car;
	t->this.pair.cdr=cdr;
	return t;
}

object make_symbol( string str )
{
    
    object t = make_object(SFS_SYMBOL);
    
    strcpy(t->this.symbol, str);
    
    return t;
}

object car(object o){
	if ( o->type !=SFS_PAIR)
	{
		ERROR_MSG("Not a pair !");
	}
	return o->this.pair.car;
}

object cdr(object o){
	if ( o->type !=SFS_PAIR)
	{
		ERROR_MSG("Not a pair !");
	}
	return o->this.pair.cdr;
}
	
object make_inf(void){
	object t=make_object(SFS_INTEGER);
	t->this.special=t;
	return t;
}

object make_new_env(void){
	return nil;
}

object init_top_level_env(void){
	object top=make_new_env();
	top=make_pair(

object get_variable_value_env(object env, object symbole){
	object p_env=env;
	if (symbole->type!=SFS_SYMBOL)
	{
		WARNING_MSG("Not a symbol !");
		return NULL;
	}
	while (cdr(p_env)!=nil)
	{
		if (strcmp(symbole,caar(p_env))==0)
		{
			return car(p_env);
		}
		p_env=cdr(p_env);
	}
	return NULL;
}
	
object get_variable_value_list_env(object list_env, object symbole){
	object p_list_env=list_env;
	while (cdr(p_list_env)!=nil)
	{
		if (get_variable_value_env(car(p_list_env))==NULL)
		{
			return get_variable_value_list_env(cdr(p_list_env));
		}
		else
		{
			return get_variable_value_env(car(p_list_env));
		}
	}
	return NULL;
}


object* ajouter_variable(object* env,object symbole,object valeur){
	if (symbole->type!=SFS_SYMBOL)
	{
		WARNING_MSG("Not a symbol !");
		return NULL;
	}
	if (get_variable_value_env(env,symbole)==NULL)
	{
		object variable=make_pair(symbole,valeur);
		env=make_pair(variable,env);
		return variable;
	}
	else
	{
		return variable;
	}
}	
	
object retourner_valeur_symbole_env(object symbole,object env){
	if (get_variable_value_env(symbole,env)==NULL)
	{
		return nil;
	}
	else
	{
		return cdr(get_variable_value_env(symbole,env));
	}
}

object retourner_valeur_symbole_list_env(object symbole,object list_env){
	if (cdr(list_env)==nil)
	{
		WARNING_MSG("Unbound variable !");
		return nil;
	}
	if (retourner_valeur_symbole_env(symbole,car(list_env))==nil)
	{
		return retourner_valeur_symbole_list_env(symbole,cdr(list_env));
	}
	else
	{
		return retourner_valeur_symbole_env(symbole,car(list_env));
	}
}
	

