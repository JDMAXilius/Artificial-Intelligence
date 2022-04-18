#pragma once


extern "C"
{
	__declspec(dllexport) void linearHeuristicSolution(float *features,
		float *inputWeights, int numImputs, float bias, float *result);

	__declspec(dllexport) void linearCostSolution(float **features, int numFeatures, float *labels,
		float *inputWeights, int numInputs, float bias, float lambda, float *result);

	__declspec(dllexport) void linearGradientDescentSolution(float alpha, float lambda,
		int numIterations, float **features, int numFeatures, float *labels,
		float *inputWeights, int numInputs, float bias, float *result);

}