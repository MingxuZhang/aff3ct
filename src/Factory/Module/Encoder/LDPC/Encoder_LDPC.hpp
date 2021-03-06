#ifndef FACTORY_ENCODER_LDPC_HPP
#define FACTORY_ENCODER_LDPC_HPP

#include <string>
#include "Tools/Algo/Sparse_matrix/Sparse_matrix.hpp"
#include "Tools/Code/LDPC/Standard/DVBS2/DVBS2_constants.hpp"

#include "Module/Encoder/LDPC/Encoder_LDPC.hpp"

#include "../Encoder.hpp"

namespace aff3ct
{
namespace factory
{
extern const std::string Encoder_LDPC_name;
extern const std::string Encoder_LDPC_prefix;
struct Encoder_LDPC : public Encoder
{
	class parameters : public Encoder::parameters
	{
	public:
		// ------------------------------------------------------------------------------------------------- PARAMETERS
		// optional
		std::string H_path = "";
		std::string G_path = "";

		// optional parameters
		std::string H_reorder = "NONE";

		// ---------------------------------------------------------------------------------------------------- METHODS
		explicit parameters(const std::string &p = Encoder_LDPC_prefix);
		virtual ~parameters();
		Encoder_LDPC::parameters* clone() const;

		// parameters construction
		void get_description(arg_map &req_args, arg_map &opt_args                              ) const;
		void store          (const arg_val_map &vals                                           );
		void get_headers    (std::map<std::string,header_list>& headers, const bool full = true) const;

		// builder
		template <typename B = int>
		module::Encoder_LDPC<B>* build(const tools::Sparse_matrix &G, const tools::Sparse_matrix &H,
		                               const tools::dvbs2_values* dvbs2 = nullptr) const;
	};

	template <typename B = int>
	static module::Encoder_LDPC<B>* build(const parameters &params, const tools::Sparse_matrix &G,
	                                                                const tools::Sparse_matrix &H,
	                                                                const tools::dvbs2_values* dvbs2 = nullptr);
};
}
}

#endif /* FACTORY_ENCODER_LDPC_HPP */
