#ifndef DECODER_LDPC_BP_FLOODING_GALLAGER_A_HPP_
#define DECODER_LDPC_BP_FLOODING_GALLAGER_A_HPP_

#include "Tools/Code/LDPC/AList_reader/AList_reader.hpp"

#include "../../../Decoder_SISO.hpp"

template <typename B, typename R>
class Decoder_LDPC_BP_flooding_Gallager_A : public Decoder_SISO<B,R>
{
protected:
	const int  n_ite;      // number of iterations to perform
	const int  n_V_nodes;  // number of variable nodes (= N)
	const int  n_C_nodes;  // number of check    nodes
	const int  n_branches; // number of branched in the bi-partite graph (connexions between the V and C nodes)

	const bool enable_syndrome;

	const mipp::vector<unsigned char> n_variables_per_parity;
	const mipp::vector<unsigned char> n_parities_per_variable;
	const mipp::vector<unsigned int > transpose;
	
	mipp::vector<unsigned char> Y_N; // input LLRs

	// data structures for iterative decoding
	mipp::vector<unsigned char> C_to_V; // check    nodes to variable nodes messages
	mipp::vector<unsigned char> V_to_C; // variable nodes to check    nodes messages

public:
	Decoder_LDPC_BP_flooding_Gallager_A(const int &K, const int &N, const int& n_ite,
	                                    const AList_reader &alist_data,
	                                    const bool enable_syndrome = true,
	                                    const int n_frames = 1,
	                                    const std::string name = "Decoder_LDPC_BP_flooding_Gallager_A");
	virtual ~Decoder_LDPC_BP_flooding_Gallager_A();

protected:
	// hard decoder (load -> decode -> store)
	void load       (const mipp::vector<R>& Y_N);
	void hard_decode(                          );
	void store      (      mipp::vector<B>& V_K) const;

	void _soft_decode(const mipp::vector<R> &Y_N1, mipp::vector<R> &Y_N2);

public:
	void soft_decode(const mipp::vector<R> &sys, const mipp::vector<R> &par, mipp::vector<R> &ext);

};

#endif /* DECODER_LDPC_BP_FLOODING_GALLAGER_A_HPP_ */