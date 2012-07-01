#ifndef PHP_NANOIRC_H

#define PHP_NANOIRC_H

#define PHP_NANOIRC_EXTNAME "nanoirc"
#define PHP_NANOIRC_EXTVER "0.1"

extern "C" {

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_interfaces.h"

}

#include "nanoircparser.hpp"

extern "C" {
/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry nanoirc_module_entry;
#define phpext_nanoirc_ptr &nanoirc_module_entry;
#define PHP_NANOIRC_OUTPUT_ARRAY        0

extern zend_class_entry *nanoirc_parser_class_entry;

typedef struct {
	zend_object zo;
	NanoIRCParser parser;
} php_nanoirc_parser_t;

}

#endif /* PHP_NANOIRC_H */
