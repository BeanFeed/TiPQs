#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <debug.h>
char *str_replace(char *str, char rep, char with) {
    char *ptr = str;
    while ((ptr = strchr (ptr, rep)) != NULL) *ptr++ = with;
    return str;
}

void * getFactors(int num) {
    int addedItems = 0;
    static int res[20];
    for (int i = 1; i <= num; i++)
    {
        //dbg_printf("loop: %d, Num: %d\n", i, num);
        if(i % 1 == 0) {
            res[addedItems] = i;
            //dbg_printf("res: %d\n", res[2]);
            addedItems++;
        }
    }
    return res;
}

void finalOut(int *p, int *q, char *res) {
    
    int oneAdded = 0;
    int i = 0, j = 0;
    int qSize = sizeof(q) - 1, pSize = sizeof(p) - 1;
    for(i = 0; i < qSize; i++) {
        for(j = 0; j < pSize; j++) {
            if((p[j] / q[i]) % 1 == 0) {
                char buf[20];
                int num = p[j] / q[i];
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
                if(strstr(res,buf) == NULL) {
                    sprintf(res,"%s, %s", res, buf);
                }
            }
        }
    }
}
void ilstr(int *list, char *res) {
    int listSize = sizeof(list);
    //dbg_printf("list Size: %d", listSize);
    int oneAdded = 0;
    for(int i = 0; i < listSize - 1; i++) {
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
    int p;
    char pstr[5];
    os_GetStringInput("What is P: ", pstr, 5);
    p = strtod(pstr, NULL);
    os_SetCursorPos(1,0);
    int q;
    char qstr[5];
    os_GetStringInput("What is Q: ", qstr, 5);
    q = strtod(qstr, NULL);
    int *factorsp;
    factorsp = getFactors(p);
    
    char out1[20];
    ilstr(factorsp, out1);
    free(factorsp);
    //dbg_printf("%s", out1);
    char out2[20];
    int *factorsq;
    factorsq = getFactors(q);
    ilstr(factorsq, out2);
    free(factorsq);
    dbg_printf("%s\n", out2);
    char outFull[50];
    //finalOut(factorsp, factorsq, outFull);
    os_SetCursorPos(1,0);
    //dbg_printf("%s\n", out1);
    char toOut1[20];
    sprintf(toOut1,"p(%d) = %s", p, out1);
    os_SetCursorPos(2,0);
    //dbg_printf("%s\n", out1);
    os_PutStrLine(toOut1);
    os_SetCursorPos(3,0);
    char toOut2[20];
    sprintf(toOut2, "q(%d) = %s", q, out2);
    os_PutStrLine(toOut2);
    while(!os_GetCSC());
    return 0;
}
