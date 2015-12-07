1. 数组快速排序算法

#include <algorithm>
#include <time.h>
using namespace std;
int partition(int arr[],int begin,int end){
 //int pivot = rand()%(end-left) + left;  //随机选择主元，防止算法退化  
    int index = (begin+end)/2;
    int p = arr[index];
    
    while(begin < end){
        while(arr[begin] < p)  begin ++;
        while(arr[end] > p)    end --;  
        if(begin<=end){
            swap(arr[begin],arr[end]);
            begin ++;
            end --;
        }
    }
    return begin;
}

// eg: arr[10] = {3,2,4,5,1,0,2,3,9,3};
// call: quickSort(arr,0,9)
void quickSort(int arr[], int begin, int end){  
    int t = parttition(arr,begin,end);
    if(begin+1 < t){
        quickSort(arr,begin,t-1);
    }
    if(t < right){
        quickSort(arr,t,end);
    }
}





2. 一个整数数组，求连续子序列的最大和
#include <cstring>
#include <algorithm>
using namespace tsd;
const maxn = 100000;   // 如果数据大小比较大的话，可以使用new来开辟dp数组
int dp[maxn];          // dp[i]表示:以i结尾的最大连续和

// eg: arr[10] = {3,2,4,5,1,0,2,3,9,3};
// call: int ans = maxContinueSum(arr,10)
// 假定：数组大小n不超过maxn，结果小于2^31-1 
int maxContinueSum(int arr[],int n){
    memset(dp,0,sizeof(dp));
    dp[0] = arr[0];
    for(int i=1;i<n;i++){
        dp[i] = max(0,dp[i-1]) + arr[i];
    }
    int ans = -1;
    for(int i=0; i<n; i++)
        if(dp[i] > ans) ans = dp[i];
    return ans;
}


3. 有二叉树A，B，判断A树是否包含B树

struct node{
    int data;
    node* left;
    node *right;
    node(int d=0, l = NULL, r = NULL):data(d),left(l),right(r){}
};
// Given: the root pointer of two binary tree
// call check(root1,root2) to see if  tree1 contains tree2

bool testEqual(node* r1,node* r2){
    // use dfs to test if equals
    if(r1==NULL&&r2==NULL) return true;
    else if((r1==NULL&&r2!=NULL) return false;
    else if((r2!=NULL&&r2==NULL) return false;
    if(r1->left==r2->data){
        return testEqual(r1->left,r2->left)&&testEqual(r1->right,r2->right);
    }
    else return false;
}
bool check(node *root1, node* root2){
    // 先考虑空树
    if(toot1==NULL) return false;
    //if(root1==NULL&&root2!=NULL) return true;
    if(root1!=NULL&&root2==NULL) return true;
    bool ans = false;    
    if(root1->data!=root2->data){
        if(root1.left!=NULL) ans = check(root1->left,root2);
        if(!ans&&root1->right!=NULL)  ans = check(root1->right,root2);
    }
    else{
        ans = testEqual(root1,root2);
    }
    return ans;
}