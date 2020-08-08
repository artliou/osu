# CS325 HW5
# Time: O(n + r)
# Space: O(Graph)

# Global Variables
wrestlers = []
rivalries = {}
wrestlerTeam = {}
totalWrestlers = 0;
# Open a file caled act.txt
inFile = open("wrestler.txt")

# Each line is a string in the linesToSplit array
linesToSplit = inFile.read().splitlines()
# print "Raw Parse", linesToSplit

# Parsing Text File
while len(linesToSplit) > 0:
	# Parsing Wrestlers
	wrestlerNum = int(linesToSplit.pop(0))
	# print "westlerNum:", wrestlerNum
	totalWrestlers = wrestlerNum
	wrestlerNumTemp = wrestlerNum
	# tempActivity = []
	while wrestlerNumTemp > 0:
		wrestlerName = linesToSplit.pop(0)
		wrestlers.append(wrestlerName)
		rivalries[wrestlerName] = []
		wrestlerNumTemp -= 1
	# print "Done with Wrestler Name"

	# Start Rivalries
	rivalryNum = int(linesToSplit.pop(0))
	# print "rivalryNum:", rivalryNum
	rivalryNumTemp = rivalryNum
	while rivalryNumTemp > 0:
		rivalryPair = linesToSplit.pop(0)
		pairArray = rivalryPair.split()
		person1 = pairArray.pop(0)
		person2 = pairArray.pop(0)
		# Get Index from the wrestlers array
		wrestlers1 = wrestlers.index(person1)
		wrestlers2 = wrestlers.index(person2)
		# print(person1, person2, wrestlers1, wrestlers2)
		# Note: I know the list will contain the wrester name, so do not need to worry about ValueError issues
		# Fields of each key are arrays of the edges. So now each key in rivaltries will be connected to other nodes, IE rivaltries is like a graph and each node in that graph has an array of what it is connected to
		rivalries[wrestlers[wrestlers1]].append(wrestlers[wrestlers2])
		rivalries[wrestlers[wrestlers2]].append(wrestlers[wrestlers1])

		rivalryNumTemp -= 1
	# print "Done with Rivalry Pairs"
# Done Parsing
# print "Wrestlers", wrestlers
# print "Rivalries", rivalries
# print "Parsing Complete"

# Shortest Path List & Set Up Edges LIst
rivalriesCopy = rivalries.copy()
# print rivalriesCopy
graphLengthsList = {}
for person in wrestlers:
	graphLengthsList[person] = 0
# print "Edges", graphLengthsList

# BFS tailored specifically to keep track of distances between wrestlers/rivalries
# Resource: https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
# Resource: https://codereview.stackexchange.com/questions/135156/bfs-implementation-in-python-3
def bfs(wrestlers, startNode, pathLengths):
    traversed = []
		# Start at 1st Node & Set Length as 1
    queue = [startNode]
    pathLengths[startNode] = 1
    counter = 1
    while queue:
        node = queue.pop(0)
        counter = counter + 1
				# If we haven't traversed this node, then add to traversed, grab the list of rivalries / other nodes it is connected too.
        if node not in traversed:
            traversed.append(node)
            rivalries = wrestlers[node]
						# iterate through those nodes and append to queue if not startNode and pathLength is not 0.
            for rival in rivalries:
                if pathLengths[rival] == 0 and rival != startNode:
                    # if it is, then counter will jump
										pathLengths[rival] = counter
                queue.append(rival)
		# Else Move On
    return traversed
# END BFS Function

# Run BFS to clean out the rivalries list
def cleanRivals():
	wrestlerCounter = 0
	while (wrestlerCounter != totalWrestlers):
		localCounter = 0;
		for node in rivalriesCopy:
				if localCounter == 0:
						newStart = node;
						localCounter+=1;
		traversed = bfs(rivalriesCopy, newStart, graphLengthsList)
		wrestlerCounter = wrestlerCounter + len(traversed)
		if wrestlerCounter != totalWrestlers:
			for f in traversed:
					del rivalriesCopy[f]
			# End Iterating Through Traversed List
		# Back to Top
# print "Path Cleansing Complete"

# Iterate Through graphLengthsList. All wrestlers whose distance is even to be babyfaces and all wrestlers whose distance is odd to be heels.
def labelTeams():
	for name in graphLengthsList:
			if (graphLengthsList[name] % 2 == 0):
					wrestlerTeam[name] = "Babyfaces"
					# print "Added", name, "to", wrestlerTeam[name]
			else:
					wrestlerTeam[name] = "Heels"
					# print "Added", name, "to", wrestlerTeam[name]
	# print wrestlerTeam
# print labelTeams() Complete

# Global Variable. Allows for Print Results
inValid = False;

# Validates Team / Check the rival at both ends of an edge to verify that it goes between a babyface and a heel
def checkValid():
	for wrestler in rivalries:
				for rival in rivalries[wrestler]:
						if(wrestlerTeam[wrestler] == wrestlerTeam[rival]):
								inValid = True
								break;
	return;

# Prints Results of the algorithm
def printResults():
	# Checks. If Valid, then prints results
	if inValid == True:
			print "Not Possible"
	else:
			print "Yes Possible"
			babyfaces = []
			heels = []
			for x in wrestlerTeam:
					if wrestlerTeam[x] == "Babyfaces":
						babyfaces.append(x)
			for y in wrestlerTeam:
					if wrestlerTeam[y] == "Heels":
						heels.append(y)
			print "Babyfaces:", babyfaces
			print "Heels:", heels

# Run all Functions
def main():
	cleanRivals()
	labelTeams()
	checkValid()
	printResults()

main()

# print "Algo Complete"
inFile.close()
