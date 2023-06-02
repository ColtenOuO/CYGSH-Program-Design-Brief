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
	cout << "�п�J�����ҸաA�@���X��ǥ�\n\n";
	
	cout << "�����Ҹժ��ǥͼƶq : ";
	
	cin >> student_count;
	
	cout << "\n�n���A�����Ҹզ@�� " << student_count << " �ǥ�\n\n";
	
	cout << "���U�ӡA�п�J�����Ҹզ@���X�D ( ���h��@�_�p�� )\n\n";
	
	cout << "�����Ҹժ��D�ؼƶq : ";
	
	cin >> problem_count;
	
	cout << "\n�n���A�����Ҹզ@�� " << problem_count << " �D���D\n\n";
	
	return;
}
void problem_score_setting()
{
	cout << "���U�ӡA�n�]�w�C�@�D���t���A���T�w�@�U�A�аݥ����ҸլO�_���h���D�A���п�J 1�A�S���h��J 0\n\n";
	
	cout << "�����ҸլO�_���h���D : ";
	
	bool check;
	
	cin >> check;
	
	if( check == true )
	{
		cout << "\n�w�T�{�����Ҹժ��D�اt���h���D�A���U�ӱN�i��h���D�t�����{��\n\n";
		
		cout << "�п�J�����Ҹզ@���X�D�h���D\n\n";
		
		int problem_count;
		
		cout << "�����Ҹժ��h���D�D�� : ";
		
		cin >> problem_count;
		
		cout << "\n�n���A�����Ҹզ@�� " << problem_count << " �D�h���D�A���U�ӽШ̧ǿ�J���X�D(�D��)���h���D\n\n";
		
		cout << "��J�榡�d�� : 30 31 32 33 34 35 36 37 41 47 50\n\n";
		
		cout << "�п�J�h���D���D�� : ";
		
		for(int i=0;i<problem_count;i++)
		{
			int problem_num;
			
			cin >> problem_num;
			
			is_more_choose_problem[problem_num] = true;
		}
		
		cout << "\n���U�ӱN�T�{�h���D���t���A���U�ӽШ̷Ӵ��ܶi���J\n\n";
		
		for(int i=0;i<=5;i++)
		{
			cout << "�� " << i << " �ӿﶵ�i�H�o�쪺���� : ";
			
			int input;
			
			cin >> input;
			
			more_choose_score_set[i] = input; 
		}
		
		cout << "\n�h���D�t���]�w����...\n\n";
	}
	else
	{
		cout << "\n�w�T�{�����Ҹժ��D�ؤ��t���h���D\n\n";
	}
	
	cout << "���U�ӱN�i�����D���t���]�w�A�]�w�����п�J 0 0 0 �����]�w�{��\n\n";
	
	while( true )
	{
		cout << "�п�J�T�ӼƦr L,R,S  ( L <= R ) ��ܱN�D�� L ~ R �C�@�D���t���]�m�� S : ";
		
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
	
	cout << "\n\n����D�t���]�w����...";
	
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
	
	cout << "�y��\t" << "����\t";
	
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
//	before(); �p�i�H���Ф@�U�p���{�� 
	
	student_problem_count_get();
	
	problem_score_setting();
	
	cout << "�{���B�⤤... �p�⧹����N�۰������{��\n\n";
	
	student_answer_get();
	
	correct_answer_get();
	
	student_answer_checker();
	
	excel_data_write();
	
	return 0;
}
