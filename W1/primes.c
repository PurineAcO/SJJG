#include <stdio.h>
#include <math.h>

int main(){
    int num,sign;
    scanf("%d",&num);

    for(int i=2;i<(int) sqrt(num)+1;i++){
        sign=0;
        while(num%i==0){sign++;num/=i;}
        if(sign==1){printf("%d ",i);}
    }
    
    if(num!=1){printf("%d",num);}
    return 0;
}



// struct {int prime;int cnt;} primes[10000]={};

// int judgeprime(int n){
//     double pdsj=(int) sqrt(n)+1;
//     // int isprime=0;
//     for(int i=2;i<pdsj;i++){
//         if(i>5){if(i%2==0 || i%3==0 || i%5==0){continue;}}
//         if(n%i==0){return 0;}
//     }
//     return 1;
// }

// int main(){

//     int num;
//     scanf("%d",&num);

//     int primecnt=0;int lastprime=0;
//     while(judgeprime(num)==0){
//         for(int i=2;i<(int) sqrt(num)+1;i++){
//             if(i>5 && (i%2==0 || i%3==0 || i%5==0)){continue;}
//             if(judgeprime(i) && num%i==0){
//                 if(i!=lastprime){primecnt++;primes[primecnt].prime=i;}
//                 lastprime=i;primes[primecnt].cnt++;num/=i;
//                 break;
//             }
//         }
//     }
//     if(num!=lastprime){primecnt++;primes[primecnt].prime=num;primes[primecnt].cnt=1;}
//     else{primes[primecnt].cnt++;}

//     // for(int i=1;i<=primecnt;i++){
//     //     printf("%d %d\n",primes[i].prime,primes[i].cnt);
//     // }
//     // printf("%d",primecnt);

//     for(int i=1;i<=primecnt;i++){
//         if(primes[i].cnt==1){printf("%d ",primes[i].prime);}
//     }

//     return 0;
// }