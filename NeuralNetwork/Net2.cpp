#include "Net2.h"

Net2::Net2(const vector<pair<int, int>>& topology, int size_input, int minibatch):
	ratio_mini_batch(minibatch)
{

	size_t number_of_sample = size_input /= minibatch;
	if (!number_of_sample)
		throw("number of sample must superior to zero");
	
	//  Redimension the network
	for (size_t i(0); i < topology.size(); ++i) {
		size_t nextLayerSizeRows = (i == topology.size() - 1 ? 0 : topology[i + 1].first );
		layers.push_back(Couche(topology[i].first, number_of_sample, nextLayerSizeRows));
	}
}


void Net2::fit(const mat& X,const mat& y) {
	// if(random_shuffle)
	// Not possible in C++ :'(
	int first_indice = 0;
	int ratio = number_of_samples / ratio_mini_batch;
	int last_indice = std::min(number_of_samples,ratio);
	
	while (last_indice != number_of_samples) {
		mat X1 = X.cols(first_indice, last_indice);
		mat y1 = y.cols(first_indice, last_indice);

		feedforward(X1, y1);

		last_indice = std::max(number_of_samples, last_indice + ratio);
		first_indice += ratio;
	}
}