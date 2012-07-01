PHP_ARG_ENABLE(nanoirc, Whether to enable the "nanoirc" extension,
	[ --enable-nanoirc 	Enable "nanoirc" extension support])

if test $PHP_NANOIRC != "no"; then
    PHP_REQUIRE_CXX()
    PHP_ADD_LIBRARY(stdc++, 1, NANOIRC_SHARED_LIBADD)
    PHP_SUBST(NANOIRC_SHARED_LIBADD)

    PHP_NEW_EXTENSION(nanoirc, php_nanoirc.cpp nanoirc.cpp, $ext_shared)

    PHP_ADD_BUILD_DIR([$ext_builddir/nanoircparser])

    CPPFLAGS=" -Wunused-variable -Wpointer-sign -Wimplicit-function-declaration"
    PHP_SUBST([CPPFLAGS])

    PHP_ADD_INCLUDE([$ext_srcdir/nanoircparser])
fi
