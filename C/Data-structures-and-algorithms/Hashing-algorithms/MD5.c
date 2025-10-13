#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

//typedef uint32_t WORD

#define A       0x67452301
#define B       0xefcdab89
#define C       0x98badcfe
#define D       0x10325476
#define A_prime 0x00000000
#define B_prime 0x00000000
#define C_prime 0x00000000
#define D_prime 0x00000000

void pad_string(int string_length) {
    int i = 0;
    
    if(string_length % 512 < 448) {
        i = string_length / 512;
    }
    
}

void MD5() {
    int iteration = 0;

    for(iteration = 0; iteration < 16; iteration++) {
        A_prime = D;
        C_prime = B;
        D_prime = C;

        
    }
    


}

int main() {
    unsigned char
    char *input_string; 

    printf("Enter string to be hashed: ");
    scanf("%s", input_string);





    return 0;
}