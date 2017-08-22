#include <stdio.h>
#include <math.h>

#define NUM_QUE 6
static count =0;
int solution_num = 0;

//判断一个位置能否放皇后，即判断是否和已经放置的皇后冲突
int place(int queen_site[], int queenN)
{
	int i;
	for (i=0; i<queenN; i++)
			if(queen_site[i] == queen_site[queenN] ||\
			abs(i-queenN) == abs(queen_site[i] - queen_site[queenN]))
			return 0;
	return 1;
}

void print_solution(int queen_site[])
{
	int i=0, j=0;
	printf("第%d种解法：\n", solution_num);
	for(i=0; i<NUM_QUE; i++)
	{
		for(j=0; j<NUM_QUE; j++)
			if(j==queen_site[i])
				printf("Q ");
			else
				printf(". ");
			printf("\n");
	}
	printf("\n");
}

void backTracking(int queen_site[], int queenN)
{
	int i;
	count++;
	if(queenN >= NUM_QUE)
	{
		solution_num++;
		print_solution(queen_site);
	}
	else
		for(i=0; i<NUM_QUE; i++)
		{
			queen_site[queenN]=i;
			if(place(queen_site, queenN))
				backTracking(queen_site, queenN+1);
		}
}

int main(void)
{
	//每个皇后i按编号分别放入第i行，queen_site[i]为第i个皇后的列号
	int queen_site[NUM_QUE];
	int i;
	for(i=0; i<NUM_QUE; i++)
		queen_site[i] = -1;
	backTracking(queen_site, 0);
	if(solution_num == 0)
		printf("无解！\n");
	//printf("%d", count);
	return 0;	
}
