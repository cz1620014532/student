#include <stdio.h>
#include <stdlib.h>
#define CourseNum 3 //课程数量
#define N 100
int stuNum = 0;
typedef struct
{
	int flag;
	int Class;
	int Sno;
	char Name[15];
	char Sex;
	float Score[CourseNum];
	float Total;
	float Average;

} STUDENT;
void Menu(float x)
{
	printf("\n--------------------------------学生管理系统--------------------------------\n\n");
	if (x == 0)
	{
		printf("-------------1:添加学生信息                      2:删除学生信息-------------\n\n");
		printf("-------------3:查询学生信息                      4:查询成绩信息-------------\n\n");
		printf("-------------5:学生成绩分析                      6:学生信息保存-------------\n\n");
		printf("-------------7:学生信息读入                      0:退出管理系统-------------\n\n");
	}
	else if (x == 3)
	{
		printf("-------------1:单个学生查询                      2:班级学生查询-------------\n\n");
	}
	else if (x == 4)
	{
		printf("-------------1:课程成绩查询                      2:学生成绩查询-------------\n\n");
	}
	else if (x == 4.5)
	{
		printf("-------------1:数学成绩         2:英语成绩         3:计算机成绩-------------\n\n");
	}
	else if (x == 5)
	{
		printf("-------------1:班级总分升序                      2:班级总分降序-------------\n\n");
		printf("-------------3:课程平均升序                      4:课程平均降序-------------\n\n");
	}
	printf("----------------------------------------------------------------------------\n\n");
}
int Lookup(STUDENT student[], int cla, int sno)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (student[i].flag == 1 && student[i].Class == cla && student[i].Sno == sno)
			return 0;
	}
	return 1;
}
void Add(STUDENT student[], int n)
{
	int i = 0, j, index = 0;
	float total = 0;
	printf("请输入学生信息[班级 学号 姓名 性别 数学 英语 计算机成绩]:\n");
	while (i != n)
	{ //判断成功输入的数量是否达到需要输入的数量
		if (student[index].flag == 0)
		{ //如果flag为0表示无效数据
			scanf("%d %d %s %c", &student[index].Class, &student[index].Sno, student[index].Name, &student[index].Sex);
			if (Lookup(student, student[index].Class, student[index].Sno))
			{
				for (j = 0; j < CourseNum; j++)
				{
					scanf("%f", &student[index].Score[j]); //输入成绩
					total += student[index].Score[j];
				}
				student[index].flag = 1;								   //初始化为1表示为有效信息
				student[index].Total = total;							   //计算总成绩
				student[index].Average = student[index].Total / CourseNum; //计算平均分
				i++;													   //成功输入+1
				stuNum++;												   //学生总数+1
				printf("添加成功\n");
				total = 0;
			}
		}
		index++; //数组下标+1
	}
}
void StuQuery(STUDENT student[], int flag, int cla, int sno)
{
	printf("%-3s %-10s %-6s %-6s  %-6s  %-6s  %-6s  %-6s  %-6s\n", "班级", "学号", "姓名", "性别", "数学", "英语", "计算机", "总分", "平均分");
	if (flag == 1)
	{
		int i = 0, j;
		for (i = 0; i < N; i++)
		{
			if (student[i].Class == cla && student[i].Sno == sno && student[i].flag == 1)
			{
				printf("%-4d %-10d %-6s %-6c", student[i].Class, student[i].Sno, student[i].Name, student[i].Sex);
				for (j = 0; j < CourseNum; j++)
				{
					printf("  %-6.2f", student[i].Score[j]);
				}
				printf("  %-6.2f  %-6.2f", student[i].Total, student[i].Average);
			}
		}
	}
	else if (flag == 2)
	{
		int i = 0, j, count = 0;
		for (i = 0; i < N; i++)
		{
			if (student[i].Class == cla && student[i].flag == 1)
			{
				printf("%-4d %-10d %-6s %-6c", student[i].Class, student[i].Sno, student[i].Name, student[i].Sex);
				for (j = 0; j < CourseNum; j++)
				{
					printf("  %-6.2f", student[i].Score[j]);
				}
				printf("  %-6.2f  %-6.2f", student[i].Total, student[i].Average);
				printf("\n");
				if (count == stuNum)
					break;
			}
		}
	}
}
void Delete(STUDENT student[], int cla, int sno)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (student[i].Class == cla && student[i].Sno == sno && student[i].flag == 1)
		{
			student[i].flag = 0;
			stuNum--;
			printf("删除成功");
			return;
		}
	}
	printf("没有找到学生信息!");
}
void ScoreQuery(STUDENT student[], int flag, int subject, int cla)
{
	int i;
	if (flag == 1)
	{
		if (subject == 0)
		{
			printf("%-3s %-10s %-6s %-6s  %-6s\n", "班级", "学号", "姓名", "性别", "数学");
		}
		else if (subject == 1)
		{
			printf("%-3s %-10s %-6s %-6s  %-6s\n", "班级", "学号", "姓名", "性别", "英语");
		}
		else if (subject == 2)
		{
			printf("%-3s %-10s %-6s %-6s  %-6s\n", "班级", "学号", "姓名", "性别", "计算机");
		}
		for (i = 0; i < N; i++)
		{
			if (student[i].Class == cla && student[i].flag == 1)
			{
				printf("%-4d %-10d %-6s %-6c  %-6.2f", student[i].Class, student[i].Sno, student[i].Name, student[i].Sex, student[i].Score[subject]);
				printf("\n");
			}
		}
	}
	else if (flag == 2)
	{
		int j;
		for (i = 0; i < N; i++)
		{
			if (student[i].Class == cla && student[i].Sno == subject && student[i].flag == 1)
			{
				printf("%-3s %-10s %-6s %-6s %-6s %-6s %-6s\n", "班级", "学号", "姓名", "性别", "数学", "英语", "计算机");
				printf("%-4d %-10d %-6s %-6c", student[i].Class, student[i].Sno, student[i].Name, student[i].Sex);
				for (j = 0; j < CourseNum; j++)
				{
					printf(" %-6.2f", student[i].Score[j]);
				}
				break;
			}
		}
	}
}
void TotalSort(STUDENT student[], int cla, STUDENT *stuSort[], int flag)
{
	int i, j, count = 0;
	if (flag == 1 || flag == 2)
	{
		for (i = 0; i < stuNum; i++)
		{
			if (student[i].flag != 0 && student[i].Class == cla)
			{
				stuSort[count] = student + i;
				count++;
			}
		}
	}
	if (flag == 3 || flag == 4)
	{
		for (i = 0; i < stuNum; i++)
		{
			if (student[i].flag != 0)
			{
				stuSort[count] = student + i;
				count++;
			}
		}
	}
	if (flag == 1)
	{
		STUDENT *p = student;
		for (i = 0; i < count; i++)
		{
			for (j = i + 1; j < count; j++)
			{
				if (stuSort[i]->Total > stuSort[j]->Total)
				{
					p = stuSort[j];
					stuSort[j] = stuSort[i];
					stuSort[i] = p;
				}
			}
		}
	}
	else if (flag == 2)
	{
		STUDENT *p = student;
		for (i = 0; i < count; i++)
		{
			for (j = i + 1; j < count; j++)
			{
				if (stuSort[i]->Total < stuSort[j]->Total)
				{
					p = stuSort[j];
					stuSort[j] = stuSort[i];
					stuSort[i] = p;
				}
			}
		}
	}
	else if (flag == 3)
	{
		STUDENT *p = student;
		for (i = 0; i < count; i++)
		{
			for (j = i + 1; j < count; j++)
			{
				if (stuSort[i]->Average > stuSort[j]->Average)
				{
					p = stuSort[j];
					stuSort[j] = stuSort[i];
					stuSort[i] = p;
				}
			}
		}
	}
	else if (flag == 4)
	{
		STUDENT *p = student;
		for (i = 0; i < count; i++)
		{
			for (j = i + 1; j < count; j++)
			{
				if (stuSort[i]->Average < stuSort[j]->Average)
				{
					p = stuSort[j];
					stuSort[j] = stuSort[i];
					stuSort[i] = p;
				}
			}
		}
	}
	printf("%-3s %-10s %-6s %-6s  %-6s  %-6s  %-6s  %-6s  %-6s\n", "班级", "学号", "姓名", "性别", "数学", "英语", "计算机", "总分", "平均分");
	for (i = 0; i < count; i++)
	{
		printf("%-4d %-10d %-6s %-6c", stuSort[i]->Class, stuSort[i]->Sno, stuSort[i]->Name, stuSort[i]->Sex);
		for (j = 0; j < CourseNum; j++)
		{
			printf("  %-6.2f", stuSort[i]->Score[j]);
		}
		printf("  %-6.2f  %-6.2f\n", stuSort[i]->Total, stuSort[i]->Average);
	}
}

void write(STUDENT student[])
{
	int i, j, count = 0;
	FILE *fp = fopen("student.txt", "w+");
	fprintf(fp, "%d\n", stuNum);
	for (i = 0; i < N; i++)
	{
		if (student[i].flag == 1 && !(Lookup(student, student[i].Class, student[i].Sno)))
		{
			fprintf(fp, "%d %d %s %c ", student[i].Class, student[i].Sno, student[i].Name, student[i].Sex);
			for (j = 0; j < CourseNum; j++)
			{
				fprintf(fp, "%.2f ", student[i].Score[j]);
			}
			fprintf(fp, "%.2f ", student[i].Total);
			fprintf(fp, "%.2f\n", student[i].Average);
			count++;
		}
		if (count == stuNum)
		{
			for (; i < N; i++)
			{
				fprintf(fp, "%c", '\n');
			}
			break;
		}
	}
	fclose(fp);
	fp = NULL;
}
void Read(STUDENT student[])
{
	int i, j, count = 0;
	FILE *fp = fopen("student.txt", "r");
	fscanf(fp, "%d\n", &stuNum);
	for (i = 0; i < N; i++)
	{
		student[i].flag = 1;
		fscanf(fp, "%d %d %s %c", &student[i].Class, &student[i].Sno, student[i].Name, &student[i].Sex);
		for (j = 0; j < CourseNum; j++)
		{
			fscanf(fp, " %f", &student[i].Score[j]);
		}
		fscanf(fp, " %f", &student[i].Total);
		fscanf(fp, " %f\n", &student[i].Average);
		if (count == stuNum)
		{
			for (; i < N; i++)
			{
				student[i].flag = 0;
			}
			break;
		}
		count++;
	}
	fclose(fp);
	fp = NULL;
}
int main(void)
{
	int select;
	STUDENT student[N] = {0};
	STUDENT *stuSort[N] = {NULL};
	while (1)
	{
		Menu(0);
		printf("请输入功能项:");
		fflush(stdin);
		scanf("%d", &select);
		switch (select)
		{
		case 1:
		{
			int n;
			printf("请输入要添加的数量:");
			fflush(stdin);
			scanf("%d", &n);
			Add(student, n);
			break;
		}
		case 2:
		{
			int cla, sno;
			printf("请输入删除学生的班级和学号");
			fflush(stdin);
			scanf("%d%d", &cla, &sno);
			Delete(student, cla, sno);
			break;
		}
		case 3:
		{
			Menu(3);
			printf("请输入查询功能项:");
			fflush(stdin);
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				int cla, sno;
				printf("请输入查询学生的班级和学号:");
				scanf("%d%d", &cla, &sno);
				StuQuery(student, 1, cla, sno);
				break;
			}
			case 2:
			{
				int cla, sno = 0;
				printf("请输入查询班级:");
				fflush(stdin);
				scanf("%d", &cla);
				StuQuery(student, 2, cla, sno);
				break;
			}
			}

			break;
		}
		case 4:
		{
			Menu(4);
			printf("请输入查询功能项:");
			fflush(stdin);
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				int subject, cla;
				Menu(4.5);
				printf("请输入要查询的课程名序号和班级:");
				fflush(stdin);
				scanf("%d%d", &subject, &cla);
				ScoreQuery(student, 1, subject - 1, cla);
				break;
			}
			case 2:
			{
				int sno, cla;
				printf("请输入要查询的班级和学号:");
				fflush(stdin);
				scanf("%d%d", &cla, &sno);
				ScoreQuery(student, 2, sno, cla);
				break;
			}
			}

			break;
		}
		case 5:
		{
			Menu(5);
			printf("请输入查询功能项:");
			fflush(stdin);
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				int cla;
				printf("请输入排序的班级:");
				fflush(stdin);
				scanf("%d", &cla);
				TotalSort(student, cla, stuSort, 1);
				break;
			}
			case 2:
			{
				int cla;
				printf("请输入排序的班级:");
				fflush(stdin);
				scanf("%d", &cla);
				TotalSort(student, cla, stuSort, 2);
				break;
			}
			case 3:
			{
				TotalSort(student, 0, stuSort, 3);
				break;
			}
			case 4:
			{
				TotalSort(student, 0, stuSort, 4);
				break;
			}
			}
			break;
		}
		case 6:
		{
			write(student);
			printf("学生信息保存成功");
			break;
		}
		case 7:
		{
			printf("学生信息读入成功");
			Read(student);
			break;
		}
		case 0:
		{
			printf("系统退出");
			break;
		}
		default:
		{
			printf("你的输入错误!");
		}
		}
		if (select == 0)
			break;
	}
	system("pause");
	return 0;
}
