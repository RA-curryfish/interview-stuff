# Things about programs compiling, linking, loading
- extern tells compiler not to reserve memory, as it is defined and allocated space later? Don't need to include that file, but need to link them together
- thunk -> lambda funciton, do calc later?; vtable stuff; use in archs to get current \%ip by call (implicitly pushin ip on stack), then pop or store (%esp) in reg, then ret without epilogue

## PIC,PIE,ASLR
- PIC older than PIE, former used for shared libraries more so than executables. Becuase each executable has its own address space, but libraries need to be loaded at an unpredictible address. PIE is lesser overhead than PIC and can be used for executables. Program counter relative addressing in PIE?
- x86_64 arch have \%ip relative addressing, the earlier one didn't making PIC tricky to generate?
- 

## Compilation
Compilation units, pure C files (expanded macros, included files,...). Still contain unresolved addresses. However, needs at least a declaration of undefined symbols to check syntax.

## Linking
Links multiple files together to try and resolve addresses. Creates GOT and PLT in ELF types. Static libraries are inserted, dynamic libraries have 'stubs'?

## Links
- https://eli.thegreenplace.net/2011/11/03/position-independent-code-pic-in-shared-libraries/
- https://lettieri.iet.unipi.it/hacking/aslr-pie.pdf
- https://www.technovelty.org/linux/plt-and-got-the-key-to-code-sharing-and-dynamic-libraries.html
- https://stackoverflow.com/questions/38189169/elf-pie-aslr-and-everything-in-between-specifically-within-linux?rq=3
- 

