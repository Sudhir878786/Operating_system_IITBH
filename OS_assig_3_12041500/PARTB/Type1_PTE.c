/*
                       _oo0oo_ 
                      o8888888o 
                      88" . "88 
                      (| -_- |) 
                      0\  =  /0 
                    ___/`---'\___ 
                  .' \\|     |// '. 
                 / \\|||  :  |||// \ 
                / _||||| -:- |||||- \ 
               |   | \\\  -  /// |   | 
               | \_|  ''\---/''  |_/ | 
               \  .-\__  '-'  ___/-. / 
             ___'. .'  /--.--\  `. .'___ 
          ."" '<  `.___\_<|>_/___.' >' "". 
         | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
         \  \ `_.   \_ __\ /__ _/   .-` /  / 
     =====`-.____`.___ \_____/___.-`___.-'===== 
                       `=---=' 
 
*/

// **************************************************************************** //
//                                                                              //
//                                                         :::      ::::::::    //
//                                              :+:      :+:    :+: //
//                                                     +:+ +:+         +:+      //
//    By: Sudhir_Sharma <12041500>        +//+  +:+            +//+             //
//                                                 +//+//+//+//+//+   +//+      //
//                                      //+//    //+//          //
//                                                     //#   ########.fr        //
//                                                                              //
// **************************************************************************** //
 
 
 
//#define s(n)                        scanf("%d",&n) 
#define s2(a,b)                      scanf("%d%d",&a,&b) 
#define s3(a,b,c)                    scanf("%d%d%d",&a,&b,&c) 
#define sc(n)                       scanf("%c",&n) 
#define sl(n)                       scanf("%I64d",&n) 
#define sf(n)                        
//----------------------------------------------- SUDHIR SHARMA--------------------------------------------
// #define mp make_pair
#define f first
#define s second
// vectors
// size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define eb emplace_back
#define pf push_front
// #define rtn return
 
#define lb lower_bound
#define ub upper_bound
 

#define FOR(i,a,b) for (int (i) = (a); (i) < (b); ++(i))
#define REP(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int (i) = (b)-1; (i) >= (a); --(i))
#define PER(i,a) ROF(i,0,a)
#define rep(a) REP(_,a)
#define each(a,x) for (auto& a: x)
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>


#define PAGEMAP_ENTRY 8
#define GET_BIT(X,Y) (X & ((uint64_t)1<<Y)) >> Y
#define GET_PFN(X) X & 0x7FFFFFFFFFFFFF

const int __endian_bit = 1;
#define is_bigendian() ( (*(char*)&__endian_bit) == 0 )

int i, c, pid, status;
unsigned long virt_addr;
uint64_t read_val, file_offset;
char path_buf [0x100] = {};
FILE * f;
char *end;

int read_pagemap(char * path_buf, unsigned long virt_addr)
{
   printf("Big endian? %d\n", is_bigendian());
   f = fopen(path_buf, "rb");
   if (f == NULL) {
       printf("Error! Cannot open %s\n", path_buf);
       return -1;
   }

   // Shifting by virt-addr-offset number of bytes
   // and multiplying by the size of an address (the size of an entry in pagemap file)
   file_offset = virt_addr / getpagesize() * PAGEMAP_ENTRY;
   printf("Vaddr: 0x%lx\nPage_size: %d\nEntry_size: %d\n", virt_addr, getpagesize(), PAGEMAP_ENTRY);
   printf("Reading %s at 0x%llx\n", path_buf, (unsigned long long)file_offset);
   status = fseek(f, file_offset, SEEK_SET);
   if (status) {
      perror("Failed to do fseek!");
      return -1;
   }
   errno = 0;
   read_val = 0;
   unsigned char c_buf[PAGEMAP_ENTRY];
   for(i=0; i < PAGEMAP_ENTRY; i++){
      c = getc(f);
      if(c==EOF){
         printf("\nReached end of the file\n");
         return 0;
      }
      if(is_bigendian())
           c_buf[i] = c;
      else
           c_buf[PAGEMAP_ENTRY - i - 1] = c;
      printf("PTE[%d]in hex  0x%llx\n ", i, c);
   }
   for(i=0; i < PAGEMAP_ENTRY; i++){
     // printf("ghsvf%d\n ",c_buf[i]);
      read_val = (read_val << 8) + c_buf[i];
   }
   printf("\n");
   printf("Result: Physical Adrr in Hex  0x%llX\n", (unsigned long long) read_val);
      printf("Result: Physical Adrr in Decimal  %lld\n", (signed long long) read_val);
   //if(GET_BIT(read_val, 63))
   if(GET_BIT(read_val, 63))
      printf("PFN in hex: 0x%lld\n",(unsigned long long) GET_PFN(read_val));
   else
      printf("Page not present\n");
   if(GET_BIT(read_val, 62))
      printf("Page swapped\n");
   fclose(f);
   return 0;
}

int main(int argc, char ** argv){
   

   if (argc != 3) {
      printf("Argument number is not correct!\n pagemap PID VIRTUAL_ADDRESS\n");
      return -1;
   }
   if (!memcmp(argv[1], "self", sizeof("self"))) {
      sprintf(path_buf, "/proc/self/pagemap");
      pid = -1;
   } else {
      pid = strtol(argv[1],&end, 10);
      if (end == argv[1] || *end != '\0' || pid<=0) {
         printf("PID must be a positive number or 'self'\n");
         return -1;
      }
   }
   virt_addr = strtol(argv[2], NULL, 16);
   if (pid!=-1)
      sprintf(path_buf, "/proc/%u/pagemap", pid);

   read_pagemap(path_buf, virt_addr);
   return 0;
}


