/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2011 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Shuhei Tanuma <chobieee@gmail.com>                          |
   +----------------------------------------------------------------------+
 */

#include "php_nanoirc.hpp"
#include <iostream>

extern "C" {

zend_class_entry *nanoirc_parser_class_entry;

void php_nanoirc_init(TSRMLS_D);
static void php_nanoirc_parser_free_storage(php_nanoirc_parser_t *obj TSRMLS_DC);


static zend_object_value php_nanoric_parser_new(zend_class_entry *ce TSRMLS_DC) /* {{{ */
{
	zend_object_value retval;
	php_nanoirc_parser_t *object;

	object = (php_nanoirc_parser_t *)ecalloc(1, sizeof(*object));
	zend_object_std_init(&object->zo, ce TSRMLS_CC);
	object_properties_init(&object->zo, ce);

	retval.handle = zend_objects_store_put(object,
		(zend_objects_store_dtor_t)zend_objects_destroy_object,
		(zend_objects_free_object_storage_t) php_nanoirc_parser_free_storage ,
	NULL TSRMLS_CC);

	retval.handlers = zend_get_std_object_handlers();
	return retval;
} /* }}} */

static void php_nanoirc_parser_free_storage(php_nanoirc_parser_t *obj TSRMLS_DC)
{
	zend_object_std_dtor(&obj->zo TSRMLS_CC);
	efree(obj);
}

PHP_METHOD(nanoirc_parser, parse)
{
	zval *result, *params;
	zval *obj = getThis();
	php_nanoirc_parser_t *container;
	NanoIRCParser::Message msg;
	std::vector<std::string>::iterator itr;
	char *str;
	int str_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s",&str, &str_len) == FAILURE) {
		return;
	}
	
	container = (php_nanoirc_parser_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
	container->parser.parse(str, msg);
	
	MAKE_STD_ZVAL(result);
	array_init(result);
	MAKE_STD_ZVAL(params);
	array_init(params);
	
	add_assoc_string_ex(result, "prefix", sizeof("prefix"), (char *)msg.prefix.c_str(), 1);
	add_assoc_string_ex(result, "command", sizeof("command"), (char *)msg.command.c_str() , 1);

	for (itr = msg.params.begin(); itr < msg.params.end(); ++itr) {
		add_next_index_string(params, (char *)&*itr->c_str(), 1);
	}

	add_assoc_zval_ex(result, "params", sizeof("params"), params);
	RETURN_ZVAL(result, 0, 1);
}

static zend_function_entry php_nanoirc_parser_methods[] = {
	PHP_ME(nanoirc_parser, parse, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

void php_nanoirc_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_CLASS_ENTRY(ce, "NanoIRCParser", php_nanoirc_parser_methods);
	nanoirc_parser_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	nanoirc_parser_class_entry->create_object = php_nanoric_parser_new;

}

}