/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2013 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors:                                                             |
   +----------------------------------------------------------------------+
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_demo.h"
#include "Zend/zend.h"
#include "Zend/zend_hash.h"

ZEND_BEGIN_ARG_INFO(arginfo_mydump, 0)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO();

zend_function_entry demo_functions[] =
{
    ZEND_FE(mydump, arginfo_mydump)
    {NULL,NULL,NULL} /* Marks the end of function entries */
};


/* {{{ demo_module_entry
 */
zend_module_entry demo_module_entry = {
    STANDARD_MODULE_HEADER,
    "demo",
    demo_functions, /* Function entries */
    NULL, /* Module init */
    NULL, /* Module shutdown */
    NULL, /* Request init */
    NULL, /* Request shutdown */
    NULL, /* Module information */
    "0.1", /* Replace with version number for your extension */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEXT
ZEND_GET_MODULE(demo)
#endif

PHP_FUNCTION(mydump)
{
    zval *value;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &value) == FAILURE)
    {
        RETURN_FALSE;
    }

    switch (Z_TYPE_P(value)) {
        case IS_NULL:
            php_printf("The variable passed is of type IS_NULL\n");
            break;

        case IS_LONG:
            php_printf("The variable passed is of type IS_LONG\n");
            php_printf("Computing %ld * 2: %ld\n", Z_LVAL_P(value), Z_LVAL_P(value) * 2 );
            break;

        case IS_DOUBLE:
            php_printf("The variable passed is of type IS_DOUBLE\n");
            php_printf("Computing %f * 0.5: %f\n", Z_DVAL_P(value), Z_DVAL_P(value) * 0.5 );
            break;

        case IS_BOOL:
            php_printf("The variable passed is of type IS_BOOL\n");
            break;

        case IS_ARRAY:
            php_printf("The variable passed is of type IS_ARRAY\n");
            php_printf("There is %ld direct elements in the array\n", zend_hash_num_elements(Z_ARRVAL_P(value)));
            break;

        case IS_OBJECT:
            php_printf("The variable passed is of type IS_OBJECT\n");
            break;

        case IS_STRING:
            php_printf("The variable passed is of type IS_STRING\n");
            php_printf("The content is \"%s\"\n", Z_STRVAL_P(value));
            php_printf("The content reversed is \"");
            char *p = Z_STRVAL_P(value) + Z_STRLEN_P(value);
            while (--p>=Z_STRVAL_P(value))
                php_printf("%c", *p);
            php_printf("\"\n");
            break;

        case IS_RESOURCE:
            php_printf("The variable passed is of type IS_RESOURCE\n");
            php_printf("The number of the resource is: %ld\n", Z_RESVAL_P(value));
            break;
    }
}
