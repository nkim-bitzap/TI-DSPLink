********************************************************************************
***************** Start of Annex A: Support for C55x+ Devices ******************
********************************************************************************
*                               March 2012                                     *
********************************************************************************

********************************************************************************
 Annex A Support for C55x+ Devices
********************************************************************************

================================================================================
Table of Contents
================================================================================
 A.1.00 Overview
 A.1.01 Invocation
 A.1.02 Runtime Support Libraries
 A.1.03 Predefined Symbols
 A.1.04 Legacy IO Memory and "IO Access" to Memory
 A.1.05 Comment on -mb Option
 A.1.06 Use of coef() and CDP to dictate Cmem encoding
 A.1.07 pragma C55X_CALL(function)
 A.1.08 Calling Conventions
 A.1.09 Support for C54x Mnemonic Assembly Language
 A.1.10 Deprecation of --assume_smul_off
 A.1.11 Processor Configurations in the .ivec Directive
 A.1.12 Accessing Control Registers Within C/C++ Source Code
 A.1.13 Behavior of --align_functions option
 A.1.14 Related Documentation from Texas Instruments
 A.1.15 Memory Model Restrictions
 A.1.16 Representation of Enumeration Types
 A.1.17 GCC Type Attribute "packed"
 A.1.18 Silicon Bug Detection in the Assembler
 A.1.19 Silicon Bug Workarounds in the Compiler

 A.2.00 C55x+ Byte Mode
 A.2.01 C User Interface Changes
 A.2.02 Assembler User Interface Changes
 A.2.03 Scaling Operator in Assembly Language Memory Operands
 A.2.04 Runtime Support Libraries

 A.3.00 C55x+ Byte With Word Mode ("Mixed Mode")
 A.3.01 Invoking Word Mode Assembly Functions from C
 A.3.02 Including Word Mode Assembly Code in a Byte Mode Executable
 A.3.03 Other Rules and Ramifications
 A.3.04 Porting C Code from Word to Byte Mode


================================================================================
 A.1.00 Overview
================================================================================
The toolset supports both C55x and C55x+, including byte mode for C55x+ (see
section A.2.00) and C55x+2, revision 2 of the C55x+ CPU.

As they do for C55x, for C55x+ the tools support both algebraic and mnemonic
assembly languages, with the default being "mnemonic".  The -mg option is used
to select "algebraic".

Only DWARF debug directives are supported for C55x+.


================================================================================
 A.1.01 Invocation
================================================================================
To select C55x+ as the target use the cl55 option -vcpu+ (or equivalently
-vplus) to select word-mode code generation.  You must additionally specify
--byte_mode to select byte mode operation.

        cl55 -vcpu+ bar.asm
        cl55 -vcpu+ --byte_mode --memory_model=huge foo.c

The default memory model for word mode is Small Memory Model (as is the case for
C55x compilation).  When --byte_mode is used the memory model defaults to Huge
Memory Model.

Compiling code for C55x+ Rev 2 (C55x+2) is selected using the option -vcpu+:2
(or equivalently -vplus:2).


================================================================================
 A.1.02 Runtime Support Libraries
================================================================================
The runtime libraries for C55x+ are named "rts55p" instead of "rts55."  For
example, the small model library is rts55p.lib.  The byte mode libraries append
"b" to the usual names.  Only Large and Huge Memory Models are supported for
byte mode.

    Use this library	  With these options
    ----------------      ------------------
    rts55p.lib            -vcpu+
    rts55p_eh.lib         -vcpu+ --exceptions
    rts55px.lib           -vcpu+ -mL
    rts55px_eh.lib        -vcpu+ -mL --exceptions
    rts55ph.lib           -vcpu+ --memory_model=huge
    rts55ph_eh.lib        -vcpu+ --memory_model=huge --exceptions

    rts55pxb.lib      	  -vcpu+ -mL --byte_mode
    rts55pxb_eh.lib   	  -vcpu+ -mL --byte_mode --exceptions
    rts55phb.lib      	  -vcpu+ --memory_mode=huge --byte_mode
    rts55phb_eh.lib   	  -vcpu+ --memory_mode=huge --byte_mode --exceptions

Each library provides interrupt vectors that put the program into the correct
mode (word or byte) at RESET.  The default boot.asm provided in the library will
automatically force inclusion of a "_Reset" symbol.  If you do not want the
default interrupt vector, you must provide your own boot code or provide a
definition of "_Reset".

Static data initialization handles byte-aligned and byte-sized objects.


================================================================================
 A.1.03 Predefined Symbols
================================================================================
The following new C predefined symbols are provided as macros:

    __TMS320C55X_PLUS__
    __TMS320C55X_PLUS_BYTE__
    __TMS320C55X_PLUS_WORD__

If the associated predicate is false, the macro will not be defined, so the
user can test the predicate by either of the following methods:

    #if __TMS320C55X_PLUS__
or
    #if defined(__TMS320C55x_PLUS__)

Note that the macro __TMS320C55X__ will be set when compiling for C55x+.


The following new predefined symbols are provided in the assembler:

    __TMS320C55X_PLUS__
    __TMS320C55X_PLUS_BYTE__
    __TMS320C55X_PLUS_WORD__

These symbols are always defined.  The value will indicate either true or false,
so the test for the predicate is the following:

    .if __TMS320C55X_PLUS__


================================================================================
 A.1.04 Legacy IO Memory and "IO Access" to Memory
================================================================================
The ioport type qualifier is supported as it was for C55x.  It specifies access
to the legacy IO memory space.  The new C55x+ hardware support for "IO access"
or "strongly ordered access" to data memory is used in implementing C volatile
variables.


================================================================================
 A.1.05 Comment on -mb Option
================================================================================
The -mb option (assume all data is in onchip memory) is accepted but has no
impact on the compilation.  This option existed to facilitate generation of the
dual MAC, MAS and MPY instructions which on C55x required the memory operands
to be in onchip memory.


================================================================================
 A.1.06 Use of coef() and CDP to dictate Cmem encoding
================================================================================
coef() Usage Notes:

o Assembler will now detect invalid usage of coef() qualifier on Xmem,
  Ymem, and Smem address operands.  One exception, coef() is allowed on
  Ymem in memory to memory move instructions.

o Users can now use coef() qualifier to dictate which address operand is to
  be encoded as a Cmem.  In the memory to memory move instructions, an
  address operand qualified with coef() will be encoded as a Ymem.

CDP Usage Notes:

o In the majority of instructions, users can freely interchange the CDP
  register with the AR15 and get the same instruction opcode with either
  register.

o In the case of "CDP = P16", the user should not expect to get the
  same encoding if the AR15 register is used in place of CDP.  In the
  case of "CDP = P16", the instruction will be encoded as a LD_RPK_DAX
  instruction which performs the register write in the address phase of
  the pipeline.  In the case of "AR15 = K16", the instruction will be
  encoded as a LD_RWK instruction which performs the register write in
  the execute phase of the pipeline.

o In cases involving the use of a Cmem address operand.  The user can
  specify CDP as the base register in a valid Cmem address operand to
  dictate that the operand is to be encoded in the Cmem bit field of the
  opcode format, regardless of whether another address operand in the same
  instruction is a legal Cmem or not.


================================================================================
 A.1.07 pragma C55X_CALL(asm_function)
================================================================================
This pragma supports the calling of assembly code written for the C55x and using
the calling conventions of the C55x C runtime environment.

The pragma indicates that the function should be invoked using the standard C55x
calling sequence and that it obeys the C55x C runtime environment conventions.
The pragma must appear before any declaration or call to the named function.

This pragma does not support calling assembly functions that call C code.  In
such a case, the assembly code must be modified to account for the differences
in the C55x and C55x+ runtime environments.  Similarly, if the assembly code is
modified to take advantage of the additional registers or other architectural
enhancements available on the C55x+, the code must not violate the conventions
of the C55x+ runtime environment.


================================================================================
 A.1.08 Calling Conventions
================================================================================
The C function calling sequence has been changed to take advantage of the C55x+
ISA.  A system may be compiled using one of the previous calling conventions by
using the -call option.  -call=<id> can be used to select the calling convention
used on P2 Reserved Mode devices (-call=c55_compat) or on standard C55x devices
(-call=c55_std).  All C files linked into the system must use the same calling
convention.

Calling conventions are described in Chapter 6 of the C55x Compiler User's
Guide.  For C55x+ function calls behave as described there except the registers
used for the classes of arguments are as follows:

       data pointer   (X)AR0, (X)AR1, ..., (X)AR4
       16-bit data    AC0.L, AC0.H, AC1.L, AC1.H, AC2.L, AC2.H, AC3.L, AC3.H
       32-bit data    AC0, AC1, AC2

Return value locations are as described except that 16-bit data values are
returned in AC0.L.

The register save/restore conventions are an extension of the existing
conventions (described in section 6.3 of the C55x Compiler User's Guide) with
the addition of the following registers being saved by the child (called)
function: AC5, AC6, AC7.  All other new-with-C55x+ ACs and XARs are saved by
the parent (calling) function.


================================================================================
 A.1.09 Support for C54x Mnemonic Assembly Language: 
              --translate_c54x_mnem_source
================================================================================
A mnemonic assembly language source that contains C54x assembly language and
C55x assembly language, but not any of the instructions newly introduced in
C55x+, may be assembled to C55x+ object code.  To do this the
--translate_c54x_mnem_source option is used in conjunction with the -vcpu+ and
--asm_source=mnemonic options.  (Note: --asm_source=mnemonic is the default and
need not be specified.)  An example:
   
  cl55 -vcpu+ --translate_c54x_mnem_source file.asm


================================================================================
 A.1.10 Deprecation of --assume_smul_off
================================================================================
The --assume_smul_off option is not supported for the C55x+ target.


================================================================================
 A.1.11 Processor Configurations in the .ivec Directive
================================================================================
The assembler directive .ivec has been enhanced to allow setting the
configurations supported by C55x+.  The assembler syntax for .ivec is the
following:

  [label:]  .ivec [address, [configuration]]

The configuration value is created using combinations of the following symbolic
values separated by the OR operator ("|"):

   STK_LINEAR or STK_PAGED selects the stack addressing mode

   DATA_PTR_WORD or DATA_PTR_BYTE selects the default processor pointer mode.
   
   RET_FAST (or USE_RETA) or RET_SLOW (or NO_RETA) or RET_SLOW32 (or C54X_STK)
   selects the return mode.

For example, a typical entry for the reset entry in the interrupt vector table
for a byte mode program would be:

  reset: .ivec  main, STK_LINEAR | RET_FAST | DATA_PTR_BYTE

Descriptions of the various modes and of the legal mode combinations may be
found in the TMS320C55x+ CPU Reference Guide.


================================================================================
 A.1.12 Accessing Control Registers Within C/C++ Source Code
================================================================================
The keywords cregister and __cregister are introduced to allow high level
language access to control registers.  __cregister may be used even when strict
ANSI checking is enabled (-ps) since it obeys the naming rules given in the
language standard.  cregister is available only when strict checking is not
being done.

When you use the cregister keyword on an object, the compiler compares the name
of the object to a list of standard control registers.  If the name matches, the
compiler generates the code to reference the control register. If the name does
not match, the compiler issues an error.

Hardware Control Registers

  BER    - Bus error register
  BIOS   - BIOS register
  CPUREV - CPU revision ID register (read-only)
  CPUCFG - CPU configuration register (read-only)
  DBIER0 - Debug interrupt enable register 0
  DBIER1 - Debug interrupt enable register 1
  IER0   - Interrupt enable register 0
  IER1   - Interrupt enable register 1
  IFR0   - Interrupt flag register 0
  IFR1   - Interrupt flag register 1
  IIR    - Interrupt ID register (read-only)
  IVPD   - Interrupt vector pointer
  RETA   - Return address register
  ST0    - Status register 0 (accesses ST0_55)
  ST1    - Status register 1 (accesses ST1_55)
  ST2    - Status register 2 (accesses ST2_55)
  ST3    - Status register 3 (accesses ST3_55)
  XSP    - Extended data stack pointer
  XSSP   - Extended system stack pointer

Extended Control Registers 
  IER    - Interrupt enable registers accessed as 32-bit value
  IFR    - Interrupt flag registers accessed as 32-bit value
  DBIER  - Debug interrupt enable registers accessed as 32-bit value

To use the control registers listed above, you must declare each register in a
manner similar to the following:

  extern cregister <type> <register name>

<type> must be "unsigned long" for the extended control register and for XSP,
XSSP and RETA.  For all others <type> must be "unsigned int".  The c55x.h
header file contains definitions for all of the control registers.

The cregister keyword can only be used in file scope. The cregister keyword is
not allowed on any declaration within the boundaries of a function.

The cregister keyword does not imply that the object is volatile. If the control
register being referenced is volatile (that is, can be modified by some external
control), then the object must be declared with the volatile keyword also.
Similarly, a read-only register should have the const keyword added to its
declaration.

See the CPU and Instruction Set Reference Guides for detailed information on
the function of these control registers.  Note that modifying these registers
can have profound effects on the program behavior.  The user needs to
understand the impact of any operations on these registers.


********************************************************************************
 A.1.13 Behavior of --align_functions option
********************************************************************************
For C55x+ the --align_functions options aligns all function on an 8-byte
boundary


********************************************************************************
 A.1.14 Related Documentation from Texas Instruments
********************************************************************************
The following books are available from TI:

SPRU281: TMS320C55x Optimizing C Compiler User's Guide. Describes the
TMS320C55x C/C++ Compiler. This C/C++ compiler accepts ISO standard C/C++
source code and produces assembly language source code for TMS320C55x devices.

SPRU280: TMS320C55x Assembly Language Tools User's Guide. Describes the
assembly language tools (assembler, linker, and other tools used to develop
assembly language code), assembler directives, macros, common object file
format, and symbolic debugging directives for TMS320C55x and TMS320C55x+
devices.

SPRU376: TMS320C55x DSP Programmer's Guide. Describes ways to optimize C and
assembly code for the TMS320C55x? DSPs and explains how to write code that uses
special features and instructions of the DSP.

SWPU086: TMS320C55x+ DSP CPU Reference Guide. Describes the architecture,
registers, and operation of the CPU for the TMS320C55x+ digital signal
processors (DSPs).

SWPU104: TMS320C55x+ Algebraic Instruction Set Reference Guide. Describes the
TMS320C55x+ DSP algebraic instructions individually. Also includes a summary of
the instruction set, a list of the instruction opcodes, and a cross-reference
to the mnemonic instruction set.

SWPU123: TMS320C55x+ Mnemonic Instruction Set Reference Guide. Describes the
TMS320C55x+ DSP mnemonic instructions individually. Also includes a summary of
the instruction set, a list of the instruction opcodes, and a cross-reference
to the algebraic instruction set.


********************************************************************************
 A.1.15 Memory Models
********************************************************************************
Small Memory Model is available only in word mode.  Large and Huge Memory
Models are supported for both word and byte modes.  The features, rules and
restrictions for C55x+ are the same as for C55x with the following differences:

 o In Large and Huge Memory Models the .stack and .sysstack sections are not
   required to be on the same page.

 o In Large Memory Model objects may cross page boundaries.


********************************************************************************
 A.1.16 Representation of Enumeration Types
********************************************************************************
Values of enumerated types are normally represented in the type 'int'.  When the
--gcc option is used an enumerated type represented in an integer type no
smaller (narrower) than the type 'int', but which may be a larger (wider) type
such as 'long'.

Using the GCC Type Attribute language extension an individual enumerated type
may be designated as having a "packed" representation. In this case the
underlying integer type will be the smallest integer type that can represent all
the values of the enumeration constants.  For example:

  typedef enum {E1, E2, E3} __attribute__((packed)) E_PACKED;
  typedef enum {X1, X2 = 0x10000, X3} __attribute__((packed) E_NOT;

  E_PACKED var; /* occupies 8 bits in C55x+ byte mode, 16 otherwise */
  E_NOT var2;   /* occupies 32 bits */

The option --small_enum may be used to indicate that all enumerated types will
be "packed".  The GCC Type Attribute mechanism can be used to override this for
an individual type by specifying TI implementation-specific attribute
"unpacked".

The --small_enum option is always available.  However, applying attributes to an
enumerated type is available only when compiling with the --gcc option.  The
--gcc option is available for both C and C++ source files.

The user must be careful to ensure that within a program ALL uses of a
particular enumerated type are packed or not.  In particular, special care
should be taken when using the --small_enum option which quietly adds the packed
attribute to all enumeration types in the compilation.


********************************************************************************
 A.1.17 GCC Type Attribute "packed"
********************************************************************************
The type attribute "packed" which is permitted when the --gcc option is used to
enable GNU C language extensions may only be applied to an enum definition.
Applying this attribute to struct and union types is not supported.

When applied to an enumerated type definition it indicates that the smallest
possible integer type should be used to represent the type. (See section A.1.16)

Note that ALL definitions of a given type should contain or not contain this
attribute.


********************************************************************************
 A.1.18 Silicon Bug Detection in the Assembler
********************************************************************************
The C55x+ CPU Errata List (29 Sep 2008) include three items.  The assembler
detects all three bugs.


********************************************************************************
 A.1.19 Silicon Bug Workarounds in the Compiler
********************************************************************************
The C55x+ CPU Errata List (29 Sep 2008) include three items. The compiler works
around all three bugs.


********************************************************************************
 A.2.00 C55x+ Byte Mode
********************************************************************************
The C55x+ CPU supports treating data memory as either word- or byte-oriented. In
word-pointer mode, or word mode, a data address is 23 bits and designates a
16-bit word.  In byte-pointer mode, or byte mode, a data address is 24 bits and
designates an 8-bit byte.  A word mode pointer of value v designates the same
memory word as the byte mode pointer with value 2*v.

The current mode is reflected in a bit in one of the CPU status registers (BPTR
in ST3_55). This bit is read-only for all instructions except special
mode-switching call instructions.  A function return restores the mode to the
caller's mode.  The initial mode is determined by a bit in the Reset interrupt
vector.  This bit also sets the pointer mode which is used in all interrupt
service routines.  The mode is saved and restored around the processing of an
interrupt.

In word mode C55x+ is upward compatible (at the assembly code, but not object
code, level) with the C55x.  Obviously byte mode operation is not.


================================================================================
 A.2.01 C User Interface Changes
================================================================================
All of the changes due to byte mode revolve around the fact that "char" is now
an 8-bit type.  "char" is such a fundamental type that there are many resultant
changes in the C language for byte mode as compared to word mode.

    - Data pointers are 24 bits wide
    - The sizeof operator yields a byte (not word) count.  Thus
      sizeof(bool)==1, sizeof(int)==2, sizeof(long)==4, sizeof(long long)==8
    - Linker map file shows all addresses and sizes in terms of bytes.
    - The value of CHAR_BIT is 8 (limits.h)
    - int8_t, etc. are now available (stdint.h)
    - C I/O (a.k.a. file I/O) operates on 8-bit characters
    - The alignment specified by the DATA_ALIGN pragma is interpreted in
      terms of byte (not word) alignment.

Things that did not change:

    - Stack frames are still 32-bit aligned.


================================================================================
 A.2.02 Assembler User Interface Changes
================================================================================
Because the size of "char" changes for C55x+ byte mode, we have to change the
handling of "byte oriented" directives in the assembler.  The best example of
this is the ".string" directive, which for C55x packs each character of the
string into a 16-bit field (as "char" is 16 bits on C55x), but for byte mode
needs to pack each character into an 8-bit field ("char" is 8 bits in
byte mode).

The list of directives which are "byte oriented" is:

        .byte
        .ubyte
        .char
        .uchar
        .string
        .cstring
        .align
        .bss
        .usect

In byte mode, each of these operates on 8-bit units instead of 16-bit units.

A user who wishes to write assembly data structures that work identically in
word and byte mode cannot use the byte-oriented directives without conditional
compilation.  For many uses, other directives can be directly substituted; for
instance, ".word" can be used to give a consistent 16 bits of storage.
However, there is no substitute for ".align".  One possibility is to write
aligns like this, with a user-defined macro:

        .align (1 * MEMORY_WIDTH)


================================================================================
 A.2.03 Scaling Operator in Assembly Language Memory Operands
================================================================================
In byte pointer mode the hardware scales the offset in many addressing modes to
accommodate accesses to word (16-bit) and double-word (32-bit) data.  (See
Section 7.5 of the TMS320C55x C55x+ CPU Reference Guide for descriptions of
addressing modes in byte pointer mode.)  For many of the register indirect,
DP-relative and SP-relative addressing modes the hardware will scale the encoded
offset by 2 or 4 for accesses to 16- or 32-bit data.  This scaling converts the
offset encoded in the instruction from a word or double-word offset into a byte
offset that can be added directly to the base addressing register to get the
actual address of the data object being accessed.

Address Expressions and New Scaling Operator
--------------------------------------------
Constant offsets specified within address expressions will always be interpreted
as byte offsets by default.  To provide the user with the capability to address
data objects in a unit that is consistent with the size of a given data access,
a new "scaling" operator syntax is supported for C55x+ byte pointer mode.

Consider the following examples (assume DP is set to _dp_val):

         .dp     _dp_val 
	 
	 T0 = byte(@(x + 4)) 	; refers to 4th byte past 'x'
	 T0 = byte(@x[4]) 	; refers to 4th byte past 'x'

	 copy(T0 = @(x + 4)) 	; refers to 2nd word past 'x'
	 copy(T0 = @x[4]) 	; refers to 4th word past 'x'

	 AC0 = dbl(@(x + 4)) 	; refers to 1st double-word past 'x'
	 AC0 = dbl(@x[4]) 	; refers to 4th double-word past 'x'

In the above examples, the scaling operator creates an explicit relationship
between the constant specified within the scaling operator and the size of the
data being accessed by the instruction in which the address operand occurs.

Some rules ...

- An expression specified inside a scaling operator must be constant
  at assembly time.  No relocatable expressions will be permitted 
  within a scaling operator.
  
- A scaling operator can be applied to the entire constant offset 
  expression in a register indirect with offset addressing mode.

- A scaling operator can be applied as an array subscript (very much 
  like a C array reference).

- A scaling operator cannot be applied to a constant term within 
  an address expression that is going to be combined via an additive
  operation with another term in the address expression.
  
Note the use of the scaling operator in many of the register indirect with
offset addressing modes described below.

Scaled Addressing Modes
-----------------------
The following table lists the addressing modes in which the encoded offset value
will be scaled by the hardware.

Note that the K/k values referenced in the "Syntax" and "Assembler Encodes"
columns refer to the range that is allowed to be specified by the user in the
assembler source.  The K/k values referenced in the "Hardware Interpretation"
column refer specifically to size of the K/k-field in the actual Smem or
instruction opcode encoding.

  Syntax                K/k-field Encoding           Hardware Interpretation
  ------                ------------------           -----------------------
  byte(*ARx(#K16))      K16                          (ARx + K16)
  *ARx(#K17)            (K17 >> 1)                   (ARx + (K16 << 1))
  dbl(*ARx(#K18))       (K18 >> 2)                   (ARx + (K16 << 2))

NOTE: When a scaling operator is not applied to a constant that is specified
      in an offset expression, then the range of the constant allowed in the 
      offset is dependent on the size of the data access being performed.  
      
      For example, if we would like to access a word using the "*ARx(#K16)" 
      addressing mode, then we know that the actual range to be allowed for 
      the constant offset for a word access is in the range of signed 17-bit 
      numbers.  This is because the constant will actually be scaled down 
      before it is encoded.

      Another interesting characteristic of un-scaled constant offsets in a 
      word or double-word data access is that they need to be aligned to a 
      word or double word address.  For example, if you want to access a 
      double-word with "dbl(*ARx(#K18))", then the constant specified in 
      #K18 must be a multiple of 4 so that when it is scaled down by the 
      assembler, there won't be any information lost (or discarded).  
      
      If the assembler encounters a constant byte offset that is not 
      appropriately aligned for the size of the access being performed by 
      the instruction in question, then the assembler will emit a warning 
      saying a part of the constant offset was lost.

      For example,

	dbl(*AR5(#14))

      would emit a warning since 14 is not a multiple of 4 as required by 
      double word accesses.

  byte(*ARx[#K16])      K16                          (ARx + K16)
  *ARx[#K16]            K16                          (ARx + (K16 << 1))
  dbl(*ARx[#K16])       K16                          (ARx + (K16 << 2))

NOTE: This is the first example of where the scaling operator is applied 
      to the entire offset expression.  The offset value is encoded as
      specified, but is then scaled up by the hardware to refer to the
      Kth-word or Kth-double-word relative to the base address in ARx.

      The '#' prefix in a scaling operator's expression will likely be
      optional.

  byte(*+ARx(#K16))     K16                          (ARx += K16)
  *+ARx(#K17)           (K17 >> 1)                   (ARx += (K16 << 1))
  dbl(*+ARx(#K18))      (K18 >> 2)                   (ARx += (K16 << 2))

  byte(*+ARx[#K16])     K16                          (ARx += K16)
  *+ARx[#K16]           K16                          (ARx += (K16 << 1))
  dbl(*+ARx[#K16])      K16                          (ARx += (K16 << 2))

  byte(*ARx(#k24))      k24                          (ARx + k24)
  *ARx(#k24)            (k24 >> 1)                   (ARx + (k24 << 1))
  dbl(*ARx(#k24))       (k24 >> 2)                   (ARx + (k24 << 2))

  byte(*ARx[#k24])      k24                          (ARx + k24)
  *ARx[#k23]            k23                          (ARx + (k24 << 1))
  dbl(*ARx[#k22])       k22                          (ARx + (k24 << 2))

NOTE: The total address range for C55x+ is 24-bits, but since the hardware
      is going to scale the encoded k-field for word and double-word accesses,
      the assembler will only allow a 23-bit offset for word accesses and
      a 22-bit offset for double-word accesses.  This is because the scaling
      operator applied to the offset dictates that the offset value will be
      encoded as specified.

  byte(*+ARx(#k24))      k24                         (ARx += k24)
  *+ARx(#k24)            (k24 >> 1)                  (ARx += (k24 << 1))
  dbl(*+ARx(#k24))       (k24 >> 2)                  (ARx += (k24 << 2))

  byte(*+ARx[#k24])      k24                         (ARx += k24)
  *+ARx[#k23]            k23                         (ARx += (k24 << 1))
  dbl(*+ARx[#k22])       k22                         (ARx += (k24 << 2))

  byte(*ARx(short(#k4))) k4                          (ARx + k4)
  *ARx(short(#k5))       (k5 >> 1)                   (ARx + (k4 << 1))
  dbl(*ARx(short(#k6)))  (k6 >> 2)                   (ARx + (k4 << 2))

  byte(*ARx(short[#k4])) k4                          (ARx + k4)
  *ARx(short[#k4])       k4                          (ARx + (k4 << 1))
  dbl(*ARx(short[#k4]))  k4                          (ARx + (k4 << 2))

  byte(*DP(#k7))         k7                          (DP + k7)
  *DP(#k8)               (k8 >> 1)                   (DP + (k7 << 1))
  dbl(*DP(#k9))          (k9 >> 2)                   (DP + (k7 << 2))

  byte(*DP[#k7])         k7                          (DP + k7)
  *DP[#k7]               k7                          (DP + (k7 << 1))
  dbl(*DP[#k7])          k7                          (DP + (k7 << 2))

  byte(@sym)             (sym - dp)                  (DP + k7)
  @sym                   ((sym - dp) >> 1)           (DP + (k7 << 1))
  dbl(@sym)              ((sym - dp) >> 2)           (DP + (k7 << 2))

  byte(@(sym + #k))      ((sym + k) - dp)            (DP + k7)
  @(sym + #k)            (((sym + k) - dp) >> 1)     (DP + (k7 << 1))
  dbl(@(sym + #k))       (((sym + k) - dp) >> 2)     (DP + (k7 << 2))

NOTE: There is no range check performed on a constant offset in this
      addressing mode since the final encoded k-field is determined
      at link-time.  As long as the result of the relocation expression
      fits within an unsigned 7-bit range, the specified k value will
      be considered legal.

  byte(@sym[#k])       ((sym + k) - dp)               (DP + k7)
  @sym[#k]             (((sym + (k << 1)) - dp) >> 1) (DP + (k7 << 1))
  dbl(@sym[#k])        (((sym + (k << 2)) - dp) >> 2) (DP + (k7 << 2))

NOTE: Specifying the constant offset as an array subscript relative to
      a given symbol has the effect of scaling up the constant offset
      that is emitted with the relocation expression based on the size
      of the data access being performed.

  byte(*SP(#k7))         k7                           (SP + k7)
  *SP(#k8)               (k8 >> 1)                    (SP + (k7 << 1))
  dbl(*SP(#k9))          (k9 >> 2)                    (SP + (k7 << 2))

  byte(*SP[#k7])         k7                           (SP + k7)
  *SP[#k7]               k7                           (SP + (k7 << 1))
  dbl(*SP[#k7])          k7                           (SP + (k7 << 2))


Unscaled Addressing Modes
-------------------------
The assembler also supports using the scaling operator in the *abs16(#k16) and
*(#k24) addressing modes as well as the register indirect modes described above.

For example, if you want to refer to the 4th double-word past 'x' using the
abs24 addressing mode you can specify this in one of two ways:

   dbl(*(#(x + 16)))
   dbl(*(#x[4]))

When used in an addressing expression, the scaling operator can only be
specified as a C-like array reference.  You cannot combine a "scaled" constant
with another additive term in an address expression.  For example, "@(x + [4])"
is not supported.

The scaling operator creates an explicit relationship between the constant
specified within the scaling operator and the size of the data being accessed by
the instruction in which the address operand occurs.


================================================================================
 A.2.04 Runtime Support Libraries
================================================================================
The libraries provided with the toolset provide interrupt vectors that put the
program into byte mode at RESET.  Your linker command file should contain a 
"-u _Reset" option.  Static data initialization handles byte-aligned and 
byte-sized objects.


********************************************************************************
 A.3.00 C55x+ Byte With Word Mode ("Mixed Mode")
********************************************************************************
In order to support the inclusion of legacy C55x (necessarily word mode) code in
a C55x+ byte mode program, the code generation tools support a limited "mixed
mode" programming model.

The tools allow the inclusion of word mode assembly code in a byte mode
executable.  The tools DO NOT ALLOW the inclusion of word mode C code in a byte
mode executable, and DO NOT ALLOW the inclusion of any byte mode code in a word
mode executable.

Legacy C code may be ported to byte mode by re-compiling in byte mode.  Most
well-written C programs may be ported in this way without change.  Section
A.3.04 discusses some issues to be considered when moving C code from word to
byte mode.

There is no mixing of modes within a single source file.  A given object file,
whether created from C or assembly source, is entirely in either word mode or
byte mode.


================================================================================
 A.3.01 Invoking Word Mode Assembly Functions from C
================================================================================
A word mode assembly function to be called from byte mode C code must be
declared with an extern function declaration and have the WORD_MODE_FUNC pragma
applied to it.

   #pragma WORD_MODE_FUNC(wfunc)
   extern short * wfunc(short *input);

Calls to the specified function will be made using the mode switching call
instruction when the call is made within a byte mode compilation.  Note that if
this pragma is used in a word mode C compilation, it has no effect.

When the word mode function is called from within a byte mode compilation any
data pointer arguments will be adjusted to convert the byte mode pointer value
into the equivalent word mode pointer value (right shift by one), and upon
return, if the function value is a data pointer the returned word mode pointer
will be converted to a byte mode pointer (left shift by one). This pointer
adjustment is also done for argument and return value types (such as structs)
that are implemented using the pass-by-reference mechanism.

Even though pointer arguments and return values may be adjusted by the compiled
code, it is still the user's responsibility to access the designated data in the
intended manner, possibly scaling offsets, indices and sizes as may be
appropriate.

Note that applying the WORD_MODE_FUNC pragma only causes the possible pointer
adjustments and the use of a mode-switching call, but does not affect other
aspects of the calling convention used to invoke the function.  In particular,
the calling convention will follow changes to the default calling convention
indicated by pragmas C55X_CALL and C54X_CALL and the -call compiler option.


================================================================================
 A.3.02 Including Word Mode Assembly Code in a Byte Mode Executable
================================================================================
The --byte_with_word_mode linker option must be used to allow a link to include
word mode assembly code in a byte mode executable.  Without this option all
object code in a link must be of the same mode.

Note that in a byte mode executable which includes word mode code only the byte
mode C runtime support is available.


================================================================================
 A.3.03 Other Rules and Ramifications
================================================================================
Code in either mode can access the static data defined in the "other" mode.

Note that special care must be used when accessing global data structures
containing pointers.  It is up to the user to see that the pointers are
interpreted as word or byte data pointers as appropriate.

The system initialization code must setup the sysstack pointer (XSSP) so that it
will be valid when running in word mode.  The startup code in the standard C
runtime support does this initialization.

Word mode assembly code included in a byte mode executable may call back into
byte mode C by following the C calling conventions, adjusting the arguments and
return value if necessary, and using a mode-switching call.


================================================================================
 A.3.04 Porting C Code from Word to Byte Mode
================================================================================
C code written to be portable within the rules of the C language standard should
have little problem being moved from word to byte mode.  The following areas are
sensitive to such a porting operation:

1. Uses of the predefined type char. In word mode char is a 16-bit value, in
byte mode it is 8 bits. Problems arise if the word mode code uses a char object
to hold values bigger than eight bits, or if char and int (or short) are assumed
to have the same size.

2. Uses of sizeof. The value returned by sizeof in byte mode is 2x the value
returned in byte mode. Problems arise if the code interprets the value returned
by sizeof to be the number of words.

3. Missing uses of sizeof. If a user specifies an integer to indicate a number
of words, such as in an argument to malloc, in byte mode the integer may be
interpreted as a number of bytes, again, the argument to malloc. sizeof should
be used to compute the size of an object or type.

4. Use of integer arithmetic to compute pointer values.

5. Use of pointers from external data structures. What assumptions are made
about the pointer value? Word or byte pointers?

However, there is legal C code that would be correct and well-written for word
mode but would sometimes give a different result for byte mode.  For example, an
expression that adds an unsigned char to a signed int results in an unsigned int
value in word mode, but yields a signed int value in byte mode.  Such examples
play at the edges of the C type conversion rules.  The belief is that such
situations would be extremely rare especially in code written for DSPs.

Since the use of char is a primary factor in moving between byte and word mode,
the less that char is used, the less likely there may be issues to contend with
in porting the code.


********************************************************************************
****************** End of Annex A: Support for C55x+ Devices *******************
********************************************************************************



