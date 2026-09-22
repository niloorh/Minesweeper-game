#include <iostream>
#include "clui.h"
#include <stdlib.h>
#include <iomanip>
#include <ctime>
using namespace std;

int choosing_row;
int choosing_col;
int choosing_mine;
char *name;
char field[30][30];
char mine[30][30];
char flag[30][30];
int count_flag;
int level;
bool lose=true;

struct acc
{
	char *name;
	int point;
};

struct unfin
{
	char *name;
	char field[30][30];
	char mine[30][30];
	char flag[30][30];
	int column;
	int row;
};
unfin *saved;
acc *accounts;
acc *currentt;

int users;

void bubble_sort()
{
	for (int i = 0; i < users; i++)
		for (int j = 0; j < users - i - 1; j++)
			if (accounts[j + 1].point > accounts[j].point)
				swap(accounts[j], accounts[j + 1]);
}

void add()
{
	users++;
	acc *listt = new acc[users];
	for (int i = 0; i < users - 1; i++)
		listt[i] = accounts[i];
	delete[] accounts;
	accounts = listt;

	accounts[users - 1].point = currentt->point;
	accounts[users - 1].name = currentt->name;
	currentt->name = new char[100];

	bubble_sort();
}

void add2()
{
	users++;
	unfin *listt = new unfin[users];
	for (int i = 0; i < users - 1; i++)
		listt[i] = saved[i];
	delete[] saved;
	saved = listt;

	saved[users - 1].name = currentt->name;
	currentt->name = new char[100];
	saved->row = choosing_row;
	saved->column = choosing_col;
	
	for (int i = 0; i < saved->row ; i++)
		for (int j = 0; i < saved->column; j++)
			saved->field[i][j] = field[i][j];
		

	for (int i = 0; i < saved->row ; i++)
		for (int j = 0; i <saved->column ; j++)
			saved->flag[i][j] = flag[i][j];

	for (int i = 0; i < saved->row ; i++)
		for (int j = 0; i < saved->column ; j++)
			saved->mine[i][j] = mine[i][j];
	
	int size_word = 0;
	while (saved[users - 1].name[size_word] != '\0')
		size_word++;

	for (char i = 0; i <= size_word; i++)
		currentt->name[i] = saved[users - 1].name[i];
}



void intro()
{
	change_color_rgb(245, 66, 111);
	cout << "welcome to hell ;3" << endl;
	delay(1000);
	change_color_rgb(66, 102, 245);
	cout << "YOU ARE NOW PLAYING MINESWEEPER" << endl;
	delay(1000);
	change_color_rgb(245, 66, 111);
	cout << "Enter your name:" << endl;
    change_color_rgb(134, 219, 192);
	cin.getline(currentt->name, 100);
	reset_color();
	clear_screen();
}

void fieldd(char field[30][30])
{
	for (int i = 0; i < choosing_row; i++)
	{
		for (int j = 0; j < choosing_col; j++)
		{
			field[i][j] = '*';
		}
	}
}

void show_the_field(char field[30][30])
{
	change_color_rgb(177, 3, 252);
	for (int a = 0; a < choosing_col; a++)
	{
		if (a + 1 < 10)
			cout << a << "   ";
		else
			cout << a << "  ";
	}

	cout << choosing_col;
	reset_color();
	cout << endl;
	cout << endl;
	for (int i = 0; i < choosing_row; i++)
	{
		change_color_rgb(177, 3, 252);
		if (i + 1 >= 10)
			cout << i + 1 << "  ";
		else
			cout << i + 1 << "   ";
		reset_color();

		for (int j = 0; j < choosing_col; j++)
		{
			if (j >= 9)
				cout << field[i][j] << "   ";
			if (j < 9)
				cout << field[i][j] << "   ";
		}

		cout << endl;
		cout << endl;
	}
}

void numnum(int i, int j, int a, int b)
{
	if (a >= 0 && a < choosing_row && b >= 0 && b < choosing_col && mine[a][b] == 'm' && mine[i][j] != 'm')
		mine[i][j]++;
}

void mines(char mine[30][30])
{

	for (int i = 0; i < choosing_row; i++)
		for (int j = 0; j < choosing_col; j++)
			mine[i][j] = '0';

	int i = 0, j = 0;
	srand(time(NULL));
	for (int x = 0; x < choosing_mine; x++)
	{
		int i = rand() % choosing_row;
		int j = rand() % choosing_col;
		if (mine[i][j] == 'm')
			x--;
		else
			mine[i][j] = 'm';
	}

	for (int i = 0; i < choosing_row; i++)
		for (int j = 0; j < choosing_col; j++)
		{
			numnum(i, j, i - 1, j);
			numnum(i, j, i + 1, j);
			numnum(i, j, i, j - 1);
			numnum(i, j, i, j + 1);
			numnum(i, j, i - 1, j - 1);
			numnum(i, j, i - 1, j + 1);
			numnum(i, j, i + 1, j - 1);
			numnum(i, j, i + 1, j + 1);
		}
}

bool mine_check(char mine[30][30], int a, int b)
{

	if (mine[a][b] == 'm')
		return true;
	else
		return false;
}

int flagg(int a, int b)
{
	if (count_flag == choosing_mine)
	{
		clear_screen();
		change_color_rgb(255, 25, 41);
		cout << "You can not put any more flags!" << endl;
		getch();
		reset_color();
		delay(2000);
		clear_screen();
		show_the_field(field);
		return 0;
	}

	if (flag[a][b] == 'f')
	{
		flag[a][b] = '*';
		count_flag--;
	}
	else if (field[a][b] >= '0' && field[a][b] <= '6')
	{
		clear_screen();
		change_color_rgb(255, 25, 41);
		cout << "why on earth you wanna put a flag on a cell you've selected before?!" << endl;
		delay(2000);
		cout << "do it again" << endl;
		getch();
		reset_color();
		delay(2000);
		show_the_field(field);
		return 0;
	}
	else
	{
		flag[a][b] = 'f';
		count_flag++;
	}
	field[a][b] = flag[a][b];
	clear_screen();
	show_the_field(field);
}

int choosing(int a, int b)
{

	if (flag[a][b] == 'f')
	{
		clear_screen();
		change_color_rgb(255, 25, 41);
		cout << "take the flag off first!!" << endl;
		getch();
		clear_screen();
		reset_color();
		show_the_field(field);
		return 0;
	}

	if (mine_check(mine, a, b) == true)
	{
		play_beep();
		clear_screen();
		change_color_rgb(245, 66, 111);
		cout << "BOOM!" << endl
			 << "YOU LOST EHEHE" << endl;
		reset_color();
		for (int i = 0; i < choosing_row; i++)
			for (int j = 0; j < choosing_col; j++)
				if (mine[i][j] == 'm')
					field[i][j] = mine[i][j];
		show_the_field(field);
		getch();
		change_color_rgb(245, 66, 111);
		cout<<"Do you want to play again LOSER?"<<endl<<"Well actually you will be moved to the (MENU),decide it there!"<<endl;
		reset_color();
		lose=false;
        getch();
		clear_screen();
		return 0;
	}
	if ((mine_check(mine, a, b) == false) && field[a][b] == '*')
		field[a][b] = mine[a][b];
	clear_screen();
	show_the_field(field);
}

bool win_check(char field[30][30])
{
	bool check = true;
	int count = 0;
	for (int i = 0; i < choosing_row; i++)
		for (int j = 0; j < choosing_col; j++)
			if ((field[i][j] != '*') && (field[i][j] != 'f'))
			{
				count++;
			}
	if (count != (choosing_row * choosing_col) - choosing_mine)
		check = false;
	return check;
}

void gamee()
{
	int x = get_window_rows();
	int y = get_window_cols();

	clear_screen();
	show_the_field(field);

	int col = 1;
	int row = 1;

	cursor_to_pos(1 + row * 2 + 2, 1 + col * 4 + 4);
	while (true)
	{
		if(lose==false)
		return ;

		char read = getch();

		if (read == 'w')
		{
			if (row > 0)
			{
				row--;
			}
		}

		if (read == 'a')
		{
			if (col > 0)
			{
				col--;
			}
		}

		if (read == 's')
		{
			if (row < choosing_row - 1)
			{
				row++;
			}
		}

		if (read == 'd')
		{
			if (col < choosing_col - 1)
			{
				col++;
			}
		}

		cursor_to_pos(1 + row * 2 + 2, 1 + col * 4 + 4);

		if (read == ' ')
			choosing(row, col);

		if (read == 'f')
			flagg(row, col);

		if (read == 'o')
		{
			add2();
		
			clear_screen();
			change_color_rgb(245, 66, 111);
			cout << "Your game will be saved";
			cout<<"(but honestly finish a game when you start it -_-)" << endl;
			reset_color();
				getch();
			return;
		}

		if (read == 'q')
		{
			clear_screen();
			cout << "Are you sure you want to quit?(your game won't be saved!)" << endl;
			cout << "1.yes" << endl
				 << "2.no" << endl;
			int i;
			cin >> i;
			if (i == 1)
				return;
			if (i == 2)
			{
				clear_screen();

				show_the_field(field);

				int col = 1;
				int row = 1;

				cursor_to_pos(1 + row * 2 + 2, 1 + col * 4 + 4);
			}
		}

		if (win_check(field) == true)
		{
			play_beep();
			change_color_rgb(245, 66, 111);
			cout << "!CONGRATULATION!" << endl
				 << "!YOU WON!";
			if (level == 1)
				currentt->point = 5 * 5 * 4;
			if (level == 2)
				currentt->point = 12 * 12 * 28;
			if (level == 3)
				currentt->point = 20 * 20 * 96;
			if (level == 4)
				currentt->point = choosing_row * choosing_col * choosing_mine;
			for (int i = 0; i < users; i++)
				if (accounts[i].name == currentt->name)
					accounts[i].point = currentt->point;
				else
					add();

			reset_color();

			exit(0);
		}
	}
}

void newgame()
{
	change_color_rgb(108, 103, 207);
	cout << "Select a level:" << endl;
	delay(500);
	change_color_rgb(204, 18, 130);
	cout << "1.";
	change_color_rgb(99, 176, 167);
	cout << "Beginner" << endl;
	change_color_rgb(204, 18, 130);
	cout << "2.";
	change_color_rgb(99, 176, 167);
	cout << "Intermediate" << endl;
	change_color_rgb(204, 18, 130);
	cout << "3.";
	change_color_rgb(99, 176, 167);
	cout << "Expert" << endl;
	change_color_rgb(204, 18, 130);
	cout << "4.";
	change_color_rgb(99, 176, 167);
	cout << "Be creative and make the game as you want(hell that took a lot of time from me tho)" << endl;
	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		choosing_row = 5;
		choosing_col = 5;
		choosing_mine = 4;
		level = 1;
		break;
	case 2:
		choosing_row = 12;
		choosing_col = 12;
		choosing_mine = 28;
		level = 2;
		break;
	case 3:
		choosing_row = 20;
		choosing_col = 20;
		choosing_mine = 96;
		level = 3;
		break;
	case 4:
		clear_screen();
		cout << "Enter the number of rows:" << endl;
		int rowrow;
		cin >> rowrow;
		choosing_row = rowrow;
		cout << "Enter the number of columns:" << endl;
		int colcol;
		cin >> colcol;
		choosing_col = colcol;
		cout << "Enter the number of the mines" << endl;
		int minemine;
		cin >> minemine;
		choosing_mine = minemine;
		level = 4;
		break;
	}
	fieldd(field);
	mines(mine);
	gamee();
}

void menu()
{

	while (true)
	{
		char *temp = new char[2];

		change_color_rgb(108, 103, 207);
		cout << "please choose your option from the menu" << endl;
		delay(500);
		change_color_rgb(204, 18, 130);
		cout << "1.";
		change_color_rgb(99, 176, 167);
		cout << "New Game" << endl;
		change_color_rgb(204, 18, 130);
		cout << "2.";
		change_color_rgb(99, 176, 167);
		cout << "Load Game" << endl;
		change_color_rgb(204, 18, 130);
		cout << "3.";
		change_color_rgb(99, 176, 167);
		cout << "Change Name" << endl;
		change_color_rgb(204, 18, 130);
		cout << "4.";
		change_color_rgb(99, 176, 167);
		cout << "Leaderboard" << endl;
		change_color_rgb(204, 18, 130);
		cout << "5.";
		change_color_rgb(99, 176, 167);
		cout << "Quit" << endl;

		cin.getline(temp, 2);
		int i = temp[0] - '0';
		clear_screen();

		int sizee = 0;

		switch (i)
		{
		case 1:
			newgame();
			lose=true;
			break;
		case 2:
		if(users==0)
		{cout<<"There are no saved games!"<<endl;
		getch();
		clear_screen();
		break;}
			else 
			cout << "choose one of the games to continue playing it" << endl;
			for (int i = 0; i < users; i++)
				cout << i+1 << "." << saved[i].name << endl;
			int x;
			cin >> x;
			for (int i = 0; i <saved[x-1].row ; i++)
				for (int j = 0; i < saved[x-1].column; j++)
					field[i][j] = saved[x-1].field[i][j];

			for (int i = 0; i < saved[x-1].row; i++)
				for (int j = 0; i < saved[x-1].column; j++)
					flag[i][j] = saved[x-1].flag[i][j];

			for (int i = 0; i < saved[x-1].row; i++)
				for (int j = 0; i < saved[x-1].column; j++)
					mine[i][j] = saved[x-1].mine[i][j];

					
	while (saved[x-1].name[sizee] != '\0')
		sizee++;
getch();
	for (char i = 0; i < sizee; i++)
		 {saved[x-1].name[i]=currentt->name[i];}

			 gamee();

			break;
		case 3:
			cout << "Enter the new name:" << endl;
			cin.getline(currentt->name, 100);
			cout << "Name changed successfully!" << endl;
			delay(1000);
			clear_screen();
			break;
		case 4:
		if(users==0)
		{cout<<"There are no scores here yet!"<<endl;
		getch();
		clear_screen();
		break;}
		cout<<"These are the best scores!"<<endl;
		for (int i = 0; i < users; i++)
				{cout << i + 1<< "." << accounts[i].name << ":"<< accounts[i].point<<endl;}
            getch();
			break;
		case 5:
			change_color_rgb(245, 66, 111);
			cout << "should've done it sooner!" << endl;
			reset_color();
			exit(0);
			delete[] temp;
		}
	}
}

int main()
{

	currentt = new acc;
	currentt->name = new char[100];
	accounts = new acc;
	saved = new unfin;
	init_clui();

	intro();

	menu();

	fieldd(field);

	mines(mine);
}