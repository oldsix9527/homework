
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>


int main()
{
	//主页面介绍
	printf("\t\t欢迎游玩fly bird小游戏\n");
	printf("\t\t以为下为游戏须知:\n");
	printf("\t\t1.你需要用空格操控小鸟飞跃一个又一个柱子\n");
	printf("\t\t2.飞出界面或撞上柱子都会失败\n");
	printf("\t\t3.活的越久 分数越高\n");
	printf("\n");
	printf("\t\t你想开始游玩吗？请输入:Y/N\n");
	printf("\t\t你的输入是:");


	//主页面选择输入
	char ch;
	scanf("%c", &ch);
	while (ch != 'Y' || ch != 'N')
	{
		printf("\t\t您的输入有误，请重新输入:");

		scanf("%c", ch);
		_getch();
	}
	if (ch == 'Y')
	{

	}
	else if (ch == 'N')

		return 0;
}
