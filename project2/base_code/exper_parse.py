import pandas as pd
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
			sample_scores.append(elem[-1])
			counter+=1
		if (counter==3):
			counter = 0
			current_row['samples'] = sample_scores
			row_list.append(current_row)
			current_row = {}
			sample_scores = []


# print(row_list)
df = pd.DataFrame(row_list)
print(df)
# pp.pprint(sample_scores)