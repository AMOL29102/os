#include <stdio.h>

void sjf(int pcount, int arrival[], int burst[])
{
    int completionTime[pcount];
    int waitingTime[pcount];
    int turnaroundTime[pcount];
    int remaining[pcount];
    int totalCompleted = 0;
    int currentTime = 0;
    int ttat = 0; // Total Turnaround Time
    int twt = 0;  // Total Waiting Time

    for (int i = 0; i < pcount; i++)
        remaining[i] = burst[i];

    while (totalCompleted != pcount)
    {
        int mini = -1;
        int minRemaining = 1e9;

        for (int i = 0; i < pcount; i++)
        {
            if (arrival[i] <= currentTime && remaining[i] > 0 && remaining[i] < minRemaining)
            {
                minRemaining = remaining[i];
                mini = i;
            }
        }

        if (mini != -1)
        {
            currentTime++;
            remaining[mini]--;

            if (remaining[mini] == 0)
            {
                totalCompleted++;
                completionTime[mini] = currentTime;
                turnaroundTime[mini] = currentTime - arrival[mini];
                waitingTime[mini] = turnaroundTime[mini] - burst[mini];
                ttat += turnaroundTime[mini];
                twt += waitingTime[mini];
            }
        }
        else
        {
            currentTime++;
        }
    }

    printf("\nAverage Turnaround Time: %.2f", (float)ttat / pcount);
    printf("\nAverage Waiting Time: %.2f", (float)twt / pcount);
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < pcount; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
}

void rr(int pcount, int tq, int arrival[], int burst[])
{
    int completionTime[pcount];
    int waitingTime[pcount];
    int turnaroundTime[pcount];
    int remaining[pcount];
    int totalCompleted = 0;
    int currentTime = 0;
    int ttat = 0; // Total Turnaround Time
    int twt = 0;  // Total Waiting Time

    for (int i = 0; i < pcount; i++)
        remaining[i] = burst[i];

    while (totalCompleted != pcount)
    {
        int processDone = 0;

        for (int i = 0; i < pcount; i++)
        {
            if (remaining[i] > 0 && arrival[i] <= currentTime)
            {
                if (remaining[i] <= tq)
                {
                    currentTime += remaining[i];
                    remaining[i] = 0;
                    completionTime[i] = currentTime;
                    turnaroundTime[i] = completionTime[i] - arrival[i];
                    waitingTime[i] = turnaroundTime[i] - burst[i];
                    ttat += turnaroundTime[i];
                    twt += waitingTime[i];
                    totalCompleted++;
                }
                else
                {
                    remaining[i] -= tq;
                    currentTime += tq;
                }
                processDone = 1;
            }
        }

        if (processDone == 0)
            currentTime++;
    }

    printf("\nAverage Turnaround Time: %.2f", (float)ttat / pcount);
    printf("\nAverage Waiting Time: %.2f", (float)twt / pcount);
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < pcount; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
}

int main()
{
    while (1)
    {
        int ch;
        printf("\nEnter choice (1 for SJF, 2 for RR, 0 to Exit): ");
        scanf("%d", &ch);

        if (ch == 0)
        {
            printf("Exiting program.\n");
            break;
        }

        int pcount;
        printf("Enter Number of processes: ");
        scanf("%d", &pcount);
        int arrival[pcount], burst[pcount];

        printf("\nEnter arrival and Burst times:\n");
        for (int i = 0; i < pcount; i++)
            scanf("%d %d", &arrival[i], &burst[i]);
        int tq;
        switch (ch)
        {
        case 1:
            sjf(pcount, arrival, burst);
            break;
        case 2:
            tq;
            printf("Enter Time Quantum for Round Robin: ");
            scanf("%d", &tq);
            rr(pcount, tq, arrival, burst);
            break;
        default:
            printf("Invalid choice. Please enter 1, 2, or 0.\n");
            break;
        }
    }

    return 0;
}