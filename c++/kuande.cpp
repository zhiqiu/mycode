

/*要求：1.不要外部编辑器，直接在网页上敲代码
        2.定义用到的数据结构
        3.时间在一个半小时
*/


1.一共有n层楼梯，每次只能走2层楼梯或3层，或者5层楼梯，问走到楼梯顶共有多少种走法。
2.基于链表的归并排序，假设排序元素是整数。
3.将1到20这20个数排成一排，使得相邻两个数之和为一个素数，且首尾两个数之和也为一个素数。编程打印出所有的排法。


1. call solve(n), n is the number of stages

const int maxn = 10000; // 保证maxn > n
long long dp[maxn];

long long solve(int n){
    for(int i = 0; i <= n; i++)   dp[i] = 0;
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        long long tmp = 0;
        if(i >= 2) tmp += dp[i-2];
        if(i >= 3) tmp += dp[i-3];
        if(i >= 5) tmp += dp[i-5];
        dp[i] = tmp; 
    }
    return dp[n];
}


2. call mergeSort(head), head is the head pointer of linked list 
// sort from small to large
struct node{
    node(int n):data(n),next(NULL){}
    int data;
    struct node* next;
};

struct node* merge(struct node* a, struct node* b){
    struct node* head = new struct node(0);
    struct node* p = head;
    while(a != NULL && b != NULL){
        if(a -> data < b -> data){
            p - > next = a;
            p = p -> next;
            a = a -> next;
        }
        else {
            p -> next = b;
            p = p -> next;
            b = b-> next;
        }
    }
    if(a != NULL)   p -> next = a;
    else p -> next = b;
    
    return head -> next;
}

struct node* mergeSort(struct node* head){
    if(head == NULL || head -> next == NULL){
        return head;
    }
    struct node* p = head, q = p -> next;
    while(q != NULL && q -> next != Null){
        p = p -> next;
        q = q -> next -> next;
    }
    struct node* half = p -> next;
    p - > next = NULL;
    return merge(mergeSort(head), mergeSort(half)); 
}

3. 
// 1 .. 20
// 用 next_permutationm()枚举所有排列，20!复杂度，应该可以，但是复杂度太高了。。
// 所以应该想办法优化和剪枝
// 固定末尾,加速，可以循环移位得到所有20次得到最终结果
// 感觉 还是需要挺长时间，暂时 只想到这个
#include <cmath>
#include <algorithm>
bool isPrime(int n){
    if(n < 2) return 0;
    if(n == 2) return 1;
    for(int i = 2; i<= sqrt(n)+1; i++){
        if(n %i ==0) return 0;
    }
    return 1;
}
int arr[21];

int ans = 0;
bool dfs(int d){    
    bool flag = false;
    if(d == 1){
        if(isPrime(arr[20]+arr[1])){ 
            ans ++;                
            cout << "case " << ans <<":";
            for(int i = 1; i <= 20; i++){
                cout << arr[i] << " ";
            }
            cout << endl;
            return true;
        }
        else return false;
    }
    for(int i = 1; i < d; i++){
        if(!isPrime(arr[d]+arr[i])){
            continue;
        }
        swap(arr[i],arr[d-1]);
        if(dfs(d-1)) flag = true;
        swap(arr[d-1], arr[i]);
    }
    return flag;
}

void solve(){
    for(int i=0; i<=20; i++){
        arr[i] = i;
    }
    dfs(20);
}




