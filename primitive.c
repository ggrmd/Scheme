/**
 * @file primitive.c
 * @author Hugo Jallet
 * @date 16/11/16
 * @brief  Fonctions réalisant les primitives
 */

#include "primitive.h"


void init_primitive()
{
  object add=make_pair(make_symbol("+"),make_primitive(handlerPrimPlus));
  add_binding_to_list_env(add, &list_env);

  object diff=make_pair(make_symbol("-"),make_primitive(handlerPrimMinus));
  add_binding_to_list_env(diff, &list_env);

  object prod=make_pair(make_symbol("*"),make_primitive(handlerPrimMult));
  add_binding_to_list_env(prod, &list_env);
/*
  object div=make_pair(make_symbol("/"),make_primitive(handlerPrimQuot));
  add_binding_to_list_env(div, &list_env);

  object sup = make_pair(make_symbol(">"),make_primitive(handlerPrimSup));
  add_binding_to_list_env(sup,&list_env);

  object inf = make_pair(make_symbol("<"),make_primitive(handlerPrimInf));
  add_binding_to_list_env(inf,&list_env);

  object equal =make_pair(make_symbol("="),make_primitive(handlerPrimEq));
  add_binding_to_list_env(equal,&list_env);

  object rem =make_pair(make_symbol("remainder"),make_primitive(handlerPrimRemain));
  add_binding_to_list_env(rem,&list_env);
*/









}


object handlerPrimPlus(object o)
{
	object elt;
	int somme=0;
	if (o==nil)
	{
		return make_integer(somme);
	}
	if (o->type!=SFS_PAIR)
	{
		WARNING_MSG("Erreur de syntaxe addition");
		return NULL;
	}
	
	while (o!=nil)
	{
		elt=sfs_eval(o->this.pair.car);
		if (elt->type!=SFS_INTEGER || elt==NULL)
		{
			WARNING_MSG("Erreur addition : les éléments ne sont pas tous entiers");
			return NULL;
		}
		somme+=elt->this.integer;
		o=o->this.pair.cdr;
	}
	return make_integer(somme);

}

object handlerPrimMinus (object o)

{
	object elt;
	int diff=0;
	if (o==nil)
	{
		return make_integer(diff);
	}
	if (o->type!=SFS_PAIR)
	{
		WARNING_MSG("Erreur de syntaxe soustraction");
		return NULL;
	}
	if(o->this.pair.cdr->type == SFS_PAIR && o->this.pair.cdr->this.pair.car->type == SFS_INTEGER)
	{
		elt=sfs_eval(o->this.pair.car);
		diff+=elt->this.integer;
		o=o->this.pair.cdr;
	}
		
	while (o!=nil)
	{
		elt=sfs_eval(o->this.pair.car);
		if (elt->type!=SFS_INTEGER || elt==NULL)
		{
			WARNING_MSG("Erreur soustraction : les éléments ne sont pas tous entiers");
			return NULL;
		}
		diff-=elt->this.integer;
		o=o->this.pair.cdr;
	}
	return make_integer(diff);

}

object handlerPrimMult(object o)
{
	object elt;
	int prod=1;
	if (o==nil)
	{
		return make_integer(prod);
	}
	if (o->type!=SFS_PAIR)
	{
		WARNING_MSG("Erreur de syntaxe produit");
		return NULL;
	}
	
	while (o!=nil)
	{
		elt=sfs_eval(o->this.pair.car);
		if (elt->type!=SFS_INTEGER || elt==NULL)
		{
			WARNING_MSG("Erreur produit : les éléments ne sont pas tous entiers");
			return NULL;
		}
		prod*=elt->this.integer;
		o=o->this.pair.cdr;
	}
	return make_integer(prod);

}

