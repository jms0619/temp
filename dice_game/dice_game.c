
/*
	주사위 게임(Dice Game)
	
	2009.07.08 - 2009.07.09
	Created by MS. Jun.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bet;                 // 배팅액 변수
int money=5000;          // 소지금 변수
int choice;              // 사람 선택 변수

int Dice();              // 랜덤주사위 함수
void Start();            // 시작 문장 함수
void BettingPrint();     // 배팅 과정 함수
void Choice();           // 사람 선택 함수
void VSPrint(int);       // 승패 여부 출력 함수
void Progress();         // 게임 진행 과정 함수
int YourMoney();         // 소지금으로 계속 진행할 수 있는지 판별하는 함수
char Question();         // 계속 게임을 진행할 것인지 묻는 함수

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
	puts("주사위 게임에 오신 것을 환영합니다.");
	puts("당신은 소지금 5000원을 가지고 게임에 참여합니다.");
	puts("소지금이 0원이 되거나 50000원 이상이 되면 게임이 종료됩니다.");
	puts("아니면 중간에 그만둘 수도 있습니다.");
	puts("재밌게 즐기시기 바랍니다.");
	puts("그럼 시작하겠습니다.");
}

void BettingPrint()
{
	int i;
	int flag;
	char bets[7];
	
	while(1)
	{
		printf("\n당신의 소지금은 %d원입니다.\n", money);
		printf("배팅 금액: ");
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
			printf("\n당신은 %d원을 걸었습니다.\n\n", bet);
			break;
		}
	}
}

void Choice()
{
	puts("┏ 이길 경우: 배팅금의 2배를 얻음");
	puts("┣ 비길 경우: 본전");
	puts("┗ 질 경우: 돈을 잃음\n");
	puts("둘 중 이길 것 같은 사람 한 명을 선택하세요.");
	
	while(1)
	{
		puts("민수에게 배팅: 1\t민수의 친구에게 배팅: 2");
		printf("1 or 2: ");
		scanf("%d", &choice);
		fflush(stdin);
		
		if(choice!=1 && choice!=2)
		{
			puts("\n다시 입력해주세요.\n");
			continue;
		}
		break;
	}
}

void VSPrint(int n)
{
	if(n==0)
		puts("민수가 이겼습니다.\n");
	else if(n==1)
		puts("민수의 친구가 이겼습니다.\n");
	else
		puts("비겼습니다.\n");
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

		printf("\n########## %d번째 게임 ##########\n", i+1);
		printf(" 민수: %d \t민수의 친구: %d\n", vs1, vs2);

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
	printf("민수가 이긴 횟수: %d \n", result[0]);
	printf("민수의 친구가 이긴 횟수: %d \n", result[1]);
	printf("비긴 횟수: %d \n", result[2]);
	puts("---------------------------------------------------");

	if(result[0]>result[1])
	{
		VSPrint(0);
		if(choice==1)
		{
			puts("당신은 배팅금의 2배를 얻었습니다.");
			money+=bet;
		}
		else
		{
			puts("당신은 배팅금만큼의 돈을 잃었습니다.");
			money-=bet;
		}
	}
	else if(result[0]<result[1])
	{
		VSPrint(1);
		if(choice==2)
		{
			puts("당신은 배팅금의 2배를 얻었습니다.");
			money+=bet;
		}
		else
		{
			puts("당신은 배팅금만큼의 돈을 잃었습니다.");
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
		puts("돈을 모두 잃으셨습니다.");
		puts("게임을 종료하도록 하겠습니다.\n");
		return 0;
	}
	else if(money>=50000)
	{
		printf("%d원으로 50000원 이상이 되었습니다.\n", money);
		puts("게임을 종료하도록 하겠습니다.\n");
		return 0;
	}
	return 1;
}

char Question()
{
	char ans;

	while(1)
	{
		printf("계속 하시겠습니까?(y/n): ");
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
		puts("\n게임을 종료하도록 하겠습니다.\n");

	return ans;
}