#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include<string.h>


void change_working_dir(char*dir_name)
{
char mem[100]={'\0'};
char*strng=mem;
char s[100];
strcpy(strng,getcwd(s, 100));
char*str="/";
strcat(strng,str);
strcat(strng,dir_name);
strng[strcspn(strng,"\n" )] = '\0';
chdir(strng);
}

void view_working_dir()
{
char s[100]; 
 printf("%s\n", getcwd(s, 100)); 
}

int main(int argc,char* argv[]){


    char inp[100];
    //char*buffer=inp;
    char *buffer = malloc(20*sizeof(inp));
    size_t buffer_size=32;
    char*st="exit\n";

    if(argc==1)
    {

     while(strcmp(buffer,"exit\n")!=0 && !feof(stdin))
     {  

      printf("wish>");
      getline(&buffer,&buffer_size,stdin);
      
      char*varb=strtok(buffer," ");
      char*my_argv[10];
      int i=0;
      while (varb!=NULL)
      {
       my_argv[i]=varb;
       varb=strtok(NULL," ");
       i=i+1;
      } 
      my_argv[i+1]=NULL;
      if (strcmp(my_argv[0],"cd")==0){
        change_working_dir(my_argv[1]); 
      } 
      else if (strcmp(my_argv[0],"pwd\n")==0){
        view_working_dir();
      } 
      else if (strcmp(my_argv[0],"ls\n")==0){
         int rc=fork();
         if (rc==0)
         {
           char*my_argv_1[10];
           my_argv_1[0]="/bin/ls";
           my_argv_1[2]=NULL;
           int exec_rc=execv("/bin/ls",my_argv_1);
         }
         else
         {
         int wait_rc=wait(NULL);
         } 
      }

    }
    free(buffer);
    } 

   else{ 
    /*read file from batch_script*/
   }

   return 0;
}
