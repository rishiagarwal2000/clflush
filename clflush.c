#include<stdio.h>
#include <stdlib.h>

unsigned long long rdtsc() {
    unsigned long long a, d;
    asm volatile ("mfence");
    asm volatile ("rdtsc": "=a" (a), "=d" (d));
    a = (d << 32) | a;
    asm volatile ("mfence");
    return a;
}

void flush(void* p){
    asm volatile ("clflush 0(%0)\n"
        :
        : "c" (p)
        : "rax");
}

int main(){
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    FILE *fp3 = NULL;
    FILE *fp4 = NULL;

    fp1 = fopen("out/misses.txt", "w");
    fp2 = fopen("out/hits.txt", "w");
    fp3 = fopen("out/r.txt", "w");
    fp4 = fopen("out/w.txt", "w");

    int n = 100000;
    int k = 1000;
    int a[n]; int temp = 0, ind = 0;
    unsigned long long t1, t2, t3, t4, t5;

    // bring a to cache
    for(int i=0; i<n; i++){
        flush(&a[i]);
        t3 = rdtsc();
        temp = a[i];
        t4 = rdtsc();
        temp = a[i];
        t5 = rdtsc();
        printf("Miss: %lld\n", t4-t3);
        printf("Hit: %lld\n", t5-t4);
        fprintf(fp1, "%d %lld\n", i, t4-t3);
        fprintf(fp2, "%d %lld\n", i, t5-t4);
    }
    
    // flush
    for(int i=0; i<k; i++){
        ind = rand() % n;
        t1 = rdtsc();
        flush(&a[ind]);
        t2 = rdtsc();
        printf("clf: %lld\n", t2-t1);
        fprintf(fp3, "%d %lld\n", i, t2-t1);
    }
    // bring a to cache
    for(int i=0; i<n; i++){
        temp = a[i];
    }
    // make dirty
    for(int i=0; i<n; i++){
        a[i] = 0;
    }

    // // check if a is in cache
    // for(int i=0; i<n; i++){
    //     t4 = rdtsc();
    //     temp = a[i];
    //     t5 = rdtsc();
    //     printf("Hit: %lld\n", t5-t4);
    //     fprintf(fp2, "%d %lld\n", i, t5-t4);
    // }

    // flush
    for(int i=0; i<k; i++){
        ind = rand() % n;
        t1 = rdtsc();
        flush(&a[ind]);
        t2 = rdtsc();
        printf("clf: %lld\n", t2-t1);
        fprintf(fp4, "%d %lld\n", i, t2-t1);
    }
}