#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#define NUM_THREADS 512

void searchCommand (char *command, int count, char *fptr);
void replaceCommand (char *command, char *neword, int count, char *fptr, char *newptr);
void insertCommand (char *neword, int count, char *location, char *command, char *fptr, char *newptr);
void lineCountCommand (char *fptr);
void splitCommand (int count, char *fptr, char *newptr);
void headCommand (int linecount, char *fptr);
void tailCommand (int linecount, char *fptr);
void midCommand (int startline, int endline, char *fptr);
void mainfunc (char *com, char *file);

struct prompt {
    char *com[20];
    char *target[30];
    char *insert[30];
    char *count[4];
    char afterorbefore [2];
    int numone;
    int numtwo;
    char *file[50];
    char *newfile[50];

}Command;


void searchCommand (char *command, int count, char *fptr){

    char line[200], copyline[200], temp[200];
    int c = 0;
    FILE *fp;
    fp = fopen(fptr, "r");
    char *pos;
    int index = 0;
    int owlen;
    int c1 = 0;

    owlen = strlen(command);

    while (fgets(line, 200, fp) != NULL) /* read a line */ {
        c1 = c;
        strcpy(copyline,line);
        while(( pos = strstr(line,command))){
            c++;
            strcpy(temp, line);
            index = pos - line;
            line[index] = '\0';
            strcpy(line, " ");
            strcat(line, temp + index + owlen);
        } if (c > c1){
            fputs(copyline,stdout);
        }

    }

    if (count == 1) {
        unsigned int a = strlen(command);
        for (int i = 0; i<a; i++) {
            printf("%c", command[i]);
        }
        printf(" keyword has been found: %d times\n\n",c);
    }

    fclose(fp);
}

void replaceCommand (char *command, char *neword, int count, char *fptr, char *newptr){

    char line [200],line1 [200];
    int c = 0;
    FILE *fp;
    FILE *fp1;
    FILE *fTemp;
    fp = fopen(fptr, "r");
    fp1 = fopen(fptr, "r");

    if (strcmp(newptr, " ") != 0){
        fTemp = fopen(newptr, "w+");
        char *pos, temp[200];
        int index = 0;
        int owlen;
        owlen = strlen(command);
        int c1 = 0;

        while (fgets(line, 200, fp) != NULL) /* read a line */ {
                c1 = c;
            while(( pos = strstr(line,command))){
                c++;
                strcpy(temp, line); // Bakup current line
                index = pos - line; // Index of current found word
                line[index] = '\0'; // Terminate str after word found index
                strcat(line, neword); // Concatenate str with new word
                strcat(line, temp + index + owlen); // Concatenate str with remaining words after oldword found index.
            }
            if (c == c1) {
                fputs(line,fTemp);
            } else if (c > c1){
                fputs(line,stdout);
                fputs(line,fTemp);
            }
        }
        fclose(fTemp);

    } else if (strcmp(newptr, " ") == 0) {
        char *pos1, temp1[200];
        int index1 = 0;
        int owlen1;
        owlen1 = strlen(command);
        int c2 = 0;

        while (fgets(line1, 200, fp1) != NULL) /* read a line */ {
                c2 = c;
            while(( pos1 = strstr(line1,command))){
                c++;
                strcpy(temp1, line1); // Bakup current line
                index1 = pos1 - line1; // Index of current found word
                line1[index1] = '\0'; // Terminate str after word found index
                strcat(line1, neword); // Concatenate str with new word
                strcat(line1, temp1 + index1 + owlen1); // Concatenate str with remaining words after oldword found index.

            } if (c > c2){
                fputs(line1,stdout);
            }
        }

    }

    fclose(fp);
    fclose(fp1);

    if (count == 1) {
        unsigned int a = strlen(command);
        for (int i = 0; i<a; i++) {
            printf("%c", command[i]);
        }
        printf(" keyword has been found: %d times\n\n",c);
    }
}

void insertCommand (char *neword, int count, char *location, char *command, char *fptr, char *newptr) {

    char line [200], copyline[200], line1 [200], copyline1[200];
    char delim[] = " ";
    int c = 0;
    FILE *fp;
    FILE *fp1;
    FILE *fTemp;
    fp = fopen(fptr, "r");
    fp1 = fopen(fptr, "r");

    if (strcmp(newptr, " ") != 0){
        fTemp = fopen(newptr, "w+");
        char *pos, temp[200];
        int index = 0;
        int owlen;
        owlen = strlen(command);
        int owlen1;
        owlen1 = strlen(neword);
        int c1 = 0;

        if (strcmp(location, "-a") == 0) {
            while (fgets(line, 200, fp) != NULL) /* read a line */ {
                c1 = c;
                strcpy(copyline,line);
                while( (pos = strstr(copyline,command)) ){
                    c++;
                    strcpy(temp, copyline); //Bakup current linei
                    index = pos - copyline; // Index of current found word
                    index += owlen;
                    copyline[index] = '\0';
                    strcat(copyline, delim);
                    strcat(copyline, neword);
                    fputs(copyline, stdout);
                    fputs(copyline, fTemp);
                    memset(copyline,'\0', index + 1 + owlen1 + owlen1);
                    strcat(copyline, temp + index);
                } if (c > c1){
                    fputs(copyline, stdout);
                    fputs(copyline, fTemp);
                } else if (c == c1) {
                    fputs(line,fTemp);
                }
             }
        } else if (strcmp(location, "-b") == 0) {
            while (fgets(line, 200, fp) != NULL) /* read a line */ {
                c1 = c;
                strcpy(copyline,line);
                while(( pos = strstr(copyline,command))){
                    c++;
                    strcpy(temp, copyline); // Bakup current line
                    index = pos - copyline; // Index of current found word
                    copyline[index] = '\0';
                    strcat(copyline, neword);
                    strcat(copyline, delim);
                    strcat(copyline, command);
                    fputs(copyline, stdout);
                    fputs(copyline, fTemp);
                    memset(copyline,'\0', index + 1 + owlen1 + owlen1 + owlen);
                    strcat(copyline, temp + index + owlen);
                } if (c > c1){
                    fputs(copyline, stdout);
                    fputs(copyline, fTemp);
                 } else if (c == c1) {
                    fputs(line,fTemp);
                 }
            }
        }
        fclose(fTemp);

    } if (strcmp(newptr, " ") == 0){
        char *pos1, temp1[200];
        int index1 = 0;
        int owlen2;
        owlen2 = strlen(command);
        int owlen3;
        owlen3 = strlen(neword);
        int c2 = 0;

        if (strcmp(location, "-a") == 0) {
            while (fgets(line1, 200, fp1) != NULL) /* read a line */ {
                c2 = c;
                strcpy(copyline1,line1);
                while( (pos1 = strstr(copyline1,command)) ){
                    c++;
                    strcpy(temp1, copyline1); //Bakup current linei
                    index1 = pos1 - copyline1; // Index of current found word
                    index1 += owlen2;
                    copyline1[index1] = '\0';
                    strcat(copyline1, delim);
                    strcat(copyline1, neword);
                    fputs(copyline1, stdout);
                    memset(copyline1,'\0', index1 + 1 + owlen3 + owlen3);
                    strcat(copyline1, temp1 + index1);
                } if (c > c2){
                    fputs(copyline1, stdout);
                }
             }
        } else if (strcmp(location, "-b") == 0) {
            while (fgets(line1, 200, fp1) != NULL) /* read a line */ {
                c2 = c;
                strcpy(copyline1,line1);
                while(( pos1 = strstr(copyline1,command))){
                    c++;
                    strcpy(temp1, copyline1); // Bakup current line
                    index1 = pos1 - copyline1; // Index of current found word
                    copyline1[index1] = '\0';
                    strcat(copyline1, neword);
                    strcat(copyline1, delim);
                    strcat(copyline1, command);
                    fputs(copyline1, stdout);
                    fputs(copyline1, fTemp);
                    memset(copyline1,'\0', index1 + 1 + owlen3 + owlen3 + owlen2);
                    strcat(copyline1, temp1 + index1 + owlen2);
                } if (c > c2){
                    fputs(copyline1, stdout);
                 }
            }
        }
    }

    fclose(fp);
    fclose(fp1);

    if (count == 1) {
        unsigned int a = strlen(neword);
        for (int i = 0; i<a; i++) {
            printf("%c", neword[i]);
        }
        printf(" keyword has been found: %d times\n\n",c);
    }

}

void lineCountCommand (char *fptr){

    char line [200];
    int count_lines = 0;
    FILE *fp;
    fp = fopen(fptr, "r");

    while (fgets(line, 200, fp) != NULL) {
        fputs(line,stdout);
        count_lines++;
    }

    fclose(fp);

    printf("\nThere are %d lines\n\n", count_lines);


}

void splitCommand (int count, char *fptr, char *newptr){

    FILE *fp;
    FILE *fp1;
	FILE *ptr_writefile;
	FILE *son;
	int count_lines = 0;
	char linetxt [200];
	char line [count];

    fp = fopen(fptr, "r");
    fp1 = fopen(fptr, "r");

	if (strcmp(newptr, " ") != 0){
        ptr_writefile = fopen(newptr, "w+");

        while (fgets(line, sizeof line, fp) != NULL) {
            fprintf(ptr_writefile,"%s\n", line);
        }

        fclose(fp);
        fclose(ptr_writefile);

        son = fopen(newptr, "r");

        while (fgets(line, sizeof line, son) != NULL) {
            fputs(line,stdout);
        }
        puts("\n\n");

        fclose(son);


	} else if (strcmp(newptr, " ") == 0){

        while (fgets(line, sizeof line, fp1) != NULL) {
            fprintf(stdout,"%s\n", line);
        }

	    fclose(fp);
        puts("\n\n");

	}

}

void headCommand (int linecount, char *fptr){

    char line [200];
    int count_lines = 0;
    FILE *fp;
    fp = fopen(fptr, "r");

    while (fgets(line, 200, fp) != NULL) {
        count_lines++;
        if (count_lines <= linecount) {
            fputs(line,stdout);
        }
    }

    puts("\n\n");

    fclose(fp);

}

void tailCommand (int linecount, char *fptr){

    char line [200];
    char line1 [200];
    int count_lines = 0;
    int count_lines1 = 0;
    int lines = 0;
    FILE *fp;
    fp = fopen(fptr, "r");
    FILE *fp1;
    fp1 = fopen(fptr, "r");

    while (fgets(line, 200, fp) != NULL) {
        count_lines++;
    }

    lines = count_lines - linecount;

    while (fgets(line1, 200, fp1) != NULL) {
        count_lines1++;
        if (count_lines1 > lines) {
            fputs(line1,stdout);
        }
    }

    puts("\n\n");

    fclose(fp);
    fclose(fp1);
}

void midCommand (int startline, int endline, char *fptr) {

    char line [200];
    int count_lines = 0;
    FILE *fp;
    fp = fopen(fptr, "r");

    while (fgets(line, 200, fp) != NULL) {
        count_lines++;
        if (count_lines >= startline && count_lines <= endline) {
            fputs(line,stdout);
        }
    }

    puts("\n\n");

    fclose(fp);

}

void sequentially (char *com, char *file) {

    bool boolarr[2] = {true, false};

    char *tok[200];
    char delim[] = " ";
    int i = 0;
    int j = 0;
    int count = 0;
    int oneorzero;

    char *token = strtok(com, delim);
        while (token != NULL){
            tok[count++] = token;
            token = strtok (NULL, delim);
        }

    if (strcmp(tok[0], "search") == 0) {
        if (strcmp(tok[2], "-c") == 0) {
            oneorzero = boolarr[0];
            searchCommand(tok[1], oneorzero, file);
        } else if (strcmp(tok[2], "-c") != 0) {
            oneorzero = boolarr[1];
            searchCommand(tok[1], oneorzero, file);
        }

    } else if (strcmp(tok[0], "replace") == 0){
        if (strcmp(tok[3], "-c") == 0) {
            oneorzero = boolarr[0];
            if (strcmp(tok[4], ">") == 0){
                replaceCommand(tok[1], tok[2], oneorzero, file, tok[5]);
            } else {
                replaceCommand(tok[1], tok[2], oneorzero, file, " ");
            }
        } else if (strcmp(tok[3], "-c") != 0) {
            oneorzero = boolarr[1];
            if (strcmp(tok[3], ">") == 0){
                replaceCommand(tok[1], tok[2], oneorzero, file, tok[4]);
            } else {
                replaceCommand(tok[1], tok[2], oneorzero, file, " ");
            }
        }
    } else if (strcmp(tok[0], "insert") == 0) {
        if (strcmp(tok[2], "-c") == 0) {
            oneorzero = boolarr[0];
            if (strcmp(tok[5], ">") == 0){
                insertCommand(tok[1], oneorzero, tok[3], tok[4], file, tok[6]);
            } else {
                insertCommand(tok[1], oneorzero, tok[3], tok[4], file, " ");
            }
        } else if (strcmp(tok[2], "-c") != 0) {
            oneorzero = boolarr[1];
            if (strcmp(tok[4], ">") == 0){
                insertCommand(tok[1], oneorzero, tok[2], tok[3], file, tok[5]);
            } else {
                insertCommand(tok[1], oneorzero, tok[2], tok[3], file, " ");
            }
        }

    } else if (strcmp(tok[0], "lineCount") == 0) {
        lineCountCommand(file);

    } else if (strcmp(tok[0], "split") == 0) {
        if (strcmp(tok[2], ">") == 0){
            sscanf(tok[1], "%d", &i);
            splitCommand(i, file, tok[3]);
        } else {
            sscanf(tok[1], "%d", &i);
            splitCommand(i, file, " ");
        }

    } else if (strcmp(tok[0], "head") == 0) {
        sscanf(tok[1], "%d", &i);
        headCommand(i,file);

    } else if (strcmp(tok[0], "tail") == 0) {
        sscanf(tok[1], "%d", &i);
        tailCommand(i,file);

    } else if (strcmp(tok[0], "mid") == 0) {
        sscanf(tok[1], "%d", &i);
        sscanf(tok[2], "%d", &j);
        midCommand(i,j,file);

    }

}



int main() {

    struct prompt prompt;

    char command[200], command1[200], command2[200];
    char *tok[200], *tok1[200];
    char delim[] = " ";
    char point[] = ":";
    int count = 0;
    int count1 = 0;

    printf("prompt> ");
    gets(command);
    strcpy(command1, command);
    strcpy(command2, command);

    char *token1 = strtok(command1, delim);
            while (token1 != NULL){
                tok1[count1++] = token1;
                token1 = strtok (NULL, delim);
        }

        strcpy(prompt.file,tok1[count1-1]);
    if (strstr(command, " : ") || strstr(command, " : ")){


    }
    if (strstr(command, " : ")){
        if (strstr(command, " ; ")) {

        } else {
            char *token = strtok(command, point);
                while (token != NULL){
                    tok[count] = token;
                    token = strtok (NULL, point);
                    count++;
                }
                for (int a = 0; a<count ; a++) {
                sequentially(tok[a],prompt.file);
            }
        }

    } else if (strstr(command, " ; ")){
        printf("baaa");

    } else {
        sequentially(command2,prompt.file);
    }

    return 0;

}
