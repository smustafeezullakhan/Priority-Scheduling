#include <stdio.h>
#define MAX_PROCESSES 100 

int main() {
  
  int num_processes;
  printf("Enter number of processes: ");
  scanf("%d", &num_processes);

  int arrival_times[MAX_PROCESSES];
  int burst_times[MAX_PROCESSES];

  for(int i=0; i<num_processes; i++) {
    printf("Enter arrival time and burst time for process %d: ", i+1);
    scanf("%d%d", &arrival_times[i], &burst_times[i]);
  }

  int current_time = 0;
  int completed_count = 0;
  int completion_times[MAX_PROCESSES]; 
  int total_wait_time = 0;

  while(completed_count != num_processes) {
    
    for(int i=0; i<num_processes; i++) {
      if(arrival_times[i] <= current_time && completion_times[i] == 0) {
        double priority = 1.0 + (double)(current_time - arrival_times[i]) / burst_times[i];
        printf("Priority of P%d: %lf\n", i+1, priority);
      }
    }

    int selected_index = -1;
    double max_priority = -1;

    for(int i=0; i<num_processes; i++) {
      if(arrival_times[i] <= current_time && completion_times[i] == 0) {
        double priority = 1.0 + (double)(current_time - arrival_times[i]) / burst_times[i];
        if(priority > max_priority) {
          max_priority = priority;
          selected_index = i; 
        }
      }
    }

    if(selected_index != -1) {
      completion_times[selected_index] = current_time + burst_times[selected_index];
      total_wait_time += current_time - arrival_times[selected_index];
      current_time += burst_times[selected_index];
      completed_count++;

      printf("Process %d completed at time %d\n", selected_index+1, completion_times[selected_index]);
    }
    else {
      current_time++;
      printf("\n"); 
    }
  }

  double average_wait_time = (double)total_wait_time / num_processes;
  printf("Average waiting time = %lf ms", average_wait_time);

  printf("\nGANTT CHART:\n");
  for(int i=0; i<num_processes; i++) {
    printf("P%d ", i+1); 
    for(int j=arrival_times[i]; j<completion_times[i]; j++) {
      printf("--");
    }
    printf("\n");
  }

  printf("\nIndividual waiting times:\n");
  for(int i=0; i<num_processes; i++) {
    int wait_time = completion_times[i] - arrival_times[i] - burst_times[i];
    printf("P%d: %d ms\n", i+1, wait_time);
  }

  return 0;
}
