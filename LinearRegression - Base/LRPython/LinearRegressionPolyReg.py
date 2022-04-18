import LinearRegression as LR
import random

def main():
    LR.alpha = 0.01
    LR.lambdaVal = 1.0
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
    LR.run()
##end main()

main()

if __name__ == "__main__":
    LR.linearCallbackSmall()
