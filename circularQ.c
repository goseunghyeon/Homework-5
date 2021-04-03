/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType* createQueue();
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();

int main(void)
{
	QueueType* cQ = createQueue();
	element data;
	char command;

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ)
{
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
/*큐가 비었을 경우 empty출력*/
int isEmpty(QueueType* cQ)
{
	if (cQ == NULL)
		return -1;
	else  {
		printf("empty!");
		return 0;
	}
}

/* complete the function */
/*큐가 다찾을 경우 full출력*/
int isFull(QueueType* cQ)
{
	if (cQ!=NULL)
		printf("full!");
	return 0;
}


/* complete the function */
/*큐에 새로운 데이터 삽입시 rear와 front가 같은 배열을 지칭하는 경우 해당
배열의 원소는 비워두거야 하므로 full출력후 이전 rear의 값으로 다시 돌려놓음
그냥 계속진행시 큐를 덮어 씌우는 경우가 발생해서 이전상태로 되돌리는 기능이 필요했다*/
void enQueue(QueueType* cQ, element item)
{
	int i = cQ->rear;
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
	if (cQ->front == cQ->rear) {
		isFull(cQ);
		cQ->rear = i;
	}

	else 
		cQ->queue[cQ->rear] = item;
	
}

/* complete the function */
/*큐가 비었다면 empty출력 이경우는 시작부터 rear과front가 같은 위치면 
큐가 비었음을 알수 있고 큐가 비어있지 않은경우 큐를 비운다*/
void deQueue(QueueType* cQ, element* item)
{
	
	if (cQ->front == cQ->rear)
		isEmpty(cQ);
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->front] = *item;
	}

	
}

/*큐의 저장되어있는 원소 출력*/
void printQ(QueueType* cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

