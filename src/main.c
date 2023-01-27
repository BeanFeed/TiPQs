#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <debug.h>
#include <math.h>

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


void finalOut(int *p, int *q, char *res, int qSize, int pSize) {
    
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
                        oneAdded++;
                    } else {
                        sprintf(res, "%s, %s", res, buf);
                    }
                }
            } else {
                char buf[20];
                sprintf(buf,"%d/%d",p[j],q[i]);
                dbg_printf("P: %d, Q: %d, Num: %s\n", p[j], q[i], buf);
                if(strstr(res,buf) == NULL) {
                    sprintf(res,"%s, %s", res, buf);
                }
            }
        }
    }
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
    char pstr[5];
    os_GetStringInput("What is P: ", pstr, 5);
    p = strtod(pstr, NULL);
    os_SetCursorPos(1,0);

    //Get q input
    int q;
    char qstr[5];
    os_GetStringInput("What is Q: ", qstr, 5);
    q = strtod(qstr, NULL);

    //Get all factors of q and the amount of factors
    int factorsp[20];
    int psize;
    getFactors(p, factorsp, &psize);
    //dbg_printf("P: %d, P Size: %d\n",p, psize);

    //Get all factors of q and the amount of factors
    int factorsq[20];
    int qsize;
    getFactors(q, factorsq, &qsize);

    //Get p list as a string
    char strpl[20];
    ilstr(factorsp, strpl, psize);
    char out1[20];
    sprintf(out1, "p(%d)=%s",p,strpl);

    //Get q list as a string
    char strql[20];
    ilstr(factorsq, strql, qsize);
    char out2[20];
    sprintf(out2, "q(%d)=%s",q,strql);
    //dbg_printf("%s", out2);



    os_SetCursorPos(3,0);
    os_PutStrLine(out1);
    os_SetCursorPos(4,0);
    os_PutStrLine(out2);

    //Get all possible solutions
    char final[50];
    finalOut(factorsp, factorsq, final, qsize, psize);
    os_SetCursorPos(6,0);
    os_PutStrLine("All Possibilities:");
    os_SetCursorPos(7,0);
    os_PutStrLine(final);
    while(!os_GetCSC());
    return 0;
}
