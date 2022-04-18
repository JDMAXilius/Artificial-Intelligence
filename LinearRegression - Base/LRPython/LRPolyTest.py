import time
import LinearRegression as LR
import Regression

def main():
    LR.alpha = 0.0001
    LR.lambdaVal = 0.0
    LR.numIterations = 1000000
    LR.xDataRange = [0.0, 11.0]
    LR.yDataRange = [0.0, 11.0]
    LR.polynomial = 3
    LR.trainDataToLoad = "LinearTrainData2.csv"
    LR.testDataToLoad = "LinearTestData2.csv"
    LR.inputWeights = []
    for pIndex in range(0, LR.polynomial):
        LR.inputWeights.append(3.0)
    LR.bias = 1.0

    LR.initialize()

    testInput = [5, 25, 125]

    #test initial heuristic prediction result
    print("Current prediction for input:")
    print(testInput)
    print("Y = %f" %LR.predict(testInput))
    print("Expected value of 466.0\n")

    #test initial trainning cost calculation
    print("Initial trainning cost = %f" %LR.currentTrainningCost())
    print("Expected value of 631.631836\n")

    #test initial test cost calculation
    print("Initial test cost = %f" %LR.currentTestCost())
    print("Expected value of 647.173584\n")

    #test gradient descent
    print("Running gradient descent %d times" %LR.numIterations)
    elapsedTime = LR.runGradient()
    print("... took %f seconds\n." %elapsedTime)

    #test resulting heuristic prediction result
    print("Current prediction for input:")
    print(testInput)
    print("Y = %f" %LR.predict(testInput))
    print("Expected value of -100.401848\n")

    #test resulting trainning cost calculation
    print("Current trainning cost = %f" %LR.currentTrainningCost())
    print("Expected value of 2.208094\n")

    #test resulting test cost calculation
    print("Current test cost = %f" %LR.currentTestCost())
    print("Expected value of 5.201693\n")

## end main

if __name__ == "__main__":
    main()