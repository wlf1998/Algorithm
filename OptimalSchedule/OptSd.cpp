#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#define INFINITY 999999999    //���������INFINITY=999999999
#define MAXSIZE 100           //�������������
using namespace std;

//��������ȫ�ֱ���
//int N, K;                    //N����������K:������
//int taskTime[MAXSIZE];
int taskTime1[MAXSIZE] = { 47, 20, 28, 44, 21, 45, 30, 39, 28, 33 };
int taskTime2[MAXSIZE] = { 98, 84, 50, 23, 32, 99, 22, 76, 72, 61, 81, 39, 76, 54, 37 };
int taskTime3[MAXSIZE] = { 39, 39, 23, 45, 100, 69, 21, 81, 39, 55, 20, 86, 34, 53, 58, 99, 36, 45, 46 };      //�����Ӧ��ʱ��
int bestTime = INFINITY;      //���Ž⣺�����ȫ���������ʱ�䣬��ʼ��Ϊ�����
int scheduleNow[MAXSIZE];   //��ǰ���ŵ��ȷ�����ֵΪ0��ʾ��δ����
int best_N_to_K[MAXSIZE];   //���Ž�ĵ��ȷ�����best_N_to_K[i]=m,��ʾ��i+1
							//��i��0��ʼ�㣩����������m̨����
void Init(int N, int K) {
	N = 0;
	K = 0;
	bestTime = INFINITY;
	for ( int i = 0; i < MAXSIZE; i++) {
		scheduleNow[i] = 0;
		best_N_to_K[i] = 0;
	}
 }
/*
//������ʾ������N��K��ֵk
void Display()
{
	cout << "**********��ѵ�������Ļ����㷨***********" << endl;
	cout << "��������ȵ�������N= ";
	cin >> N;
	cout << endl << "������ɲ��й����Ļ�����K= ";
	cin >> K;
}
*/

/*
//��������������i��Ҫ��ʱ��
void setTaskTime(int taskTime[], int N)
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < N; i++)
		taskTime[i] = int((rand() % 20) + 3);   //ʱ�䷶Χ��[3,23)֮�������
}
*/

//��ӡԭʼ����ʱ���Ӧ��
void printTaskTime(int taskTime[], int N, int K)
{
	cout << "1��ԭʼ����ʱ���Ӧ�����£�\n" << "  ����   |   ʱ��" << endl << "-------------------" << endl;
	for (int i = 0; i < N; i++)
		cout << "  Task " << i + 1 << " : " << setw(2) << taskTime[i] << " hours" << endl;
}

//������Ҷ�ڵ�ʱ������Ҷ�ڵ���н���������ʱ��
int ScheduleTime(int taskTime[], int N, int K)
{
	int k[MAXSIZE] = { 0 };    //���ڼ�¼ÿ��������Ӧ��������ʱ��,�����±�
						   //��1��ʼ�㣬��ΪscheduleNow[i]=0ʱ��ʾδ����
	for (int i = 0; i < N; i++)
	{//����i������ʱ��ӵ��ڡ�scheduleNow[i]����������ȥ
		k[scheduleNow[i]] += taskTime[i];
	}

	int max = k[1];
	for (int i = 1; i <= K; i++)
	{//���й��������л����й���ʱ������Ǹ�ʱ�����Ҷ�ӽڵ���н�ʱ��
		if (k[i] > max)max = k[i];
	}
	return max;
}

//���������ݷ�������֦��
void BackTrack(int taskTime[], int deep, int N, int K)
{	
	if (deep == N)
	{
		int temp = ScheduleTime(taskTime, N, K);		//��ʱ���Ҷ�ڵ�Ŀ��н��ֵ
		if (temp < bestTime)							//���н��뵱ǰ���Ž���бȽ�
		{
			bestTime = temp;
			for (int i = 0; i < N; i++)
			{
				best_N_to_K[i] = scheduleNow[i];
			}
		}
		return;
	}

	for (int i = 1; i <= K && i<=deep+1; i++)
	{
		scheduleNow[deep] = i;							//������deep�������ǰ����
		if (ScheduleTime(taskTime, N, K) < bestTime)	//��֦��Լ������
			BackTrack(taskTime, deep + 1, N, K);
		scheduleNow[deep] = 0;							//���ݣ���������������ǰ������i=0��ʾΪ������
	}
}

//��ӡ���տ��н���
void printSchedulePlan(int N, int K)
{
	//���ÿ�������ӡ��ѵ�������
	cout << endl << "2�����ÿ���������ѵ������У�\n";
	cout << "Best Scheduling Sequence(����i��Ӧ����Ļ�����) :\n";
	for (int i = 0; i < N; i++)
	{
		cout << best_N_to_K[i] << "  ";
	}

	//���ÿ̨������ӡ���Ӧ�����Щ����
	cout << endl << endl << "3��ÿ̨������Ӧ��ɵ��������£� \n";
	for (int i = 1; i <= K; i++)
	{
		bool hasTask = false;    //hasTask���ڼ�¼�����Ƿ��з��䣬��һ
							   //������û���䣬����ʾ��δ��������
		cout << "����" << i << "���� �� ";
		for (int j = 0; j < N; j++)
		{
			if (i == best_N_to_K[j])
			{
				cout << "Task" << j + 1 << " ";
				hasTask = true;
			}
		}
		if (hasTask == false)cout << "δ��������";
		cout << endl;
	}
}

int main()
{	
	int N, K;						//N����������K:������
//	Display();						//������ʾ������N��K
//	setTaskTime(taskTime, N);		//��������������i��Ҫ��ʱ��
	printf("\n/**********************NO.1*********************/\n");
	N = 10;
	K = 3;
	printTaskTime(taskTime1, N, K);	//��ӡԭʼ����ʱ���Ӧ��
	BackTrack(taskTime1, 0, N, K);        //���������ݷ�������֦��
	printSchedulePlan(N, K);			//��ӡ���տ��н���

	printf("\n/**********************NO.2*********************/\n");
	Init(N, K);
	N = 15;
	K = 5;
	printTaskTime(taskTime2, N, K);	//��ӡԭʼ����ʱ���Ӧ��
	BackTrack(taskTime2, 0, N, K);		//���������ݷ�������֦��
	printSchedulePlan(N, K);			//��ӡ���տ��н���

	printf("\n/**********************NO.3*********************/\n");
	Init(N, K);
	N = 19;
	K = 8;
	printTaskTime(taskTime3, N, K);	//��ӡԭʼ����ʱ���Ӧ��
	BackTrack(taskTime3, 0, N, K);        //���������ݷ�������֦��
	printSchedulePlan(N, K);			//��ӡ���տ��н���

	system("pause");
}
