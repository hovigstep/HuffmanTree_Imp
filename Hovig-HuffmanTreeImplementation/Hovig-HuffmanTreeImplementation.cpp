// Hovig-HuffmanTreeImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

struct nodemh {

	char data;
	unsigned freq;
	struct nodemh *left, *right;
};

struct MH {
	unsigned size;
	unsigned capacity;
	struct nodemh** array;
};

struct nodemh* newNode(char data, unsigned freq)
{
	struct nodemh* temp
		= (struct nodemh*)malloc
		(sizeof(struct nodemh));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MH* createMH(unsigned capacity)

{

	struct MH* MH
		= (struct MH*)malloc(sizeof(struct MH));

	MH->size = 0;
	MH->capacity = capacity;
	MH->array
		= (struct nodemh**)malloc(MH->
			capacity * sizeof(struct nodemh*));
	return MH;
}

void swapnodemh(struct nodemh** a,
	struct nodemh** b)

{

	struct nodemh* t = *a;
	*a = *b;
	*b = t;
}

void MHify(struct MH* MH, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < MH->size && MH->array[left]->
		freq < MH->array[smallest]->freq)
		smallest = left;

	if (right < MH->size && MH->array[right]->
		freq < MH->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapnodemh(&MH->array[smallest],
			&MH->array[idx]);
		MHify(MH, smallest);
	}
}

int isSizeOne(struct MH* MH)
{

	return (MH->size == 1);
}

struct nodemh* extractMin(struct MH* MH)

{

	struct nodemh* temp = MH->array[0];
	MH->array[0]
		= MH->array[MH->size - 1];

	--MH->size;
	MHify(MH, 0);

	return temp;
}

void insertMH(struct MH* MH,
	struct nodemh* nodemh)

{

	++MH->size;
	int i = MH->size - 1;
	while (i && nodemh->freq < MH->array[(i - 1) / 2]->freq) {
		MH->array[i] = MH->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	MH->array[i] = nodemh;
}

void buildMH(struct MH* MH)

{

	int n = MH->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		MHify(MH, i);
}

void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);

	printf("\n");
}

int isLeaf(struct nodemh* root)

{

	return !(root->left) && !(root->right);
}
struct MH* createAndBuildMH(char data[], int freq[], int size)

{

	struct MH* MH = createMH(size);

	for (int i = 0; i < size; ++i)
		MH->array[i] = newNode(data[i], freq[i]);

	MH->size = size;
	buildMH(MH);

	return MH;
}

struct nodemh* buildHuffmanTree(char data[], int freq[], int size)

{
	struct nodemh *left, *right, *top;
	struct MH* MH = createAndBuildMH(data, freq, size);
	while (!isSizeOne(MH)) {

		left = extractMin(MH);
		right = extractMin(MH);
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMH(MH, top);
	}

	return extractMin(MH);
}

void printCodes(struct nodemh* root, int arr[], int top)

{

	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right) {
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root)) {

		printf("%c: ", root->data);
		printArr(arr, top);
	}
}

void HuffmanCodes(char data[], int freq[], int size)

{
	struct nodemh* root
		= buildHuffmanTree(data, freq, size);
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
}

int main()
{
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 5, 9, 12, 13, 16, 45 };
	int size = sizeof(arr) / sizeof(arr[0]);
	HuffmanCodes(arr, freq, size);

	return 0;
}


