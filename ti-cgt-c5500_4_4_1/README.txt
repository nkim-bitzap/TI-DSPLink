TMS320C55x Code Generation Tools Release Version 4.4.1
Release Notes
March 2012

================================================================================
Table of Contents
================================================================================
 4.4.0-01. Overview
 4.4.0-02. Support for Circular Addressing in Large/Huge Memory Models
 4.4.0-03. Compiler Intrinsic for Circular Increment (_circ_incr)
 4.4.0-04. GCC Language Extensions Available in C++
 4.4.0-05. GCC Language Extensions Included in Relaxed ANSI Mode
 4.4.0-06. Improved Robustness in Processing of GCC Extensions
 4.4.0-07. Additional GCC Extensions Supported
 4.4.0-08. New Devices Recognized by -v Option (5525, 5532, 5533, 5534, 5535)
 4.4.0-09. Mixing Declarations and Code
 4.4.0-10. stdbool.h
 4.4.0-11. MISRA-C:2004 Support
 4.4.0-12. Applying Options to Individual Functions
 4.4.0-13. New Pragmas: SET_DATA_SECTION and SET_CODE_SECTION
 4.4.0-14. Fewer pre-built libraries, automatic library building

 4.4.0-15. Silicon Bug Detection in the Assembler
 4.4.0-16. Silicon Bug Workarounds in the Compiler
 4.4.0-17. Validation Information

 Annex A.  Support for C55x+ Devices (see separate file readmeplus.txt)


================================================================================
 4.4.0-01. Overview
================================================================================
This release is an upgrade release of the C55x Code Generation Tools including
support for new features as well as fixes for reported defects.

The list of fixed bugs and known defects for this release is in the file
DefectHistory.txt.

For development tools support please see the Texas Instruments
engineer-to-engineer (E2E) Community and the Development Tools Forum at:
http://e2e.ti.com/support/development_tools/default.aspx


================================================================================
 4.4.0-02. Support for Circular Addressing in Large/Huge Memory Models
================================================================================
The support for allowing C code to utilize the circular addressing hardware by
using the modulus operation (see Section 2.30-04 in these Release Notes),
previously available only in Small Memory Model, is now also available in Large
and Huge Memory Models.


================================================================================
 4.4.0-03. Compiler Intrinsic for Circular Increment (_circ_incr)
================================================================================
The following intrinsic is available for performing a circular (modular)
increment:

   int _circ_incr(int index, int incr, unsigned int size)

The returns the circular increment of 'index+incr' relative to 'size' when
these preconditions are met: 0 <= index < size and incr <= size.


================================================================================
 4.4.0-04. GCC Language Extensions Available in C++
================================================================================
Any GCC extensions supported in the TI compiler and which are supported in the
GNU C++ compiler (g++) are also available in the TI compiler for C++ source.


================================================================================
 4.4.0-05. GCC Language Extensions Included in Relaxed ANSI Mode
================================================================================
When relaxed ANSI mode is selected using the --relaxed_ansi (or -pr) option,
all supported GCC language extensions are available.  (Previously the --gcc
option had to be used to enable the GCC extensions.)


================================================================================
 4.4.0-06. Improved Robustness in Processing of GCC Extensions
================================================================================
The GCC features usually referred to as Labels as Values, Hex Floats, Extended
Asm and Constraints are rejected by the compiler.  Previously the constructs
associated with these features were accepted but the feature was not
implemented.

Similarly unsupported function, variable and type attributes are rejected with
a warning rather than being quietly accepted and ignored.


================================================================================
 4.4.0-07. Additional GCC Extensions Supported
================================================================================
The GNU Compiler Collection C compiler (gcc) defines a number of language
features not found in the ISO standard for the C language.  Many of the GCC
extensions are and have been available (since version 4.0.0) in the TI compiler
when the --gcc option is used.  With this release, support for the following
features has been added:

 o Designated initializers for unions.  (Designated initializers for arrays and
   structs have been available previously.)

 o Pointer arithmetic on void* and function pointers.

 o The function attributes always_inline, const, constructor, format,
   format_arg, malloc, noinline, noreturn, pure, used, and warn_unused_result.

   The format attribute is applied to the declarations of printf, fprintf,
   sprintf, snprintf, vprintf, vfprintf, vsprintf, vsnprintf, scanf, fscanf and
   sscanf in stdio.h.  This means that when GCC extensions are available the
   data arguments of these functions will be type checked against the format
   specifiers in the format string argument and warnings issued when there is a
   mismatch.  These warnings can be suppressed in the usual ways if they are
   not desired.

 o The malloc attribute is applied to the declarations of malloc, calloc,
   realloc and memalign in stdlib.h

 o The variable attributes aligned, mode, transparent_union, and used.

 o The type attributes aligned, deprecated and transparent_union.

 o The function __builtin_constant_p.  (Previously partially available.)

 o The function __builtin_frame_address.  This function returns zero for all
   arguments except a constant zero.

   The functions __builtin_abs, __builtin_fabs, __builtin_fabsf,
   __builtin_labs, __builtin_llabs, and __builtin_memcpy.

The definition and examples of these language constructs can be found online at
http://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/C-Extensions.html#C-Extensions


================================================================================
 4.4.0-08. New Devices Recognized by -v Option (5525, 5532, 5533, 5534, 5535)
================================================================================
The 5525, 5532, 5533, 5534, and 5535 devices are now recognized by the -v
option.  Remember that -vlist may be used to display of the list of supported
device:rev values.


================================================================================
 4.4.0-09. Mixing Declarations and Code
================================================================================
Object declarations in C are now allowed anywhere within a scope.  This can be
disabled (requiring declarations to be at the beginning of a scope) by using
the --strict_ansi option.


================================================================================
 4.4.0-10. stdbool.h
================================================================================
The stdbool.h header file is now supported for supporting the bool type in C.


================================================================================
 4.4.0-11. MISRA-C:2004 Support
================================================================================
You can alter your code to work with the MISRA-C:2004 rules. The following
enable/disable the rules:

o The --check_misra option enables checking of the specified MISRA-C:2004
  rules.

o The CHECK_MISRA pragma enables/disables MISRA-C:2004 rules at the source
  level. This pragma is equivalent to using the --check_misra option.
  
  RESET_MISRA pragma resets the specified MISRA-C:2004 rules to the state they
  were before any CHECK_MISRA pragmas were processed.

The syntax of the option and pragmas are:

  --check_misra={all|required|advisory|none|rulespec}

  #pragma CHECK_MISRA ("{all|required|advisory|none|rulespec}");
  #pragma RESET_MISRA ("{all|required|advisory|rulespec}");

The rulespec parameter is a comma-separated list of these specifiers:

   -[-]X Enable (or disable) all rules in topic X.
   -[-]X-Z Enable (or disable) all rules in topics X through Z.
   -[-]X.A Enable (or disable) rule A in topic X.
   -[-]X.A-C Enable (or disable) rules A through C in topic X.

Example: --check_misra=1-5,-1.1,7.2-4
o Checks topics 1 through 5
o Disables rule 1.1 (all other rules from topic 1 remain enabled)
o Checks rules 2 through 4 in topic 7

Two options control the severity of certain MISRA-C:2004 rules:

o The --misra_required option sets the diagnostic severity for required
  MISRA-C:2004 rules.

o The --misra_advisory option sets the diagnostic severity for advisory
  MISRA-C:2004 rules.

The syntax for these options is:

  --misra_advisory={error|warning|remark|suppress}
  --misra_required={error|warning|remark|suppress}


================================================================================
 4.4.0-12. Applying Options to Individual Functions
================================================================================
The FUNCTION_OPTIONS pragma allows you to compile a specific function in a C or
C++ file with additional command-line compiler options. The affected function
will be compiled as if the specified list of options appeared on the command
line after all other compiler options. In C, the pragma is applied to the
function specified. In C++, the pragma is applied to the next function.

The syntax of the pragma in C is:

  #pragma FUNCTION_OPTIONS(func, "additional options");

The syntax of the pragma in C++ is:

  #pragma FUNCTION_OPTIONS("additional options");


================================================================================
 4.4.0-13. New Pragmas: SET_DATA_SECTION and SET_CODE_SECTION
================================================================================
Two new pragmas have been added to the compiler, SET_DATA_SECTION and
SET_CODE_SECTION. These pragmas can be used to set the section for all
declarations below the pragma.

Example:

  #pragma SET_DATA_SECTION("mydata")
  int x;
  int y;
  #pragma SET_DATA_SECTION()

In the example above, x and y will both be put in the section mydata. To reset
the current section to the default used by the compiler, a blank parameter
should be passed to the pragma. An easy way to think of the pragma is that it
is like applying the CODE_SECTION or DATA_SECTION pragma to all symbols below
it.

The pragmas apply to both declarations and definitions. If applied to a
declaration and not the definition, the pragma that is active at the
declaration is used to set the section for that symbol. Here is an example:

  #pragma SET_CODE_SECTION("func1")
  extern void func1();
  #pragma SET_CODE_SECTION()
  ...
  void func1() { ... } 

In this example func1 will end up in section func1. If conflicting sections are
specified at the declaration and definition, a diagnostic will be issued.

The current CODE_SECTION and DATA_SECTION pragmas and GCC attributes can be
used to override the SET_CODE_SECTION and SET_DATA_SECTION pragmas. For
example:

  #pragma DATA_SECTION(x, "x_data")
  #pragma SET_DATA_SECTION("mydata")
  int x;
  int y;
  #pragma SET_DATA_SECTION()

In this example, x will be placed in x_data and y will be placed in mydata. No
diagnostic is issued for this case.

The pragmas work for both C and C++. In C++, the pragmas are ignored for
templates and for implicitly created objects, such as implicit constructors and
virtual function tables.


================================================================================
 4.4.0-14) Fewer pre-built libraries, automatic library building
================================================================================
This release provides fewer pre-built compiler run-time support libraries,
which makes the CCS package download size much smaller, reducing download
time.  Users are expected to build less-commonly used libraries as needed.
The RTS source code is provided in each compiler release, which allows the
user to build libraries with custom command-line options, and it also allows
the linker to automatically build missing libraries.

Users with shared or read-only installation directories need to take special
action to build (at installation time) libraries that will be needed.

More details about the mechanism behind rebuilding libraries can be found at
the TI Embedded Processors Wiki http://processors.wiki.ti.com/index.php/Mklib


================================================================================
 4.4.0-15. Silicon Bug Detection in the Assembler
================================================================================
At the time of the 4.4.0 release the last bug on the C55x silicon bug list was
CPU_127.  The assembler detects all bugs except CPU_05, CPU_06, CPU_13, CPU_71,
CPU_73, CPU_79, CPU_82 and CPU_90 which are the user's responsibility, and
CPU_101, CPU_102, CPU_104, CPU_106, CPU_108 - CPU_111, CPU_113, and CPU_114
which will be addressed in a future release.  CPU_125 and CPU_126 will be
addressed in a future release, but will not affect code that will not be ported
to hardware revisions beyond revision 3.x.

The silicon bug list for C55x+ includes three items.  The assembler detects
all three bugs.

Various documents available at the TI Web Site (www.ti.com) contain information
about silicon errata.


================================================================================
 4.4.0-16. Silicon Bug Workarounds in the Compiler
================================================================================
At the time of the 4.4.0 release the last bug on the C55x silicon bug list was
CPU_127.  The compiler works around all except CPU_13, CPU_71, CPU_95, CPU_96,
and CPU_121 which are the user's responsibility, and CPU_101 and CPU_102 which
will be addressed in a future release.

The silicon bug list for C55x+ includes three items.  The compiler works around
all three bugs.

Various documents available at the TI Web Site (www.ti.com) contain information
about silicon errata.


================================================================================
 4.4.0-17. Validation Information
================================================================================
Version 4.4.0 of the Code Generation Tools was validated using the C55x Cycle
Accurate Simulator Version 3.5.31, P2 Reserved Mode Simulator Version 1.50
(CModel Release 0.89:2.3:0.57), C55x+ Functional Simulator Version 02.01.11, and
C55x+ Cycle Accurate Simulator Version 04.03.38.
