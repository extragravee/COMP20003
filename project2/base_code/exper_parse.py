import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pprint


pp = pprint.PrettyPrinter()

stream = ""
with open("acc_output.txt", "r") as file:
	for line in file:
		if "./" not in line:
			stream += line
		else:
			temp = line.split("./")
			stream += (temp[0] + "\n" + "./" + temp[1])


stream = stream.split("\n")[1:]

row_list = []
current_row = {}
sample_scores = []
counter = 0
for elem in stream:
	if "./" in elem:
		elem = elem.split()
		current_row['level'] = elem[1]
		current_row['propagation'] = elem[3]
		current_row['budget'] = elem[-1]
		# row_list.append(current_row)
	if "Score" in elem:
		if(counter < 3):
			elem = elem.split()
			sample_scores.append(int(elem[-1]))
			counter+=1
		if (counter==3):
			counter = 0
			current_row['samples'] = np.array(sample_scores)
			row_list.append(current_row)
			current_row = {}
			sample_scores = []


# print(row_list)
df = pd.DataFrame(row_list)
sample_scores = df.samples.values
# print(sample_scores)
averages = []
std_dev = []
for i in sample_scores:
	averages.append(np.mean(i))
	std_dev.append(np.std(i))

df['average_sample_score'] = averages
df['std_dev'] = std_dev

df_max = df[df['propagation']=="max"]
df_avg = df[df['propagation']=="avg"]
del df_max['propagation']
del df_max['std_dev']
del df_max['samples']
del df_avg['propagation']
del df_avg['std_dev']
del df_avg['samples']

# PLOTTING MAX PROP
df_max_1 = df_max[df_max['level']=="1"]
df_max_2 = df_max[df_max['level']=="2"]
df_max_3 = df_max[df_max['level']=="3"]

plot = plt.scatter(df_max_1.budget.values, df_max_1.average_sample_score.values)
plot = plt.scatter(df_max_2.budget.values, df_max_2.average_sample_score.values)
plot = plt.scatter(df_max_3.budget.values, df_max_3.average_sample_score.values)
plt.title("Max Propogation")
plt.xlabel("Budget")
plt.legend([1,2,3], title="Level")
plt.ylabel("Average Scores")
plt.show()

#PLOTTING AVG PROP
df_avg_1 = df_avg[df_avg['level']=="1"]
df_avg_2 = df_avg[df_avg['level']=="2"]
df_avg_3 = df_avg[df_avg['level']=="3"]

plot = plt.scatter(df_avg_1.budget.values, df_avg_1.average_sample_score.values)
plot = plt.scatter(df_avg_2.budget.values, df_avg_2.average_sample_score.values)
plot = plt.scatter(df_avg_3.budget.values, df_avg_3.average_sample_score.values)
plt.title("Avg Propogation")
plt.xlabel("Budget")
plt.legend([1,2,3], title="Level")
plt.ylabel("Average Scores")
plt.show()

# mpl.pyplot.savefig("1.png")
# print(df_max)
# print(df_avg)

