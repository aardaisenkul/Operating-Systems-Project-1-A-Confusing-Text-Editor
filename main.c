#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE    0
#define TRUE    1

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
    int correct_or_not;
};

int Search_in_File(char *str,char *fname,int cOrNot,char *outFile,int print) {

    FILE *fp;
    FILE *fOut;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    //gcc users
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    if(!print){
        fOut = fopen(outFile, "w");
    }


    while(fgets(temp, 512, fp) != NULL) {
        if((strstr(temp, str)) != NULL) {
            // printf("A match found on line: %d\n", line_num);
            if(print){
                printf("\n%s\n", temp);
            } else{
             //file a yaz
                fprintf(fOut,"\n%s\n",temp);
            }
            find_result++;
        }
        line_num++;
    }

    if(find_result == 0) {
        if(print){
            printf("\nSorry, couldn't find a match.\n");
        } else{
            fputs("\nSorry, couldn't find a match.\n", fOut);
        }
    }
    if(cOrNot){
        if(print){
            printf("%s has been found %d times",str,find_result);
        } else{
            //file a yaz
            fprintf(fOut, "%s has been found %d times.", str,find_result);
        }

    }
    //Close the file if still open.
    if(fp) {
        fclose(fp);
    }
    if(fOut){
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
int replaceAll(const char *oldWord, const char *newWord,char *fname,int cOrNot,char *outFile,int print)
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
    fclose(fOut);

    if(cOrNot){
        if(print){
            printf("\nNumber of changed words: %d",count);
        }else{
            fprintf(fOut,"\nNumber of changed words: %d",count );
        }

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
int split(int splitNum,char *fname,char *outFile,int print){
    FILE *fp;
    FILE *fOut;
    char temp[512];
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
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
    if(fOut){
        fclose(fOut);
    }
    return(0);
}
int headTailMid(char *type,int start,int end, char *fname,char *outFile,int print){
    FILE *fp;
    FILE *fOut;
    int lCount = lineCount(fname);
    char temp[512];
    int current =1;

    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    if(!print){
        fOut = fopen(outFile, "w");
    }
    if(strcmp(type,"tail")==0){

        if(lCount>=end){

            while ((fgets(temp,1000, fp)) != NULL)
            {
                if(current >lCount-end){
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
        if(lCount>=end) {
            for (int i = 0; i < end; i++) {
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
    if(fOut){
        fclose(fOut);
    }
    return(0);
}
int insert(const char *insertedWord, int keyCount,const char *afterBefore,const char *targetKeyword,char *fname,char *outFile,int print)
{//<insertedkeyword> [-c] <-a OR -b> <targetkeyword> <inFile>

    FILE * fp;
    FILE * fOut;
    char buffer[512];
    char *pos, temp[512];

    int index = 0;
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
        exit(EXIT_SUCCESS);
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
            strcat(buffer, temp + index + ilen-1);
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
    if(fOut){
        fclose(fOut);
    }
    return 0;
}

void funcCall(struct InpStruct *cmd){
    if(cmd->correct_or_not==0){
        printf("Wrong command!\n");
    }else if(strcmp(cmd->Fonksiyon,"search")==0){
        Search_in_File(cmd->Aranicak,cmd->inputFile,cmd->counterOrNot,cmd->outFile,cmd->print);
        //search çağır
    }else if(strcmp(cmd->Fonksiyon,"replace")==0){
        replaceAll(cmd->Aranicak,cmd->Degistirilecek,cmd->inputFile,cmd->counterOrNot,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"insert")==0){
        insert(cmd->Degistirilecek,cmd->counterOrNot,cmd->BeforeAfter,cmd->Aranicak,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"lineCount")==0){
        lineCount(cmd->inputFile);
    }else if(strcmp(cmd->Fonksiyon,"split")==0){
        split(cmd->input_number,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"head")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"tail")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else if(strcmp(cmd->Fonksiyon,"mid")==0){
        headTailMid(cmd->Fonksiyon,cmd->start,cmd->end,cmd->inputFile,cmd->outFile,cmd->print);
    }else{}
}
void nonThread(char *func,char*file){

}
void threaded(){

}
int main() {
    int nw;
    int i = 0;
    char *split_input[50];
    struct InpStruct *cmd;
    char string[512] = "insert amcik -c -b arda file3.txt";
    //gets(string);

    for (int j = 0; i < 20; i++) {
        split_input[j] = (char *)malloc(100* sizeof(char));
    }
    nw = countWords(string);
    printf("number of words %d\n", nw);
    split_input[i++] = strtok(string, " ");//method


    if (split_input[0] != NULL) {
        if (strcmp(split_input[0], "search") == 0) {
            cmd->Fonksiyon ="search";
            if(strstr(string,"-c")){//count varsa
                cmd->counterOrNot =1;
                if(strstr(string,">")){//out varsa
                    cmd->print =0;
                }
                else{
                   // search terrible -c pigs.txt
                }
            }
            else{//count yoksa
                if(strstr(string,">")){//out varsa
                    cmd->print =0;
                }
                else{//out ve count yoksa
                    if(nw==3){
                        funcCall(cmd);
                    }
                    //search terrible file3.txt
                }
            }
/*
            if (nw == 3) {
                Search_in_File(strtok(NULL, " "), strtok(NULL, " "), nw);
            } else if (nw == 4) {
                strcpy(split_input[i++], strtok(NULL, " "));
                strcpy(split_input[i++], strtok(NULL, " "));
                strcpy(split_input[i++], strtok(NULL, " "));
                Search_in_File(param1, param3, nw);
            } else {
                printf("An incorrect number of command line arguments to your program.");
                return (-1);
            }*/
        }
        else if (strcmp(split_input[0], "replace") == 0) {

            if (nw == 4) {
                strcpy(param1, strtok(NULL, " "));
                strcpy(param2, strtok(NULL, " "));
                strcpy(param3, strtok(NULL, " "));
                replaceAll(param1, param2, param3,nw);
            } else if (nw == 5) {
                strcpy(param1, strtok(NULL, " "));
                strcpy(param2, strtok(NULL, " "));
                strcpy(param3, strtok(NULL, " "));
                strcpy(param4, strtok(NULL, " "));
                replaceAll(param1,param2, param4,nw);
            } else {
                printf("An incorrect number of command line arguments to your program.");
                return (-1);
            }
        }
        else if (strcmp(split_input[0], "insert") == 0) {//<insertedkeyword> [-c] <-a OR -b> <targetkeyword> <inFile>
            if (nw == 5) {
                strcpy(param1, strtok(NULL, " "));//insertedkeyword
                strcpy(param2, strtok(NULL, " "));//a or b
                strcpy(param3, strtok(NULL, " "));//targetkeyword
                strcpy(param4, strtok(NULL, " "));//file
                insert(param1,FALSE, param2, param3,param4);
            } else if (nw == 6) {
                strcpy(param1, strtok(NULL, " "));//inserted
                strcpy(param2, strtok(NULL, " "));//c
                strcpy(param3, strtok(NULL, " "));//a or b
                strcpy(param4, strtok(NULL, " "));// target
                strcpy(param5, strtok(NULL, " "));//file
                insert(param1,TRUE,param3, param4,param5);
            } else {

                printf("An incorrect number of command line arguments to your program.");
                return (-1);
            }
        }
        else if (strcmp(split_input[0], "lineCount") == 0) {
            strcpy(param1, strtok(NULL, " "));
            printf("There are %d lines in the file.",lineCount(param1));
        }
        else if (strcmp(split_input[0], "split") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            split(atoi(param1),param2);
        }
        else if (strcmp(split_input[0], "head") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            headTailMid('h',1,atoi(param1),param2);
        }
        else if (strcmp(split_input[0], "tail") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            headTailMid('t',-1,atoi(param1),param2);
        }
        else if (strcmp(split_input[0], "mid") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            strcpy(param3, strtok(NULL, " "));
            headTailMid('m',atoi(param1),atoi(param2),param3);
        }
        else {
            printf("A command does not exist or cannot be executed.");
        }
    }

    else{
        printf("Empty command!");
        exit(0);
    }

//    if(argc < 3 || argc > 3) {
//        Usage(argv[0]);
//        exit(1);
//    }
    //Use system("cls") on windows
    //Use system("clear") on Unix/Linux
//    system("cls");
}