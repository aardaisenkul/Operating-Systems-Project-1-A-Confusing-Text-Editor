#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    char *arda = "search arda file3.txt : search bengisu file3.txt ; search ardam file3.txt";
    char *ali[200];
    char *thread[200];
    int j = 0;
    int m = 0;
    int lastsemi = 0;
    char str[100];
    for (int i = 0; arda[i] != '\0'; i++) {

        if (arda[i] ==';' || arda[i]==':' ) {
            if(arda[i]==';'){
                printf("%s\n",str);
                ali[j] = str;
                str[0]='\0';
                lastsemi = i;
                j++;
                thread[m] ="threaded";
                m++;
            }
            else if(arda[i]==':'){
                printf("%s\n",str);
                ali[j] = str;
                str[0]='\0';
                lastsemi = i;
                j++;
                thread[m] ="nonthreaded";
                m++;
            }

        }
        else{
            if(arda[i+1]==':' || arda[i-1]==':'){

            }
            else if(arda[i+1]==';' || arda[i-1]==';'){

            }
            else{
                strncat(str,&arda[i],1);
            }


        }
        if(arda[i+1]=='\0'){
            ali[j] = str;
            thread[m]="nonthreaded";
        }

    }
    printf("%s",str);
    printf("\n%s",thread[2]);

    return 0;
}
