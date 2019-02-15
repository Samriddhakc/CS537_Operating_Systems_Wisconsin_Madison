#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include<string.h>

char* strings[100];
int counter=0;
void change_working_dir(char*dir_name)
{

  //For changing directory using to build the cd utility for wish shell

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

void print_history(char* n)
{

  if(atoi(n)>counter){
    printf("Invalid Input!");
  }

  else {

  for (int i = counter-atoi(n);i<counter;i++) {
    printf("%s",strings[i]);
  }

  }


}

void store_history(char*character)
{

  strings[counter]=malloc(strlen(character)+1);
  strcpy(strings[counter],character);
  counter=counter+1;

}


void view_working_dir()
{

//For viewing which directory the program belongs to to build the pwd utility for wish shell

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

      printf("wish> ");
      getline(&buffer,&buffer_size,stdin);
      store_history(buffer);
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

      if (strcmp(my_argv[0],"cd\n")==0){
          printf("wish> Missing arguments\n");
        }

      else if (strcmp(my_argv[0],"cd")==0){
        if(my_argv[2]!=NULL)
        {
          printf("wish> More than one arguments!\n");
        }
        change_working_dir(my_argv[1]);
        //store_history("cd");
      }
      else if (strcmp(my_argv[0],"pwd\n")==0){
        view_working_dir();
      }
      else if (strcmp(my_argv[0],"history\n")==0)
      {
      char count_char[20];
      sprintf(count_char, "%d",counter);
      print_history(count_char);
      }
      else if (strcmp(my_argv[0],"history")==0){
        //store_history("history");
        if (my_argv[1]!=NULL)
        {
        print_history(my_argv[1]);
       }
      }
      else if (strcmp(my_argv[0],"ls\n")==0){
         //store_history("ls");
         int rc=fork();
         if (rc==0)
         {
           char*my_argv_1[10];
           my_argv_1[0]="/bin/ls";
           my_argv_1[2]=NULL;
           int exec_rc=execv("/bin/ls",my_argv_1); //completes replaces the code base by a different process
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
      char curr_array[100]={0};
      char*current_line=curr_array;
      size_t buffer_size=99;
      FILE*fp=fopen(argv[1],"r");
      if (fp==NULL){
          printf("cannot open file\n");
          exit(1);
        }

      while(fgets(current_line,buffer_size,fp)!=NULL && (strcmp(current_line,"exit")!=0))
      {
        char*varb=strtok(current_line," ");
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
         store_history("cd");
        }

        else if (strcmp(my_argv[0],"pwd\n")==0){
         view_working_dir();
        }

        else if (strcmp(my_argv[0],"history")==0){
         store_history("history");
         if (my_argv[1]!=NULL)
         {
         print_history(my_argv[1]);
        }

        }

        else if (strcmp(my_argv[0],"ls\n")==0){
          store_history("ls");
          int rc=fork();
          if (rc==0)
          {
            char*my_argv_1[10];
            my_argv_1[0]="/bin/ls";
            my_argv_1[2]=NULL;
            int exec_rc=execv("/bin/ls",my_argv_1); //completes replaces the code base by a different process
          }
          else
          {
          int wait_rc=wait(NULL);
          }
        }

      }
    }

   //malloc variables freed from heap
   for (int i = 0;i<counter;i++) {
       free(strings[i]);
   }

   return 0;
}
