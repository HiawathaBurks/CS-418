#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define maxmiumVal 50000
#define miniVal 0
#define arraySize 10000
#define maxmiumThreads 100

int numArray[arraySize];
int maxValues[maxmiumThreads];
int minValues[maxmiumThreads];
int thread_size;
int thread_no = 0;

void arrayFiller(){

	int tempArray[maxmiumVal];
	int x, y;	
	for(x = miniVal; x < maxmiumVal; x++){
	
		tempArray[x] = x;

	}
	for(y = 0; y < arraySize; y++){

		int z = y + rand() % (maxmiumVal - y);
		int tempOfATemp = tempArray[z];
		tempArray[y] = tempArray[z];
		tempArray[z] = tempOfATemp;
		numArray[y] = tempArray[y];
	
	}
}

void printAllNums(){

	int x;
	printf("First 10 Numbers: \n");
	for(x = 0; x < 10; x++){

		printf("\t%d\n", numArray[x]);

	}
	printf("\nLast 10 Numbers: \n");
	for(x = (arraySize-10); x < arraySize; x++){

		printf("\t%d\n", numArray[x]);

	}

}

void* searchForMaxAndMin(void *arg){

	int x, number = thread_no++;
	int max = miniVal;
	int min = maxmiumVal;
	for(x = number * (arraySize/thread_size); x < (number+1) * (arraySize/thread_size); x++){

		if(numArray[x] > max){

			max = numArray[x];

		
		}
		if(numArray[x] < min){

			min = numArray[x];

		
		}

	}
	maxValues[number] = max;
	minValues[number] = min;
	printf("Threads: %d\n Min: %d\n Max: %d\n Thread No: %d\n", thread_size, min, max, 			number);

}

void search(){

	int max = miniVal;
	int min = maxmiumVal;
	int x;
	int start = clock();
	pthread_t threads[thread_size];
	for(x = 0; x < thread_size; x++){

		pthread_create(&threads[x], NULL, searchForMaxAndMin, (void*)NULL);		

	}
	for(x = 0; x < thread_size; x++){

		pthread_join(threads[x], NULL);		

	}
	for(x = 0; x < thread_size; x++){

		if(maxValues[x] > min){

			max = maxValues[x];		

		}
		if(minValues[x] < max){

			min = minValues[x];		

		}
	
	}
	int end = clock();
	int timeDifference = end - start;
	printf("Threads: %d\n Min: %d\n Max: %d\n Time Taken(in ms): %d\n", thread_size, min, max, 			timeDifference);

}

int main(){
	
	//Fills the Array
	arrayFiller();
	//Prints the first and last 10 numbers in the array
	printAllNums();
	thread_size = 2;
	thread_no = 0;
	search();
	thread_size = 10;
	thread_no = 0;
	search();
	thread_size = 100;
	thread_no = 0;
	search();
	
	return 0;

}
