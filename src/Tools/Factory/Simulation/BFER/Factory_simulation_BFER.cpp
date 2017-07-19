#include "Factory_simulation_BFER.hpp"

using namespace aff3ct;
using namespace tools;

void Factory_simulation_BFER::build_args(Arguments_reader::arg_map &req_args, Arguments_reader::arg_map &opt_args)
{
	Factory_simulation::build_args(req_args, opt_args);

	opt_args[{"sim-benchs", "b"}] =
		{"positive_int",
		 "enable special benchmark mode with a loop around the decoder."};

	opt_args[{"sim-debug", "d"}] =
		{"",
		 "enable debug mode: print array values after each step."};

	opt_args[{"sim-debug-prec"}] =
		{"positive_int",
		 "set the precision of real elements when displayed in debug mode."};

	opt_args[{"sim-debug-limit"}] =
		{"positive_int",
		 "set the max number of elements to display in the debug mode."};

	opt_args[{"sim-time-report"}] =
		{"",
		 "display time information about the simulation chain."};

	opt_args[{"sim-snr-type", "E"}] =
		{"string",
		 "select the type of SNR: symbol energy or information bit energy.",
		 "ES, EB"};

	opt_args[{"sim-coset", "c"}] =
		{"",
		 "enable the coset approach."};
}

void Factory_simulation_BFER::store_args(const Arguments_reader& ar, parameters &params)
{
#if !defined(STARPU) && !defined(SYSTEMC)
	params.n_threads = std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 1;
#endif

	Factory_simulation::store_args(ar, params);

	if(ar.exist_arg({"sim-benchs",     "b"})) params.benchs      = ar.get_arg_int({"sim-benchs",   "b"});
	if(ar.exist_arg({"sim-snr-type",   "E"})) params.snr_type    = ar.get_arg    ({"sim-snr-type", "E"});
	if(ar.exist_arg({"sim-time-report"    })) params.time_report = true;
	if(ar.exist_arg({"sim-debug",      "d"})) params.debug       = true;
	if(ar.exist_arg({"sim-coset",      "c"})) params.coset       = true;
	if(ar.exist_arg({"sim-debug-limit"}))
	{
		params.debug = true;
		params.debug_limit = ar.get_arg_int({"sim-debug-limit"});
	}
	if(ar.exist_arg({"sim-debug-prec"}))
	{
		params.debug = true;
		params.debug_precision = ar.get_arg_int({"sim-debug-prec"});
	}

	if (params.debug && !(ar.exist_arg({"sim-threads", "t"}) && ar.get_arg_int({"sim-threads", "t"}) > 0))
		// check if debug is asked and if n_thread kept its default value
		params.n_threads = 1;

}

void Factory_simulation_BFER::group_args(Arguments_reader::arg_grp& ar)
{
	Factory_simulation::group_args(ar);
}

void Factory_simulation_BFER::header(params_list& head_sim, const parameters& params)
{
	Factory_simulation::header(head_sim, params);

	if (params.benchs)
		head_sim.push_back(std::make_pair("Number of benchs", std::to_string(params.benchs)));
	head_sim.push_back(std::make_pair("SNR type", params.snr_type));
	head_sim.push_back(std::make_pair("Time report", params.time_report ? "on" : "off"));
	head_sim.push_back(std::make_pair("Debug mode", params.debug ? "on" : "off"));
	if (params.debug)
	{
		head_sim.push_back(std::make_pair("Debug precision", std::to_string(params.debug_precision)));
		if (params.debug_limit)
			head_sim.push_back(std::make_pair("Debug limit", std::to_string(params.debug_limit)));
	}
	head_sim.push_back(std::make_pair("Coset approach (c)", params.coset ? "yes" : "no"));
}
