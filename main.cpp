#include "AbcSmc.h"

using namespace std;

int main(int argc, char* argv[]) {
    const gsl_rng* RNG = gsl_rng_alloc (gsl_rng_taus2);
    gsl_rng_set(RNG, time (NULL) * getpid()); // seed the rng using sys time and the process id

    AbcSmc* abc = new AbcSmc();

    abc->add_next_parameter( "ndice", UNIFORM, INT, 1, 1000 );
    abc->add_next_parameter( "sides", UNIFORM, INT, 1, 1000 );

    abc->add_next_metric( "sum", INT, 374 );// the name and order of summary stats returned by simulator     
    abc->add_next_metric( "sd", FLOAT, 1.71517 );// are we actually going to use the numeric type attribute?

    abc->set_smc_iterations(5); // or have it test for convergence
    abc->set_num_samples(1000);
    abc->set_predictive_prior_fraction(0.1);
    abc->set_pls_validation_training_fraction(0.5); // fraction of runs to use for training (vs. testing) pls model
    abc->run("/home/tjhladish/work/AbcSmc/dice_game", RNG);  // ./executable_name summary_stats par1val par2val par3val par4val par5val ...

    return 0;
}