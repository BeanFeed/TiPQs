#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <debug.h>
#include <math.h>
#include <ti/tokens.h>

char *str_replace(char *str, char rep, char with) {
    char *ptr = str;
    while ((ptr = strchr (ptr, rep)) != NULL) *ptr++ = with;
    return str;
}

void getFactors(int num, int *res, int *size) {
    int addedItems = 0;
    //size = &addedItems;
    //int temp[20];
    for (int i = 1; i <= num; i++)
    {
        //dbg_printf("loop: %d, Num: %d\n", i, num);
        if(fmod((float)num/ (float)i, 1.0) == 0) {
            res[addedItems] = i;
            //printf("i: %d, NumDiv: %d, res: %d\n", i, num / i, res[i]);
            addedItems++;
        }
    }
    *size = addedItems;
}


void finalOut(int *p, int *q, char *res, int qSize, int pSize, int *amount) {
    int count = 0;
    int oneAdded = 0;
    int i = 0, j = 0;

    for(i = 0; i < qSize; i++) {
        for(j = 0; j < pSize; j++) {
            if(fmod((float)p[j] / (float)q[i], 1.0) == 0) {
                char buf[20];
                int num = p[j] / q[i];
                dbg_printf("P: %d, Q: %d, Num: %d\n", p[j], q[i], num);
                sprintf(buf,"%d",num);
                
                if(strstr(res,buf) == NULL) {
                    if(oneAdded == 0) {
                        sprintf(res, "%s", buf);
                        count++;
                        oneAdded++;
                    } else {
                        sprintf(res, "%s, %s", res, buf);
                        count++;
                    }
                }
            } else {
                char buf[20];
                sprintf(buf,"%d/%d",p[j],q[i]);
                dbg_printf("P: %d, Q: %d, Num: %s\n", p[j], q[i], buf);
                if(strstr(res,buf) == NULL) {
                    sprintf(res,"%s, %s", res, buf);
                    count++;
                }
            }
        }
    }
    *amount = count;
}

void ilstr(int *list, char *res, int size) {
    //dbg_printf("list Size: %d\n", listSize);
    int oneAdded = 0;
    for(int i = 0; i < size; i++) {
        if(oneAdded == 0) {
            sprintf(res, "%d", list[i]);
            oneAdded++;
        } else {
            sprintf(res, "%s, %d", res, list[i]);
        }
    }
}

int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);

    //Get p input
    int p;
    char pstr[10];
    os_GetStringInput("What is P: ", pstr, 5);
    p = strtod(pstr, NULL);
    os_SetCursorPos(1,0);

    //Get q input
    int q;
    char qstr[10];
    os_GetStringInput("What is Q: ", qstr, 5);
    q = strtod(qstr, NULL);

    //Get all factors of q and the amount of factors
    int factorsp[30];
    int psize;
    getFactors(p, factorsp, &psize);
    dbg_printf("Checkpoint 1\n");

    //Get all factors of q and the amount of factors
    int factorsq[30];
    int qsize;
    getFactors(q, factorsq, &qsize);
    dbg_printf("Checkpoint 2\n");
    //Get p list as a string
    char strl[20];
    ilstr(factorsp, strl, psize);
    char out[50];
    sprintf(out, "p(%d)=%s",p,strl);
    dbg_printf("Checkpoint 3\n");
    os_SetCursorPos(3,0);
    os_PutStrFull(out);

    //Clear strl
    sprintf(strl, "");
    //Get q list as a string
    ilstr(factorsq, strl, qsize);

    sprintf(out, "q(%d)=%s",q,strl);
    dbg_printf("Checkpoint 4\n");
    os_SetCursorPos(3,0);
    os_PutStrFull(out);
    //dbg_printf("%s", out2);
    
    //Get all possible solutions
    //char final[50];
    int fullSize = 0;
    finalOut(factorsp, factorsq, out, qsize, psize, &fullSize);
    dbg_printf("Checkpoint 5\n");
    os_SetCursorPos(6,0);
    char si[22];
    sprintf(si, "All Possibilities: %d", fullSize);
    os_PutStrFull(si);
    os_SetCursorPos(7,0);
    os_PutStrFull(out);
    while(!os_GetCSC());
    return 0;
}