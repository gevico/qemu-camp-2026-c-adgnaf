
#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    unsigned int result;
    
    __asm__ volatile (
        "mov %1, %%eax\n\t"     // 将a存入eax
        "mov %2, %%ecx\n\t"     // 将b存入ecx
        "jmp .L_check\n\t"      // 跳转到检查条件
        
        ".L_loop:\n\t"
        "   xor %%edx, %%edx\n\t"
        "   div %%ecx\n\t"
        "   mov %%ecx, %%eax\n\t"
        "   mov %%edx, %%ecx\n\t"
        
        ".L_check:\n\t"
        "   test %%ecx, %%ecx\n\t"      // 测试ecx是否为0
        "   jne .L_loop\n\t"    // 如果不为0，继续循环
        
        "mov %%eax, %0"         // 将结果（eax）存入输出变量
        : "=r" (result)
        : "r" (a), "r" (b)
        : "eax", "ecx", "edx"
    );
    
    return result;
}

int main(int argc, char* argv[]) {
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}