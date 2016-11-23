/**
 * @file primitive.h
 * @author Hugo Jallet
 * @date 16/11/16
 * @brief  Definition of functions for primitives
 */

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#include "environnement.h"

void init_primitive();

object handlerPrimPlus(object o);
object handlerPrimMinus(object o);
object handlerPrimMult(object o);






#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
