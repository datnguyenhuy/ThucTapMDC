#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
using namespace std;

struct Node {
	int MaNode;
	char TenNode[10];
	int soNutCon;
	struct Node* NodeCon[1000000];
	struct Node* next;
};

typedef struct Node* node;

string X, Y, Z;

node Search(node head, int numberParent) {
	node p;
	for (p = head; p != NULL; p = p->next) {
		if (p->MaNode== numberParent) {
			return p;
		}
	}
	return NULL;
}

node searchByName(node head, string name) {
	node p;
	for (p = head; p != NULL; p = p->next) {
		if (p->TenNode == name) {
			return p;
		}
	}
	return NULL;
}

node createNode(node head,int number,int numberParent,char name[])
{
	node temp;
	temp = (node)malloc(sizeof(struct Node)); // Cấp phát vùng nhớ dùng malloc()
	temp->MaNode= number;
	strcpy(temp->TenNode,name);
	temp->next = NULL;
	node search = Search(head, numberParent);
	if (search != NULL)
	{
		if (search->soNutCon < 0) search->soNutCon = 0;
		search->NodeCon[search->soNutCon] = temp;
		search->soNutCon++;
	}
	return temp; //Trả về node mới đã có giá trị
}

node addTail(node head, int number, int numberParent, char name[]) {
	node temp, p;// Khai báo 2 node tạm temp và p
	temp = createNode(head,number,numberParent,name);//Gọi hàm createNode để khởi tạo node temp có next trỏ tới NULL và giá trị là value
	if (head == NULL) {
		head = temp;     //Nếu linked list đang trống thì Node temp là head luôn
	}
	else {
		p = head;// Khởi tạo p trỏ tới head
		while (p->next != NULL) {
			p = p->next;//Duyệt danh sách liên kết đến cuối. Node cuối là node có next = NULL
		}
		p->next = temp;
	}
	return head;
}

node addHead(node head, int number, int numberParent, char name[]) {
	node temp = createNode(head,number, numberParent, name);
	if (head == NULL) {
		head = temp; // //Nếu linked list đang trống thì Node temp là head luôn
	}
	else {
		temp->next = head; // Trỏ next của temp = head hiện tại
		head = temp; // Đổi head hiện tại = temp
	}
	return head;
}

char result[1000][1000];
int run = 0;

bool Find(node head,string sta,string fin)
{
	for (int i = 0; i < head->soNutCon; i++)
	{
		if (head->NodeCon[i]->TenNode == fin)
			return true;
		else
		{
			if (Find(head->NodeCon[i], head->NodeCon[i]->TenNode, fin) == true)
			{
				for (int j = 0; j < 1000; j++)
				{
					result[run][j] = head->NodeCon[i]->TenNode[j];
				}
				run++;
				return true;
			}
		}
	}
	return false;
}

void findFull(node head)
{
	for (int i = 0; i < head->soNutCon; i++)
	{
		cout << head->NodeCon[i]->MaNode << " "<< head->NodeCon[i]->TenNode<<endl;
		if (head->NodeCon[i]->soNutCon == 0)
		{
			break;
		}
		else
		{
			findFull(head->NodeCon[i]);
		}
	}
}


int main()
{
	node head = NULL;

	ifstream input("tree.txt");
	if (input.is_open())
	{
		int number, numberParent;
		char name[10];

		while ((input >> number >> numberParent >> name ))
		{
			if (number == 1)
			{
				head=addHead(head, number, numberParent, name);
			}
			else
			{
				head= addTail(head, number, numberParent, name);
			}
			cout << number << " " << numberParent << " " << name << "\n";
		}
	}

	cin >> X >> Y;

	clock_t start, end;   // Khai báo biến thời gian
	double time_use;      // Thời gian sử dụng
	start = clock();

	node p = searchByName(head, X);

	if (Find(p, X, Y) == true)
	{
		Find(p, X, Y);
		cout << X << "=>";
		for (int i = run - 1; i >= run / 2; i--)
		{
			cout << result[i] << "=>";
		}
		cout << Y << endl;
	}
	else {
		cout << X << " khong phai cha cua " << Y << endl;
	}

	end = clock();  // lấy thời gian sau khi thực hiện 
	time_use = (double)(end - start) / CLOCKS_PER_SEC * 1000;    //Tính thời gian sử dụng
	cout << "Thoi gian chay y 2: " << time_use << " ms";
	

	cin >> Z;
	start = clock();
	node q = searchByName(head, Z);
	if (q == NULL)
	{
		cout << "Khong co nut trong cay" << endl;
	}
	else {
		cout << endl << "Tat ca cac node cua " << Z << " la" << endl;
		findFull(q);
	}

	end = clock();  // lấy thời gian sau khi thực hiện 
	time_use = (double)(end - start) / CLOCKS_PER_SEC * 1000;    //Tính thời gian sử dụng
	cout << "Thoi gian chay y 3: " << time_use <<" ms";

	return 0;
}