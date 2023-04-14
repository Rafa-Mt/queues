// Estructuras Dinamicas de Datos: Colas
// Rafael Mata

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 80
#define true 1
#define false 0

typedef struct {
    char name[MAX_STRING];
    char author[MAX_STRING];
    char genre[MAX_STRING];
    int pages;
    int launchYear;
    char editorial[MAX_STRING];
    char printer[MAX_STRING];
    int copies; 
    int isColored;
} Document;

typedef struct Node {
    Document content;
    struct Node* next;
} Node;

typedef struct {
    Node* first;
    Node* last;
    int size;
} Queue;

Node* NewNode(Document value) {
    Node* new = NULL;
    new = (Node*)malloc(sizeof(Node));

    if (new != NULL) {
        new->content = value;
        new->next = NULL;
    }
    return new;
}

Queue* NewStack(Document firstValue) {
    Queue* new = NULL;
    new = (Queue*)malloc(sizeof(Queue));

    if (new != NULL) {
        Node* node = NewNode(firstValue);
        new->first = node;
        new->last = node;
        new->size = 1;
    }
    return new;
}

void push(Queue* queue, Document value) {
    Node* node = NewNode(value);
    node->next = queue->first;
    queue->first = node;
    queue->size++;
}

void pop(Queue* queue) {
    Node* erased = queue->first;
    queue->first = erased->next;
    free(erased);
    queue->size--;
}

void iterateQueue(Queue* queue, Document (*function)(Document)) {
    Node* actual = queue->first;
    while (actual != NULL) {
        (*function)(actual->content);
        actual = actual->next;
    }
}

int itemExist(Queue* queue, char name[]) {
    Node* actual = queue->first;
    while (actual != NULL) {
        if (!strcmp(actual->content.name, name)) return 1; 
    }
    return 0;
}

Document printInfo(Document n) {
    printf(
        "#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&\n"
        " * \t Name: \t %s \n"
        " * \t Author: \t %s \n"
        " * \t Genre: \t %s \n"
        " * \t Editorial: \t\t%s \n"
        " * \t Copies: \t\t%i \n"
        " * \t Printer target: %s\n"        
        " * \t Launch Year: \t %i \n"               
        " * \t Print type: \t %s \n"
        " * \t N# of Pages:\t %i \n"
        "#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&#&\n"
        ,n.name, n.author, n.genre, n.editorial, n.copies, n.printer, n.launchYear
        , n.isColored ? "Colored" : "Grayscale", n.pages
        );

    return n;
}

int main() {
    Document dummy1 = {"Inteligencia artificial en automoviles", "Elon Musk", "Tesis", 59, 2020, "Tesla", "Industrial HP", 1024, true};
    Document dummy2 = {"Tu, pero mas fuerte", "Jose Juan", "Analisis", 24 , 2022, "Eurogamer", "Digital", 200000, true};

    Queue* queue = NewStack(dummy1);
    push(queue, dummy2);

    iterateQueue(queue, &printInfo);

    printf("\nAfter deleting a record\n\n");
    pop(queue);

    iterateQueue(queue, &printInfo);
    return 0;
}
