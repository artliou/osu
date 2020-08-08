# CS325 HW5
# Time: O(n + r)
# Space: O()

# Tasks
# Create a graph G where each vertex represents a wrestler and each edge represents a rivalry. The graph will contain n vertices and r edges. 
# Perform as many BFS’s as needed to visit all vertices. 
# Assign all wrestlers whose distance is even to be babyfaces and all wrestlers whose distance is odd to be heels. 
# Then check each edge to verify that it goes between a babyface and a heel. 

# def bfs(activitySet, start, finish):

# End Function

# Global Variable
wrestlers = []
rivalries = []

# Open a file caled act.txt
# inFile = open("wrestler.txt")

# Each line is a string in the linesToSplit array
linesToSplit = inFile.read().splitlines()
# print "Raw Parse", linesToSplit

# Gathering and Activities
while len(linesToSplit) > 0:
	# Parsing Wrestlers
	wrestlerNum = int(linesToSplit.pop(0))
	print wrestlerNum
	wrestlerNumTemp = wrestlerNum
	# tempActivity = []
	while wrestlerNumTemp > 0:
		wrestlerName = linesToSplit.pop(0)
		# print wrestlerName
		wrestlers.append(wrestlerName)
		wrestlerNumTemp -= 1
	print "Done with Wrestler Name"

	rivalryNum = int(linesToSplit.pop(0))
	print "rivalryNum: ", rivalryNum
	rivalryNumTemp = rivalryNum
	while rivalryNumTemp > 0:
		rivalryPair = linesToSplit.pop(0)
		pairArray = rivalryPair.split()
		clearPair = [pairArray.pop(0), pairArray.pop(0)]
		rivalry.append(clearPair)
		rivalryNumTemp -= 1
	print "Done with Rivalry Pairs"
# Done Parsing
print "Wrestlers", wrestlers
print "Rivalries", rivalries
print "Parsing Complete"


# print "Algo Complete"
# inFile.close()