import sys
#bfs of wrestlers and the rivalries keeping track of distance from
#initial node
def bfs(wrestlers, start, lengthFromStart):
    explored = []
    queue = [start]
    counter = 1
    lengthFromStart[start] = 1
    while queue:
        node = queue.pop(0)
        counter = counter + 1
        if node not in explored:
            explored.append(node)
            rivalries = wrestlers[node]

            for rival in rivalries:
                if lengthFromStart[rival] == 0 and rival != start:
                    lengthFromStart[rival] = counter
                queue.append(rival)
    return explored

#reads files into corresponding variables for use in calculations
with open("wrestler.txt", "r+") as myfile:
    counter = 0
    numWrestlers = 0
    numRivalries = -1
    counter2 = 0
    wrestlerList = []
    rivalry = []
    indexWrest1 = 0
    indexWrest2 = 0
    rivalryList = {}
    lengthList = {}
    wrestlerType = {}

    #reads in wrestlers and rivalries
    for line in myfile:
        if counter == numWrestlers + 1:
            nR = line.split()
            for n in nR:
                numRivalries = int(n)
            counter = counter + 1
        elif counter2 <= numRivalries:
            riv = line.split()
            rivCount = 0
            for e in riv:
                if rivCount == 0:
                    rivCount = rivCount + 1
                    for i in range(0, len(wrestlerList)):
                        if (e == wrestlerList[i]):
                            indexWrest1 = i
                else:
                    for i in range(0, len(wrestlerList)):
                        if (e == wrestlerList[i]):
                            indexWrest2 = i
            rivalryList[wrestlerList[indexWrest2]].append(
                wrestlerList[indexWrest1])
            rivalryList[wrestlerList[indexWrest1]].append(
                wrestlerList[indexWrest2])
            counter2 = counter2 + 1
        if counter == 0:
            nW = line.split()
            for n in nW:
                numWrestlers = int(n)
            counter = counter + 1
        elif counter <= numWrestlers:
            rivalryList[str(line.strip())] = []
            lengthList[str(line.strip())] = 0
            wrestlerList.append(str(line.strip()))
            counter = counter + 1
    print "Wrestle", wrestlerList
    print "Rival", rivalryList
    # print "Length", lengthList

    #creates second list to use for my while loop
    testRivList = {}
    for wrestler in rivalryList:
        testRivList[wrestler] = rivalryList[wrestler]
    foundWrestlers = 0
    print "Test List1", testRivList
    while(foundWrestlers != numWrestlers):
        counter = 0
        for x in testRivList:
            if counter == 0:
                start = x
                #print start
                counter = counter + 1
        found = bfs(testRivList, start, lengthList)
        foundWrestlers = foundWrestlers + len(found)
        #print lengthList
        if(foundWrestlers != numWrestlers):
            for f in found:
                del testRivList[f]
    print "Test List2", testRivList
    print "Rival List", rivalryList
    #sets teams
    for e in lengthList:
        if(lengthList[e] % 2 == 0):
            wrestlerType[e] = "Babyfaces"
        else:
            wrestlerType[e] = "Heels"

    #checks if current team set is a valid one for the problem
    notPossible = False
    for wrestler in rivalryList:
        for rival in rivalryList[wrestler]:
            if(wrestlerType[wrestler] == wrestlerType[rival]):
                notPossible = True

    if notPossible == False:
        print "Babyfaces: ",
        for x in wrestlerType:
            if wrestlerType[x] == "Babyfaces":
                print x, " ",
        print
        print "Heels: ",
        for y in wrestlerType:
            if wrestlerType[y] == "Heels":
                print y, " ",
    else:
        print "Not Possible"
        #print wrestlerType
