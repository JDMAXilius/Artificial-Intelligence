#include "..\RegressionSolutions\RegressionSolutions.h"

extern "C"
{
	/// <summary>
	/// Estimates the relationship between a scalar output value (y), "result",
	/// and one or more input variables (X), "features".
	/// </summary>
	/// <param name="features">An array of the input variable(s) to be mapped to the output.</param>
	/// <param name="inputWeights">An array of weights to be applied to each feature.</param>
	/// <param name="numImputs">The size of the "features" & "inputWeight" arrays </param>
	/// <param name="bias">The bias value to be added to our heuristic</param>
	/// <param name="result">Output variable to hold the heuristic result, because python made all my C 
	///							function returns into integers</param>
	__declspec(dllexport) void linearHeuristic(float *features,
		float *inputWeights, int numImputs, float bias, float *result)
	{
		// TODO: Replace with your own solution
		linearHeuristicSolution(features, inputWeights, numImputs, bias, result);
	}

	/// <summary>
	/// Calculates the cost of our current heuristic compared to our trainning labels. Cost can be 
	/// thought of as a rating of error, the higher the cost the further the heuristic is away from 
	/// estimating correct results.
	/// </summary>
	/// <param name="features">An array of features used to compare heuristic estimates to known labels,
	///							where each feature is an array of input variable(s) to be compared.</param>
	/// <param name="numFeatures">The number of features contained in parameter "features".</param>
	/// <param name="labels">An array of the known values for each feature. This array is the same size as parameter "features"</param>
	/// <param name="inputWeights">An array of weights to be applied to each feature.</param>
	/// <param name="numImputs">The size of "inputWeight" array and each feature array in "features". 
	///							Note: numInputs == length(features[0]) && numInputs != length(features)</param>
	/// <param name="bias">The bias value to be added to our heuristic</param>
	/// <param name="lambda">The weight penalty value for regularization. Ignore this if not or until you
	///							are implementing support for regularization.</param>
	/// <param name="result">Output variable to hold the cost result, because python made all my C 
	///						function returns into integers</param>
	__declspec(dllexport) void linearCost(float **features,
		int numFeatures, float *labels, float *inputWeights, 
		int numInputs, float bias, float lambda, float *result)
	{
		// TODO: Replace with your own solution
		// NOTE: This solution method does not call your linearHeuristic
		linearCostSolution(features, numFeatures, labels, inputWeights, numInputs, 
			bias, lambda, result);
	}

	/// <summary>
	/// Attempts to adjust input weights (theta) so as to minimize the value returned by the cost function 
	/// linearCost, which internally calls linearHeuristic which uses inputWeights. This minimization is 
	/// done by iteratively adjusting the input weights and bias values based on the derivative of our cost
	/// function. If our cost function is thought to define a particular amount of error for our current
	/// heuristic, then the derivative of the cost function will define the current velocity of our cost 
	/// which can be used to tell which direction to adjust to reduce cost.
	/// </summary>
	/// <param name="alpha">The learning rate. If this is set too high cost may increase quickly resulting 
	///						in numerical run-time errors.</param>
	/// <param name="lambda">The weight penalty value for regularization. Ignore this if not or until you
	///							are implementing support for regularization.</param>
	/// <param name="numIterations">The number of iterations fo gradient descent to be performed.</param>
	/// <param name="features">An array of features used to compare heuristic estimates to known labels,
	///							where each feature is an array of input variable(s) to be compared.</param>
	/// <param name="numFeatures">The number of features contained in parameter "features".</param>
	/// <param name="labels">An array of the known values for each feature. This array is the same size as parameter "features"</param>
	/// <param name="inputWeights">An array of weights to be applied to each feature.</param>
	/// <param name="numImputs">The size of "inputWeight" array and each feature array in "features". 
	///							Note: numInputs == length(features[0]) && numInputs != length(features)</param>
	/// <param name="bias">The bias value to be added to our heuristic</param>
	/// <param name="result">Output variable to hold the bias result, because python made all my C 
	///						function returns into integers</param>
	__declspec(dllexport) void linearGradientDescent(float alpha,
		float lambda, int numIterations, float **features, int numFeatures, 
		float *labels,float *inputWeights, int numInputs, float bias, 
		float *result)
	{
		// TODO: Replace with your own solution
		// NOTE: This solution method does not call your linearHeuristic
		linearGradientDescentSolution(alpha, lambda, numIterations, features, numFeatures,
			labels, inputWeights, numInputs, bias, result);
	}
}


