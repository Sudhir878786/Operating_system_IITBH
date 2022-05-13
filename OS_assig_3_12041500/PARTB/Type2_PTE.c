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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
	This maps a 6-bit Virtual Page Number (requested by process) to a
	14-bit Physical Frame Number. This PFN added to the offset will give
	the Physical Address
*/

struct PageTableEntry{
	unsigned int pfn : 14;	// Physical Frame Number
	unsigned int offset : 10; // offset
	unsigned int valid : 1;	// Valid
	unsigned int present : 1;	// Present
	unsigned int protect : 3;	// Protect 01R, 10W, 11X
	unsigned int dirty : 1;	// Dirty
	unsigned int supervisor : 1;	// User/Kernel
};

#define PAGES 64 // This comes from Calculations - (1)

int bin2dec(unsigned long long int num){
	int dec = 0;

	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;

		dec += last_digit * base;

		base = base * 2;
	}

	return dec;
}

long long dec2bin(int num){
	long long binaryNumber = 0;

	int remainder;
	int i = 1;

	while (num!=0){
		remainder = num % 2;
		num /= 2;
		binaryNumber += remainder * i;
		i *= 10;
	}

	return binaryNumber;
}

int initPageTable(struct PageTableEntry *PTE){

	srand(time(NULL));
	PTE[0].pfn = rand() % 16384;
	PTE[0].valid = rand() % 2;
	PTE[0].present = rand() % 2;
	PTE[0].protect = rand() % 4;
	PTE[0].dirty = rand() % 2;
	PTE[0].supervisor = rand() % 2;

	for (int i = 1; i < PAGES; ++i){
		srand(time(NULL));

		int validPFN_Flag = 0;

		while (!validPFN_Flag){
			PTE[i].pfn = rand() % 16384;

			for (int j = 0; j < i; ++j){
				if (PTE[i].pfn == PTE[j].pfn){
					validPFN_Flag = 0;
					break;
				} else{
					validPFN_Flag = 1;
					PTE[i].valid = rand() % 2;
					PTE[i].present = rand() % 2;
					PTE[i].protect = rand() % 4;
					PTE[i].dirty = rand() % 2;
					PTE[i].supervisor = rand() % 2;

					sleep(rand()%100 * 0.001);
				}
			}
		}
	}

	return 1;
}

int get_VPN(long int request){
	int mask = 0xFC00; // [(111111)-0000000000]

	int VPN = (request & mask) >> 10;

	return VPN;
}

int get_Offset(long int request){
	int mask = 0x3FF; // [(000000)-1111111111]

	return (request & mask);
}

struct PageTableEntry AccessMemory(long int request, struct PageTableEntry *PTE){
	int VPN = get_VPN(request);

	int offset = get_Offset(request);

	PTE[VPN].offset = offset;

	return (PTE[VPN]);
}


int main(int argc, char *argv[]){
	struct PageTableEntry PTE[PAGES]; // 64 pages per process

	initPageTable(PTE);

	for (int i = 0; i < PAGES; ++i){
		printf("PAGE NUMBER %d\n", i);
		printf("\tPFN %d\n", PTE[i].pfn);
		printf("\tvalid %d\n", PTE[i].valid);
		printf("\tpage present %d\n", PTE[i].present);
		printf("\tpage swapped %d\n", PTE[i].protect);
		printf("\tis soft-dirty %d\n", PTE[i].dirty);
		printf("\tpage is file-page or shared-anon %d\n", PTE[i].supervisor);
	}

	int request;

	// Enter Request HERE
	printf("\nEnter an Virtual address :\t");
	scanf("%x", &request);

	struct PageTableEntry Req_PTE = AccessMemory(request, PTE);


	int physical_address = Req_PTE.pfn * 1024 + Req_PTE.offset;

	printf("\nPhysical Address: in Hex\t%llx\n", physical_address);
	printf("\nPhysical Address: in Decimal\t%lld\n", physical_address);

	return 0;
}
