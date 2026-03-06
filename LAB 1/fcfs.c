#include <stdio.h>

struct Process {
    int pid, at, bt;
    int ct, tat, wt, rt;
    int remaining;
    int completed;
    int started;
};

int main() {
    int n, choice;
    struct Process p[20];
    float total_ct=0, total_tat=0, total_wt=0, total_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT and BT for P%d: ",p[i].pid);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].remaining=p[i].bt;
        p[i].completed=0;
        p[i].started=0;
    }

    printf("\n1. SJF Non-Preemptive");
    printf("\n2. SJF Preemptive (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    int currentTime=0, completed=0;

   
    if(choice==1){

        while(completed<n){
            int idx=-1;
            int minBT=9999;

            for(int i=0;i<n;i++){
                if(p[i].at<=currentTime && p[i].completed==0){
                    if(p[i].bt<minBT){
                        minBT=p[i].bt;
                        idx=i;
                    }
                }
            }

            if(idx!=-1){
                p[idx].rt=currentTime-p[idx].at;
                currentTime+=p[idx].bt;

                p[idx].ct=currentTime;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;

                total_ct+=p[idx].ct;
                total_tat+=p[idx].tat;
                total_wt+=p[idx].wt;
                total_rt+=p[idx].rt;

                p[idx].completed=1;
                completed++;
            }
            else{
                currentTime++;
            }
        }
    }

    else if(choice==2){

        while(completed<n){
            int idx=-1;
            int minRT=9999;

            for(int i=0;i<n;i++){
                if(p[i].at<=currentTime && p[i].remaining>0){
                    if(p[i].remaining<minRT){
                        minRT=p[i].remaining;
                        idx=i;
                    }
                }
            }

            if(idx!=-1){

                if(p[idx].started==0){
                    p[idx].rt=currentTime-p[idx].at;
                    total_rt+=p[idx].rt;
                    p[idx].started=1;
                }

                p[idx].remaining--;
                currentTime++;

                if(p[idx].remaining==0){
                    p[idx].ct=currentTime;
                    p[idx].tat=p[idx].ct-p[idx].at;
                    p[idx].wt=p[idx].tat-p[idx].bt;

                    total_ct+=p[idx].ct;
                    total_tat+=p[idx].tat;
                    total_wt+=p[idx].wt;

                    completed++;
                }
            }
            else{
                currentTime++;
            }
        }
    }

    else{
        printf("Invalid Choice!");
        return 0;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,
        p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    printf("\nAverage CT = %.2f",total_ct/n);
    printf("\nAverage TAT = %.2f",total_tat/n);
    printf("\nAverage WT = %.2f",total_wt/n);
    printf("\nAverage RT = %.2f\n",total_rt/n);

    return 0;
}
