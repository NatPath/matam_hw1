#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

char *stringDuplicator(char *s, int times) {
    assert(s);
    assert(times > 0);
    int len = strlen(s);
    char *out = malloc(sizeof(char)*len*times);
    if (out==NULL){
        return NULL;
    }
    for (int i = 0; i < times; i++) {
        strcpy(out, s);
        out = out + len;
    }
    return out-len*times;
}

void q2_test(){
    char string[100];
    int num;
    printf("Enter String:\n");
    scanf("%s",string);
    printf("Enter num:\n");
    scanf("%d",&num);
    char *res=stringDuplicator(string,num);
    puts(res);
}
int main(){
    q2_test();
    return 0;
}