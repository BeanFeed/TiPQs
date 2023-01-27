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

void getFactors(int num, int *res, const int *size) {
    int addedItems = 0;
    size = &addedItems;
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
}

/*
void finalOut(int *p, int *q, char *res) {
    
    int oneAdded = 0;
    int i = 0, j = 0;
    size_t qSize = sizeof(q) / sizeof(q[0]), pSize = sizeof(p) / sizeof(p[0]);
    char buf[21];
    sprintf(buf, "Q Size: %zu, P Size: %zu", qSize, pSize);
    dbg_printf("%s", buf);
    for(i = 0; i < (int)qSize; i++) {
        for(j = 0; j < (int)pSize; j++) {
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
    int listSize = sizeof(list) / sizeof(list[0]);
    dbg_printf("list Size: %d\n", listSize);
    int oneAdded = 0;
    for(int i = 0; i < listSize; i++) {
        if(oneAdded == 0) {
            sprintf(res, "%d", list[i]);
            oneAdded++;
        } else {
            sprintf(res, "%s, %d", res, list[i]);
        }
    }
}
*/
int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    int p;
    char pstr[5];
    os_GetStringInput("What is P: ", pstr, 5);
    p = strtod(pstr, NULL);
    os_SetCursorPos(1,0);
    /*
    int q;
    char qstr[5];
    os_GetStringInput("What is Q: ", qstr, 5);
    q = strtod(qstr, NULL);
     */
    int *factorsp = malloc(20);
    int psize;
    getFactors(p, factorsp, &psize);
    dbg_printf("P: %d, P Size: %d\n",p, psize);
    free(factorsp);
    while(!os_GetCSC());
    return 0;
}
