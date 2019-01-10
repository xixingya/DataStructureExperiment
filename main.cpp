#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define NOTSUIT 2
#define MAX_N 30
int countAll[MAX_N+1][MAX_N+1]={};
/*int left=1;
int num=0;
int right=0;
*//*int n=0;
int k=0;*/
char str[1000];
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
void listKuoHao(int d,char *a,int max);
void solve(int n, int ls, int rs,int k);
void solve3(int n, int ls, int rs, int k,int *count);
void countA(int n,int k);
int main(){
    char a[100];
    int k=1;
    //当k!=0，输入序列并且判断深度是不是为k
    while(true) {
        scanf("%d", &k);
        if (k == 0)
            break;
        scanf("%s", a);
        int iSK = iSDeepthK(a, k);
        if (iSK == OK)
            printf("YES\n");
        else if (iSK == ERROR)
            printf("NO\n");
        else if (iSK == NOTSUIT)
            printf("括号不匹配\n");
    }//first question

    while(true){
        printf("please input n and k so that we can list the kuohao\n");
        scanf("%d %d",&n,&k);
        if(k>n)
            break;
        solve(n,0,0,k);

    }//second question
    for(n=1;n<=MAX_N;n++){
        countAll[n][1]=1;
        countAll[n][n]=1;
    }
    for(n=1;n<=MAX_N;n++){
        for(k=1;k<=n;k++){
            if(k!=n&&k!=1)
                countA(n,k);
        }
    }
    while(true){
        printf("please input n and k so that we can count the kuohao\n");
        scanf("%d %d",&n,&k);
        if(k>n)
            break;
        printf("%d %d have %d situation\n",n,k,countAll[n][k]);



    }
    /*while(true){
        int *count;
        *count=0;
        printf("please input n and k so that we can list the kuohao\n");
        scanf("%d %d",&n,&k);
        if(k>n)
            break;
        solve3(n,0,0,k,count);
        printf("%d\n",*count);

    }*/



}
/*void listKuoHao(int d,char *a,int max){
    if(d==2*n){
        if(a[d-1]==')'&&max==k){
            printf("%d %s\n",++num,a);
        }
        return;
    }
    if(left<right||(left-right)>k||left>n)//当右括号大于于左括号，或者嵌套深度大于k时
        return;
    if(max<k&&(d+2*max-(left-right)>=2*n))
        return;
    a[d]='(';
    left++;
    listKuoHao(d+1,a,max>(left-right)?max:(left-right));
    left--;
    a[d]=')';
    right++;
    listKuoHao(d+1,a,max>(left-right)?max:(left-right));
    right--;
}*/
void solve3(int n, int ls, int rs, int k,int *count)
{
    if(ls == rs && ls + rs == 2*n&&iSDeepthK(str,k)==OK) {
        (*count)++;
        return ;
    }
    if(ls < rs || ls + rs >= 2*n) return ;
    int index = ls + rs;
    str[index] = '(';
    solve3(n, ls+1, rs,k,count);
    str[index] = ')';
    solve3(n, ls, rs+1,k,count);
}

void solve(int n, int ls, int rs, int k)
{
    if(ls == rs && ls + rs == 2*n&&iSDeepthK(str,k)==OK) {
        printf("%s\n", str);
        return ;
    }
    if(ls < rs || ls + rs >= 2*n) return ;
    int index = ls + rs;
    str[index] = '(';
    solve(n, ls+1, rs,k);
    str[index] = ')';
    solve(n, ls, rs+1,k);
}
void countA(int n,int k){
    int i,j;
    for (i=k;i<n;i++){
        int temp=0;
        for(j=0;j<=n-i;j++){
            int temp_i=j;
            int temp_j=n-i-j;
            int temp_k1=0;
            int temp_k2=0;
            if(temp_i>k-1)   temp_i=k-1;//j和k-1的较小值赋给temp_i,最大深度不能大于k-1;
            if(temp_j>k)     temp_j=k;//n-i-j和k的较小值赋给temp_j,最大深度不能大于k
            for(;temp_i>0;temp_i--)
                temp_k1=temp_k1+countAll[j][temp_i];//求和countAll[j][temp_i]
            for(;temp_j>0;temp_j--)
                temp_k2=temp_k2+countAll[n-i-j][temp_j];//求和countAll[n-i-j][temp_j]
            if(temp_k1<1)  temp_k1=1;
            if(temp_k2<1)  temp_k2=1;
            temp=temp+temp_k1*temp_k2;//求和temp_k1*temp*k2
        }
        countAll[n][k]=countAll[n][k]+countAll[i-1][k-1]*temp;
    }
    countAll[n][k]=countAll[n][k]+countAll[n-1][k-1];
}