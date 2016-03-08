//Kyler Kiminki
//kkiminki
//cmps101
//Lex.c
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
   
   int count=0;
   FILE *inC, *out;
   char buffer[MAX_LEN];

   if(argc!=3){
      printf("Usage Error: Lex [inputFile] [outputFile]\n");
      exit(1);
   }

   inC = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if(inC==NULL){
      printf("Unable to read input file\n");
      exit(1);
   }
   if(out==NULL){
      printf("Unable to write to output file\n");
      exit(1);
   }

   char *inputFile[MAX_LEN];
   while(count < MAX_LEN){
      char *line = fgets(buffer, MAX_LEN, inC);
      if(line==NULL) break;
      line = strchr(buffer, '\n');
      if(line==NULL){
         line = '\0';
      }else{
         line = buffer;
      }
      char *linestr = malloc(sizeof(char *[MAX_LEN]));
      strcpy(linestr, line);
      inputFile[count] = linestr;
      count++;
   }
   fclose(inC);

   List L = newList();
   append(L, 0);
   moveFront(L);
   int i;
   for(i = 1; i < count; i++){
      moveFront(L);
      while(strcmp(inputFile[get(L)], inputFile[i]) < 0){
         moveNext(L);
         if(index(L)== -1) break;
      }
      if(index(L)== -1){
         append(L, i);
      }else{
         insertBefore(L, i);
      }
   }

   moveFront(L);
   while(index(L) != -1){
      fprintf(out, "%s",inputFile[get(L)]);
      moveNext(L);
   }
   fclose(out);
   clear(L);
   freeList(&L);
   for(i = 0; i<count; i++){
      free(inputFile[i]);
   }
}


