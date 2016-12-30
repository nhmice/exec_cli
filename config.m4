dnl $Id$
dnl config.m4 for extension exec_cli

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(exec_cli, for exec_cli support,
dnl Make sure that the comment is aligned:
dnl [  --with-exec_cli             Include exec_cli support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(exec_cli, whether to enable exec_cli support,
 Make sure that the comment is aligned:
 [  --enable-exec_cli           Enable exec_cli support])

if test "$PHP_EXEC_CLI" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-exec_cli -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/exec_cli.h"  # you most likely want to change this
  dnl if test -r $PHP_EXEC_CLI/$SEARCH_FOR; then # path given as parameter
  dnl   EXEC_CLI_DIR=$PHP_EXEC_CLI
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for exec_cli files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       EXEC_CLI_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$EXEC_CLI_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the exec_cli distribution])
  dnl fi

  dnl # --with-exec_cli -> add include path
  dnl PHP_ADD_INCLUDE($EXEC_CLI_DIR/include)

  dnl # --with-exec_cli -> check for lib and symbol presence
  dnl LIBNAME=exec_cli # you may want to change this
  dnl LIBSYMBOL=exec_cli # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EXEC_CLI_DIR/$PHP_LIBDIR, EXEC_CLI_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_EXEC_CLILIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong exec_cli lib version or lib not found])
  dnl ],[
  dnl   -L$EXEC_CLI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(EXEC_CLI_SHARED_LIBADD)

  PHP_NEW_EXTENSION(exec_cli, exec_cli.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
