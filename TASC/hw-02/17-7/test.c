#include <stdio.h>
#include "queue.h"
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"

int main()
{
    queueADT Q = NewQueue();
    string s;
    printf("Please enter strings in line.\nIf there's a string, queue will push.\nIf there's nothing but 'enter', queue will pop.\nEnter 'exit' if you want to quit.\n");
    while ((s = GetLine()) && !StringEqual(ConvertToLowerCase(s), "exit")) {
        if (StringEqual(s, "")) {
            printf("%s\n", (char*)Dequeue(Q));
        }
        else {
            Enqueue(Q, (void*)s);
        }
        printf("length: %d\n", QueueLength(Q));
    }
    
    return 0;
    
}