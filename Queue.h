struct Queue {
	QueueNode * top;
	QueueNode * last;
};

Queue * initQueue ();
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, Incident data);
Incident dequeue (Queue * q);
