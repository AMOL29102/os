#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// FCFS Page Replacement
void fcfs(int pages[], int n, int frames)
{
    int page_faults = 0;
    int frame[frames];
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            page_faults++;
            frame[i % frames] = pages[i]; // Place the page in the next available frame
            printf("Page %d is loaded\n", pages[i]);
        }
    }
    printf("FCFS: Total Page Faults = %d\n", page_faults);
}

// LRU Page Replacement
void lru(int pages[], int n, int frames)
{
    int page_faults = 0;
    int frame[frames];
    int last_used[frames];
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                last_used[j] = i; // Update the last used index
                break;
            }
        }
        if (flag == 0)
        {
            page_faults++;
            int min_index = 0;
            for (int j = 1; j < frames; j++)
            {
                if (last_used[j] < last_used[min_index])
                {
                    min_index = j;
                }
            }
            frame[min_index] = pages[i];
            last_used[min_index] = i;
            printf("Page %d is loaded\n", pages[i]);
        }
    }
    printf("LRU: Total Page Faults = %d\n", page_faults);
}

// Optimal Page Replacement
void optimal(int pages[], int n, int frames)
{
    int page_faults = 0;
    int frame[frames];
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            page_faults++;
            if (i < frames)
            {
                frame[i] = pages[i]; // Fill the frames initially
            }
            else
            {
                int farthest = -1, replace_index = -1;
                for (int j = 0; j < frames; j++)
                {
                    int found = 0;
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == pages[k])
                        {
                            found = 1;
                            break;
                        }
                    }
                    if (!found)
                    {
                        replace_index = j;
                        break;
                    }
                    if (farthest < k)
                    {
                        farthest = k;
                        replace_index = j;
                    }
                }
                frame[replace_index] = pages[i];
            }
            printf("Page %d is loaded\n", pages[i]);
        }
    }
    printf("Optimal: Total Page Faults = %d\n", page_faults);
}

int main()
{
    int frames;
    int pages[MAX_PAGES];
    int n;

    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &frames);
    if (frames < 3)
    {
        printf("Frame size must be at least 3!\n");
        return -1;
    }

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\nFCFS Page Replacement Algorithm:\n");
    fcfs(pages, n, frames);

    printf("\nLRU Page Replacement Algorithm:\n");
    lru(pages, n, frames);

    printf("\nOptimal Page Replacement Algorithm:\n");
    optimal(pages, n, frames);

    return 0;
}
