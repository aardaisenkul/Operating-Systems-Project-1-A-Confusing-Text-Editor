#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <zconf.h>

#define FALSE    0
#define TRUE    1
#define num_threads 10
int Thread_num = 0;
struct InpStruct {
    char *Fonksiyon;
    char *Degistirilecek;
    char *Aranicak;
    char *BeforeAfter;
    int   print;
    char *outFile;
    char *inputFile;
    int counterOrNot;
    int input_number;
    int start;
    int end;
    int threaded_or_not;
}anaStruc;

int Search_in_File(char *str,char *fname,int cOrNot,char *outFile,int print) {

    FILE *fp;
    FILE *fOut;
    int index;
    char *pos;
    int line_num = 1;
    int find_result = 0;
    char temp[512];
    char temp2[512];
    //gcc users
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    if(!print){
        fOut = fopen(outFile, "w");
    }


    while(fgets(temp, 512, fp) != NULL) {
        index=0;
        if((strstr(temp, str)) != NULL) {
            strcpy(temp2,temp);
            // printf("A match found on line: %d\n", line_num);
            if(print){
                printf("%s", temp);
            } else{
                //file a yaz
                fprintf(fOut,"%s",temp);
            }
            if(cOrNot){
                while ((pos = strstr(temp + index, str)) != NULL)
                {
                    index = (pos - temp) + 1;

                    find_result++;
                }
            }


        }
        line_num++;
    }

    if(find_result == 0 && cOrNot) {
        if(print){
            printf("\nSorry, couldn't find a match.\n");
        } else{
            fputs("\nSorry, couldn't find a match.\n", fOut);
        }
    }
    if(cOrNot){
        if(print){
            printf("\nThe word %s has been found %d times",str,find_result);
        } else{
            //file a yaz
            fprintf(fOut, "\nThe word %s has been found %d times.", str,find_result);
        }

    }
    //Close the file if still open.
    if(fp) {
        fclose(fp);
    }
    if(!print){
        fclose(fOut);
    }

    return(0);
}
int countWords(char *str)
{
    int state = FALSE;
    unsigned wc = 0;  // word count

    // Scan all characters one by one
    while (*str)
    {
        // If next character is a separator, set the
        // state as OUT
        if (*str == ' ' || *str == '\t')
            state = FALSE;

        else if (state == FALSE)
        {
            state = TRUE;
            ++wc;
        }

        // Move to next character
        ++str;
    }

    return wc;
}
void replaceAll(const char *oldWord, const char *newWord,char *fname,int cOrNot,char *outFile,int print)
{

    FILE * fp;
    FILE * fOut;
    char buffer[512];
    char *pos, temp[512];
    int index = 0;
    int owlen = strlen(oldWord);
    int count =0;



    /*  Open all required files */
    fp  = fopen(fname, "r");
    if(!print){
        fOut = fopen(outFile, "w");
    }


    if (fp == NULL )
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    /* fopen() return NULL if unable to open file in given mode. */
    /*
     * Read line from source file and write to destination
     * file after replacing given word.
     */

    while ((fgets(buffer,1000, fp)) != NULL)
    {

        // Replace all occurrence of word from current line
        while ((pos = strstr(buffer, oldWord)) != NULL)
        {

            // Bakup current line
            strcpy(temp, buffer);

            // Index of current found word
            index = pos - buffer;

            // Terminate str after word found index
            buffer[index] = '\0';

            // Concatenate str with new word
            strcat(buffer, newWord);

            // Concatenate str with remaining words after
            // oldword found index.
            strcat(buffer, temp + index + owlen);
            count++;
        }

        // After replacing write it to temp file.
        if(print){
            printf("%s",buffer);
        }else{
            fputs(buffer, fOut);
        }

    }


    /* Close all files to release resource */
    fclose(fp);

    if(cOrNot){
        if(print){
            printf("\nNumber of changed words: %d",count);
        }else{
            fprintf(fOut,"\nNumber of changed words: %d",count );
        }

    }
    if(!print){
        fclose(fOut);
    }

    /*
     * Repeat till all occurrences are replaced.
     */

}
int lineCount(char *fname){
    FILE *fp;
    int count = 0;
    char temp[512];
    char c;

    //gcc users
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    while ((fgets(temp,1000, fp)) != NULL)
    {
        count+=1;
    }
    if(fp) {
        fclose(fp);
    }
    return(count);
}
void split(int splitNum,char *fname,char *outFile,int print){
    FILE *fp;
    FILE *fOut;
    char temp[512];
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return;
    }
    if(!print){
        fOut = fopen(outFile, "w");
    }
    while ((fgets(temp,1000, fp)) != NULL)
    {
        for (int i = 0; i< strlen(temp); i++)
        {
            if ((i % splitNum)== 0){
                if(print){
                    printf("\n");
                }
                else{
                    fputs("\n",fOut);
                }

            }
            if(print){
                printf("%c", temp[i]);
            }
            else{
                fprintf(fOut,"%c",temp[i]);
            }

        }
    }
    if(fp) {
        fclose(fp);
    }
    if(!print){
        fclose(fOut);
    }
}
void headTailMid(char *type,int start,int end, char *fname,char *outFile,int print){
    FILE *fp;
    FILE *fOut;
    int lCount = lineCount(fname);
    char temp[512];
    int current =1;

    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return;
    }
    if(!print){
        fOut = fopen(outFile, "w");
    }
    if(strcmp(type,"tail")==0){

        if(lCount>=start){

            while ((fgets(temp,1000, fp)) != NULL)
            {
                if(current >lCount-start){
                    if(print){
                        printf("%s", temp);
                    }
                    else{
                        fputs(temp,fOut);
                    }

                }
                current +=1;
            }

        } else{
            printf("Value is greater than line number in file.");
        }

    }
    else if(strcmp(type,"head")==0){
        if(lCount>=start) {
            for (int i = 0; i < start; i++) {
                (fgets(temp, 1000, fp));
                if(print){
                    printf("%s", temp);
                }
                else{
                    fputs(temp,fOut);
                }
            }
        }
        else{
            printf("Value is greater than line number in file.");
        }
    }
    else{
        if(lCount>=end && start<end && start<=lCount){

            while ((fgets(temp,1000, fp)) != NULL)
            {
                if(current >=start&&current<=end){
                    if(print){
                        printf("%s", temp);
                    }
                    else{
                        fputs(temp,fOut);
                    }
                }
                current +=1;
            }

        } else{
            printf("One of the value is greater than line number in file.");
        }
    }

    if(fp) {
        fclose(fp);
    }
    if(!print){
        fclose(fOut);
    }
}
void insert(const char *insertedWord, int keyCount,const char *afterBefore,const char *targetKeyword,char *fname,char *outFile,int print)
{//<insertedkeyword> [-c] <-a OR -b> <targetkeyword> <inFile>

    FILE * fp;
    FILE * fOut;
    char buffer[512];
    char *pos, temp[512];

    int index = 0;
    int tlen = strlen(targetKeyword);
    int ilen = strlen(insertedWord);
    int count =0;

    /*  Open all required files */
    fp  = fopen(fname, "r");

    if(!print){
        fOut = fopen(outFile, "w");
    }

    if (fp == NULL )
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return;
    }
    /* fopen() return NULL if unable to open file in given mode. */
    /*
     * Read line from source file and write to destination
     * file after replacing given word.
     */

    while ((fgets(buffer,1000, fp)) != NULL)
    {
        char orgin[512] ="";
        // Replace all occurrence of word from current line
        while ((pos = strstr(buffer, targetKeyword)) != NULL)
        {
            int i = 0;
            // Bakup current line
            strcpy(temp, buffer);

            // Index of current found word
            index = pos - buffer;

            // Terminate str after word found index
            buffer[index] = '\0';
            if(strcmp(afterBefore,"-a")==0){
                strcat(buffer, targetKeyword);
                strcat(buffer, " ");
                strcat(buffer, insertedWord);
            }
            else if(strcmp(afterBefore,"-b")==0){
                strcat(buffer, insertedWord);
                strcat(buffer, " ");
                strcat(buffer, targetKeyword);
            }
            // Concatenate str with new word
            // Concatenate str with remaining words after
            // oldword found index.
            strcat(orgin,buffer);
            while(buffer[i]!='\0'){
                buffer[i]='\0';
                i++;
            }
            strcat(buffer, temp + index + ilen+(tlen-ilen));
            count++;
        }
        strcat(orgin,buffer);
        // After replacing write it to temp file.
        //burada o functionunda olcak
        if(print){
            printf("%s",orgin);
        }else{
            fputs(orgin,fOut);
        }


        // fputs(buffer, fTemp);
    }

    if(keyCount){
        if(print){
            printf("\nNumber of changed words: %d",count);
        }
        else{
            fprintf(fOut,"\nNumber of changed words: %d",count);
        }
    }
    /* Close all files to release resource */
    fclose(fp);
    if(!print){
        fclose(fOut);
    }
}
void funcCall(struct InpStruct *cmd){
    if(strcmp(cmd->Fonksiyon,"search")==0){
        Search_in_File(cmd->Aranicak,cmd->inputFile,cmd->counterOrNot,cmd->outFile,cmd->print);
        //search çağır
    }else if(strcmp(cmd->Fonksiyon,"replace")==0){
        replaceAll(cmd->Aranicak,cmd->Degistirilecek,cmd->inputFile,cmd->counterOrNot,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"insert")==0){
        insert(cmd->Degistirilecek,cmd->counterOrNot,cmd->BeforeAfter,cmd->Aranicak,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"lineCount")==0){
        printf("%d lines in file",lineCount(cmd->inputFile));
    }else if(strcmp(cmd->Fonksiyon,"split")==0){
        split(cmd->input_number,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"head")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"tail")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"mid")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else{printf("Wrong command!\n");}
}
void nonThread(char *string,char*file){
    struct InpStruct* cmd = &anaStruc;
    int num = 0;
    char string1[512];
    strcpy(string1,string);
    cmd->inputFile = file;
    char *split_input[50];
    for (int k = 0; k < 50; k++) {
        split_input[k] = (char *)malloc(100* sizeof(char));
    }


    char *split= strtok(string," ");
    while (split != NULL){
        split_input[num++] = split;
        split = strtok (NULL, " ");
    }
    if (split_input[0] != NULL) {
        if (strcmp(split_input[0], "search") == 0) {
            cmd->Fonksiyon = split_input[0] ;
            cmd->Aranicak = split_input[1];
           // cmd->inputFile = "file3.txt";//değişecek
            if(strstr(string1,"-c")){//count varsa
                cmd->counterOrNot =1;
                if(strstr(string1,">")){//out varsa
                    cmd->print =0;
                    cmd->outFile = split_input[4];

                    funcCall(cmd);
                    //search arda -c > beng.txt file3.txt
                }
                else{
                    cmd->print=1;
                    funcCall(cmd);
                    // search arda -c file3.txt
                }
            }
            else{//count yoksa
                cmd->counterOrNot =0;
                if(strstr(string1,">")){//out varsa
                    cmd->outFile = split_input[3];
                    cmd->print =0;
                    funcCall(cmd);
                }
                else{//out ve count yoksa
                    cmd->print =1;
                    funcCall(cmd);
                }
            }
        }
        else  if (strcmp(split_input[0], "replace") == 0) {

            cmd->Fonksiyon = split_input[0] ;
            cmd->Aranicak = split_input[1];
            cmd->Degistirilecek = split_input[2];
          //  cmd->inputFile = "file3.txt";//değişecek
            if(strstr(string1,"-c")){//count varsa
                cmd->counterOrNot =1;
                if(strstr(string1,">")){//out varsa
                    cmd->print =0;
                    cmd->outFile = split_input[5];
                    funcCall(cmd);

                }
                else{
                    cmd->print=1;
                    funcCall(cmd);

                }
            }
            else{//count yoksa
                cmd->counterOrNot =0;
                if(strstr(string1,">")){//out varsa
                    cmd->outFile = split_input[4];
                    cmd->print =0;
                    funcCall(cmd);
                }
                else{//out ve count yoksa
                    cmd->print =1;
                    funcCall(cmd);
                }
            }
        }
        else  if (strcmp(split_input[0], "insert") == 0) {
            if(strstr(string1,"-a")){
                cmd->BeforeAfter ="-a";
            } else if (strstr(string1,"-b")){
                cmd->BeforeAfter ="-b";
            }
            cmd->Fonksiyon = split_input[0] ;
            cmd->Degistirilecek = split_input[1];
          //  cmd->inputFile = "file3.txt";//değişecek
            if(strstr(string1,"-c")){//count varsa
                cmd->counterOrNot =1;
                if(strstr(string1,">")){//out varsa
                    // insert arda -c -a terrible > beng.txt pigs.txt
                    cmd->Aranicak = split_input[4];
                    cmd->print =0;
                    cmd->outFile = split_input[6];
                    funcCall(cmd);

                }
                else{
                    cmd->Aranicak = split_input[4];
                    cmd->print=1;
                    funcCall(cmd);

                }
            }
            else{//count yoksa
                cmd->counterOrNot =0;
                cmd->Aranicak = split_input[3];
                if(strstr(string1,">")){//out varsa
                    cmd->outFile = split_input[5];
                    cmd->print =0;
                    funcCall(cmd);
                }
                else{//out ve count yoksa
                    cmd->print =1;
                    funcCall(cmd);
                }
            }
        }
        else if (strcmp(split_input[0], "split") == 0) {
            cmd->Fonksiyon = split_input[0] ;
            cmd->input_number = atoi(split_input[1]);
      //      cmd->inputFile = "file3.txt";//değişecek
            //split 30 > beng.txt pigs.txt

            if(strstr(string1,">")){//out varsa
                cmd->outFile = split_input[3];
                cmd->print =0;
                funcCall(cmd);
            }
            else{//out ve count yoksa
                cmd->print =1;
                funcCall(cmd);
            }
        }


        else if (strcmp(split_input[0], "lineCount") == 0) {
            cmd->Fonksiyon = split_input[0] ;
       //     cmd->inputFile = "file3.txt";//değişecek
            cmd->print =1;
            funcCall(cmd);

        }

        else if (strcmp(split_input[0], "head") == 0) {
            cmd->Fonksiyon = split_input[0] ;
            cmd->start = atoi(split_input[1]);
        //    cmd->inputFile = "file3.txt";//değişecek
            //split 30 > beng.txt pigs.txt

            if(strstr(string1,">")){//out varsa
                cmd->outFile = split_input[3];
                cmd->print =0;
                funcCall(cmd);
            }
            else{//out ve count yoksa
                cmd->print =1;
                funcCall(cmd);
            }
        }
        else if (strcmp(split_input[0], "tail") == 0) {
            cmd->Fonksiyon = split_input[0] ;
            cmd->start = atoi(split_input[1]);
         //   cmd->inputFile = "file3.txt";//değişecek
            //split 30 > beng.txt pigs.txt

            if(strstr(string1,">")){//out varsa
                cmd->outFile = split_input[3];
                cmd->print =0;
                funcCall(cmd);
            }
            else{//out ve count yoksa
                cmd->print =1;
                funcCall(cmd);
            }
        }

        else if (strcmp(split_input[0], "mid") == 0) {
            cmd->Fonksiyon = split_input[0] ;
            cmd->start = atoi(split_input[1]);
            cmd->end = atoi(split_input[2]);
    //        cmd->inputFile = "file3.txt";//değişecek


            if(strstr(string1,">")){//out varsa
                cmd->outFile = split_input[4];
                cmd->print =0;
                funcCall(cmd);
            }
            else{//out ve count yoksa
                cmd->print =1;
                funcCall(cmd);
            }
        }
        else {
            printf("A command does not exist or cannot be executed.");
        }
    }

    else{
        printf("Empty command!");
        exit(0);
    }

}



void waitThread(){
    while(Thread_num){
        usleep(100);
    }
}

int main() {

    int num =0;
    char *arr[200];
    char file[50];
    char arda[200] ;
    char arda1[200];
    for(;;) {
        gets(arda);
        if (strcmp(arda, "quit") == 0) {
            waitThread();
            exit(0);
        }
        strcpy(arda1, arda);
        char *token1 = strtok(arda1, " ");
        pthread_t tid = (pthread_t)calloc(15,sizeof(pthread_t));
        while (token1 != NULL) {
            arr[num++] = token1;
            token1 = strtok(NULL, " ");
        }
        strcpy(file, arr[num - 1]);
        char string[512] = "";
        for (int i = 0; arda[i] != '\0'; i++) {

            if (arda[i] == ';' || arda[i] == ':') {
                if (arda[i] == ';') {
                    nonThread(string, file);
                    strcpy(string, "");
                } else if (arda[i] == ':') {
                    nonThread(string, file);
                    strcpy(string, "");
                }
            } else {
                if (arda[i + 1] == ':' || arda[i - 1] == ':' || arda[i + 1] == ';' || arda[i - 1] == ';') {
                } else {
                    strncat(string, &arda[i], 1);
                }
            }
            if (arda[i + 1] == '\0') {
                nonThread(string, file);
            }
        }
    }
}