#include<stdio.h>
#include<string.h>

int main()
{ 
   char str_mem[100];
   char str_1_mem[100];
   char*str1=str_mem;
   strcpy(str1,"sam");
   strcat(str1," ");
   char*name="kc";
   strcat(str1,name);
   printf("%s\n",str1);
   return 0; 
}
