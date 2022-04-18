import time
import LinearRegression as LR
import Regression

def main():
    LR.alpha = 0.01
    LR.lambdaVal = 100.0
    LR.numIterations = 10000000
    LR.xDataRange = [0.0, 11.0]
    LR.yDataRange = [0.0, 11.0]
    LR.polynomial = 5
    LR.trainDataToLoad = "LRTrainDataReg.csv"
    LR.testDataToLoad = "LRTestDataReg.csv"
    LR.inputWeights = []

    for pIndex in range(0, LR.polynomial):
        LR.inputWeights.append(0)
    LR.bias = 0

    LR.initialize()

    testInput = [5, 25, 125, 625, 3125]

    #test initial heuristic prediction result
    print("Current prediction for input:")
    print(testInput)
    print("Y = %f" %LR.predict(testInput))
    print("Expected value of 0.0\n")

    #test initial trainning cost calculation
    print("Initial trainning cost = %f" %LR.currentTrainningCost())
    print("Expected value of 9.526786\n")

    #test initial test cost calculation
    print("Initial test cost = %f" %LR.currentTestCost())
    print("Expected value of 6.750000\n")

    #test gradient descent
    print("Running gradient descent %d times" %LR.numIterations)
    elapsedTime = LR.runGradient()
    print("... took %f seconds\n." %elapsedTime)

    #test resulting heuristic prediction result
    print("Current prediction for input:")
    print(testInput)
    print("Y = %f" %LR.predict(testInput))
    print("Expected value of 45.493839\n")

    #test resulting trainning cost calculation
    print("Current trainning cost = %f" %LR.currentTrainningCost())
    print("Expected value of 0.284119\n")

    #test resulting test cost calculation
    print("Current test cost = %f" %LR.currentTestCost())
    print("Expected value of 0.915728\n")

## end main

if __name__ == "__main__":
    main()