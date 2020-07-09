TMS320C55x Code Generation Tools Release Version 4.4.1
Linker Release Notes
March 2012

===============================================================================
Contents
===============================================================================
1. Replacement COFF Linker

2. New Features
  2.1 Linker Command File Preprocessing
  2.2 Controlling Linker Diagnostics
  2.3 Automatic Run-Time-Support Library Selection
  2.4 Scan libraries for duplicate symbol definitions
  2.5 Named UNION/GROUP support
  2.6 Source Level Diagnostics
  2.7 Symbol mapping
  2.8 Wildcards in File, Section, and Symbol Patterns
  2.9 Managing Map File Content

3. Fixed Issues

-------------------------------------------------------------------------------
1. Replacement COFF Linker
-------------------------------------------------------------------------------

The new COFF linker is a drop in replacement COFF linker. It supports all
the current linker features and behaviors with the following exceptions:

1. The new COFF linker may not duplicate the exact allocation algorithm of 
 the old linker. That is, use of the new linker may result in a slightly 
 different input section layout into the memory compared to the old linker. 
 Also, the --default_order option is not supported in the new linker. This 
 option was added to the current COFF linker to support legacy section 
 allocation behavior. The new COFF linker does not support this option. 

2. The new linker uses most restrictive section specifier to match input
 sections, whereas the old linker uses the section specifier order in the 
 linker command file. 

 For example, consider the following linker command file:

   SECTIONS
   {
      .text: { *(.text) } > ROM
      .criticl_text: { critical.obj(.text) } > FASTROM
   }

 The new linker includes the input section  critical.obj(.text) in the output
 section .criticl_text. The remaining .text input sections are placed in 
 the .text output section.

 The old linker includes all .text sections in the output section .text.
 The output section .criticl_text becomes empty in this case. 

 Use the new linker option --match_first_section_spec=on to get the old linker 
 behavior.


-------------------------------------------------------------------------------
2) New Features
-------------------------------------------------------------------------------

The new COFF linker has the following new features. These features are
NOT supported in the previous COFF linker. 

2.1 Linker Command File Preprocessing
-------------------------------------
The linker now preprocesses linker command files using a standard C
preprocessor. This means command files may contain the well-known
preprocessing directives such as #define, #include, and #if/#endif.

Three new linker options control the preprocessor. They are:

  --disable_pp        - disables preprocessing for command files
  --defineNAME[=val]  - predefine NAME as a preprocessor macro
  --undefineNAME      - remove the macro NAME

The shell also has --define and --undefine options with the same meaning.
However, the linker options are distinct; only --define/--undefine
following -z are passed to the linker. For example:

  cl55 --define FOO=1 main.c -z --define BAR=2 lnk.cmd

The linker sees only the --define for BAR; the compiler only sees the --define
for FOO.

When one command file #includes another, preprocessing context is carried
from parent to child in the usual way (i.e. macros defined in the parent are
visible in the child). However, when a command file is invoked other than
via #include, either on the command line or by the typical way of being
named in another command file, preprocessing context is *not* carried into the
nested file.  The exception to this is --define and --undefine options,
which apply globally from the point they are encountered.  For example:

  --define GLOBAL
  #define LOCAL

  #include "incfile.cmd"     /* sees GLOBAL and LOCAL */
  nestfile.cmd               /* only sees GLOBAL      */

Two cautions apply to the use of --define and --undefine in command files.
First, they have global effect as mentioned above. Second, since they are
not actually preprocessing directives themselves, they are subject to macro
substitution, probably with unintended consequences.  This effect can be
defeated by quoting the symbol name. For example:

  --define MYSYM=123
  --undefine MYSYM     /* expands to --undefine 123 (!) */
  --undefine "MYSYM"   /* ahh, that's better            */

The linker uses the same search paths to find #include files as it does to
find libraries. That is, #include files are searched in the following
places:

   1. If the #include file name is "quotes" (rather than <brackets>), in
      the directory of the current file
   2. In the list of directories specified with -I options or environment
      variables

There are two exceptions: relative pathnames (e.g. "../name") always
search the current directory; and absolute pathnames (e.g. "/usr/tools/name")
bypass search paths entirely.

The linker has the standard built-in definitions for the macros __FILE__,
__DATE__, and __TIME__. It does not, however, have the compiler specific
options for the target (e.g. __TMS320C55X_PLUS__), version 
(__TI_COMPILER_VERSION__), runtime model, and so on.


2.2 Controlling Linker Diagnostics
----------------------------------
The new COFF linker provides diagnostic options to control the linker 
generated diagnostics. This support is an extension of the current support
to control compiler diagnostics as documented in the compiler user guide. The
following compiler options also affect the linker diagnostics now. These
options should be specified before the -z option.

--diag_error=num 
   Categorizes the diagnostic identified by num as an error. To determine the
   numeric identifier of a diagnostic message, use the --display_error_number
   option first in a separate compile. Then use --diag_error=num to 
   recategorize the diagnostic as an error. You can only alter the severity 
   of discretionary diagnostics.

--diag_remark=num 
   Categorizes the diagnostic identified by num as a remark. To determine the
   numeric identifier of a diagnostic message, use the --display_error_number
   option first in a separate compile. Then use --diag_remark=num to
   recategorize the diagnostic as a remark. You can only alter the severity of
   discretionary diagnostics.

--diag_suppress=num 
   Suppresses the diagnostic identified by num. To determine the numeric
   identifier of a diagnostic message, use the --display_error_number option
   first in a separate compile. Then use --diag_suppress=num to suppress the
   diagnostic. You can only suppress discretionary diagnostics.

--diag_warning=num 
   Categorizes the diagnostic identified by num as a warning. To determine the
   numeric identifier of a diagnostic message, use the --display_error_number
   option first in a separate compile. Then use --diag_warning=num to
   recategorize the diagnostic as a warning. You can only alter the severity of
   discretionary diagnostics.

--display_error_number 
   Displays a diagnostic's numeric identifier along with its text. Use this 
   option in determining which arguments you need to supply to the diagnostic
   suppression options (--diag_suppress, --diag_error, --diag_remark, and
   --diag_warning). This option also indicates whether a diagnostic is
   discretionary. A discretionary diagnostic is one whose severity can be
   overridden. A discretionary diagnostic includes the suffix -D; otherwise, no
   suffix is present. 

--issue_remarks 
   Issues remarks (non-serious warnings), which are suppressed by default.

--no_warnings 
  Suppresses warning diagnostics (errors are still issued).

--set_error_limit=num 
  Sets the error limit to num, which can be any decimal value. The compiler
  abandons compiling after this number of errors. (The default is 100.)

--verbose_diagnostics 
  Provides verbose diagnostics that display the original source with line-wrap
  and indicate the position of the error in the source line.

--no_demangle
  By default the linker uses demangled symbol names in diagnostics. For 
  example,

   undefined             first referenced
    symbol                   in file
   ---------             ----------------
   ANewClass::getValue() test.obj

  When the --no_demangle option is used, the mangled name is used by the 
  linker:

   undefined                first referenced
    symbol                      in file
   ---------                ----------------
   _ZN9ANewClass8getValueEv test.obj


2.3 Automatic Run-Time-Support Library Selection
------------------------------------------------
If --rom_model or --ram_model is specified during the link step, and the entry
point for the program (normally c_int00) is not resolved by any specified
object file or library, the link step will attempt to automatically include
the best compatible run-time-support library for your program.  The chosen
run-time-support library will be linked in as if it was specified with the
--library option last on the command line.  Alternatively, you can always
force the link step to choose an appropriate run-time-support library by
specifying libc.a as an argument to the --library option, or when specifying
the run-time-support library name explicitly in a link step command file.

If the --issue_remarks option is specified before the --run_linker option
during the link step, a remark will be generated indicating which run-time
support library was linked in.  If a different run-time-support library is
desired, you must specify the name of the desired run-time-support library
using the --library option and in your link step command files when necessary.

Example:
cl55 --v --issue_remarks main.obj --run_linker --rom_model
<Linking>
lnk55 --"tm_feedback=/tmp/10266lypVdg" hi.obj --rom_model --issue_remarks
remark: automatic RTS selection:  linking in index library "libc.a"
remark: automatic RTS selection:  linking in "rts55p.lib" in place of index
   library "libc.a"


2.4 Scan libraries for duplicate symbol definitions
---------------------------------------------------
The new option --scan_libraries (-scanlibs) will cause the linker to scan 
all libraries during a link to look for duplicate symbol definitions to those 
symbols that are actually included in a link.  The scan will not consider
absolute symbols or symbols defined in COMDAT sections. The option will
help determine those symbols that were actually chosen by the
linker over other existing definitions of the same symbol in a library.

This feature can be used to check aginst unintended resolution of a symbol 
reference to a definition when multilple definitions are available in 
the libraries.

2.5 Named UNION/GROUP support
-----------------------------
The linker now allows user to specify an optional name for UNIONs and GROUPs
specifications in the linker command file. The name should be specified after
the GROUP/UNION keyword: 
            
   GROUP (BSS_SYSMEM_STACK_GROUP)
   {
      .bss     : {}
      .sysmem  : {}
      .stack   : {}
   } load=D_MEM, run=D_MEM

The user-given name is used in diagnostics for easy identification of the
problem LCF area. For example, the above GROUP specification generates
the following diagnostic:

   warning: LOAD placement ignored for "BSS_SYSMEM_STACK_GROUP": object is 
            uninitialized

UNION (PINIT_CINIT_UNION)
{
   .const    : {} load=D_MEM, table(table1)
   .pinit   : {} load=D_MEM, table(table1)
} run=P_MEM

   warning: table(table1) operator ignored: table(table1) has already been 
            applied to a section in the UNION "PINIT_CINIT_UNION" in which 
            ".pinit" is a descendant


2.6 Source Level Diagnostics
----------------------------
When reporting diagnostics that relate to section offsets in the object file, 
the linker uses any available debug information to provide the file name and 
the line number of the corresponding source code.

For example, the test below contains a call to a function that is out of 
range, causing a relocation overflow:

cl55 --verbose_diagnostics -vcore+ -mg -g -z foo.obj bar.obj

"foo.c", line 8: warning: relocation from function "main" to symbol
   "_some_func" overflowed; the 29-bit relocated address 0x12345678 is too
   large to encode in the 24-bit field (type = 'R_REL24' (5), file =
   "foo.obj", offset = 0x00000003, section = ".text")
   some_func();
   ^


2.7 Symbol mapping
------------------
The following option was added to support symbol mapping.

  --symbol_map=refname=defname

Symbol mapping allows a symbol reference to be resolved by a symbol with
different name. This enables functions to be overridden with alternate 
definitions. This feature can be used to patch in alternate implementations,
which provide patches (bug fixes) or alternate functionality. For example, the
option --symbol_map='foo=foo_patch' makes the linker resolve any references to
foo by the definition foo_patch.


2.8 Wildcards in File, Section, and Symbol Patterns
---------------------------------------------------
The linker allows file, section, and symbol names to be specified using
'*' and '?' wild cards. This can make it easier to handle
related objects, provided they follow a suitable naming convention.

Examples:
mp3*.obj     /* matches anything .obj starting with "mp3" */
task?.o*     /* matches "task1.o", "task2.obj", "taskX.o55", etc */
SECTIONS
{    
   .fast_code: { *.obj(*fast*) }              > FAST_MEM
   .vectors  : { vectors.obj(.vector:part1:*) > 0xFFFFFF00    
   .str_code : { rts*.lib<str*.obj>(.text) }  > S1ROM 
}

2.9 Managing Map File Content
-----------------------------
The following option was added to assist with managing the content of a
linker-generated map files:

  --mapfile_contents=filter[,filter]

When the '-m' option is specified to the linker, the linker will produce
a map file containing information about memory usage, placement information
about sections that were created during a link, details about linker-
generated copy tables, and symbol values.

The new '--mapfile_contents' option provides a mechanism for you to control
what information is included in or excluded from a map file.  When you specify
'--mapfile_contents=help' from the linker (lnk55) command line (or after the 
'-z' option on the cl55 command line), you will see the following help screen:


The --mapfile_contents option controls display filter settings by specifying a
comma-delimited list of display attributes.  When prefixed with the word "no",
an attribute is disabled instead of enabled.

The following attributes are available:

    copytables: copy tables                   (default: on)
         entry: entry point                   (default: on)
     load_addr: display load addresses        (default: off)
        memory: memory ranges                 (default: on)
      sections: sections                      (default: on)
      sym_defs: defined symbols per file      (default: off)
      sym_name: symbols sorted by name        (default: on)
   sym_runaddr: symbols sorted by run address (default: on)
           all: enables all attributes
	  none: disables all attributes
								       
   Examples:  --mapfile_contents=copytables,noentry
              --mapfile_contents=all,nocopytables
	      --mapfile_contents=none,entry


By default, those sections that are currently included in the map file when
the '-m' option is specified will be included.  The filters specified in the
--mapfile_contents options will be processed in the order that they appear
in the command line.  In the third example above, the first filter, 'none', 
clears all map file content.  The second filter, 'entry', will then enable
information about entry points to be included in the generated map file.
That is, when '--mapfile_contents=none,entry' is specified, the map file will
contain *only* information about entry points.

There are two new filters included with the --mapfile_contents option,
'load_addr' and 'sym_defs'.  These are both disabled by default.  If you
turn on the 'load_addr' filter, the map file will include the load address
of symbols that are included in the symbol list in addition to the run
address (if the load address is different from the run address).

The 'sym_defs' filter can be used to include information about all static
and global symbols defined in an application on a file by file basis.  You
may find it useful to replace the 'sym_name' and 'sym_runaddr' sections of 
the map file with the 'sym_defs' section by specifying the following
--mapfile_contents option:

  --mapfile_contents=nosym_name,nosym_runaddr,sym_defs
  

-------------------------------------------------------------------------------
3. Fixed Issues
-------------------------------------------------------------------------------

------------------------------------------------------------------------------
FIXED  SDSCM00008208
------------------------------------------------------------------------------
Summary         : During partial link unwanted sections from RTS exit.obj 
                  is included.

Resolution      : The function atexit() was moved from exit.c into its own 
                  file atexit.c.

------------------------------------------------------------------------------
FIXED  SDSCM00008271
------------------------------------------------------------------------------
Summary         : Linker option to suppress unused sections warning

Resolution      : The new linker supports diagnostic control options. See
                  section 2.2 above.

------------------------------------------------------------------------------
FIXED  SDSCM00008424
------------------------------------------------------------------------------
Summary         : Make it possible to have named groups and unions in the 
                  Linker command file. 

Resolution      : The new linker allows named groups and unions. Refer to
                  section 2.5.

------------------------------------------------------------------------------
FIXED  SDSCM00008568
------------------------------------------------------------------------------
Summary         : Linker diagnostic control in general and specific to an 
                  output section.

Resolution      : Partially resolved. The new linker supports diagnostic 
                  control options. See section 2.2 above. The second part of
                  request to control messages pertaining to a specific output
                  section is not resplved.

------------------------------------------------------------------------------
FIXED  SDSCM00008590
------------------------------------------------------------------------------
Summary         : Map file should provide 'unused' memory and indicate failed
                  allocations.

Resolution      : The new linker includes lists unused memory in the map file:

MEMORY CONFIGURATION

          name          origin    length      used     unused   attr   fill
   ------------------  --------  ---------  --------  --------  ----  ------
     P_MEM             00000020   00040000  00004a21  0003b5df  RWIX
     D_MEM             00040020   00014000  000120b8  00001f48  RWIX

The mapfile also indicates falied allocations:
   .sysmem    0    00040020    00002000     FAILED TO ALLOCATE

------------------------------------------------------------------------------
FIXED  SDSCM00008619
------------------------------------------------------------------------------
Summary         : Linker to accept conditional MEMORY directives

Resolution      : The new linker supports linker command file preprocessing.
                  Refer to section 2.1.

------------------------------------------------------------------------------
FIXED  SDSCM00008776
------------------------------------------------------------------------------
Summary         : Holes in uninitialized output sections are not listed in 
                  map file

Resolution      : The new linker supports this.

------------------------------------------------------------------------------
FIXED  SDSCM00008797
------------------------------------------------------------------------------
Summary         : Lack of debug information for linker generated trampolines

Resolution      : The new linker generates debug information for the linker
                  generated trampolines.

------------------------------------------------------------------------------
FIXED  SDSCM00014260, SDSCM00008552
------------------------------------------------------------------------------
Summary         : Linker silently ignores -e option if the symbol is not 
                  defined.

Resolution      : The new linker genertaes undefined symbol error as expected.

------------------------------------------------------------------------------
FIXED  SDSCM00015446
------------------------------------------------------------------------------
Summary         : Request for linker errors to have more information so it can
                  better correlate to source location

Resolution      : Supported in the new linker. Refer to section 2.6

------------------------------------------------------------------------------
FIXED  SDSCM00015844
------------------------------------------------------------------------------
Summary         : '$bss' should be redefined in the final link

Resolution      : The new linker redefines the $bss symbol during final link.

------------------------------------------------------------------------------
FIXED  SDSCM00018242
------------------------------------------------------------------------------
Summary         : Linker generates errors on archives with no global symbols 
                  is linked.

Resolution      : The new linker generates warning.

