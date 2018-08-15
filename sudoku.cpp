#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <locale.h>
using namespace std;

int N;
vector<vector<int> > A,G;
vector<vector<pair<int,int> > > GtoA;

pair<int,int> better(){
	int best=0,temp;
	pair<int,int> cell;
	
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			if (A[i][j]==0) goto exit;
		}
	}
	return make_pair(-1,-1);
	exit:
	
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			if (A[i][j]==0){
				temp=0;
				for (int q=0; q<N; q++) if (A[i][q]!=0) temp++;
				for (int q=0; q<N; q++) if (A[q][j]!=0) temp++;
				for (auto c: GtoA[G[i][j]-1]) if (A[c.first][c.second]!=0) temp++;
				if (temp>best || best==0) { cell=make_pair(i,j); best=temp; }
			}
		}
	}
	return cell;
}

int sudoku(pair<int,int> cell){
	int r,flag=0;
	for (int q=1; q<=N; q++){
		for (int j=0; j<N; j++) if (A[cell.first][j]==q) goto next_q;
		for (int i=0; i<N; i++) if (A[i][cell.second]==q) goto next_q;
		for (auto c: GtoA[G[cell.first][cell.second]-1]) if (q==A[c.first][c.second]) goto next_q;
		A[cell.first][cell.second]=q;
		if (better()!=make_pair(-1,-1)) r=sudoku(better());
		else return 1;
		if (r==1) return 1;
		else A[cell.first][cell.second]=0;
		next_q:;
	}
	if (A[cell.first][cell.second]==0) return 0;
	
	return 1;
}

main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "rus");
	
	int a,r,x=0,y=0;
	char ch;
	ifstream file("input.txt");
	
	cout<<"Enter the number of different digits."; cin>>N;
	A.resize(N); G.resize(N); GtoA.resize(N);
	
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			file>>a;
			G[i].push_back(a);
			GtoA[a-1].push_back(make_pair(i,j));
		}
	}
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			A[i].push_back(0);
		}
	}
	//*******************************************************************************************
	loop1:
	system("cls");
	cout<<"Set the digits"<<endl<<endl;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
		if (x==i){
			for (int q=0; q<y*2; q++) cout<<" ";
			cout<<"-";
		}
		cout<<endl;
	}
	ch=getch();
	switch(ch){
		case 72: if (x>0) x--; goto loop1;
		case 80: if (x<N-1) x++; goto loop1;
		case 75: if (y>0) y--; goto loop1;
		case 77: if (y<N-1) y++; goto loop1;
		case 13: break;
		case 48: A[x][y]=0; goto loop1;
		case 49: A[x][y]=1; goto loop1;
		case 50: A[x][y]=2; goto loop1;
		case 51: A[x][y]=3; goto loop1;
		case 52: A[x][y]=4; goto loop1;
		case 53: A[x][y]=5; goto loop1;
		case 54: A[x][y]=6; goto loop1;
		case 55: A[x][y]=7; goto loop1;
		case 56: A[x][y]=8; goto loop1;
		case 57: A[x][y]=9; goto loop1;
		default: goto loop1;
	}
	cout<<endl<<endl;
	
	r=sudoku(better());
	cout<<r<<endl;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	system("pause");
}
