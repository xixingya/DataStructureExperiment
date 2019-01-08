#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define NOTSUIT 2
/*int left=1;
int num=0;
int right=0;
*//*int n=0;
int k=0;*/
int iSDeepthK(char a[],int k){//判断是不是一个深度为k的序列
    int b=strlen(a);
    int countLeft=0;
    int countRight=0;
    if(b%2!=0)
        return NOTSUIT;//判断是不是偶数，不是偶数一定不匹配
    for(int i=0;i<b;i++){
        if(a[i]=='(')
            countLeft++;
        if(a[i]==')')
            countRight++;
    }//判断括号对数是否相等
    if(countLeft!=countRight){
        return NOTSUIT;
    }

    int MAX=0;//最大深度
    int count=0;
    for(int i=0;i<b;i++){
        if(a[i]=='('){
            count++;
            if(MAX<count){
                MAX=count;
            }
        }


        if(a[i]==')'){
            count--;
        }

    }
    if(MAX==k)
        return OK;
    else return ERROR;

}//函数判断深度是不是为k结尾
int n,k,num,left,right,i,d,max;
void listKuoHao(int d,char *a,int max){
    if(d==2*n){
        if(a[d-1]==')'&&max==k){
            printf("%d %s\n",++num,a);
        }
        return;
    }
    if(left<right||(left-right)>k||left>n)//当右括号大于于左括号，或者嵌套深度大于k时
        return;
    if(max<k&&d+2*max-(left-right)>=2*n)
        return;
    a[d]='(';
    left++;
    listKuoHao(d+1,a,max>left-right?max:(left-right));
    left--;
    a[d]=')';
    right++;
    listKuoHao(d+1,a,max>(left-right)?max:(left-right));
    right--;
}

int main(){
    char a[100];
    int k=1;
    //当k!=0，输入序列并且判断深度是不是为k
    while(true){
        scanf("%d",&k);
        if(k==0)
            break;
        scanf("%s",a);
        int iSK=iSDeepthK(a,k);
        if(iSK==OK)
            printf("YES\n");
        else if(iSK==ERROR)
            printf("NO\n");
        else if(iSK==NOTSUIT)
            printf("括号不匹配\n");
    }
    a[0]='(';
    while(true){
        printf("please input n and k so that we can list the kuohao\n");
        scanf("%d %d",&n,&k);
        if(k>n)
            break;
        a[2*n]='\0';
        left=1;num=right=0;
        listKuoHao(1,a,0);
        printf("%dkuohao %dqiantao is%d suggestion\n",n,k,num);

    }



}