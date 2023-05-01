import matplotlib.pyplot as plt

words = []
file = open('/Users/michael/Desktop/Project/Process Scheduler/FCFS_Finishing_Time.txt', 'r')
lines = file.read().split(' ')
for line in lines:
    words.extend(line.split())

finishing_time = words

tasks = []
file2 = open('/Users/michael/Desktop/Project/Process Scheduler/FCFS_Processes.txt', 'r')
lines = file2.read().split(' ')
for line in lines:
    tasks.extend(line.split())

processes = tasks

fig = plt.figure(figsize=(7,5))
plt.bar (processes, finishing_time, width=0.5)
plt.show()













