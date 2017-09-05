// 二叉树的建立和输出.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#define MAX_ROW_SIZE 33 //最大行节点数
typedef char DateType;
using namespace std; 

struct Node{
	DateType data;
	struct Node *leftChildren;
	struct Node *rightChildren;
};

Node *BinTreeEst(Node *root, DateType data[], int size, int counter=0, int sum=1){ /*递归建立二叉树*/
	if(size==0||sum>size) return NULL;
	root=(Node*)malloc(sizeof(Node));
	root->data=data[counter]; ++sum;
	if(2*counter+1<size){ //判断是否有左孩子节点
		root->leftChildren=BinTreeEst(root->leftChildren,data,size,2*counter+1,sum);
	}else root->leftChildren=NULL;
	if(2*counter+2<size){ //判断是否有右孩子节点
		root->rightChildren=BinTreeEst(root->rightChildren,data,size,2*counter+2,sum);
	}else root->rightChildren=NULL;
	return root;
}

inline void visit(Node *root){ //访问操作函数
	cout<<root->data<<' ';
}

void layPrint(Node *root){ /*层序输出*/
	Node *arr[MAX_ROW_SIZE]; int i=0,layer=1;
	if(root){ 
		arr[0]=root; cout<<"层序: ";
		for(;;){
			for(int j=0;j<layer;j++)
				if(root=arr[j]) cout<<root->data<<' '; //非空节点输出
				else return; //最下层到末尾退出
			if(arr[0]->leftChildren==NULL) return; //完全二叉树左下角第一个非空
			for(i=layer-1;root->leftChildren==NULL;root=arr[--i]); //找到同一层最右边左孩子非空节点
			for(;i>=0;--i){ //由本层节点找到下层节点
				root=arr[i]; 
				arr[2*i+1]=root->rightChildren;
				arr[2*i]=root->leftChildren;
			}
		layer*=2; //当前数组节点数翻倍
		}
	}
}

void printBTreeStat(Node *root, int i=1){ /*凹入打印二叉树*/
	if(root->rightChildren)
		printBTreeStat(root->rightChildren,i+1); //搜索左节点
	for(int n=i;n>0;--n) cout<<"   "; //打印当前节点
	cout<<"---"<<root->data<<endl;
	if(root->leftChildren)
		printBTreeStat(root->leftChildren,i+1); //搜索右节点
}

bool isComBTree(Node *root){ /*判断是否完全二叉树*/
	Node *arr[MAX_ROW_SIZE]; int i=0,layer=1, flag=0, counter=0;
	if(root){ //空节点不是
		arr[0]=root;
		for(;;){
			counter=0; //层节点数计数器置零
			for(i=layer-1;i>=0;--i){ //由当前节点找到子节点
				arr[2*i+1]=arr[i]->rightChildren; 
				arr[2*i]=arr[i]->leftChildren;
				if(arr[2*i+1]!=NULL&&arr[2*i]==NULL) return false; //顺便判断若左节点为空，右节点不空的情况
				if(arr[2*i+1]) ++counter; //计数非空节点
				if(arr[2*i]) ++counter;
			}
			if(counter==0) return true; //本层都为空那就是完全二叉树啦
			layer*=2; if(counter==layer) continue; //如果当前节点数达到最大值，就不用判断了
			if(!arr[layer-1]&&(arr[0]->leftChildren||
				arr[0]->rightChildren)) return false; //判断最右边为空但下层节点存在的情况
			for(i=layer-2;i>=2;i-=2) //判断夹缝之间的左非空右空情况
				if(arr[i]&&!arr[i-1]) return false;
			if(counter<=layer) return true; //如果都拦不住符合咯
		}
	}else return false;
}

void bTreeDLR(Node *root){ //非递归先序输出 较简单不用解释啦
	int i=0; Node *arr[MAX_ROW_SIZE];
	cout<<"非递归DLR: ";
	for(;;){
		if(root) visit(root);
		if(root->leftChildren){
			if(root->rightChildren)
				arr[i++]=root->rightChildren;
			root=root->leftChildren;
		}else if(root->rightChildren){
			visit(root); root=root->rightChildren;
		}else{
			if(i==0) return;
			root=arr[--i];
		}
	}
}

void bTreeLDR(Node *root){ /*中序输出*/
	if(root->leftChildren)
		bTreeLDR(root->leftChildren);
	cout<<root->data<<' ';
	if(root->rightChildren)
		bTreeLDR(root->rightChildren);
}

void bTreeLRD(Node *root){ /*后序输出*/
	if(root->leftChildren)
		bTreeLRD(root->leftChildren);
	cout<<root->data<<' ';
	if(root->rightChildren)
		bTreeLRD(root->rightChildren);
}

void counter(Node *root, int arr[]){ /*arr[0]储存叶子节点，arr[1]存非叶子节点*/
	if(root==NULL) return;
	if(root->leftChildren==NULL&&root->rightChildren==NULL){ ++arr[0]; return;}
	else ++arr[1];
	counter(root->leftChildren,arr);
	counter(root->rightChildren,arr);
}

int bTreeDeep(Node *root, int i=0){ /*二叉树深度*/
	if(root->leftChildren==NULL&&root->rightChildren==NULL) return i;
	int temp, te=i;
	if(root->leftChildren)
		temp=bTreeDeep(root->leftChildren,i+1); i=temp>i ? temp:i; //比较取较大值
	if(root->rightChildren){
		temp=bTreeDeep(root->leftChildren,te+1); i=temp>i ? temp:i;	
	}
	return i;
}

int main(int argc, char* argv[])
{
	char BT[]={'a','b','c','d','e','f','g','h','i','j','k','l',
		'm','n','o','p'}; int arr[2]={0,0};
	Node *root=NULL;
	root=BinTreeEst(root,BT,16);
	cout<<"递归LDR: ";
	bTreeLDR(root); cout<<endl;
	printBTreeStat(root);
	cout<<endl<<"深度: "<<bTreeDeep(root)<<endl;
	counter(root,arr);
	cout<<"叶节点个数: "<<arr[0]<<endl<<"节点个数:"<<arr[1]<<endl;
	bTreeDLR(root); cout<<endl;
	layPrint(root); cout<<endl;
	if(isComBTree(root)) cout<<"是二叉树"<<endl;
	else cout<<"不是二叉树"<<endl;
	return 0;
}

