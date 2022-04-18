from bokeh.layouts import column, row
from bokeh.models import Button
from bokeh.plotting import figure, curdoc

global polynomial
polynomial = 1
polyNormalizer = [1, 1]

def updateLinearRegPlot(dataSource, xDataRange, inputWeights, bias):
    linePointsY = []
    #for plotInt in range(xDataRange[0], xDataRange[1], 0.1):
    #for plotInt in range(0.0, 11.1, 0.1):
    plotVal = xDataRange[0]
    while plotVal < xDataRange[1]:
        numWeights = len(inputWeights)
        y = bias
        for weightIndex in range(0, numWeights):
            y += inputWeights[weightIndex] / pow(10, weightIndex) * pow(plotVal, weightIndex+1)
            #y += inputWeights[weightIndex] * pow(plotVal, weightIndex+1)
        linePointsY.append(y)
        plotVal += 0.1
    dataSource.data["y"] = linePointsY
##end updatePlotYData

def updateCostHistoryPlot(trainDataSource, testDataSource, numGradIterations, 
                          numIterations, trainCostHistory, testCostHistory):
    numHist = len(numGradIterations)
    numGradIterations.append(numGradIterations[numHist-1] + numIterations)

    trainDataSource.data["x"] = numGradIterations        
    trainDataSource.data["y"] = trainCostHistory

    testDataSource.data["x"] = numGradIterations        
    testDataSource.data["y"] = testCostHistory
##end updateCostHistoryPlot

def createLinearRegressionPlot(xDataRange, yDataRange, trainningFeatures, trainningLabels, 
                               testFeatures, testLabels, numIterations, numGradIterations, 
                               trainCostHistory, testCostHistory, linearCallbackL,
                               linearCallbackM, linearCallbackS):

    for pIndex in range(2, polynomial+1):
        polyNormalizer.append(pow(10, pIndex-1))

    # create a new plot with a title and axis labels
    p = figure(title="Linear Regression", x_axis_label='x', y_axis_label='y', 
               x_range=xDataRange, y_range=yDataRange)

    linePointsX = []
    linePointsY = []
    #for plotInt in range(xDataRange[0], xDataRange[1], 0.1):
    #for plotInt in range(0.0, 11.1, 0.1):
    plotVal = xDataRange[0]
    while plotVal < xDataRange[1]:
        linePointsX.append(plotVal)
        plotVal += 0.1

    linePlot = p.line(linePointsX, linePointsY, legend="current prediction", 
                      color="red", line_width=10)
    lpDataSource = linePlot.data_source

    numFeatures = len(trainningFeatures)

    for index in range(0, numFeatures):
        p.circle([trainningFeatures[index][0]],
                trainningLabels[index], size = 10, color = "navy", legend="trainning input")

    testNumFeatures = len(testFeatures)

    for index in range(0, testNumFeatures):
        p.x([testFeatures[index][0]],
                testLabels[index], size = 10, color = "green", legend="test input")

    buttonL = Button(label="Gradient Descent for %d times" %numIterations)
    buttonL.on_click(linearCallbackL)

    buttonM = Button(label="Gradient Descent for %d times" %(numIterations/10))
    buttonM.on_click(linearCallbackM)

    buttonS = Button(label="Gradient Descent for %d times" %(numIterations/100))
    buttonS.on_click(linearCallbackS)

    #create figure for cost histroy plot
    hist = figure(plot_height=300, title="Cost History", x_axis_label="x", 
                  y_axis_label="y", y_range=[0,10])

    trainHistPlot = hist.line(numGradIterations, trainCostHistory, legend="train cost", 
                              color="blue", line_width=2)
    trainHistDataSource = trainHistPlot.data_source

    testHistPlot = hist.line(numGradIterations, testCostHistory, legend="test cost", 
                             color="green", line_width=2)
    testHistDataSource = testHistPlot.data_source

    buttons = row(buttonL, buttonM, buttonS)
    # put the button and plot in a layout and add to the document
    curdoc().add_root(column(buttons, p, hist))
    return lpDataSource, trainHistDataSource, testHistDataSource
##end createLinearRegressionPlot