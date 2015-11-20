typedef struct queueElement{
  unsigned short num;
  struct queueElement * next;
}queueElement;

extern queueElement **qBack;
extern queueElement **qFront;

extern void enqueue(unsigned short number);
extern unsigned short dequeue();
