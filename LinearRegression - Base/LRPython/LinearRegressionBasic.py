import LinearRegression as LR
import random

def main():
    LR.alpha = 0.01
    LR.lambdaVal = 0
    LR.numIterations = 1000000
    LR.xDataRange = [0.0, 11.0]
    LR.yDataRange = [0.0, 11.0]
    LR.polynomial = 1
    LR.trainDataToLoad = "LinearTrainData1.csv"
    LR.testDataToLoad = "LinearTestData1.csv"
    LR.inputWeights = []
    for pIndex in range(0, LR.polynomial):
        LR.inputWeights.append(random.uniform(-5, 5.0))
    LR.bias = random.uniform(-5, 5.0)

    LR.initialize()
    LR.run()

##end main()

main()

if __name__ == "__main__":
    LR.linearCallbackSmall()