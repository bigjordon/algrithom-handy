#include <stdio.h>

#define ELEMENT_NUM 6
#define SUM_T 30

int element[2][ELEMENT_NUM]={\
							{5, 10, 12, 13, 15, 18},\
							{0}};
int sum=0;
int solution_num=0;

void printsolution(int element[][ELEMENT_NUM])
{
	int i=0;
	for(i=0; i<ELEMENT_NUM; i++)
		if(element[1][i] == 1)
			printf("%d ", element[0][i]);
		printf("\n");
}

void backTracking(int elem_n)
{
	int i;
	if(sum == SUM_T)
	{
		solution_num++;
		printsolution(element);
	}
	else
	{
		if(sum+element[0][elem_n]<=SUM_T && elem_n<ELEMENT_NUM)
		{
			for(i=1; i>=0; i--)
			{
				if(i==1)
				{
					sum += element[0][elem_n];
					element[1][elem_n]=1;
				}
				else
				{
					sum -= element[0][elem_n];
					element[1][elem_n]=0;
				}
				backTracking(elem_n+1);
			}
		}
	}
}



int main(void)
{
	int i;
	printf("集合元素为：");
	for (i=0; i<ELEMENT_NUM; i++)
		printf("%d ", element[0][i]);
	printf("\n和数为：%d\n解为：\n", SUM_T);
	backTracking(0);
	if(solution_num==0)
		printf("无解！\n");
	return 0;
}