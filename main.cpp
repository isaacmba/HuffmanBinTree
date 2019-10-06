#include <fstream>
#include <iostream>
using namespace std;

class treeNode{
	public:
		string chStr;
		int prob;
		treeNode *next;
		treeNode *left;
		treeNode *right;
		string code;

		treeNode(string str, int count){
			chStr = str;
			prob = count;
			next = NULL;
			left = NULL;
			right = NULL;
		}
		string printNode(treeNode *T){
			string node = T->chStr+" "+to_string(T->prob);
			if(T->next != NULL)
				node+=" "+T->next->chStr;
			if(T->left != NULL)
				node+=" "+T->left->chStr;			
			if(T->right != NULL)
				node+=" "+T->right->chStr;
	
			return node;
		}
};
class linkedList{
	public:
		treeNode *listHead;
		linkedList(treeNode *lhead){
			listHead = lhead;
		}
		void insertOneNode(treeNode *spot, treeNode *nnode){
			nnode->next = spot->next;
			spot->next = nnode;
		}
		treeNode *findSpot(treeNode *lhead, treeNode *nnode){
			// findSpot(LHead, NewNode) Alg steps:
			treeNode *spot = lhead;// step 1: spot <-- LHead
			while(spot->next != NULL && spot->next->prob<nnode->prob){// 2: if(spot.next != null && spot.next.count < NewNode.count)
				spot = spot->next;// spot <-- spot.next
			}// 3: repeat step 2 until the condition fails
			return spot;// 4: return spot
		}
		void printList(treeNode *lhead, ofstream& outFile){

			string list = "listHead-->";
	
			while(lhead->next != NULL){
				list += string("(\"")+ string(lhead->chStr) + string("\", ")+to_string(lhead->prob) + string(", \"") + string(lhead->next->chStr)+ string("\")-->");
				lhead = lhead->next;
			}
			list += string("(\"") + string(lhead->chStr)+ string("\", ") +to_string(lhead->prob) + string(", NULL)-->NULL\n");
			outFile << list;
		}
};
class huffmanBinaryTree{
	public:
		treeNode *Root;
		treeNode *listHead;
		huffmanBinaryTree(){
			Root = NULL;
			listHead = new treeNode("dummy",0);
		}
		bool isLeaf(treeNode *T){
			bool isLeaf;
			if(T->left == NULL && T->right == NULL)
				return true;
			else
				return false;
		}
		void constructHuffmanLList(ifstream& in, ofstream& out){
			linkedList ll(listHead);
			string chr;
			int prob;
			while(in >> chr >> prob) {
				treeNode *nnode = new treeNode(chr, prob);
				treeNode *spot = ll.findSpot(listHead,nnode);
				ll.insertOneNode(spot, nnode);
				ll.printList(listHead,out);
			}
			in.close();
		}
		void constructHuffmanBinTree(treeNode *listHead, ofstream& outFile){
			linkedList ll(listHead);
			treeNode *nnode;
			while(listHead->next->next != NULL) {
				nnode = new treeNode(listHead->next->chStr + listHead->next->next->chStr,
											   listHead->next->prob + listHead->next->next->prob);
				nnode->left = listHead->next;
				nnode->right = listHead->next->next;
				treeNode *spot = ll.findSpot(listHead, nnode);
				ll.insertOneNode(spot, nnode);
				listHead->next = listHead->next->next->next;
				ll.printList(listHead, outFile);
			}
			Root = nnode;
		}
		void getCode(treeNode *T, string code, ofstream& outFile1){
			if(isLeaf(T)){
				T->code = code;
				outFile1<< T->chStr << " "<<T->code<<endl;
			} else{
				getCode(T->left, code+"0",outFile1);
				getCode(T->right, code+"1",outFile1);
			}
		}
		void preOrderTraversal(treeNode *T, ofstream& outFile2){
			if(T == NULL)
				return;
			else{
				outFile2<<T->printNode(T)<<endl;
				preOrderTraversal(T->left, outFile2);
				preOrderTraversal(T->right, outFile2);
			}
		}
		void inOrderTraversal(treeNode *T, ofstream& outFile3){
			if(T == NULL)
				return;
			else{
				inOrderTraversal(T->left, outFile3);
				outFile3<<T->printNode(T)<<endl;
				inOrderTraversal(T->right, outFile3);
			}
		}
		void postOrderTraversal(treeNode *T, ofstream& outFile4){
			if(T == NULL)
				return;
			else{
				postOrderTraversal(T->left, outFile4);
				postOrderTraversal(T->right, outFile4);
				outFile4<<T->printNode(T)<<endl;
			}
		}

};

int main(int argc, char const *argv[])
{

	if(argc<7){
		cout<<endl<<"Pass correct # of args"<<endl<<endl;
		return 0;
	}
	
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1;
	outFile1.open(argv[2]);
	ofstream outFile2;
	outFile2.open(argv[3]);
	ofstream outFile3;
	outFile3.open(argv[4]);
	ofstream outFile4;
	outFile4.open(argv[5]);
	ofstream outFile5;
	outFile5.open(argv[6]);

	huffmanBinaryTree *hbt = new huffmanBinaryTree();

	hbt->constructHuffmanLList(inFile, outFile5);//Step 1
	hbt->constructHuffmanBinTree(hbt->listHead, outFile5);//Step 2
	hbt->preOrderTraversal(hbt->Root, outFile2);//Step 3
	hbt->inOrderTraversal(hbt->Root, outFile3);
	hbt->postOrderTraversal(hbt->Root, outFile4);
	hbt->getCode(hbt->Root," ",outFile1);

	return 0;
}