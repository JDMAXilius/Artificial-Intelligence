import time
import Regression
import BokehRegressionPlotting as BRP
import pandas

def polynomialPrint():
    string = "Y = %f + %f * x" %(bias, inputWeights[0])

    for pIndex in range(1, polynomial):
        string += " + %f * x^%d" %(inputWeights[pIndex]/pow(10, pIndex), pIndex+1)
    print(string)
##end polynomialPrint

def predict(testInput):
    testFeatures = [testInput]
    return Regression.linearHeuristic(testFeatures, 0, inputWeights, bias)
## end predict

def linearCallback(iterations):
    global bias  
    global trainHistDS  
    global testHistDS  
    trainHistDS.data["x"] = []
    trainHistDS.data["y"] = []
    testHistDS.data["x"] = []
    testHistDS.data["y"] = []

    print( "Performing gradient descent for %d iterations with a "\
            "learning rate of %lg and regularization rate of %lg" %(iterations, alpha,
                                                                 lambdaVal))
    start_time = time.clock()
    bias = Regression.linearGradientDescent(alpha, lambdaVal, iterations,
                                trainningFeatures, trainningLabels, inputWeights, bias);
    elapsed = time.clock() - start_time
    print("Performing gradient descent for %d iterations took %f seconds" %(iterations, elapsed))

    curTrainCost = Regression.linearCost(trainningFeatures, trainningLabels, inputWeights, 
                                    bias, 0)
    trainCostHistory.append(curTrainCost)
    
    curTestCost = Regression.linearCost(testFeatures, testLabels, inputWeights, 
                                    bias, 0)
    testCostHistory.append(curTestCost)

    polynomialPrint()
    print("Current trainning cost = %f\n" %curTrainCost)
    print("Current test cost = %f\n" %curTestCost)
    
    BRP.updateLinearRegPlot(ds, xDataRange, inputWeights, bias)
    BRP.updateCostHistoryPlot(trainHistDS, testHistDS, numGradIterations, 
                              iterations, trainCostHistory, testCostHistory)
##endlinearCallback

def linearCallbackLarge():
    linearCallback(numIterations)
##end linearCallbackLarge

def linearCallbackMedium():
    linearCallback(int(numIterations/10))
##end linearCallbackLarge

def linearCallbackSmall():
    linearCallback(int(numIterations/100))
##end linearCallbackLarge

def currentTrainningCostRegularized():
    return Regression.linearCost(trainningFeatures, trainningLabels, inputWeights, 
                                    bias, lambdaVal)
## end currentTrainningCost

def currentTrainningCost():
    return Regression.linearCost(trainningFeatures, trainningLabels, inputWeights, 
                                    bias, 0)
## end currentTrainningCost

def currentTestCost():
    return Regression.linearCost(testFeatures, testLabels, inputWeights, 
                                    bias, 0)
## end currentTrainningCost

def runGradient():
    global bias
    start_time = time.clock()
    bias = Regression.linearGradientDescent(alpha, lambdaVal, numIterations,
                                trainningFeatures, trainningLabels, inputWeights, bias);
    elapsed = time.clock() - start_time
    return elapsed
# end runGradient

def initialize():

    global trainningFeatures
    global trainningLabels

    global testFeatures
    global testLabels

    global polynomial

    global trainDataToLoad
    global testDataToLoad

    # trainning load data
    rawData = pandas.read_csv(trainDataToLoad)
    rawFeatures = rawData["X"].tolist()
    numRawFeatures = len(rawFeatures)
    trainningFeatures = []
    testFeatures = []

    for fIndex in range(0, numRawFeatures):
        trainningFeatures.append([rawFeatures[fIndex]])

    trainningLabels = rawData["Y"].tolist()

    # testing load data
    rawData = pandas.read_csv(testDataToLoad)
    rawFeatures = rawData["X"].tolist()
    numRawFeatures = len(rawFeatures)
    
    for fIndex in range(0, numRawFeatures):
        testFeatures.append([rawFeatures[fIndex]])

    testLabels = rawData["Y"].tolist()

    numTrainFeatures = len(trainningFeatures)
    numTestFeatures = len(testFeatures)

    BRP.polynomial = polynomial
    polyNormalizer = [1, 1]
    for pIndex in range(2, polynomial+1):
        polyNormalizer.append(pow(10, pIndex-1))
    # create polynomial features
    for fIndex in range(0, numTrainFeatures):
        for pIndex in range(2, polynomial+1):
            trainningFeatures[fIndex].append(pow(trainningFeatures[fIndex][0], pIndex)/polyNormalizer[pIndex])

    for fIndex in range(0, numTestFeatures):
        for pIndex in range(2, polynomial+1):
            testFeatures[fIndex].append(pow(testFeatures[fIndex][0], pIndex)/polyNormalizer[pIndex])
## end initialize

def run():
    #range of data to be plotted
    global xDataRange
    #data_source of line plot
    global ds
    global trainHistDS
    global testHistDS

    # gradient descent iterations per run
    global numIterations
    # learning rate
    global alpha 
    global lambdaVal 

    global trainningFeatures
    global trainningLabels

    global testFeatures
    global testLabels

    global trainCostHistory
    global testCostHistory
    global numGradIterations
    global inputWeights
    global bias

    global polynomial

    global trainDataToLoad
    global testDataToLoad

    curCost = Regression.linearCost(trainningFeatures, trainningLabels, inputWeights, 
                                    bias, lambdaVal)

    trainCostHistory = [curCost]
    print("Current trainning cost = %f" %curCost)

    curCost = Regression.linearCost(testFeatures, testLabels, inputWeights, 
                                    bias, 0)

    testCostHistory = [curCost]
    print("Current testing cost = %f" %curCost)

    numGradIterations = [0]

    ds, trainHistDS, testHistDS = BRP.createLinearRegressionPlot(xDataRange, yDataRange, 
                                                trainningFeatures, trainningLabels, 
                                                testFeatures, testLabels, 
                                                numIterations, numGradIterations, 
                                                trainCostHistory, testCostHistory,
                                                linearCallbackLarge, 
                                                linearCallbackMedium, 
                                                linearCallbackSmall)

    BRP.updateLinearRegPlot(ds, xDataRange, inputWeights, bias)

    
##end run()
