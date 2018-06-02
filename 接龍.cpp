#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#define S 20
using namespace std;
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

class Card {
private:
	int num;
	char suit;
public:
	friend void Shuffle(Card* card);
	friend void DisplayPoker(Card* card,int oflag,int* LastCOL,int& k,
							int *deletek,int eflag,int& sucess,int& i, int& j,int& z,int& t);
	friend void first(Card* card);
	friend void Exchange(int* LastCOL);
	friend void PutDown(Card* card,int& k,int* LastCOL, int *deletek,int& Psucess);
	friend void Up(int& i, int& j,int& z,int& t);
};
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
			Up(i,j,z,t);
			break;
		}
		system("cls");
		DisplayPoker(card,oflag,LastCOL,k,deletek,eflag,Psucess,i,j,z,t);
		if (command == 'o' || command == 'd' && Psucess==1) k++;
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
		Card temp = card[i];
		int position = rand() % 52;
		card[i] = card[position];
		card[position] = temp;
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
			if (kflag==1)
				cout << card[k].suit << setw(2) << setfill('0') << card[k].num;
			else
				cout << card[k+1].suit << setw(2) << setfill('0') << card[k+1].num;
		}
	}

	cout << "    ";
	cout << "a    " << "b    " << "c    " << "d  " << endl;
	cout << setw(10) << setfill(' ');
	if (!a[0].num) cout << " --- ";
	else cout << a[i-1].suit << setw(2) << setfill('0') << a[i-1].num << " ";
	if (!b[0].num) cout << " --- ";
	else cout << b[j-1].suit << setw(2) << setfill('0') << b[j-1].num << " ";
	if (!c[0].num) cout << " --- ";
	else cout << c[z-1].suit << setw(2) << setfill('0') << c[z-1].num << " ";
	if (!d[0].num) cout << " --- ";
	else cout << d[t-1].suit << setw(2) << setfill('0') << d[t-1].num << " ";

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
					cout << board[ROW][COL].suit << setw(2) << setfill('0') << board[ROW][COL].num << " ";
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
	cout << "請輸入 預換的行數 目的地行數 要移動的張數" << endl;
	cin >> preCOL >> changeCOL >> number;
	
	if ( board[LastCOL[changeCOL]][changeCOL].num - board[LastCOL[preCOL]-number+1][preCOL].num==1 &&
		board[LastCOL[changeCOL]][changeCOL].suit % 2 != board[LastCOL[preCOL] - number + 1][preCOL].suit % 2
		|| LastCOL[changeCOL] ==0 && board[LastCOL[preCOL] - number + 1][preCOL].num==13 )	
	{
		for (int i = 1;i<=number;++i)
		{
			LastCOL[changeCOL]++;
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
	static int i = 0;
	int changeCOL;

	cout << "請輸入目的地行數" << endl;
	cin >> changeCOL;
	int temp=k-1;
	Psucess = 0;
	if ( board[LastCOL[changeCOL]][changeCOL].num - card[temp].num == 1 &&
		board[LastCOL[changeCOL]][changeCOL].suit % 2 != card[temp].suit % 2 
		|| LastCOL[changeCOL] == 0 && card[temp].num ==13 )
	{
		LastCOL[changeCOL]++;
		board[LastCOL[changeCOL]][changeCOL].num = card[temp].num;
		board[LastCOL[changeCOL]][changeCOL].suit = card[temp].suit;
		board[LastCOL[changeCOL]][changeCOL].face = true;
		deletek[i] = temp;
		i++;
		Psucess = 1;
	}
}
void Up(int& i, int& j, int& z, int& t)
{
	char n;
	int ROW, COL,flag=0;

	cout << "請輸入要移動哪一張牌(列數 行數) 目的地" << endl;
	cin >> ROW >> COL >> n;
	switch (n)
	{
	case 'a':
	{
		if (a[0].num == 0 && board[ROW][COL].num==1 || a[0].suit == board[ROW][COL].suit
			&& board[ROW][COL].num - a[i - 1].num == 1)
		{
			a[i].num = board[ROW][COL].num;
			a[i].suit = board[ROW][COL].suit;
			board[ROW][COL].num = 0;
			flag = 1;
			i++;
		}
		break;
	}
	case 'b':
	{
		if (b[0].num == 0 && board[ROW][COL].num == 1 || b[0].suit == board[ROW][COL].suit
			&& board[ROW][COL].num - b[j - 1].num == 1)
		{
			b[j].num = board[ROW][COL].num;
			b[j].suit = board[ROW][COL].suit;
			board[ROW][COL].num=0;
			flag = 1;
			j++;
		}
		break;
	}
	case 'c':
	{
		if (c[0].num == 0 && board[ROW][COL].num == 1 || c[0].suit == board[ROW][COL].suit
			&& board[ROW][COL].num - c[z - 1].num == 1)
		{
			c[z].num = board[ROW][COL].num;
			c[z].suit = board[ROW][COL].suit;
			board[ROW][COL].num = 0;
			flag = 1;
			z++;
		}
		break;
	}
	case 'd':
	{
		if (d[0].num == 0 && board[ROW][COL].num == 1 || d[0].suit == board[ROW][COL].suit
			&& board[ROW][COL].num - d[t - 1].num == 1)
		{
			d[t].num = board[ROW][COL].num;
			d[t].suit = board[ROW][COL].suit;
			board[ROW][COL].num = 0;
			flag = 1;
			t++;
		}
		break;
	}
	}
	if(flag && !board[ROW-1][COL].face) board[ROW - 1][COL].face = true;
}




