#ifndef DECODER_LDPC_BP_LAYERED_ONMS_INTER_HPP_
#define DECODER_LDPC_BP_LAYERED_ONMS_INTER_HPP_

#include <mipp.h>

#include "Tools/Algo/Sparse_matrix/Sparse_matrix.hpp"

#include "../../Decoder_LDPC_BP.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float>
class Decoder_LDPC_BP_layered_ONMS_inter : public Decoder_LDPC_BP<B,R>
{
private:
	const float normalize_factor;
	const R offset;
	mipp::vector<mipp::Reg<R>> contributions;

protected:
	const R saturation;
	const int n_C_nodes; // number of check nodes (= N - K)

	// reset so C_to_V and V_to_C structures can be cleared only at the beginning of the loop in iterative decoding
	bool init_flag;

	const std::vector<unsigned> &info_bits_pos;

	// data structures for iterative decoding
	std::vector<mipp::vector<mipp::Reg<R>>> var_nodes;
	std::vector<mipp::vector<mipp::Reg<R>>> branches;

	mipp::vector<mipp::Reg<R>> Y_N_reorderered;
	mipp::vector<mipp::Reg<B>> V_reorderered;

public:
	Decoder_LDPC_BP_layered_ONMS_inter(const int K, const int N, const int n_ite,
	                                   const tools::Sparse_matrix &H,
	                                   const std::vector<unsigned> &info_bits_pos,
	                                   const float normalize_factor = 1.f,
	                                   const R offset = (R)0,
	                                   const bool enable_syndrome = true,
	                                   const int syndrome_depth = 1,
	                                   const int n_frames = 1);
	virtual ~Decoder_LDPC_BP_layered_ONMS_inter();

	void reset();

protected:
	void _load          (const R *Y_N,           const int frame_id);
	void _decode_siso   (const R *Y_N1, R *Y_N2, const int frame_id);
	void _decode_siho   (const R *Y_N,  B *V_K,  const int frame_id);
	void _decode_siho_cw(const R *Y_N,  B *V_N,  const int frame_id);

	// BP functions for decoding
	template <int F = 1>
	void BP_decode(const int frame_id);

	bool check_syndrome(const int frame_id);

	template <int F = 1>
	void BP_process(mipp::vector<mipp::Reg<R>> &var_nodes, mipp::vector<mipp::Reg<R>> &branches);
};
}
}

#endif /* DECODER_LDPC_BP_LAYERED_ONMS_INTER_HPP_ */
