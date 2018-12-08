#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#define INFINITY 999999999    //定义无穷大INFINITY=999999999
#define MAXSIZE 100           //定义最大任务数
using namespace std;

//定义所需全局变量
//int N, K;                    //N：任务数，K:机器数
//int taskTime[MAXSIZE];
int taskTime1[MAXSIZE] = { 47, 20, 28, 44, 21, 45, 30, 39, 28, 33 };
int taskTime2[MAXSIZE] = { 98, 84, 50, 23, 32, 99, 22, 76, 72, 61, 81, 39, 76, 54, 37 };
int taskTime3[MAXSIZE] = { 39, 39, 23, 45, 100, 69, 21, 81, 39, 55, 20, 86, 34, 53, 58, 99, 36, 45, 46 };      //任务对应的时间
int bestTime = INFINITY;      //最优解：即完成全部任务最短时间，初始化为无穷大
int scheduleNow[MAXSIZE];   //当前最优调度方案，值为0表示还未分配
int best_N_to_K[MAXSIZE];   //最优解的调度方案：best_N_to_K[i]=m,表示把i+1
							//（i从0开始算）任务分配给第m台机器
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
//界面显示并接收N、K的值k
void Display()
{
	cout << "**********最佳调度问题的回溯算法***********" << endl;
	cout << "请输入调度的任务数N= ";
	cin >> N;
	cout << endl << "请输入可并行工作的机器数K= ";
	cin >> K;
}
*/

/*
//随机产生完成任务i需要的时间
void setTaskTime(int taskTime[], int N)
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < N; i++)
		taskTime[i] = int((rand() % 20) + 3);   //时间范围：[3,23)之间的整数
}
*/

//打印原始任务时间对应表
void printTaskTime(int taskTime[], int N, int K)
{
	cout << "1、原始任务时间对应表如下：\n" << "  任务   |   时间" << endl << "-------------------" << endl;
	for (int i = 0; i < N; i++)
		cout << "  Task " << i + 1 << " : " << setw(2) << taskTime[i] << " hours" << endl;
}

//搜索到叶节点时，计算叶节点可行解完成任务的时间
int ScheduleTime(int taskTime[], int N, int K)
{
	int k[MAXSIZE] = { 0 };    //用于记录每个机器对应工作的总时间,机器下标
						   //从1开始算，因为scheduleNow[i]=0时表示未分配
	for (int i = 0; i < N; i++)
	{//将第i个任务时间加到第‘scheduleNow[i]’个机器中去
		k[scheduleNow[i]] += taskTime[i];
	}

	int max = k[1];
	for (int i = 1; i <= K; i++)
	{//并行工作的所有机器中工作时间最长的那个时间就是叶子节点可行解时间
		if (k[i] > max)max = k[i];
	}
	return max;
}

//排列树回溯法（含剪枝）
void BackTrack(int taskTime[], int deep, int N, int K)
{	
	if (deep == N)
	{
		int temp = ScheduleTime(taskTime, N, K);		//临时存放叶节点的可行解的值
		if (temp < bestTime)							//可行解与当前最优解进行比较
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
		scheduleNow[deep] = i;							//将任务deep分配给当前机器
		if (ScheduleTime(taskTime, N, K) < bestTime)	//剪枝，约束条件
			BackTrack(taskTime, deep + 1, N, K);
		scheduleNow[deep] = 0;							//回溯，不将任务分配给当前机器，i=0表示为不分配
	}
}

//打印最终可行解结果
void printSchedulePlan(int N, int K)
{
	//针对每个任务打印最佳调度序列
	cout << endl << "2、针对每个任务的最佳调度序列：\n";
	cout << "Best Scheduling Sequence(任务i对应分配的机器号) :\n";
	for (int i = 0; i < N; i++)
	{
		cout << best_N_to_K[i] << "  ";
	}

	//针对每台机器打印其对应完成那些任务
	cout << endl << endl << "3、每台机器对应完成的任务如下： \n";
	for (int i = 1; i <= K; i++)
	{
		bool hasTask = false;    //hasTask用于记录机器是否有分配，若一
							   //个任务都没分配，则显示“未分配任务”
		cout << "机器" << i << "分配 ： ";
		for (int j = 0; j < N; j++)
		{
			if (i == best_N_to_K[j])
			{
				cout << "Task" << j + 1 << " ";
				hasTask = true;
			}
		}
		if (hasTask == false)cout << "未分配任务！";
		cout << endl;
	}
}

int main()
{	
	int N, K;						//N：任务数，K:机器数
//	Display();						//界面显示并接收N、K
//	setTaskTime(taskTime, N);		//随机产生完成任务i需要的时间
	printf("\n/**********************NO.1*********************/\n");
	N = 10;
	K = 3;
	printTaskTime(taskTime1, N, K);	//打印原始任务时间对应表
	BackTrack(taskTime1, 0, N, K);        //排列树回溯法（含剪枝）
	printSchedulePlan(N, K);			//打印最终可行解结果

	printf("\n/**********************NO.2*********************/\n");
	Init(N, K);
	N = 15;
	K = 5;
	printTaskTime(taskTime2, N, K);	//打印原始任务时间对应表
	BackTrack(taskTime2, 0, N, K);		//排列树回溯法（含剪枝）
	printSchedulePlan(N, K);			//打印最终可行解结果

	printf("\n/**********************NO.3*********************/\n");
	Init(N, K);
	N = 19;
	K = 8;
	printTaskTime(taskTime3, N, K);	//打印原始任务时间对应表
	BackTrack(taskTime3, 0, N, K);        //排列树回溯法（含剪枝）
	printSchedulePlan(N, K);			//打印最终可行解结果

	system("pause");
}
