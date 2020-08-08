# CS325 HW4
# Time: O(n log n)
# Space: O(n)

# Tasks
# 1) Parse Input
# 2) Sort activities
# 3) Prep to insert into greedyActivity
# 4) Make greedy work

def greedyActivity(activitySet, start, finish):
	n = len(activitySet) - 1
	# print "First", [activitySet[n][0]]
	resultsArray = [activitySet[n][0]]
	currIndex = n
	# m = n-1
	for m in range(n - 1, -1, -1):
		if finish[m] <= start[currIndex]:
			# Add to front of results array
			resultsArray.insert(0, activitySet[m][0])
			#set to activiti's start time index
			currIndex = m
	return resultsArray

# End Function

# Global Variable
activitySets = []

# Open a file caled act.txt
inFile = open("act.txt")

# Each line is a string in the linesToSplit array
linesToSplit = inFile.read().splitlines()
# print "Raw Parse", linesToSplit

# Gathering and Activities
while len(linesToSplit) > 0:
	testCase = int(linesToSplit.pop(0))
	# print "Length of Case #", len(activitySets), ":", testCase
	trim = testCase
	tempActivity = []
	while trim > 0:
		activityLine = linesToSplit.pop(0)
		activityStringArray = activityLine.split()
		# print activityStringArray
		# activityNum = int(activityStringArray.pop(0))
		# activityStart = int(activityStringArray.pop(0))
		# activityFinish = int(activityStringArray.pop(0))
		activityNumArray = [int(activityStringArray.pop(0)),
                      int(activityStringArray.pop(0)), int(activityStringArray.pop(0))]
		# activityNumArray.append(int(activityStringArray.pop(0)))
		# activityNumArray.append(int(activityStringArray.pop(0)))
		# activityNumArray.append(int(activityStringArray.pop(0)))
		tempActivity.append(activityNumArray)
		
		trim -= 1
	activitySets.append(tempActivity)
# Done Parsing

# print activitySets
# print "Parsing Complete"

# Helper Function to sort by finish Time
def finishTime(activity):
    return activity[2]

# For each activitySet, sort activities, run greedy, then print
setNumber = 1
for activityList in activitySets:
	#sort set
	activityList.sort(key=finishTime)
	# print "Sorted", activityList
	# End Sorting
	number = []
	start = []
	finish = []
	for activity in activityList:
			number.append(activity[0])
			start.append(activity[1])
			finish.append(activity[2])
	# End Array Creation

	# run greedy
	results = greedyActivity(activityList, start, finish)
	print "Set", setNumber
	print "Number of activities selected =", len(results)
	print "Activities", results

	setNumber += 1
	# When Greedy is Complete, print list
#End Test Case Iteration

# print activitySets
# print "Sorting Complete"
# print "Greedy Complete"
inFile.close()
