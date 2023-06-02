#include <iostream>

#include <sstream>

#include <fstream>

#include <algorithm>

using namespace std;

int student_count,problem_count;

string student_answer_data[105][105];

string correct_answer_data[105];

double student_total_score[105];

double problem_score[105];

double more_choose_score_set[105];

bool is_more_choose_problem[105];

bool is_student_answer_correct[105][105];

void check_data_debug()
{
	for(int i=1;i<=student_count;i++)
	{
		for(int k=1;k<=problem_count;k++)
		{
			cout << student_answer_data[i][k];
		}
		
		cout << "\n";
	}	
}
void student_problem_count_get()
{
	cout << "請輸入本次考試，共有幾位學生\n\n";
	
	cout << "本次考試的學生數量 : ";
	
	cin >> student_count;
	
	cout << "\n好的，本次考試共有 " << student_count << " 學生\n\n";
	
	cout << "接下來，請輸入本次考試共有幾題 ( 單選多選一起計算 )\n\n";
	
	cout << "本次考試的題目數量 : ";
	
	cin >> problem_count;
	
	cout << "\n好的，本次考試共有 " << problem_count << " 道問題\n\n";
	
	return;
}
void problem_score_setting()
{
	cout << "接下來，要設定每一題的配分，先確定一下，請問本次考試是否有多選題，有請輸入 1，沒有則輸入 0\n\n";
	
	cout << "本次考試是否有多選題 : ";
	
	bool check;
	
	cin >> check;
	
	if( check == true )
	{
		cout << "\n已確認本次考試的題目含有多選題，接下來將進行多選題配分的程序\n\n";
		
		cout << "請輸入本次考試共有幾題多選題\n\n";
		
		int problem_count;
		
		cout << "本次考試的多選題題數 : ";
		
		cin >> problem_count;
		
		cout << "\n好的，本次考試共有 " << problem_count << " 題多選題，接下來請依序輸入哪幾題(題號)為多選題\n\n";
		
		cout << "輸入格式範例 : 30 31 32 33 34 35 36 37 41 47 50\n\n";
		
		cout << "請輸入多選題的題號 : ";
		
		for(int i=0;i<problem_count;i++)
		{
			int problem_num;
			
			cin >> problem_num;
			
			is_more_choose_problem[problem_num] = true;
		}
		
		cout << "\n接下來將確認多選題的配分，接下來請依照提示進行輸入\n\n";
		
		for(int i=0;i<=5;i++)
		{
			cout << "錯 " << i << " 個選項可以得到的分數 : ";
			
			int input;
			
			cin >> input;
			
			more_choose_score_set[i] = input; 
		}
		
		cout << "\n多選題配分設定完成...\n\n";
	}
	else
	{
		cout << "\n已確認本次考試的題目不含有多選題\n\n";
	}
	
	cout << "接下來將進行單選題的配分設定，設定完成請輸入 0 0 0 結束設定程序\n\n";
	
	while( true )
	{
		cout << "請輸入三個數字 L,R,S  ( L <= R ) 表示將題號 L ~ R 每一題的配分設置為 S : ";
		
		double L,R,S;
		
		cin >> L >> R >> S;
		
		if( L == 0.0 && R == 0.0 && S == 0.0 )
		{
			break;	
		}
		
		for(int i=L;i<=R;i++)
		{
			problem_score[i] = S;
		}
	}
	
	cout << "\n\n單選題配分設定完成...";
	
	return;
}
void student_answer_get()
{
	ifstream ifs( "student_answer_pasted.txt",ios::in );
	
	if( !ifs.is_open() )
	{
		cout << "Fail to open student_answer file\n";
		
		exit(0);
	}
	else
	{
		string s;
		
		int index1 = 0;
		
		while( getline(ifs,s) )
		{
			int index2 = 0;
			
			stringstream ss;
			
			ss << s;
			
			string s2;
			
			while( ss >> s2 )
			{
				student_answer_data[index1][index2] = s2;
				
				index2++; 
			}
			
			index1++;
		}
	}
	
	return;
}
void correct_answer_get()
{
	ifstream ifs( "test_answer_pasted.txt",ios::in );
	
	if( !ifs.is_open() )
	{
		cout << "Fail to test answer file\n";
		
		exit(0);
	}
	else
	{
		string s;
		
		int index = 0,problem_ID = 0;
		
		while( getline(ifs,s) )
		{
			if( index == 0 )
			{
				index++;
				
				continue;
			}
			
			stringstream ss;
			
			ss << s;
			
			string u2;
			
			while( ss >> u2 )
			{
				if( problem_ID != 0 )
				{
					correct_answer_data[problem_ID] = u2;	
				}
				
				problem_ID++;
			}
		}
	}
	
	return;
}
void student_answer_checker()
{
	for(int i=1;i<=student_count;i++)
	{
		for(int k=1;k<=problem_count;k++)
		{
			if( is_more_choose_problem[k] == true )
			{
				/* sort the student answer and correct answer */
				
				sort( correct_answer_data[k].begin(),correct_answer_data[k].end() );
				
				sort( student_answer_data[i][k].begin(),student_answer_data[i][k].end() );
				
				if( student_answer_data[i][k] == correct_answer_data[k] ) // student's answer is correct
				{
					student_total_score[i] += more_choose_score_set[0]; // wrong answer's count is zero
					
					is_student_answer_correct[i][k] = true;
				}
				else
				{
					is_student_answer_correct[i][k] = false;
					
					int correct_count = 0,index = 0;
					
					for(int j=0;j<correct_answer_data[k].size();j++)
					{
						for(int t=index;t<student_answer_data[i][k].size();t++)
						{
							if( student_answer_data[i][k][t] == correct_answer_data[k][j] )
							{
								correct_count++;
								
								index = t + 1;
								
								break;
							}
						}
					}
					
					student_total_score[i] += more_choose_score_set[5 - correct_count];
				}
			}
			else
			{
				if( student_answer_data[i][k] == correct_answer_data[k] )
				{
					is_student_answer_correct[i][k] = true;
					
					student_total_score[i] += problem_score[k];
				}
				else
				{
					is_student_answer_correct[i][k] = false;
				}
			}
		}
	}
	
	return;
}
void excel_data_write()
{
	ofstream oFILE;
	
	freopen("student_score_copy.txt","w",stdout);
	
	cout << "座號\t" << "分數\t";
	
	for(int i=1;i<=problem_count;i++)
	{
		cout << "Q" << i << "\t"; 
	}
	
	cout << "\n";
	
	for(int i=1;i<=student_count;i++)
	{
		cout << i << "\t" << student_total_score[i] << "\t";
		
		for(int k=1;k<=problem_count;k++)
		{
			if( is_student_answer_correct[i][k] == true )
			{
				cout << "O\t";
			}
			else
			{
				cout << "X\t";
			}
		}
		
		cout << "\n";
	}
	
	return;
}
int main(void)
{
//	before(); 妳可以介紹一下妳的程式 
	
	student_problem_count_get();
	
	problem_score_setting();
	
	cout << "程式運算中... 計算完成後將自動關閉程式\n\n";
	
	student_answer_get();
	
	correct_answer_get();
	
	student_answer_checker();
	
	excel_data_write();
	
	return 0;
}
