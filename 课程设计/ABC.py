import copy
import math
import random

import matplotlib.pyplot as plt


class Func:
    def __init__(self):
        self.Pro1 = None

    def GriewankFunction(self, x):
        itemOne = 0
        itmeTwo = 0
        for i, value in enumerate(x):
            itemOne += (value ** 2) / 4000
            itmeTwo *= (math.cos(value / math.sqrt(i + 1)))
        return 1 + itemOne - itmeTwo

    def GeneralizeRastrigin(self, x):
        s = 0
        for value in x:
            s += (value ** 2 - 10 * math.cos(2 * math.pi * value) + 10)
        return -s

    def AckleyFunction(self, x):
        s1 = 0
        s2 = 0
        for value in x:
            s1 += value ** 2
            s2 += math.cos(2 * math.pi * value)
        s1 = s1 / len(x)
        s2 = s2 / len(x)
        return -20 * math.exp(-0.2 * math.sqrt(s1)) - math.exp(s2) + 20 + math.e


class choose_max_min:
    def fitneForMin(self, value, average):
        if value >= 0:
            return 1 / (1 + value)
        else:
            return 1 + math.fabs(value)

    def fitneForMax(self, value, average):
        return math.exp(value / average)


class Nectar:
    def __init__(self, pos):
        self.LIMIT = 8
        self.pos = pos
        self.beAbandoned = 0
        self.beChoosed = 1
        self.followers = []
        self.func = Func().GriewankFunction
        self.fitFunc = choose_max_min().fitneForMin

    def getValue(self):
        return self.func(self.pos)

    def getBeAbandoned(self):
        return self.beAbandoned

    def addAbandoned(self):
        self.beAbandoned += 1

    def addBechoosed(self):
        self.beChoosed += 1

    def getPos(self):
        return self.pos

    def setPos(self, pos):
        self.pos = pos

    def getFollowers(self):
        return self.followers

    def setFollowers(self, newFoll):
        self.followers = newFoll

    def addFolloers(self, f):
        self.followers.append(f)

    def getLimit(self):
        return self.LIMIT


class Bee:
    def __init__(self, id, type):
        self.id = id
        self.type = type

    def setType(self):
        self.type = type

    def getType(self):
        return self.type

    def getId(self):
        return self.id


class ABC:
    def __init__(self, pro, B, E, L, S, I, bound):
        self.pro = pro
        self.B = B
        self.E = E
        self.L = L
        self.S = S
        self.I = I
        self.st = []
        self.bound = bound
        self.onLookList = []
        self.scoutsList = []
        self.bestValue = None
        self.bestPos = None
        self.fitnessFun = choose_max_min().fitneForMin
        self.resultRecord = []
        self.resultForPicture = []

    def initial(self):
        for i in range(self.B):
            if i < self.E:
                randomPos = [self.getFeasibleSol(self.bound), self.getFeasibleSol(self.bound)]
                thisNectar = Nectar(randomPos)
                thisNectar.addFolloers(i)
                self.st.append(thisNectar)
            else:
                self.onLookList.append(i)
        for i in range(self.S):
            self.scoutsList.append(i)
        bestIndex, self.bestValue = list(min(enumerate([item.getValue() for item in self.st])))
        self.bestPos = self.st[bestIndex].getPos()

    def getRandomPos(self, pos1, pos2):
        randomStep = random.random()
        return [pos1[0] + randomStep * (pos2[0] - pos1[0]), pos1[1] + randomStep * (pos2[1] - pos1[1])]

    def roulette(self, pList):
        arrow = random.random()
        s = 0
        for index, value in enumerate(pList):
            s += value
            if s >= arrow:
                return index

    def employedPro(self):
        newStList = []
        for nc in self.st:
            if len(nc.getFollowers()) == 0:
                pass
            else:
                flyAway = []
                notFly = []
                for bee in nc.getFollowers():
                    if random.random() < 0.3:
                        self.onLookList.append(bee)
                        continue
                    if random.random() < 0.6 and random.random() > 0.3:
                        self.scoutsList.append(bee)
                        continue
                    else:
                        ranNc = random.choice(self.st)
                        newPos = self.getRandomPos(nc.getPos(), ranNc.getPos())
                        newNc = Nectar(newPos)
                        if newNc.getValue() < nc.getValue():
                            newNc.addFolloers(bee)
                            newStList.append(newNc)
                            flyAway.append(bee)
                            nc.addAbandoned()
                            if newNc.getValue() < self.bestValue:
                                self.bestValue = newNc.getValue()
                                self.bestPos = newNc.getPos()
                        else:
                            nc.addBechoosed()
                            notFly.append(bee)
                if len(flyAway) == len(nc.getFollowers()):
                    pass
                elif (nc.getBeAbandoned() >= nc.getLimit()):
                    for bee in nc.getFollowers():
                        if random.random() < 0.5:
                            self.onLookList.append(bee)
                        else:
                            self.scoutsList.append(bee)
                else:
                    nc.setFollowers(notFly)
                    newStList.append(nc)
        self.st = copy.deepcopy(newStList)

    def onLookerPro(self):
        valueList = []
        for nc in self.st:
            valueList.append(nc.getValue())
        aveValue = sum(valueList) / len(valueList)
        fitnessList = [self.fitnessFun(item, aveValue) for item in valueList]
        sumFit = sum(fitnessList)
        pList = [item / sumFit for item in fitnessList]
        notBeEmployed = []
        for bee in self.onLookList:
            if random.random() < 0.3:
                notBeEmployed.append(bee)
            else:
                follow = self.roulette(pList)
                self.st[follow].addFolloers(bee)
        self.onLookList = copy.deepcopy(notBeEmployed)

    def scoutsPro(self):
        newScoutList = []
        for bee in self.scoutsList:
            newSt = Nectar([self.getFeasibleSol(self.bound), self.getFeasibleSol(self.bound)])
            for i in range(30):
                temPos = [self.getFeasibleSol(self.bound), self.getFeasibleSol(self.bound)]
                temSt = Nectar(temPos)
                if temSt.getValue() > newSt.getValue():
                    newSt = temSt
            if newSt.getValue() < self.bestValue:
                self.st.append(newSt)
                self.bestValue = newSt.getValue()
                self.bestPos = newSt.getPos()
            else:  # r
                if random.random() < 0.3:
                    self.onLookList.append(bee)
                else:
                    newScoutList.append(bee)
        self.scoutsList = copy.deepcopy(newScoutList)

    def run(self):
        self.initial()
        for i in range(self.I):
            self.employedPro()
            self.onLookerPro()
            self.scoutsPro()
            self.resultRecord.append(self.bestValue)
            if i in self.pictureIndex:
                self.resultForPicture.append(self.st)

    def showResult(self):
        fig = plt.figure()
        plt.plot(range(len(self.resultRecord)), self.resultRecord)
        fig1 = plt.figure()
        for i in range(len(self.pictureIndex)):
            ax = fig1.add_subplot(3, 4, i + 1)
            x, y = [], []
            for st in self.resultForPicture[i]:
                x.append(st.getPos()[0])
                y.append(st.getPos()[1])
        plt.tight_layout()
        plt.show()


if __name__ == '__main__':
    I = 200
    B = 120
    onLookers = int(0.5 * B)
    employedBee = int(0.5 * B)
    scouts = 80
    myPros = Func()
    grienWankFunc = myPros.GriewankFunction
    bounds = [-10, 10]
    myBCA = ABC(grienWankFunc, B, onLookers, employedBee, scouts, I, bounds)
    myBCA.run()
    print(myBCA.bestValue)
    print(myBCA.bestPos)
    myBCA.showResult()

