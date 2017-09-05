// �������Ľ��������.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#define MAX_ROW_SIZE 33 //����нڵ���
typedef char DateType;
using namespace std; 

struct Node{
	DateType data;
	struct Node *leftChildren;
	struct Node *rightChildren;
};

Node *BinTreeEst(Node *root,DateType data[],int size,int counter=0,int sum=1){ /*�ݹ齨��������*/
	if(size==0||sum>size) return NULL;
	root=(Node*)malloc(sizeof(Node));
	root->data=data[counter]; ++sum;
	if(2*counter+1<size){ //�ж��Ƿ������ӽڵ�
		root->leftChildren=BinTreeEst(root->leftChildren,data,size,2*counter+1,sum);
	}else root->leftChildren=NULL;
	if(2*counter+2<size){ //�ж��Ƿ����Һ��ӽڵ�
		root->rightChildren=BinTreeEst(root->rightChildren,data,size,2*counter+2,sum);
	}else root->rightChildren=NULL;
	return root;
}

inline void visit(Node *root){ //���ʲ�������
	cout<<root->data<<' ';
}

void layPrint(Node *root){ /*�������*/
	Node *arr[MAX_ROW_SIZE]; int i=0,layer=1;
	if(root){ 
		arr[0]=root; cout<<"����: ";
		for(;;){
			for(int j=0;j<layer;j++)
				if(root=arr[j]) cout<<root->data<<' '; //�ǿսڵ����
				else return; //���²㵽ĩβ�˳�
			if(arr[0]->leftChildren==NULL) return; //��ȫ���������½ǵ�һ���ǿ�
			for(i=layer-1;root->leftChildren==NULL;root=arr[--i]); //�ҵ�ͬһ�����ұ����ӷǿսڵ�
			for(;i>=0;--i){ //�ɱ���ڵ��ҵ��²�ڵ�
				root=arr[i]; 
				arr[2*i+1]=root->rightChildren;
				arr[2*i]=root->leftChildren;
			}
		layer*=2; //��ǰ����ڵ�������
		}
	}
}

void printBTreeStat(Node *root,int i=1){ /*�����ӡ������*/
	if(root->rightChildren)
		printBTreeStat(root->rightChildren,i+1); //������ڵ�
	for(int n=i;n>0;--n) cout<<"   "; //��ӡ��ǰ�ڵ�
	cout<<"---"<<root->data<<endl;
	if(root->leftChildren)
		printBTreeStat(root->leftChildren,i+1); //�����ҽڵ�
}

bool isComBTree(Node *root){ /*�ж��Ƿ���ȫ������*/
	Node *arr[MAX_ROW_SIZE]; int i=0,layer=1, flag=0, counter=0;
	if(root){ //�սڵ㲻��
		arr[0]=root;
		for(;;){
			counter=0; //��ڵ�������������
			for(i=layer-1;i>=0;--i){ //�ɵ�ǰ�ڵ��ҵ��ӽڵ�
				arr[2*i+1]=arr[i]->rightChildren; 
				arr[2*i]=arr[i]->leftChildren;
				if(arr[2*i+1]!=NULL&&arr[2*i]==NULL) return false; //˳���ж�����ڵ�Ϊ�գ��ҽڵ㲻�յ����
				if(arr[2*i+1]) ++counter; //�����ǿսڵ�
				if(arr[2*i]) ++counter;
			}
			if(counter==0) return true; //���㶼Ϊ���Ǿ�����ȫ��������
			layer*=2; if(counter==layer) continue; //�����ǰ�ڵ����ﵽ���ֵ���Ͳ����ж���
			if(!arr[layer-1]&&(arr[0]->leftChildren||
				arr[0]->rightChildren)) return false; //�ж����ұ�Ϊ�յ��²�ڵ���ڵ����
			for(i=layer-2;i>=2;i-=2) //�жϼз�֮�����ǿ��ҿ����
				if(arr[i]&&!arr[i-1]) return false;
			if(counter<=layer) return true; //���������ס���Ͽ�
		}
	}else false
}

void bTreeDLR(Node *root){ //�ǵݹ�������� �ϼ򵥲��ý�����
	int i=0; Node *arr[MAX_ROW_SIZE];
	cout<<"�ǵݹ�DLR: ";
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
			root=arr[--i];}
	}
}

void bTreeLDR(Node *root){ /*�������*/
	if(root->leftChildren)
		bTreeLDR(root->leftChildren);
	cout<<root->data<<' ';
	if(root->rightChildren)
		bTreeLDR(root->rightChildren);
}

void bTreeLRD(Node *root){ /*�������*/
	if(root->leftChildren)
		bTreeLRD(root->leftChildren);
	cout<<root->data<<' ';
	if(root->rightChildren)
		bTreeLRD(root->rightChildren);
}

void counter(Node *root,int arr[]){ /*arr[0]����Ҷ�ӽڵ㣬arr[1]���Ҷ�ӽڵ�*/
	if(root==NULL) return;
	if(root->leftChildren==NULL&&root->rightChildren==NULL){ ++arr[0]; return;}
	else ++arr[1];
	counter(root->leftChildren,arr);
	counter(root->rightChildren,arr);
}

int bTreeDeep(Node *root,int i=0){ /*���������*/
	if(root->leftChildren==NULL&&root->rightChildren==NULL) return i;
	int temp, te=i;
	if(root->leftChildren)
		temp=bTreeDeep(root->leftChildren,i+1); i=temp>i ? temp:i; //�Ƚ�ȡ�ϴ�ֵ
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
	cout<<"�ݹ�LDR: ";
	bTreeLDR(root); cout<<endl;
	printBTreeStat(root);
	cout<<endl<<"���: "<<bTreeDeep(root)<<endl;
	counter(root,arr);
	cout<<"Ҷ�ڵ����: "<<arr[0]<<endl<<"�ڵ����:"<<arr[1]<<endl;
	bTreeDLR(root); cout<<endl;
	layPrint(root); cout<<endl;
	if(isComBTree(root)) cout<<"�Ƕ�����"<<endl;
	else cout<<"���Ƕ�����"<<endl;
	return 0;
}

