
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

object make_character(char caractere) {
    object t=make_object(SFS_CHARACTER);
    t->this.character=caractere;
    return t;
}


object make_string(char * str ) {
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

object make_pair(object car,object cdr) {
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


object make_plus_inf(void) {
    object t=make_object(SFS_INTEGER_PINF);
    t->this.special=t;
    return t;
}

object make_minus_inf(void) 
{
    object t=make_object(SFS_INTEGER_MINF);
    t->this.special=t;
    return t;
}

object make_primitive(Primitive p)
{   object t = make_object(SFS_PRIMITIVE);
    t->this.primitive = p;
    return t;
}

object make_compound(object param,object body,object env)
{
	object t=make_object(SFS_COMPOUND);
	t->this.compound.parms=param;
	t->this.compound.body=body;
	t->this.compound.env=env;
	return t;
}
