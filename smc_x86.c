#include <stdio.h>
#include <string.h>


#define SYS_MPROTECT			125

#define PROT_READ			1
#define PROT_WRITE			2
#define PROT_EXEC			4

void enable_exec(void *p);

//int f_data[] = {0x554889e5, 0xbf1c0640, 0x00e8cefe, 0xffff5dc3};
//static int f_data2[100];
int f_data[] __attribute__((section (".data")))  = {0xb8e58955, 0x00000064, 0x9090c35d};

typedef int (*P_FUNC)(void);

int main()
{
    P_FUNC p_func = (P_FUNC)f_data;

    memcpy(f_data2, f_data, sizeof(f_data));

    enable_exec(f_data);
    
    printf("%i", p_func());

    return 0;
}

void enable_exec(void *p)
{
//    long res;
//    __asm__ volatile (
//        "int $0x80" \
//        : "=a"  \
//        : "b" ((long)p), "c" ($0x2000), "d" ($0x7));
    asm volatile
    (
        "movl	$125, %eax\n\t"
	"movl	$f_data, %ebx\n\t"
	"andl	$0xfffff000, %ebx \n\t"
	"movl	$0x2000, %ecx\n\t"
	"movl	$7, %edx\n\t"
	"int	$0x80\n\t"
    );
}
