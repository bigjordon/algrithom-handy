#include <stdio.h>
#include <stdlib.h>

struct record
{
	int     year;
	int     month;
	double  tmprature;
};

struct avarageTemprature
{
	int		yearID;
	int     monthID;
	double  avarageT;
};

void output(FILE *fp1, FILE *fp2, struct avarageTemprature avarageTemprature_12[], int outputyear, double yearavarage)
{
	int i=0;
	fprintf(fp1, "\n********%d年的数据**********\n", avarageTemprature_12[i].yearID);
	fprintf(fp1, "%d年的平均风速：%.2lf\n", avarageTemprature_12[i].yearID, yearavarage);
	fprintf(fp2, "%d	%.2lf\n", avarageTemprature_12[i].yearID, yearavarage);

	for(i=0; i<12; i++)
	{
		if(outputyear == avarageTemprature_12[i].yearID)
		{
			fprintf(fp1, "第%2d月平均风速为：%.2lf\n", avarageTemprature_12[i].monthID, avarageTemprature_12[i].avarageT);
			fprintf(fp2, "%4d	%-d	%.2lf\n", avarageTemprature_12[i].yearID, avarageTemprature_12[i].monthID, avarageTemprature_12[i].avarageT);
		}
	}

}

int main(void)
{
	int i = 0, j =0;
	int count = 0;   //avarageTemprature_12的索引              
	int last_start = 0;
	int f_return=0;
	int gabday;
	int bad_data=0;
	double yearavarage=0;
	struct record record_366[367];
	struct avarageTemprature avarageTemprature_12[12]; 
	FILE *fp = NULL;
	FILE *fpout1 = NULL;
	FILE *fpout2 = NULL;
	fp = fopen("data.txt", "r");
	fpout1 = fopen("out_text.txt", "w");
	fpout2 = fopen("out_data.txt", "w");
	printf("正在处理...\n processing... ...\n\n");
	if(fp != NULL && fpout1 !=NULL && fpout2 != NULL)
	{
		while(!feof(fp))
		{
			for(; i<367; i++)
			{
				fscanf(fp, "%d", &record_366[i].year);
				fscanf(fp, "%d", &record_366[i].month);
				fscanf(fp, "%d", &gabday);
				fscanf(fp, "%lf", &record_366[i].tmprature);
				if(record_366[i].tmprature == 23766)
				{
					record_366[i].tmprature=0;
					bad_data++;
				}
				if(record_366[i].month != record_366[last_start].month)
				{ 
					avarageTemprature_12[count].avarageT = 0.0;
					for(j = last_start; j<i; j++)
						avarageTemprature_12[count].avarageT += record_366[j].tmprature;
					
					avarageTemprature_12[count].avarageT /= (i - last_start-bad_data);
					avarageTemprature_12[count].yearID = record_366[i-1].year;
					avarageTemprature_12[count].monthID = record_366[i-1].month;
					yearavarage+=avarageTemprature_12[count].avarageT;
					count++;
					last_start = i;
					bad_data=0;
				}
				if(record_366[i].year!=record_366[i-1].year && i!=0)
				{

					record_366[0].year = record_366[i].year;
					record_366[0].month = record_366[i].month;
					record_366[0].tmprature = record_366[i].tmprature;
					i = 1;
					last_start = 0;
					count = 0;
					yearavarage/=12;
					output(fpout1, fpout2, avarageTemprature_12, avarageTemprature_12[0].yearID, yearavarage);
					yearavarage=0;
					break;
				}
			}
		}
	}
	else
	{
		printf("不能打开文件数据data.txt，或创建文件失败\n");
		exit(0);
	}
	fclose(fp);
	fclose(fpout1);
	fclose(fpout2);
	printf("处理完成，处理结果保存在out_data.txt, and out_text.txt中。\nDone! Check out the results in the file out_data.txt and out_text.txt.\n");
//	system("pause");
	return 0;
}
