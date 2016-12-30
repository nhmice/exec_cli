/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: qiufeng <peven-na@qq.net>                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_exec_cli.h"


/* If you declare any globals in php_exec_cli.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(exec_cli)
*/

/* True global resources - no need for thread safety here */

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("exec_cli.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_exec_cli_globals, exec_cli_globals)
    STD_PHP_INI_ENTRY("exec_cli.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_exec_cli_globals, exec_cli_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_exec_cli_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(exec_cli)
{
    char *file,*command = NULL;
    char *params = "";
    zend_bool is_async = 1;
	size_t file_len, params_len;
    zend_file_handle file_handle;
	zend_op_array 	*op_array;
    php_stream      *stream;
    zend_string     *ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|sb", &file, &file_len, &params, &params_len, &is_async) == FAILURE)
    {
		return;
	}

    char path[MAXPATHLEN];

	if (!VCWD_REALPATH(file, path))
    {
		RETURN_FALSE;
	}

    command = emalloc(sizeof(char));

    if (is_async)
    {
        sprintf(command, "php %s \"%s\" %s", file, params, "> /dev/null 2>&1 &");
    }
    else
    {
        sprintf(command, "php %s \"%s\"", file, params);
    }

    // php_printf("%s", command);

    FILE *fp;

#ifdef PHP_WIN32
	fp = VCWD_POPEN(command, "rb");
#else
	fp = VCWD_POPEN(command, "r");
#endif
    efree(command);

	if (!fp)
    {
		php_error_docref(NULL, E_WARNING, "Unable to fork [%s]", command);
        RETURN_FALSE;
	}

	stream = php_stream_fopen_from_pipe(fp, "rb");
	ret = php_stream_copy_to_mem(stream, PHP_STREAM_COPY_ALL, 0);
	php_stream_close(stream);

	if (ret && ZSTR_LEN(ret) > 0)
    {
		RETVAL_STR(ret);
	}
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_exec_cli_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_exec_cli_init_globals(zend_exec_cli_globals *exec_cli_globals)
{
	exec_cli_globals->global_value = 0;
	exec_cli_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(exec_cli)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(exec_cli)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(exec_cli)
{
#if defined(COMPILE_DL_EXEC_CLI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(exec_cli)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(exec_cli)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "exec_cli support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ exec_cli_functions[]
 *
 * Every user visible function must have an entry in exec_cli_functions[].
 */
const zend_function_entry exec_cli_functions[] = {
	PHP_FE(exec_cli,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in exec_cli_functions[] */
};
/* }}} */

/* {{{ exec_cli_module_entry
 */
zend_module_entry exec_cli_module_entry = {
	STANDARD_MODULE_HEADER,
	"exec_cli",
	exec_cli_functions,
	NULL,
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
	PHP_EXEC_CLI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EXEC_CLI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(exec_cli)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
