#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <queue>
#include <fstream>
using namespace std;
struct process_struct
{
  int pid;
  int at;       
  int bt;       
  int ct;
  int wt;
  int tat;
  int rt;
  int start_time;   
  int bt_remaining;

} ps[100];

struct process_rr 
{
public:
    int pid;
    int arrival_time;
    int burst_time;
    int finishing_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int start_time;
} prr[100];

bool comperator_arrival_time(struct process_rr a, struct process_rr b)
{
    float x;
    x = a.arrival_time;
    float y;
    y = b.arrival_time;
    return x < y;
};
bool comperator_pid(struct process_rr a, struct process_rr b)
{
    float x;
    x= a.pid;
    float y;
    y = b.pid;
    return x < y;
};

bool comparatorAT(struct process_struct a,struct process_struct b)
{
   int x =a.at;
   int y =b.at;
   return x < y;
}
bool comparatorPID(struct process_struct a,struct process_struct b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}

int main()
{
    int n, quantum_time;;
    float burst_time_remaining[100];
   cout << "\t\t\t Hello There \n";
   cout << "\t OS Process Scheduling Program \n ";
   cout << "Please Enter Number of Processes: ";
   cin >> n;
   cout << "Please Enter Quantum Time no. (if there is): ";
   cin >> quantum_time;;
   float sum_tat=0;
   float sum_wt=0;
   float sum_rt=0;
   int length_cycle,total_idle_time=0;
   float cpu_utilization;
   cout << fixed << setprecision(2);
        
        for(int i=0;i<n;i++)
        {
            cout<<"\nEnter Process (" <<i+1<< ") Arrival Time: ";
            cin >> ps[i].at;
            prr[i].arrival_time = ps[i].at; 
            ps[i].pid=i;
            prr[i].pid=i;
        }
        
        for(int i=0;i<n;i++)
        {
            cout<<"\nEnter Process (" <<i+1<< ") Burst Time: ";
            cin >> ps[i].bt;
            prr[i].burst_time = ps[i].bt;
            burst_time_remaining[i]=prr[i].burst_time;

        }
        sort(ps,ps+n, comparatorAT);
        for(int i=0;i<n;i++)
        {
          ps[i].start_time = (i==0) ? ps[i].at : max(ps[i].at, ps[i-1].ct);
          ps[i].ct =  ps[i].start_time + ps[i].bt;
          ps[i].tat = ps[i].ct-ps[i].at;
          ps[i].wt = ps[i].tat-ps[i].bt;
          ps[i].rt=ps[i].wt;
           
          sum_tat += ps[i].tat;
          sum_wt += ps[i].wt;
          sum_rt += ps[i].rt;
          total_idle_time += (i==0) ? 0 : (ps[i].start_time -  ps[i-1].ct);
        }
        length_cycle = ps[n-1].ct - ps[0].start_time;
        sort(ps,ps+n, comparatorPID);

        ofstream fileOut;
        ofstream process;
        ofstream num1;
        fileOut.open("output.txt");
        num1.open("FCFS_Finishing_Time.txt");
        process.open("FCFS_Processes.txt");

        fileOut<<"\n\t\t\t FCFS \n";
        fileOut<<"\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
        for(int i=0;i<n;i++)
        { fileOut<<i+1<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt
        <<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
        fileOut<<endl;
        num1<<ps[i].ct<<" ";
        process<<"Process ("<<i+1<<")"<<" ";
        
        
        }
        num1.close();
        process.close();

        cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle;        
        fileOut<<"\nAverage Turn Around time= "<< sum_tat/n;
        fileOut<<"\nAverage Waiting Time= "<<sum_wt/n;
        fileOut<<"\nAverage Response Time= "<<sum_rt/n;
        fileOut<<"\nThroughput= "<<n/(float)length_cycle;
        fileOut<<"\nCPU Utilization(Percentage)= " << cpu_utilization*100;
        fileOut<<endl;

        bool is_completed[100]={false},is_first_process=true;
        int current_time = 0;
        int completed = 0;;
        int sum_tat1=0,sum_wt1=0,sum_rt1=0,total_idle_time1=0,prev=0,length_cycle1;
        float cpu_utilization1;
        int max_completion_time,min_arrival_time;
        cout << fixed << setprecision(2);

        //SJF 
        while(completed!=n)
           {
               //find process with min. burst time in ready queue at current time
               int min_index = -1;
               int minimum = INT_MAX;
               for(int i = 0; i < n; i++) {
                   if(ps[i].at <= current_time && is_completed[i] == false) {
                       if(ps[i].bt < minimum) {
                           minimum = ps[i].bt;
                           min_index = i;
                       }
                       if(ps[i].bt== minimum) {
                           if(ps[i].at < ps[min_index].at) {
                               minimum= ps[i].bt;
                               min_index = i;
                           }
                       }
                   }
               }

               if(min_index==-1)
               {
                   current_time++;
               }
               else
               {
               ps[min_index].start_time = current_time;
               ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
               ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
               ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
               ps[min_index].rt = ps[min_index].wt;
               // ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;
                       
               sum_tat1 +=ps[min_index].tat;
               sum_wt1 += ps[min_index].wt;
               sum_rt1 += ps[min_index].rt;
               total_idle_time1 += (is_first_process==true) ? 0 : (ps[min_index].start_time -  prev);
               
               completed++;
               is_completed[min_index]=true;
               current_time = ps[min_index].ct;
               prev= current_time;
               is_first_process = false;
               }
           }
           
           //Calculate Length of Process completion cycle
           max_completion_time = INT_MIN;
           min_arrival_time = INT_MAX;
           for(int i=0;i<n;i++)
           {
               max_completion_time = max(max_completion_time,ps[i].ct);
               min_arrival_time = min(min_arrival_time,ps[i].at);
           }
           length_cycle1 = max_completion_time - min_arrival_time;
           
           ofstream num2;
           ofstream process1;
           process1.open("SJF_Process");
           num2.open("SJF_Finishing_Time.txt");
           fileOut<<"\n\t\t\t SJF \n";
           fileOut<<"\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
           for(int i=0;i<n;i++)
           {
            fileOut<<i+1<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt
            <<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt
            <<"\t"<<ps[i].rt<<endl;
            num2<<ps[i].ct<<" ";
            process1<<i+1<<" ";
           
            fileOut<<endl;
           }
           num2.close();
           process1.close();
           
           cpu_utilization1 = (float)(length_cycle1 - total_idle_time1)/ length_cycle1;

           fileOut<<"\nAverage Turn Around time= "<< (float)sum_tat1/n;
           fileOut<<"\nAverage Waiting Time= "<<(float)sum_wt1/n;
           fileOut<<"\nAverage Response Time= "<<(float)sum_rt1/n;
           fileOut<<"\nThroughput= "<<n/(float)length_cycle1;
           fileOut<<"\nCPU Utilization(Percentage)= " << cpu_utilization1*100;

    int index;
    float cpu_utilizationRR;
    queue<int> q;
    bool visitedRR[50]={false}, is_first_processRR=true;
    int current_timeRR = 0, max_completetion_timeRR;
    int completedRR = 0, total_idle_timeRR=0, cycle_lengthRR;
    float turn_around_time_sum=0,waiting_time_sum=0,response_time_sum =0;
    
    cout << fixed << setprecision(2);
    
    sort(prr, prr+n,comperator_arrival_time);
    
    q.push(0);
    visitedRR[0] = true;
    
    while (completedRR != n)
    {
        index = q.front();
        q.pop();
        if (burst_time_remaining[index] == prr[index].burst_time)
        {
            prr[index].start_time = max(current_timeRR, prr[index].arrival_time);
            total_idle_timeRR += (is_first_processRR == true) ? 0 : prr[index].start_time - current_timeRR ;
            current_timeRR = prr[index].start_time;
            is_first_processRR = false;
            
        }
        if (burst_time_remaining[index] - quantum_time > 0)
        {
            burst_time_remaining[index] -= quantum_time;
            current_timeRR += quantum_time;
        }
        else
        {
            current_timeRR += burst_time_remaining[index];
            burst_time_remaining[index]=0;
            completedRR++;
            
            prr[index].finishing_time = current_timeRR;
            prr[index].turnaround_time = prr[index].finishing_time - prr[index].arrival_time;
            prr[index].waiting_time = prr[index].turnaround_time - prr[index].burst_time;
            prr[index].response_time = prr[index].start_time - prr[index].arrival_time;
            
            turn_around_time_sum += prr[index].turnaround_time;
            waiting_time_sum += prr[index].waiting_time;
            response_time_sum += prr[index].response_time;
        }
    
            
            for (int i = 1; i<n; i++)
            {
                if (burst_time_remaining[i] > 0 && prr[i].arrival_time <= current_timeRR && visitedRR[i] == false )
                {
                    q.push(i);
                    visitedRR[i] = true;
                }
            }
        if (burst_time_remaining[index]>0)
            q.push(index);
        
        if (q.empty()) {
            for (int i =1; i<n; i++) {
                if (burst_time_remaining[i] > 0 ) {
                    q.push(i);
                    visitedRR[i] = true;
                    break;
                }
            }
        }
    }
        max_completetion_timeRR = INT_MIN;
        
        for (int i = 0 ; i < n ; i++)
            max_completetion_timeRR = max(max_completetion_timeRR, prr[i].finishing_time);
        
        cycle_lengthRR = max_completetion_timeRR - prr[0].arrival_time;
        
        cpu_utilizationRR = (float)(cycle_lengthRR - total_idle_timeRR)/ cycle_lengthRR;
        
        sort (prr, prr+n , comperator_pid);
        ofstream num3;
         ofstream process2;
         process2.open("RR_Process.txt");
        num3.open("RR_Finishing_Time.txt");
        fileOut<<endl;
        fileOut<<"\n\t\t\t RR \n";
        fileOut<<"\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
        for (int i= 0 ; i < n ; i++)
        {   
        fileOut<<i<<"\t\t"<<prr[i].arrival_time<<"\t"<<prr[i].burst_time<<"\t\t"<<prr[i].finishing_time<<"\t"<<prr[i].turnaround_time<<"\t"<<prr[i].waiting_time<<"\t"<<prr[i].response_time<<endl;
        fileOut<<endl;
        num3<<prr[i].finishing_time<<" ";
        process2<<i+1<<" ";
        }
        fileOut<<" \n Average Turn Around time = "<<(float)turn_around_time_sum/n;
        fileOut<<" \n Average Waiting Time = "<<(float)waiting_time_sum/n;
        fileOut<<" \n Average Response Time = "<<(float)response_time_sum/n;
        fileOut<<" \n Throughput=" << n/(float)cycle_lengthRR;
        fileOut<<" \n CPU Utilization(Percentage) = "<< (cpu_utilizationRR*100)<<endl;
        process2.close();
        num3.close();
        fileOut.close();
        return 0;
    
}