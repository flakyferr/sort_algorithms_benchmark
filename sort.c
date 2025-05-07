#include <iostream>
#include <benchmark/benchmark.h>
#include <random>
#define N 500000



static void init_rand_array(std::vector<int> &array){
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1,N);
	for(int i=0 ; i<array.size(); i++)
		array[i]=dist6(rng);
}

static bool is_sorted(const std::vector<int>& arr) {

    if (arr.size() <= 1) {
	    return true;
    }
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            	std::cout<<"Nawwww, not in order with size " << arr.size() << std::endl;
		for (int element: arr){
			std::cout << element << " ";
		}
		std::cout << std::endl;
		return false;
        }
    }

    return true;
}

static void DoSetup(const benchmark::State& state){

}
static void DoTeardown(const benchmark::State& state){
	
}
static void BM_insertion_sort(benchmark::State& state){
	int key,i;
	std::vector<int> array(state.range(0));
	for (auto _ : state){
		state.PauseTiming();
		init_rand_array(array);
		state.ResumeTiming();
		for (int j=1; j<state.range(0) ; j++)
		{
			key=array[j];
			i = j-1;
			while (i>-1 && array[i]>key)
			{
				array[i+1] = array[i];
				i = i-1;
			}
			array[i+1]=key;
	
		}

	}
	state.SetComplexityN(state.range(0));
	assert(is_sorted(array));

	  
}

BENCHMARK(BM_insertion_sort)->DenseRange(1, 3000, 50) ->Complexity();

std::vector<int> merge(std::vector<int> &A1, std::vector<int> &A2)
{	
	std::vector<int> merged_A;

	std::merge(A1.begin(), A1.end(), A2.begin(), A2.end(), std::back_inserter(merged_A));
	return merged_A;
}

void merge_sort(std::vector<int> &A){
	if (A.size()==1) return;
 	std::vector<int> A1;
 	std::vector<int> A2;
 	for(int i=0; i<A.size()/2; i++)
 		A1.push_back(A[i]);
 	for(int i=A.size()/2; i<A.size(); i++)
 		A2.push_back(A[i]);
 	merge_sort(A1);
 	merge_sort(A2);
 	A = merge(A1,A2);
}

static void BM_merge_sort(benchmark::State& state){
	std::vector<int> array(state.range(0));
	for(auto _ : state){
		state.PauseTiming();
		init_rand_array(array);
		state.ResumeTiming();
	
		merge_sort(array);

	}

	state.SetComplexityN(state.range(0));
	assert(is_sorted(array));
}

BENCHMARK(BM_merge_sort)->DenseRange(1, 3000, 50) ->Complexity();

BENCHMARK_MAIN();

