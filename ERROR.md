```
# First Compile:

root@bc-test-1:~/fischer_project_1/build# ninja
[1/5] Compiling C++ object 'distsync@exe/src_Node.cpp.o'.
FAILED: distsync@exe/src_Node.cpp.o
c++  -Idistsync@exe -I. -I.. -I/root/include_external/spdlog -I/root/include_external/tab/ -I/root/include_external/httplib/ -I/root/include_external/CLI11/ -I../include -fdiagnostics-color=always -pipe -D_FILE_OFFSET_BITS=64 -Wall -Winvalid-pch -Wnon-virtual-dtor -Wextra -Wpedantic -Werror -std=c++17 -O0 -g -pthread -MD -MQ 'distsync@exe/src_Node.cpp.o' -MF 'distsync@exe/src_Node.cpp.o.d' -o 'distsync@exe/src_Node.cpp.o' -c ../src/Node.cpp
c++: internal compiler error: Killed (program cc1plus)
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-7/README.Bugs> for instructions.
[3/5] Compiling C++ object 'distsync@exe/src_main.cpp.o'.
FAILED: distsync@exe/src_main.cpp.o
c++  -Idistsync@exe -I. -I.. -I/root/include_external/spdlog -I/root/include_external/tab/ -I/root/include_external/httplib/ -I/root/include_external/CLI11/ -I../include -fdiagnostics-color=always -pipe -D_FILE_OFFSET_BITS=64 -Wall -Winvalid-pch -Wnon-virtual-dtor -Wextra -Wpedantic -Werror -std=c++17 -O0 -g -pthread -MD -MQ 'distsync@exe/src_main.cpp.o' -MF 'distsync@exe/src_main.cpp.o.d' -o 'distsync@exe/src_main.cpp.o' -c ../src/main.cpp
{standard input}: Assembler messages:
{standard input}:391200: Warning: end of file not at end of a line; newline inserted
{standard input}: Error: .size expression for _ZSt9addressofINSt8__detail10_Hash_nodeISt4pairIKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10shared_ptrIN6spdlog6loggerEEELb1EEEEPT_RSG_ does not evaluate to a constant
c++: internal compiler error: Killed (program cc1plus)
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-7/README.Bugs> for instructions.
[4/5] Compiling C++ object 'distsync@exe/src_Coordinator.cpp.o'.
ninja: build stopped: subcommand failed.


# Second Compile:

root@bc-test-1:~/fischer_project_1/build# ninja
[3/3] Linking target distsync.

root@bc-test-1:~/fischer_project_1/build#
```