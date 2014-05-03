
/*
	�ֻ��� ����(Dice Game)
	
	2009.07.08 - 2009.07.09
	Created by MS. Jun.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bet;                 // ���þ� ����
int money=5000;          // ������ ����
int choice;              // ��� ���� ����

int Dice();              // �����ֻ��� �Լ�
void Start();            // ���� ���� �Լ�
void BettingPrint();     // ���� ���� �Լ�
void Choice();           // ��� ���� �Լ�
void VSPrint(int);       // ���� ���� ��� �Լ�
void Progress();         // ���� ���� ���� �Լ�
int YourMoney();         // ���������� ��� ������ �� �ִ��� �Ǻ��ϴ� �Լ�
char Question();         // ��� ������ ������ ������ ���� �Լ�

int main(void)
{
	char answer='y';

	srand((int)time(NULL));

	Start();

	while(answer=='y')
	{
		BettingPrint();
		Choice();
		Progress();

		if(YourMoney()==0)
			break;
		else		
			answer=Question();
	}

	system("PAUSE");

	return 0;
}

int Dice()
{
	return rand()%6+1;
}

void Start()
{
	puts("�ֻ��� ���ӿ� ���� ���� ȯ���մϴ�.");
	puts("����� ������ 5000���� ������ ���ӿ� �����մϴ�.");
	puts("�������� 0���� �ǰų� 50000�� �̻��� �Ǹ� ������ ����˴ϴ�.");
	puts("�ƴϸ� �߰��� �׸��� ���� �ֽ��ϴ�.");
	puts("��հ� ���ñ� �ٶ��ϴ�.");
	puts("�׷� �����ϰڽ��ϴ�.");
}

void BettingPrint()
{
	int i;
	int flag;
	char bets[7];
	
	while(1)
	{
		printf("\n����� �������� %d���Դϴ�.\n", money);
		printf("���� �ݾ�: ");
		fgets(bets, sizeof(bets), stdin);
		fflush(stdin);

		flag=1;
		for(i=0; i<7; i++)
		{
			if('0'<=bets[i] && bets[i]<='9')
				continue;
			else if(bets[i]=='\n')
				break;

			flag=0;
			break;
		}

		if(flag==0)
			continue;
		else
		{
			bet=atoi(bets);
			if(bet<0 || bet>money)
				continue;
			printf("\n����� %d���� �ɾ����ϴ�.\n\n", bet);
			break;
		}
	}
}

void Choice()
{
	puts("�� �̱� ���: ���ñ��� 2�踦 ����");
	puts("�� ��� ���: ����");
	puts("�� �� ���: ���� ����\n");
	puts("�� �� �̱� �� ���� ��� �� ���� �����ϼ���.");
	
	while(1)
	{
		puts("�μ����� ����: 1\t�μ��� ģ������ ����: 2");
		printf("1 or 2: ");
		scanf("%d", &choice);
		fflush(stdin);
		
		if(choice!=1 && choice!=2)
		{
			puts("\n�ٽ� �Է����ּ���.\n");
			continue;
		}
		break;
	}
}

void VSPrint(int n)
{
	if(n==0)
		puts("�μ��� �̰���ϴ�.\n");
	else if(n==1)
		puts("�μ��� ģ���� �̰���ϴ�.\n");
	else
		puts("�����ϴ�.\n");
}

void Progress()
{
	int i;
	int vs1, vs2;
	int result[3]={0};

	for(i=0; i<3; i++)
	{
		vs1=Dice();
		vs2=Dice();

		printf("\n########## %d��° ���� ##########\n", i+1);
		printf(" �μ�: %d \t�μ��� ģ��: %d\n", vs1, vs2);

		if(vs1>vs2)
		{
			VSPrint(0);
			result[0]++;
		}
		else if(vs1<vs2)
		{
			VSPrint(1);
			result[1]++;
		}
		else
		{
			VSPrint(2);
			result[2]++;
		}
		
		system("PAUSE");
	}

	puts("\n---------------------------------------------------");
	printf("�μ��� �̱� Ƚ��: %d \n", result[0]);
	printf("�μ��� ģ���� �̱� Ƚ��: %d \n", result[1]);
	printf("��� Ƚ��: %d \n", result[2]);
	puts("---------------------------------------------------");

	if(result[0]>result[1])
	{
		VSPrint(0);
		if(choice==1)
		{
			puts("����� ���ñ��� 2�踦 ������ϴ�.");
			money+=bet;
		}
		else
		{
			puts("����� ���ñݸ�ŭ�� ���� �Ҿ����ϴ�.");
			money-=bet;
		}
	}
	else if(result[0]<result[1])
	{
		VSPrint(1);
		if(choice==2)
		{
			puts("����� ���ñ��� 2�踦 ������ϴ�.");
			money+=bet;
		}
		else
		{
			puts("����� ���ñݸ�ŭ�� ���� �Ҿ����ϴ�.");
			money-=bet;
		}
	}
	else
		VSPrint(2);

	puts("---------------------------------------------------\n");
}

int YourMoney()
{
	if(money==0)
	{
		puts("���� ��� �����̽��ϴ�.");
		puts("������ �����ϵ��� �ϰڽ��ϴ�.\n");
		return 0;
	}
	else if(money>=50000)
	{
		printf("%d������ 50000�� �̻��� �Ǿ����ϴ�.\n", money);
		puts("������ �����ϵ��� �ϰڽ��ϴ�.\n");
		return 0;
	}
	return 1;
}

char Question()
{
	char ans;

	while(1)
	{
		printf("��� �Ͻðڽ��ϱ�?(y/n): ");
		scanf("%c", &ans);
		fflush(stdin);
		
		if(ans!='y' && ans!='n')
		{
			printf("\n");
			continue;
		}
		break;
	}

	if(ans=='n')
		puts("\n������ �����ϵ��� �ϰڽ��ϴ�.\n");

	return ans;
}