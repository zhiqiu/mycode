#include <bits/stdc++.h>

using namespace std;

int a[10] = {5,1,2,6,2,4,1,2,5,0};
int n = 10;

void bubbleSort(){
	for(int i=0;i<n;i++){  // 外层控制做n次
		for(int j=0;j<n-i-1;j++){  // 内层控制每次交换相邻两个
			if(a[j] > a[j+1]){
				swap(a[j],a[j+1]);
			}
		}
	}
}

void insertSort(){
	for(int i=1;i<n;i++){
		int j = i;
		int t = a[i];
		while(j>0 && a[j-1]>t){
			a[j] = a[j-1];  // 后移
			j--;
		}
		a[j] = t;
	}
}

void selectSort(){
	for(int i=0;i<n;i++){
		int mm = a[i],index = i;
		for(int j=i+1;j<n;j++){
			if(a[j]<a[i]){
				index = j;
			}
		}
		swap(a[index],a[i]);
	}
}
const int maxn = 1000;
int cnt = 0;
int c[maxn];
void mergeSort(int left,int right){  //0...n
	int mid, i, j, tmp;
	if(right>left+1){  //至少两个
		mid = (left+right)/2;
		mergeSort(left,mid);
		mergeSort(mid,right);
		tmp = left;
		// merge
		for(i=left,j =mid; i<mid&&j<right;){
			if(a[i] > a[j]){
				c[tmp++] = a[j++];
				cnt += mid-i;
			}
			else c[tmp++] = a[i++];
		}
		if(j < right)  while(j<right) c[tmp++] = a[j++];
		else while(i<mid) c[tmp++] = a[i++];
		// 合并
		for(i=left;i<right;++i) a[i] = c[i];
	}
}

int partition(int arr[],int left,int right){
	// 随机选主元
	srand((unsigned int)time(NULL));
	int pivot = rand()%(right-left) + left;
	int p = arr[pivot];
	while(left <= right){
		while(arr[left] < p) left ++;
		while(arr[right]> p) right --;
		if(left<=right){
			swap(arr[left++],arr[right--]);
		}
	}
	return left;
}

void quickSort(int arr[],int left,int right){
	int index = partition(arr,left,right);
	if(left+1 < index){
		quickSort(arr,left,index-1);
	}
	if(index<right){
		quickSort(arr,index,right);
	}
}
// 0..n
int bSearch(int arr[],int left,int right,int t){
	while(left < right){
		int m = (left+right)/2;
		if(arr[m] < t) left = m+1;
		else if(arr[m]==t) return m;
		else right = m;
	}
	return -1;
}

// heap sort 树根为0
int size = 10;
void insert(int i){
	int left = i*2+1, right = left+1, large = i;
	if(left<size &&a[left]>a[i]) large = left;
	if(right<size &&a[right]>a[large]) large = right;

	if(large!=i){
		swap(a[i],a[large]);
		insert(large);
	}
}

void build(){
	size = 10;
	for(int i = size/2-1;i>=0;i--){
		insert(i);
	}
}
void heapSort(int n){
	build();
	for(int last = n-1;last>=0;last--){
		//int t = a[last];
		size --;
		swap(a[last] , a[0]);
		insert(0);
	}
}
int main(int argc, char const *argv[])
{
	//bubbleSort();
	heapSort(10);
	//cout << n << endl;
	for(int i=0;i<10;i++) cout << a[i] << endl;
	return 0;
}