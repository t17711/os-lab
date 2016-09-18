#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <gmp.h> 

#define NEWZ(x) mpz_t x; mpz_init(x)  //Ceates and  initializes  x from gmp library
#define POW_VAL(x,y,z) mpz_ui_pow_ui(x,y,z) // sets x initialized gmp variable to y^z y and z unsigned ling int, uint_64 in c++
#define NEXTPRIME(x) mpz_nextprime(x,x) // sets gmp variable x to the next prime from x
#define NEXTPRIME2(x,y) mpz_nextprime(x,y) // sets gmp variable x to the next prime from y
#define IS_EQL(x,y)((mpz_cmp_ui(x,y)!=0)?(false):(true)) // sets 0 is equal, >0 if x>y, <0 if x<y

int main(void){
  NEWZ(prime1);
  NEWZ(prime2);
  NEWZ(sub_val);
  
  POW_VAL(prime1, uint64_t(2), uint64_t(64));
  gmp_printf("Start value 2^64 is %Zd\n", prime1);
  NEXTPRIME(prime1); // set prime to next prime of x
  int x = 0;
  uint64_t t = 2;
  
  while(true){
    if (x == 0){// alternatively find next prime of 1 and 2
      NEXTPRIME2(prime2,prime1); // prime2 is next prime of prime1
      mpz_sub(sub_val, prime2,prime1);
      x =1;
    }

    else{
      NEXTPRIME2(prime1,prime2);
      mpz_sub(sub_val, prime1,prime2); // prime1 is next prime of prime2
      x=0;
    }

    if(IS_EQL(sub_val,t)) { // if sub value is 2 then break
      gmp_printf("Pair prime after 2^64 are  %Zd and %Zd\n", prime1, prime2);
      break;
    }
    

      
  }


  

}

