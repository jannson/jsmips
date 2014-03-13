set -e

O="-g"

buildKernel () {

    NAME=`basename $1 .c`
    mipsisa32-elf-gcc $O -mno-abicalls -fno-pic  -o kernel_common.o -c kernel.c  -Wall -Wextra -G0  \
        -nostdlib  -fno-builtin -nostartfiles -nodefaultlibs
    mipsisa32-elf-gcc $O -mno-abicalls -fno-pic  -o kernel_$NAME.o -c $1 -Wall -Wextra -G0 \
        -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
    mipsisa32-elf-as -o entry.o entry.s
    mipsisa32-elf-ld -T linker.ld -o kernel_$NAME.elf entry.o kernel_$NAME.o kernel_common.o
    mipsisa32-elf-objdump -D kernel_$NAME.elf > kernel_$NAME.map
    mipsisa32-elf-objcopy -O srec kernel_$NAME.elf kernel_$NAME.srec

}




if [ $# -eq 1 ]; then 
    buildKernel $1
else
    for f in `ls tests/*.c`
    do 
        buildKernel $f
    done
fi
