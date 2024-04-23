////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// ************* IMPORTANT ********************************
// Please find the full instructions for this coding test in the quiz "Midterm
// Coding Test" on HDLMS.
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximum number of ASCII letters
#define MAX_CHAR 256

////////////////////////////////////////////////////////////

// structures

////////////////////////////////////////////////////////////

struct zNode {
  struct zNode *left;
  struct zNode *right;
  char letter;
  unsigned int freq;
};

struct zNode *newZNode(char letter, int freq) {
  struct zNode *self = (struct zNode *)malloc(sizeof(struct zNode));
  // Dynamically allocated memory still stays allocated until the main program
  // terminates completely
  self->left = NULL;
  self->right = NULL;
  self->letter = letter;
  self->freq = freq;
  return self;
}

struct QNode {
  struct zNode *key;
  struct QNode *next;
};

struct QNode *newQNode(struct zNode *z) {
  struct QNode *self = (struct QNode *)malloc(sizeof(struct QNode));
  // Dynamically allocated memory still stays allocated until the main program
  // terminates completely
  self->key = z;
  self->next = NULL;
  return self;
}

struct Queue {
  struct QNode *front, *rear;
};

char codewords[MAX_CHAR][100] = {0};
// assume that each codeword is less than 100 bits.
int freqs[MAX_CHAR] = {0};

////////////////////////////////////////////////////////////

// function declarations

////////////////////////////////////////////////////////////

void insert(struct Queue *Q, struct zNode *z);
struct zNode *extractMin(struct Queue *Q);
int checkQueueLen(struct Queue *Q);

struct zNode *getHuffmanCodeTree(char *text);
void getCodewords(struct zNode *codeTree);
void getCodewordsSofar(struct zNode *codeTree, char *so_far);
void printCodewords();
int getNumOfLeaves(struct zNode *codeTree);

int computeTheTotalNumberOfBits();
void printEncodedText(char *text);

////////////////////////////////////////////////////////////

// main function

////////////////////////////////////////////////////////////

int main(void) {
  char text[] =
      "The LORD is my shepherd, I shall not be in want. He makes me lie down "
      "in green pastures, he leads me beside quiet waters, he restores my "
      "soul. He guides me in paths of righteousness for his name's sake. Even "
      "though I walk through the valley of the shadow of death, I will fear no "
      "evil, for you are with me; your rod and your staff, they comfort me. "
      "You prepare a table before me in the presence of my enemies. You anoint "
      "my head with oil; my cup overflows. Surely goodness and love will "
      "follow me all the days of my life, and I will dwell in the house of the "
      "LORD forever.";
  printf("%s\n", text);
  printf("The length of the given text is %ld\n", strlen(text));

  struct zNode *codeTree = getHuffmanCodeTree(text);
  getCodewords(codeTree);

  printCodewords();

  int numOfTotalBits = computeTheTotalNumberOfBits();
  printf("Total number of bits required for the given text: %d\n",
         numOfTotalBits);

  printEncodedText(text);

  return 0;
}

////////////////////////////////////////////////////////////

// function definitions

////////////////////////////////////////////////////////////

int computeTheTotalNumberOfBits() {
  int sum = 0;
  // (3) enter your code here
  for (int i = 0; i < MAX_CHAR; i++) {
    if (freqs[i] != 0) {
      sum += freqs[i] * strlen(codewords[i]);
    }
  }
  return sum;
}

void getCodewords(struct zNode *codeTree) {
  char so_far[100] = "";
  getCodewordsSofar(codeTree, so_far);
}

void getCodewordsSofar(struct zNode *codeTree, char *so_far) {
  if (codeTree->left->letter != '\0') {
    strcat(codewords[(unsigned char)(codeTree->left->letter)], so_far);
    strcat(codewords[(unsigned char)(codeTree->left->letter)], "0");
  } else {
    char temp[100] = "";
    strcat(temp, so_far);
    strcat(temp, "0");
    getCodewordsSofar(codeTree->left, temp);
  }

  if (codeTree->right->letter != '\0') {
    strcat(codewords[(unsigned char)(codeTree->right->letter)], so_far);
    strcat(codewords[(unsigned char)(codeTree->right->letter)], "1");
  } else {
    char temp[100] = "";
    strcat(temp, so_far);
    strcat(temp, "1");
    getCodewordsSofar(codeTree->right, temp);
  }
}

int getNumOfLeaves(struct zNode *codeTree) {
  if (codeTree == NULL)
    return 0;
  if (codeTree->left == NULL && codeTree->right == NULL)
    return 1;
  else
    return getNumOfLeaves(codeTree->left) + getNumOfLeaves(codeTree->right);
}

void printCodewords() {
  for (int i = 0; i < MAX_CHAR; i++) {
    if (freqs[i] != 0) {
      printf("Letter: %c, \t Freq: %d, \tCodeword: %s\n", i, freqs[i],
             codewords[i]);
    }
  }
}

struct zNode *getHuffmanCodeTree(char *text) {

  unsigned int text_length = strlen(text);

  // inialziae Queue
  struct Queue Q;
  Q.front = NULL;
  Q.rear = NULL;

  // get the frequency of each character in the given text.
  for (int i = 0; i < text_length; i++) {
    if (text[i] == '\0') // '\0' : NULL : end of string
      break;
    else
      freqs[(unsigned char)text[i]]++;
    // (unsigned char)text[i] is the ASCII value of the current letter < 256
  }

  // find all distinct characters and create zNode for each distinct character
  int num_total_distinct_chars = 0;
  for (int i = 0; i < MAX_CHAR; i++) {
    if (freqs[i] != 0) {
      struct zNode *z = newZNode((char)i, freqs[i]);
      insert(&Q, z);
      // (1) enter your code here
      num_total_distinct_chars++;

    }
  }

  printf("The number of total distinct charaters: %d\n",
         num_total_distinct_chars);

  for (int i = 0; i < num_total_distinct_chars - 1; i++) {
    // printf("Queue Length: %d\n", checkQueueLen(&Q));
    struct zNode *z = newZNode('\0', 0); // '\0' : NULL
    // (2) enter your code here
    struct zNode *x = extractMin(&Q);
    struct zNode *y = extractMin(&Q);
    z->left = x;
    z->right = y;
    z->freq = z->left->freq + z->right->freq;
    insert(&Q, z);
  }

  // printf("Queue Length: %d\n", checkQueueLen(&Q));

  return extractMin(&Q);
}

void insert(struct Queue *Q, struct zNode *z) {
  struct QNode *temp = newQNode(z);

  if (Q->rear == NULL) {
    Q->front = temp;
    Q->rear = temp;
  } else {
    Q->rear->next = temp;
    Q->rear = temp;
  }
}

struct zNode *extractMin(struct Queue *Q) {
  struct zNode *z;
  struct QNode *curr = Q->front;
  int min = curr->key->freq;
  while (curr->next != NULL) {
    curr = curr->next;
    if (curr->key->freq < min)
      min = curr->key->freq;
  }

  curr = Q->front;
  if (curr->key->freq == min) {
    if (curr->next == NULL)
      Q->rear = NULL;
    else
      Q->front = curr->next;
    return curr->key;
  }
  while (curr->next != NULL) {
    struct QNode *prev = curr;
    curr = curr->next;
    if (curr->key->freq == min) {
      prev->next = curr->next;
      return curr->key;
    }
  }
  return NULL;
}

int checkQueueLen(struct Queue *Q) {
  int i = 0;
  if (Q->rear == NULL)
    return i;
  else {
    struct QNode *curr = Q->front;
    i++;
    while (curr->next != NULL) {
      curr = curr->next;
      i++;
    }
    return i;
  }
}

void printEncodedText(char *text) {
  printf("The following is the converted text using the obtained codewords.\n");
  // (4) enter your code here
  for (int i = 0; text[i] != '\0'; i++) {
    printf("%s", codewords[(unsigned char)text[i]]);
  }
  printf("\n");
}