/*
	Circular Array and Queue Implementation
	Guru Sarath
	25-Sep-2018
*/

#include <stdio.h>
#define DATA_TYPE int

// Circular Array structure
typedef struct Circular_array {

    int size;
    DATA_TYPE* C_array;

} Circular_array;

// Queue Structure
typedef struct Queue {

    int size; // Capacity of Queue
    DATA_TYPE front, rear; // Front and Read end of the queue
    Circular_array* array; //Queue is implemented using circular array

} Queue;

typedef struct BST_Node {

    DATA_TYPE value;
    BST_Node* LeftNode, RightNode;

} BST_Node;


// Function Declarations
Queue* Create_Queue(int);
Circular_array* Create_Circular_Array(int);
DATA_TYPE Circular_Array_Get_Data(Circular_array*, int);
void Circular_Array_Put_Data(Circular_array*, int, DATA_TYPE);
int QueueIsFull(Queue* Q);
int QueueIsEmpty(Queue *Q);
int EnQueue(Queue *Q, DATA_TYPE value);
int DeQueue(Queue *Q);
void DeleteQueue(Queue *Q);

// Main
int main()
{

}

// Create a circular array of size
Circular_array *Create_Circular_Array(int size)
{
    Circular_array* Cary = (Circular_array*) malloc(sizeof(Circular_array));
    Cary->C_array = (DATA_TYPE*) malloc(size * sizeof(DATA_TYPE));
    Cary->size = size;

    return Cary;
}

// Get element in a location
DATA_TYPE Circular_Array_Get_Data(Circular_array* C, int location)
{
	//In case of negative numbers,count backwards
	// Loop until negative number becomes a positive number
    while(location < 0)
    {
        location = location + C->size;
    }

    return(C->C_array[location % C->size]);
}

void Circular_Array_Put_Data(Circular_array* C, int location, DATA_TYPE value)
{
	//In case of negative numbers,count backwards
	// Loop until negative number becomes a positive number
    while(location < 0)
    {
        location = location + C->size;
    }

    C->C_array[location % C->size] = value;
}

//Function to create a Queue
Queue* Create_Queue(int size)
{
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    new_queue->size = size;
	// Create a circular array of size in the Queue
    new_queue->array = Create_Circular_Array(size);
    new_queue->front = -1;
    new_queue->rear = -1;

    return new_queue;
}

// Function to check if a Queue is Full
int QueueIsFull(Queue* Q)
{
    if((Q->rear+1)%Q->size == Q->front){
        return 1;
    }

    return 0;
}

// Function to check if a Queue is Empty
int QueueIsEmpty(Queue *Q)
{
    return ((Q->front == -1));
}

// Function to add element to the Queue
int EnQueue(Queue *Q, DATA_TYPE value)
{
	// Add element to the Queue only if it is not Full
    if(!QueueIsFull(Q))
    {
		// Rear points to the newly added element
        Q->rear += 1;
        Q->rear = Q->rear % Q->size;

		//When first element is added to the Queue, set front to 1
        if(Q->front == -1) { Q->front++; }

        Circular_Array_Put_Data(Q->array, Q->rear, value);

        return 0;
    } else {

        printf("\nQueue is FULL !!!\n");

    }

    return 1;
}

int DeQueue(Queue *Q)
{
    DATA_TYPE value = 0;

	// Get an element from the Queue only if it is not Empty
    if(!QueueIsEmpty(Q))
    {
        value = Circular_Array_Get_Data(Q->array, Q->front);

		// if (front == rear) => Queue is empty after DeQueue
        if(Q->front == Q->rear)
        {
			// Reset locations
            Q->front = Q->rear = -1;

        } else {

			// Queue is not empty after DeQueue
            Q->front += 1;
            Q->front = Q->front % Q->size;
        }

    } else {

        printf("\nQueue is EMPTY !!!!\n");

    }

    return value;
}

// Free the memory
void DeleteQueue(Queue *Q)
{
    free(Q->array);
    free(Q);
}
