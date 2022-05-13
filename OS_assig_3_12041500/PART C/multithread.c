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
 //ll gcd(ll a, ll b){if (b == 0)return a;return gcd(b, a % b);} //__gcd 
// ll lcm(ll a, ll b){return (a/gcd(a,b)*b);}
// ll moduloMultiplication(ll a,ll b,ll mod){ll res = 0;a %= mod;while (b){if (b & 1)res = (res + a) % mod;b >>= 1;}return res;}
// ll powermod(ll x, ll y, ll p){ll res = 1;x = x % p;if (x == 0) return 0;while (y > 0){if (y & 1)res = (res*x) % p;y = y>>1;x = (x*x) % p;}return res;}
 
// bool isPrime(ll n){if(n<=1)return false;if(n<=3)return true;if(n%2==0||n%3==0)return false;for(int i=5;i*i<=n;i=i+6)if(n%i==0||n%(i+2)==0)return false;return true;}
// bool isPowerOfTwo(int n){if(n==0)return false;return (ceil(log2(n)) == floor(log2(n)));}
// bool isPerfectSquare(ll x){if (x >= 0) {ll sr = sqrt(x);return (sr * sr == x);}return false;}
 
// inline int two(int n) { return 1 << n; } 
// inline int test(int n, int b) { return (n>>b)&1; } 
// inline void set_bit(int & n, int b) { n |= two(b); } 
// inline void unset_bit(int & n, int b) { n &= ~two(b); } 
// inline int last_bit(int n) { return n & (-n); } 
// inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; } 
 
// template<class T> void chmax(T & a, const T & b) { a = max(a, b); } 
// template<class T> void chmin(T & a, const T & b) { a = min(a, b); } 
 
// const int MOD = 1e9+7;
// const int MX = 2e5+5;
// const ll INF = 1e18;
// const db PI = acos((db)-1);
// const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};   // for every grid problem
// tcT> bool ckmin(T& a, const T& b) {
//     return b < a ? a = b, 1 : 0; } // set a = min(a,b)
// tcT> bool ckmax(T& a, const T& b) {
//     return a < b ? a = b, 1 : 0; }
// tcT> void remDup(vector<T>& v) { // sort and remove duplicates
//     sort(all(v)); v.erase(unique(all(v)),end(v)); }
// // Some Codes Skipped
 
// inline namespace FileIO {
//     void setIn(str s) {freopen(s.c_str(),"r",stdin);}
//     void setOut(str s) {freopen(s.c_str(),"w",stdout);}
//     void setIO(str s = "") {
//         cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
//         // cin.exceptions(cin.failbit);
//         // throws exception when do smth illegal
//         // ex. try to read letter into int
//         if (sz(s)) setIn(s+".in"), setOut(s+".out");    // for old USACO
//     }
// }
 



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 #include <syscall.h>

int sum =0;
int num;
int numCount;
int max = -100000;
int min = 100000;
int i;
float avg;

void *avg_runner(int arr[])
{

int i;

for(i = 0; i < numCount; i++)
{
sum += arr[i];
avg = sum/numCount;
}
      //  printf("This is worker_thread #%ld\n", (long)arg);
pthread_exit(0);
}

void* min_runner(int arr[])
{

int i;

for(i = 0; i < numCount; i++)
{
if(i == 0)
{
min = arr[i];
}
else if (min > arr[i])
min = arr[i];
}

pthread_exit(0);
}

void* max_runner(int arr[],void *threadid)
{
long tid;
tid = (long)threadid;

int i;

for(i = 0; i < numCount; i++)
{

if(i ==0)
{
max = arr[i];
}
else if(max < arr[i])
max = arr[i];
}

pthread_exit(0);
}
int main(int argc, char **argv)
{
  
printf("This program finds the maximum, minimum, and average of a series of numbers.\n");
printf("How many numbers would you like to process?\n");
scanf("%d",&numCount);
int arr[numCount],i; //array declared to hold numbers
printf("Enter the numbers\n");
for(i=0;i<numCount;i++){ //reading array values in main itself
scanf("%d",&arr[i]);
}

pthread_attr_t attr;
pthread_attr_init(&attr);//creating threads
long long tiid = syscall(SYS_gettid);
pthread_t thread1=syscall(SYS_gettid);
pthread_t thread2=syscall(SYS_gettid);
pthread_t thread3=syscall(SYS_gettid);
pthread_t tid;



//int t1= printf("%d\n",thread1);



//printf("tid = %d\n", syscall(SYS_gettid));






long long tpid=getppid();  //thread parent id 


pthread_create(&thread1, &attr, avg_runner, arr); //threads callling
pthread_create(&thread2, &attr, min_runner, arr);
pthread_create(&thread3, &attr, max_runner, arr);


pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
pthread_join(thread3, NULL);

//printing results
printf("-----------------worker threads---------------------\n");
//printf("The averag value is: %f\n", avg , "there");

printf("The average value is: %f   and The thread id is: %i\n", avg, tiid);
printf("The minimum  value is: %d  and The thread id is: %i\n", min, tiid+1);
printf("The maximum value is: %d   and The thread id is: %i\n", max,tiid+2);
printf("-----------------parent threads----------------------\n");
printf("AVG: %f MIN: %d MAX: %d and process id is %d\n",avg,min,max,tiid-1);

printf("-----------------extra information------------------\n");

printf("before calling pthread_create getpid: %d getpthread_self: %lu tid:%lu\n",getpid(), pthread_self(), syscall(SYS_gettid));
return 0;
} /*end main*/
