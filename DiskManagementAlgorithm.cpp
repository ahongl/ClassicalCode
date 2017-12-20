#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include<stdlib.h>

using namespace std;

const int MaxNumber = 100;

int TrackOrder[MaxNumber];    // 磁盘访问序列

int StartTrack;                // 开始磁道号

int TrackNumber;                // 请求磁道个数

void getInput()
{
	cout << "请输入要请求的磁道个数TrackNumber: ";
	cin >> TrackNumber;
	cout << "\n请依次输入磁盘访问顺序: " << endl;
	for (int i = 0; i < TrackNumber; i++)
	{
		cin >> TrackOrder[i];
	}
	cout << "\n请输入开始磁盘号StartTrack: ";
	cin >> StartTrack;
}

void showInput()
{
	cout << "\n======================================================================\n";
	cout << "\n请求的磁道个数TrackNumber为:" << TrackNumber << endl;
	cout << "\n开始磁盘号StartTrack为:" << StartTrack << endl;
	cout << "\n磁盘请求序列为: ";
	for (int i = 0; i < TrackNumber; i++)
	{
		cout << TrackOrder[i] << " ";
	}
	cout << endl;
}

void FCFS()
{
	int totalLength = 0;
	int i; int j;
	float avarageLength;
	int *moveDistance=(int *)malloc(sizeof(int)*(TrackNumber + 1));
	cout << "\n从" << StartTrack << "号磁道开始" << endl;
	cout << "被访问的下一个磁道号: ";
	for (i = 0; i < TrackNumber; i++)
	{
		cout << TrackOrder[i] << "  ";
	}
	cout << endl;

	cout << "对应移动距离: ";
	moveDistance[0] = abs(StartTrack - TrackOrder[0]);
	cout << moveDistance[0] << "  ";

	for (i = 0, j = 1; j < TrackNumber; i++, j++)
	{
		moveDistance[j] = abs(TrackOrder[j] - TrackOrder[i]);
		cout << moveDistance[j] << "  ";
	}
	for (i = 0; i < TrackNumber; i++)
	{
		totalLength = totalLength + moveDistance[i];
	}

	avarageLength = (float)totalLength / TrackNumber;
	cout << "\n总寻道长度:" << totalLength;
	cout << "\n平均寻道长度:" << setprecision(3) << avarageLength << endl << endl;
}

void SSTF()
{
	int k = 1;
	int index = 0;
	int moveDistance[MaxNumber];
	int currentTrack = StartTrack;
	int totalLength = 0;
	float avarageLength;
	int left, right;
	int i;
	int j;
	int temp;
	int a[MaxNumber];
	for (i = 0; i < TrackNumber; i++)
	{
		a[i] = TrackOrder[i];
	}

	for (i = 0; i < TrackNumber; i++)
	{
		for (j = i + 1; j < TrackNumber; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	cout << "\n从" << StartTrack << "号磁道开始" << endl;
	cout << "被访问的下一个磁道号: ";
	if (a[TrackNumber - 1] <= currentTrack)
	{
		totalLength = currentTrack - a[0];
		for (i = TrackNumber - 1, index = 0; i >= 0; i--, index++)
		{
			cout << a[i] << "  ";
			moveDistance[index] = currentTrack - a[i];
			currentTrack = a[i];
		}
	}
	else
	{
		if (a[0] >= currentTrack)
		{
			totalLength = a[TrackNumber - 1] - currentTrack;
			for (i = 0, index = 0; i < TrackNumber; i++, index++)
			{
				cout << a[i] << "  ";
				moveDistance[index] = a[i] - currentTrack;
				currentTrack = a[i];
			}
		}
		else
		{
			while (a[k] < currentTrack)
			{
				k++;
			}
			left = k - 1;
			right = k;

			for (i = 0, index = 0; i < TrackNumber; ++i)
			{
				if (left >= 0 && right < TrackNumber && (currentTrack - a[left] <= a[right] - currentTrack))
				{
					cout << a[left] << "  ";
					moveDistance[index] = currentTrack - a[left];
					currentTrack = a[left];
					left = left - 1;
				}
				else if (left >= 0 && right < TrackNumber)
				{
					cout << a[right] << "  ";
					moveDistance[index] = a[right] - currentTrack;
					currentTrack = a[right];
					right = right + 1;
				}
				else if (left < 0)
				{
					cout << a[right] << "  ";
					moveDistance[index] = a[right] - currentTrack;
					currentTrack = a[right];
					right = right + 1;
				}
				else if (right > TrackNumber - 1)
				{
					cout << a[left] << "  ";
					moveDistance[index] = currentTrack - a[left];
					currentTrack = a[left];
					left = left - 1;
				}
				totalLength += moveDistance[index];
				index = index + 1;
			}
		}
	}
	cout << endl;
	cout << "对应移动距离: ";
	for (i = 0; i < TrackNumber; i++)
	{
		cout << moveDistance[i] << "  ";
	}
	avarageLength = (float)totalLength / TrackNumber;
	cout << "\n总寻道长度:" << totalLength;
	cout << "\n平均寻道长度:" << setprecision(3) << avarageLength << endl << endl;
}

void SCAN()
{
	int index = 0;
	int moveDistance[MaxNumber];
	int currentTrack = StartTrack;
	int totalLength = 0;
	float avarageLength;
	int c;
	int i;
	int j;
	int k = 1;
	int left, right;
	int temp;
	int a[MaxNumber];
	for (i = 0; i < TrackNumber; i++)
	{
		a[i] = TrackOrder[i];
	}
	for (i = 0; i < TrackNumber; i++)
	{
		for (j = i + 1; j < TrackNumber; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	cout << "请输入磁头移动方向[1-增加、0-减小]: ";
	cin >> c;
	cout << "\n从" << StartTrack << "号磁道开始" << endl;
	cout << "被访问的下一个磁道号: ";

	if (a[TrackNumber - 1] <= currentTrack)
	{
		totalLength = currentTrack - a[0];
		for (i = TrackNumber - 1, index = 0; i >= 0; i--, index++)
		{
			cout << a[i] << "  ";
			moveDistance[index] = currentTrack - a[i];
			currentTrack = a[i];
		}
	}
	else
	{
		if (a[0] >= currentTrack)
		{
			totalLength = a[TrackNumber - 1] - currentTrack;

			for (i = 0, index = 0; i < TrackNumber; i++, index++)
			{
				cout << a[i] << "  ";
				moveDistance[index] = a[i] - currentTrack;
				currentTrack = a[i];
			}
		}
		else
		{
			while (a[k] < currentTrack)
				k++;
			left = k - 1;
			right = k;
			index = 0;

			switch (c)
			{
			case 0:
			{
				for (j = left; j >= 0; j--, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = currentTrack - a[j];
					currentTrack = a[j];
				}
				for (j = right; j < TrackNumber; j++, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = a[j] - currentTrack;
					currentTrack = a[j];
				}
				totalLength = (StartTrack - a[0]) + (a[TrackNumber - 1] - a[0]);
				break;
			}

			case 1:
			{
				for (j = right; j < TrackNumber; j++, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = a[j] - currentTrack;
					currentTrack = a[j];
				}
				for (j = left; j >= 0; j--, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = currentTrack - a[j];
					currentTrack = a[j];
				}
				totalLength = (a[TrackNumber - 1] - StartTrack) + (a[TrackNumber - 1] - a[0]);
				break;
			}

			default:
				break;
			}
		}
	}

	cout << endl;
	cout << "对应移动距离: ";
	for (i = 0; i < TrackNumber; i++)
	{
		cout << moveDistance[i] << "  ";
	}
	avarageLength = (float)totalLength / TrackNumber;
	cout << "\n总寻道长度:" << totalLength;
	cout << "\n平均寻道长度:" << setprecision(3) << avarageLength << endl << endl;
}

void CSCAN()
{
	int j;
	int temp;
	int i;
	int k = 1;
	float avarageLength;
	int a[MaxNumber];
	int c;
	int left, right;
	int index = 0;
	int moveDistance[MaxNumber];
	int currentTrack = StartTrack;
	int totalLength = 0;
	for (i = 0; i < TrackNumber; i++)
	{
		a[i] = TrackOrder[i];
	}
	for (i = 0; i < TrackNumber; i++)
	{
		for (j = i + 1; j < TrackNumber; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}


	cout << "\n请输入磁头移动方向[1-增加、0-减小]: ";
	cin >> c;
	cout << "从" << StartTrack << "号磁道开始" << endl;
	cout << "被访问的下一个磁道号: ";
	if (a[TrackNumber - 1] <= currentTrack)
	{
		totalLength = currentTrack - a[0];
		for (i = TrackNumber - 1, index = 0; i >= 0; i--, index++)
		{
			cout << a[i] << "  ";
			moveDistance[index] = currentTrack - a[i];
			currentTrack = a[i];
		}
	}
	else
	{
		if (a[0] >= currentTrack)
		{
			totalLength = a[TrackNumber - 1] - currentTrack;
			for (i = 0, index = 0; i < TrackNumber; i++, index++)
			{
				cout << a[i] << "  ";
				moveDistance[index] = a[i] - currentTrack;
				currentTrack = a[i];
			}
		}
		else
		{
			while (a[k] < currentTrack)
				k++;
			left = k - 1;
			right = k;
			index = 0;

			switch (c)
			{
			case 0:
			{
				for (j = left; j >= 0; j--, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = currentTrack - a[j];
					currentTrack = a[j];
				}
				for (j = TrackNumber - 1; j >= right; j--, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = abs(a[j] - currentTrack);
					currentTrack = a[j];
				}
				totalLength = 2 * (a[TrackNumber - 1] - a[0]) - (a[right] - StartTrack);
				break;
			}

			case 1:
			{
				for (j = right; j < TrackNumber; j++, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = a[j] - currentTrack;
					currentTrack = a[j];
				}
				for (j = 0; j < right; j++, index++)
				{
					cout << a[j] << "  ";
					moveDistance[index] = abs(a[j] - currentTrack);
					currentTrack = a[j];
				}
				totalLength = 2 * (a[TrackNumber - 1] - a[0]) - (StartTrack - a[left]);
				break;
			}

			default:
				break;
			}
		}
	}

	cout << endl;
	cout << "对应移动距离: ";
	for (i = 0; i < TrackNumber; i++)
	{
		cout << moveDistance[i] << "  ";
	}
	avarageLength = (float)totalLength / TrackNumber;
	cout << "\n总寻道长度:" << totalLength;
	cout << "\n平均寻道长度:" << setprecision(3) << avarageLength << endl << endl;
}

int main()
{
	char choice;
	cout << "\n---------------------------磁盘管理实验---------------------------\n\n";
	while (1)
	{
		getInput();
		showInput();
		cout << endl;
		while (1)
		{
			cout << "----1-FCFS 算法----\n";
			cout << "----2-SSTF 算法----\n";
			cout << "----3-SCAN 算法----\n";
			cout << "----4-CSCAN算法----\n";
			cout << "----q-退出----\n";
			cout << "-------其他任意键重新输入数据-----\n\n";
			cout << "请输入选择：";
			cin >> choice;
			if (choice == 'q')
			{
				return 1;
			}
			if (choice != '1' || choice != '2' || choice != '3' || choice != '4')
			{
				break;
			}
			switch (choice)
			{
			case '1':
				cout << "\nFCFS算法";
				FCFS();
				cout << endl;
				break;

			case '2':
				cout << "\nSSTF算法";
				SSTF();
				cout << endl;
				break;

			case '3':
				cout << "\nSCAN算法";
				SCAN();
				cout << endl;
				break;

			case '4':
				cout << "\nCSCAN算法";
				CSCAN();
				cout << endl;
				break;

			default:
				return 1;
			}
		}
	}
	return 1;
}
