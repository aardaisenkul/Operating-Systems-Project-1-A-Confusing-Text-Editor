#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE    0
#define TRUE    1

int Search_in_File(char *str,char *fname,int numberofWords) {

    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    //gcc users
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }


    while(fgets(temp, 512, fp) != NULL) {
        if((strstr(temp, str)) != NULL) {
            // printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result++;
        }
        line_num++;
    }

    if(find_result == 0) {
        printf("\nSorry, couldn't find a match.\n");
    }
    if(numberofWords == 4){
        printf("%s has been found %d times",str,find_result);
    }
    //Close the file if still open.
    if(fp) {
        fclose(fp);
    }
    return(0);
}
int countWords(char *str)
{//insert amcik -a arda file3.txt
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
int replaceAll(const char *oldWord, const char *newWord,char *fname,int numberofWords)
{

    FILE * fp;
    FILE * fTemp;
    char buffer[512];
    char *pos, temp[512];
    int index = 0;
    int owlen = strlen(oldWord);
    int count =0;



    /*  Open all required files */
    fp  = fopen(fname, "r");
    fTemp = fopen("replace.tmp", "w");

    if (fp == NULL || fTemp == NULL)
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
        fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fp);
    fclose(fTemp);
    remove(fname);
    rename("replace.tmp", fname);
    if(numberofWords==5){
        printf("\nNumber of changed words: %d",count);
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
int split(int splitNum,char *fname){
    FILE *fp;
    char temp[512];
    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    while ((fgets(temp,1000, fp)) != NULL)
    {
        for (int i = 0; i< strlen(temp); i++)
        {
            if ((i % splitNum)== 0)
                printf("\n");
            printf("%c", temp[i]);
        }
    }
    if(fp) {
        fclose(fp);
    }
    return(0);
}
int headTailMid(char type,int start,int end, char *fname){
    FILE *fp;
    int lCount = lineCount(fname);
    char temp[512];
    int current =1;

    if((fp = fopen(fname, "r")) == NULL) {
        printf("A command with wrong input file specified.");
        return(-1);
    }
    if(type=='t'){

        if(lCount>=end){

            while ((fgets(temp,1000, fp)) != NULL)
            {
                    if(current >lCount-end){
                        printf("%s", temp);
                    }
                    current +=1;
            }

        } else{
            printf("Value is greater than line number in file.");
        }

    }
    else if(type=='h'){
        if(lCount>=end) {
            for (int i = 0; i < end; i++) {
                (fgets(temp, 1000, fp));
                printf("%s", temp);
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
                    printf("%s", temp);
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
    return(0);
}
int insert(const char *insertedWord, int keyCount,const char *afterBefore,const char *targetKeyword,char *fname)
{//<insertedkeyword> [-c] <-a OR -b> <targetkeyword> <inFile>

    FILE * fp;
    FILE * fTemp;
    char buffer[512];
    char *pos, temp[512],orgin[512];
    int index = 0;
    int tlen = strlen(targetKeyword);
    int ilen = strlen(insertedWord);
    int count =0;

    /*  Open all required files */
    fp  = fopen(fname, "r");
    //BURAYI >o da yapcam
    //fTemp = fopen("replace.tmp", "w");

    if (fp == NULL /*|| fTemp == NULL*/)
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
        while ((pos = strstr(buffer, targetKeyword)) != NULL)
        {

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
            if(strcmp(afterBefore,"-a")==0){
                strcat(buffer, temp + index + ilen-1);
            }
            else if(strcmp(afterBefore,"-b")==0){
                strcat(buffer, temp + index + ilen-1);
            }

            count++;
        }

        // After replacing write it to temp file.
        //burada o functionunda olcak
        printf("%s",buffer);
       // fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fp);
  //  fclose(fTemp);
  //  remove(fname);
  //  rename("replace.tmp", fname);
    if(keyCount){
        printf("\nNumber of changed words: %d",count);
    }


    /*
     * Repeat till all occurrences are replaced.
     */

}
int main() {
    int nw;

    char *method, param1[32], param2[32], param3[32], param4[32], param5[32], param6[32];

    char string[50] = "insert amcik -a arda file3.txt";

    nw = countWords(string);

    printf("number of words %d\n", nw);
    method = strtok(string, " ");//method


    if (method != NULL) {
        if (strcmp(method, "search") == 0) {

            if (nw == 3) {
                Search_in_File(strtok(NULL, " "), strtok(NULL, " "), nw);
            } else if (nw == 4) {
                strcpy(param1, strtok(NULL, " "));
                strcpy(param2, strtok(NULL, " "));
                strcpy(param3, strtok(NULL, " "));
                Search_in_File(param1, param3, nw);
            } else {
                printf("An incorrect number of command line arguments to your program.");
                return (-1);
            }
        }
        else if (strcmp(method, "replace") == 0) {

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
        else if (strcmp(method, "insert") == 0) {//<insertedkeyword> [-c] <-a OR -b> <targetkeyword> <inFile>
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
        else if (strcmp(method, "lineCount") == 0) {
        strcpy(param1, strtok(NULL, " "));
        printf("There are %d lines in the file.",lineCount(param1));
        }
        else if (strcmp(method, "split") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            split(atoi(param1),param2);
        }
        else if (strcmp(method, "head") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            headTailMid('h',1,atoi(param1),param2);
        }
        else if (strcmp(method, "tail") == 0) {
            strcpy(param1, strtok(NULL, " "));
            strcpy(param2, strtok(NULL, " "));
            headTailMid('t',-1,atoi(param1),param2);
        }
        else if (strcmp(method, "mid") == 0) {
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

