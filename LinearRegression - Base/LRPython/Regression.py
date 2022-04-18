import math

from ctypes import *
lib = cdll.LoadLibrary("Regression.dll")

def linearHeuristic(features, featureIndex, inputWeights, bias):
    numInputs = len(inputWeights)

    #but what does C say?
    cFeatures = (c_float * len(features[featureIndex]))(*features[featureIndex])
    cWeights = (c_float * len(inputWeights))(*inputWeights)
    cBias = c_float(bias)
    cRet = (c_float*1)(0)
    lib.linearHeuristic(cFeatures, cWeights, c_int(numInputs), cBias, cRet)

    #return ret
    return cRet[0]
##end linearHeuristic

def linearCost(features, labels, inputWeights, bias, lambdaVal):

    numFeatures = len(features)
    numInputs = len(inputWeights)

    cFeatures_pp = (POINTER(c_float) * numFeatures)()

    for fIndex in range(numFeatures):
        cFeatures_pp[fIndex] = (c_float * numInputs)()
        for iIndex in range(numInputs):
            cFeatures_pp[fIndex][iIndex] = features[fIndex][iIndex]

    cWeights = (c_float * len(inputWeights))(*inputWeights)
    cLabels = (c_float * len(labels))(*labels)
    cBias = c_float(bias)
    cLambda = c_float(lambdaVal)
    cRet = (c_float*1)(0)
    lib.linearCost(cFeatures_pp, numFeatures, cLabels, cWeights, numInputs, cBias,
                   cLambda, cRet) 

    return cRet[0]
##end linearCost
 
def linearGradientDescent(alpha, lambdaVal, numIterations, features, labels, 
                          inputWeights, bias):
    numFeatures = len(features)
    numInputs = len(inputWeights)
    cAlpha = c_float(alpha)
    cLambda = c_float(lambdaVal)
    cWeights = (c_float * len(inputWeights))(*inputWeights)
    cLabels = (c_float * len(labels))(*labels)
    cBias = c_float(bias)
    cRet = (c_float*1)(0)
    cNumIterations = c_int(numIterations)

    cFeatures_pp = (POINTER(c_float) * numFeatures)()

    for fIndex in range(numFeatures):
        cFeatures_pp[fIndex] = (c_float * numInputs)()
        for iIndex in range(numInputs):
            cFeatures_pp[fIndex][iIndex] = features[fIndex][iIndex]

    lib.linearGradientDescent(cAlpha, cLambda, cNumIterations, cFeatures_pp, 
                              numFeatures, cLabels, cWeights, numInputs, cBias,
                              cRet)

    for iIndex in range(0, numInputs):
        inputWeights[iIndex] = cWeights[iIndex]
    bias = cRet[0]

    return bias
##end linearGradientDecsent
