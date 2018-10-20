#include <stdio.h>
#include <stdlib.h>
 
#define MAX_TREE_HT 100
 
struct MinHeapNode
{
    char data;  
    unsigned freq;
    struct MinHeapNode *left, *right;
};
 
struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 

struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
   int i;
    ++minHeap->size;
    i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}
 
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
 
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}
 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
   int i;

    struct MinHeap* minHeap = createMinHeap(size);
    for ( i = 0; i < size; ++i){
        minHeap->array[i] = newNode(data[i], freq[i]);
   }
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
 
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    if (isLeaf(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size)
{
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

   int arr[MAX_TREE_HT], top = 0;
   printCodes(root, arr, top);
}
int check(struct MinHeapNode* data,char c)
{
   int i;
   for(i=0;data[i].data != NULL;i++)
   {
      if( data[i].data == c){
         return i;
      }
   }
   return -1;
}
 
int main()
{
    FILE* fp; 
   FILE* fop;

   int i,j=0;
   int cnt=0;

   struct MinHeapNode* data = NULL;
   char* c = (char*)malloc(sizeof(char));
   char* arr;
   int* freq;

   fp = fopen("week10.txt","rt"); //입력 파일 열기
   fop = fopen("201302481.txt","wt"); //출력 파일 열기
   data = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

   while(!feof(fp)) 
   {
      c = (char*)realloc(c,sizeof(char)*(cnt+1));
      fscanf(fp,"%c,",&c[cnt++]);
   }

   data = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)*cnt);
   for(i=0;i<cnt;i++)
   {
      if(check(data,c[i]) >= 0)
      {
         data[check(data,c[i])].freq++;
      }
      else
      {
          data[j].data = c[i];
          data[j].freq = 1;
          j++;
      }
   }
   arr = (char*)malloc(sizeof(char)*j);
   freq = (int*)malloc(sizeof(int)*j);
   for(i=0;i<j;i++)
   {
      arr[i] = data[i].data;
      freq[i] = data[i].freq;
   }
   HuffmanCodes(arr, freq,j);
   
   getchar();
}