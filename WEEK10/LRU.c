#include <stdio.h>

int main() {
    int p[20], f[10], t[10], n, m, i, j, k, pos, faults = 0;
    //t[]-last used time (index) of each page in the frame.
    //n-no.of page , m-no.offrame

    scanf("%d%d", &n, &m);
    for(i = 0; i < n; i++) 
        scanf("%d", &p[i]);

    for(i = 0; i < m; i++)
        f[i] = -1;

    for(i = 0; i < n; i++) {
        int hit = 0;      //Assume page is not present.
        for(j = 0; j < m; j++)
            if(f[j] == p[i]) {
                t[j] = i;   //Update its recent usage time.
                hit = 1;
            } 

        if(!hit) {
            pos = 0;
            for(j = 1; j < m; j++) 
                if(f[j] == -1 || t[j] < t[pos])  //Smaller time means older usage, least recently used page
                    pos = j;                     //Store frame position to replace.

            f[pos] = p[i];       //Put new page into selected frame.
            t[pos] = i;          //Store current time as last used time.
            faults++;
        }
    }

    printf("Page Faults = %d", faults);
    return 0;
}
