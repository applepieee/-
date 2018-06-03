#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<Windows.h>
#define S 20

using namespace std;
static int p = 0,numCOL[8] = { 0,1,2,3,4,5,6,7 };
struct Up {
	int num;
	char suit;
}a[13],b[13],c[13],d[13];
struct MyStruct
{
	int num;
	char suit;
	bool face;
}board[S][S];

typedef struct {
	int num;
	char suit;
}Card; 


void Shuffle(Card* card);
void DisplayPoker(Card* card,int oflag,int* LastCOL,int& k,
							int *deletek,int eflag,int& sucess,int& i, int& j,int& z,int& t);
void first(Card* card);
void Exchange(int* LastCOL);
void PutDown(Card* card,int& k,int* LastCOL, int *deletek,int& Psucess);
void Up(int& i, int& j,int& z,int& t,int* LastCOL);
void Right(Card* card, int *deletek,int &k, int& i, int& j, int& z, int& t);

int main()
{
	int oflag = 0,eflag = 0,Psucess=1;
	static int k=28,i=0,j=0,z=0,t=0;
	static int LastCOL[8] = { 0,1,2,3,4,5,6,7 }, deletek[24] = {0};
	char command;
	Card card[52];

	for (int i = 0;i < 13;++i)
	{
		a[i].num = 0;
		b[i].num = 0;
		c[i].num = 0;
		d[i].num = 0;
	}
	for (int i = 1;i < S;++i)
		for (int j = 1;j < S;++j)
		{
			board[i][j].num = 0;
			board[i][j].face = false;
		}

	Shuffle(card);
	first(card);
	DisplayPoker(card,oflag,LastCOL,k,deletek,eflag,Psucess,i,j,z,t);
	while (1)
	{
		Psucess = 1;
		eflag = 0;
		cin >> command;
		switch (command)
		{
		case 'e':
		{
			eflag = 1;
			Exchange(LastCOL);
			break;
		}
		case 'o':
			oflag = 1;
			break;
		case 'd':
			PutDown(card,k,LastCOL,deletek,Psucess);
			break;
		case 'u':
			Up(i,j,z,t,LastCOL);
			break;
		case 'r':
			Right(card,deletek,k,i,j,z,t);
			break;
		}
		system("cls");
		DisplayPoker(card,oflag,LastCOL,k,deletek,eflag,Psucess,i,j,z,t);
		if (command == 'o' || command == 'd' && Psucess==1 || command == 'r') k++;
	}
}
void Shuffle(Card* card)
{
	srand((unsigned)time(NULL));
	for (int i = 0;i < 52;++i)
	{
		switch (i / 13)
		{
			case 0:
				card[i].suit = 'S';//黑桃 B
				break;
			case 1:
				card[i].suit = 'H';//紅心 R
				break;
			case 2:
				card[i].suit = 'C';//梅花 B
				break;
			case 3:
				card[i].suit = 'D';//方塊 R
				break;
		}
		card[i].num = i % 13 + 1;
	}
	for (int i = 0;i < 52;++i)
	{
		int position = rand() % 52;
		swap(card[i], card[position]);
	}
}
void first(Card* card)
{
	int space, i, j = 0;
	int FirstNum = 1;

	for (int ROW = 1;ROW <= 7;++ROW)
	{
		for (int COL = FirstNum;COL <= 7;++COL, ++j)
		{
			if (COL == FirstNum) board[ROW][COL].face = true;
			board[ROW][COL].num = card[j].num;
			board[ROW][COL].suit = card[j].suit;
		}
		++FirstNum;
	}
}
void DisplayPoker(Card* card,int oflag,int* LastCOL,int& k,int *deletek,
				 int eflag,int& Psucess, int& i, int& j, int& z, int& t)
{
	int kflag=1;
	if (eflag==1 & k > 28 || Psucess==0)
		cout << card[k - 1].suit << setw(2) << setfill('0') << card[k - 1].num;
	else
	{
		if (!oflag)
			cout << "***";
		else
		{
			if (k >= 52) k = 28;
			for (int i = 0;i < 24;++i)
				if (k == deletek[i]) kflag = 0;
			if (kflag) {
				if (card[k].suit == 'H' || card[k].suit == 'D')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
					cout << card[k].suit;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				}	
				else cout << card[k].suit;
				cout << setw(2) << setfill('0') << card[k].num;
			}
			else
				cout << card[k+1].suit << setw(2) << setfill('0') << card[k+1].num;
		}
	}

	cout << "    ";
	cout << "a    " << "b    " << "c    " << "d  " << endl;
	cout << setw(10) << setfill(' ');
	if (!a[0].num) cout << " --- ";
	else {
		if (a[i - 1].suit == 'H' || a[i - 1].suit == 'D')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			cout << a[i - 1].suit;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		}
		else cout << a[i - 1].suit;
		cout << setw(2) << setfill('0') << a[i - 1].num << " ";
	}
	if (!b[0].num) cout << " --- ";
	else {
		if (b[j - 1].suit == 'H' || b[j - 1].suit == 'D')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << b[j - 1].suit;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else cout << b[j - 1].suit;
		cout<< setw(2) << setfill('0') << b[j - 1].num << " ";
	}
	if (!c[0].num) cout << " --- ";
	else {
		if (c[z - 1].suit == 'H' || c[z - 1].suit == 'D')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << c[z - 1].suit;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else cout << c[z - 1].suit;
		cout << setw(2) << setfill('0') << c[z - 1].num << " ";
	}
	if (!d[0].num) cout << " --- ";
	else {
		if (d[t - 1].suit == 'H' || d[t - 1].suit == 'D')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << d[t - 1].suit;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else cout << d[t - 1].suit;
		cout << setw(2) << setfill('0') << d[t - 1].num << " ";
	}

	cout << endl << endl;
	for (int i = 1;i <= 7;++i) cout << " " << i << "  ";
	cout << endl;
	for (int ROW = 1;ROW < S;++ROW)
	{
		for (int COL = 1;COL < S;++COL)
		{
			if (board[ROW][COL].num !=0)
			{
				if (board[ROW][COL].face)
				{
					if (board[ROW][COL].suit == 'H' || board[ROW][COL].suit == 'D')
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
						cout << board[ROW][COL].suit;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					}
					else cout << board[ROW][COL].suit;
					cout << setw(2) << setfill('0') << board[ROW][COL].num << " ";
				}
				else
					cout << "***" << " ";
			}
			else
				cout << "    ";
		}
		cout << endl;
	}
}
void Exchange(int* LastCOL)
{
	int preCOL, changeCOL,number;
	char c;
	cout << "請輸入 預換的行數 目的地行數 要移動的張數" << endl;
	cin >> preCOL >> changeCOL >> number;

	if ( board[LastCOL[changeCOL]][changeCOL].num - board[LastCOL[preCOL]-number+1][preCOL].num==1 &&
		board[LastCOL[changeCOL]][changeCOL].suit % 2 != board[LastCOL[preCOL] - number + 1][preCOL].suit % 2
		|| LastCOL[changeCOL] ==0 && board[LastCOL[preCOL] - number + 1][preCOL].num==13 )	
	{
		for (int i = 1;i<=number;++i)
		{
			LastCOL[changeCOL]++; numCOL[changeCOL]++; numCOL[preCOL]--;
			board[LastCOL[changeCOL]][changeCOL].num = board[LastCOL[preCOL] - number + i][preCOL].num;
			board[LastCOL[changeCOL]][changeCOL].suit = board[LastCOL[preCOL] - number + i][preCOL].suit;
			board[LastCOL[changeCOL]][changeCOL].face = true;
			board[LastCOL[preCOL] - number + i][preCOL].num = 0;
		}
		LastCOL[preCOL]-=number;
	}
	if (!board[LastCOL[preCOL]][preCOL].face) board[LastCOL[preCOL]][preCOL].face = true;
}
void PutDown(Card* card,int& k,int* LastCOL,int *deletek,int& Psucess)
{
	int changeCOL;
	cout << "請輸入目的地行數" << endl;
	cin >> changeCOL;
	int temp=k-1;
	Psucess = 0;

	if ( board[LastCOL[changeCOL]][changeCOL].num - card[temp].num == 1 &&
		board[LastCOL[changeCOL]][changeCOL].suit % 2 != card[temp].suit % 2 
		|| LastCOL[changeCOL] == 0 && card[temp].num ==13 )
	{
		LastCOL[changeCOL]++; numCOL[changeCOL]++;
		board[LastCOL[changeCOL]][changeCOL].num = card[temp].num;
		board[LastCOL[changeCOL]][changeCOL].suit = card[temp].suit;
		board[LastCOL[changeCOL]][changeCOL].face = true;
		deletek[p++] = temp;
		Psucess = 1;
	}
}
void Up(int& i, int& j, int& z, int& t,int* LastCOL)
{
	char n;
	int preCOL,flag=1;

	cout << "請輸入要移動哪一張牌(行數) 目的地" << endl;
	cin >> preCOL >> n;
	numCOL[preCOL]--;
	switch (n)
	{
	case 'a':
		if (a[0].num == 0 && board[LastCOL[preCOL]][preCOL].num ==1 || a[0].suit == board[LastCOL[preCOL]][preCOL].suit
			&& board[LastCOL[preCOL]][preCOL].num - a[i - 1].num == 1)
		{
			a[i].num = board[LastCOL[preCOL]][preCOL].num;
			a[i].suit = board[LastCOL[preCOL]][preCOL].suit;
			i++;
		}
		break;
	case 'b':
		if (b[0].num == 0 && board[LastCOL[preCOL]][preCOL].num == 1 || b[0].suit == board[LastCOL[preCOL]][preCOL].suit
			&& board[LastCOL[preCOL]][preCOL].num - b[j - 1].num == 1)
		{
			b[j].num = board[LastCOL[preCOL]][preCOL].num;
			b[j].suit = board[LastCOL[preCOL]][preCOL].suit;
			j++;
		}
		break;
	case 'c':
		if (c[0].num == 0 && board[LastCOL[preCOL]][preCOL].num == 1 || c[0].suit == board[LastCOL[preCOL]][preCOL].suit
			&& board[LastCOL[preCOL]][preCOL].num - c[z - 1].num == 1)
		{
			c[z].num = board[LastCOL[preCOL]][preCOL].num;
			c[z].suit = board[LastCOL[preCOL]][preCOL].suit;
			z++;
		}
		break;
	case 'd':
		if (d[0].num == 0 && board[LastCOL[preCOL]][preCOL].num == 1 || d[0].suit == board[LastCOL[preCOL]][preCOL].suit
			&& board[LastCOL[preCOL]][preCOL].num - d[t - 1].num == 1)
		{
			d[t].num = board[LastCOL[preCOL]][preCOL].num;
			d[t].suit = board[LastCOL[preCOL]][preCOL].suit;
			t++;
		}
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		board[LastCOL[preCOL]][preCOL].num = 0;
		LastCOL[preCOL]--;
	}
	if(flag && !board[LastCOL[preCOL]][preCOL].face) board[LastCOL[preCOL]][preCOL].face = true;
}
void Right(Card* card,int *deletek,int &k, int& i, int& j, int& z, int& t)
{
	char n;
	cout << "請輸入要移動至右邊哪一欄" << endl;
	cin >> n;
	int temp = k - 1,rflag=1;

	switch (n)
	{
	case 'a':
		if (a[0].num==0 && card[temp].num==1
			|| a[0].suit == card[temp].suit && card[temp].num - a[i - 1].num == 1)
		{
			a[i].num = card[temp].num;
			a[i].suit = card[temp].suit;
			i++;
		}
		break;
	case 'b':
		if (b[0].num == 0 && card[temp].num == 1
			|| b[0].suit == card[temp].suit && card[temp].num - b[j - 1].num == 1)
		{
			b[j].num = card[temp].num;
			b[j].suit = card[temp].suit;
			j++;
		}
		break;
	case 'c':
		if (c[0].num == 0 && card[temp].num == 1
			|| c[0].suit == card[temp].suit && card[temp].num - c[z - 1].num == 1)
		{
			c[z].num = card[temp].num;
			c[z].suit = card[temp].suit;
			z++;
		}
		break;
	case 'd':
		if (d[0].num == 0 && card[temp].num == 1
			|| d[0].suit == card[temp].suit && card[temp].num - d[t - 1].num == 1)
		{
			d[t].num = card[temp].num;
			d[t].suit = card[temp].suit;
			t++;
		}
		break;
	default:
		rflag = 0;
		break;
	}
	if(rflag) deletek[p++] = temp;
}




