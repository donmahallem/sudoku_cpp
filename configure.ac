AC_INIT([Sudoku cpp],
        [1.0.1])

# Provide various options to initialize the Autoconf and configure processes.
AC_PREREQ([2.59])
AC_CONFIG_SRCDIR([./README.md])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_FILES([Makefile test/Makefile benchmark/Makefile binSrc/Makefile])

dnl configure.ac text…

dnl to give an example of default-provided help text

AM_INIT_AUTOMAKE([-Wno-portability])

dnl Example of default-enabled feature
AC_ARG_ENABLE([clang],
    AS_HELP_STRING([--enable-clang], [Use clang instead of gcc]),
    use_clang=$enableval, use_clang=no)
AC_ARG_ENABLE(coverage,
    AS_HELP_STRING([--enable-coverage], [Generate Coverage]),
    flag_gen_coverage=$enableval, flag_gen_coverage=no)
#AM_CONDITIONAL(CPPCOVERAGEFLAGS, test x$flag_gen_coverage = xtrue)

if test "$flag_gen_coverage" = "yes" && test "$use_clang" = "no" ; then
    AC_SUBST(CPPCOVERAGEFLAGS,'-fprofile-arcs -ftest-coverage -pthread')
fi
if test "$flag_gen_coverage" = "yes" && test "$use_clang" = "yes" ; then
    AC_SUBST(CPPCOVERAGEFLAGS,'-fprofile-instr-generate -fcoverage-mapping -pthread')
fi

# Output the generated files. No further autoconf macros may be used.
AC_OUTPUT