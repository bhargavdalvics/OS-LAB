#include <stdio.h>

int main() {
    int pages[20], frames[10], n, f, i, j, k = 0, faults = 0, found;
    //pages[20]-stores page reference string.
    //frames[10]-stores pages currently in memory.
    //n-number of page references.
    //f-number of frames
    //k-points to the frame to be replaced next.

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1; //initially 

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) { //If page already exists in memory.
                found = 1;
                break;
            }
        }

        if(!found) {
            frames[k] = pages[i]; //Insert page into frame k.
            k = (k + 1) % f;      //Move pointer to next frame.
            faults++;
        }
    }

    printf("Page Faults = %d\n", faults);
    return 0;
}
