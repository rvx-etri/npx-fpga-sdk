#include "platform_info.h"
#include "ervp_printf.h"
#include "ervp_printf_section.h"
#include "ervp_core_id.h"
#include "ervp_matrix_op_sw.h"

#ifdef INCLUDE_DCA
  #include "map_your_matrix_hw.h"
  #include "ip_instance_info.h"
#endif

#include "npx_parser.h"
#include "npx_layer.h"
#include "npx_network.h"
#include "npx_sample.h"
#include "npx_preprocess.h"

#define FNAME_MAX 256

char app_name[FNAME_MAX] = "verify_app";
// char app_name[FNAME_MAX] = "mnist_app";
// char app_name[FNAME_MAX] = "fmnist_app";
// char app_name[FNAME_MAX] = "cifar10_app";
// char app_name[FNAME_MAX] = "gtsrb_app";
// char app_name[255] = "dvsgesture_app";

char net_fname[FNAME_MAX];
char opt_fname[FNAME_MAX];
char parameter_fname[FNAME_MAX];
char sample_fname[FNAME_MAX];
char tv_fname[FNAME_MAX];
char pre_fname[FNAME_MAX];

#define SKIP_SIM 1
#define NUM_ITER 10

int main()
{
  if (EXCLUSIVE_ID == 0)
  {
    ervp_mop_mapping_t *mop_mapping = matrix_op_mapping_alloc();
#ifdef INCLUDE_DCA
    map_your_matrix_function(mop_mapping);
#endif

    sprintf(net_fname, "%s_network.cfg", app_name);
    sprintf(opt_fname, "%s_operator.cfg", app_name);
    sprintf(pre_fname, "%s_preprocess.cfg", app_name);
    sprintf(parameter_fname, "%s_parameter_quant.bin", app_name);

    printf_section(SKIP_SIM, "Verify App: %s", net_fname);

    npx_network_t *net = npx_parse_network_cfg(net_fname, opt_fname);
    npx_network_load_parameters(net, parameter_fname);
    npx_network_map_matrix_operator(net, -1, mop_mapping);
    npx_network_print(net);

    sprintf(sample_fname, "%s_sample_%03d.bin", app_name, 0);
    const npx_rawinput_t *npx_sample = npx_load_sample(sample_fname, pre_fname);
    const npx_layerio_tsseq_t *input_tsseq = npx_preprocess(pre_fname, net, npx_sample->tensor, npx_sample->scaled);

    for (int i = 0; i < NUM_ITER; i++)
    {
      if (!fakefile_exists(sample_fname))
        break;
      printf_subsection(SKIP_SIM, "Iteration %d", i);

      npx_network_reset(net);
      npx_layerio_state_t state;
      state.input_tsseq = input_tsseq;
      state.output_tsseq = npx_inference(net, state.input_tsseq, 0, net->num_layer);
      npx_layerio_tsseq_free(state.output_tsseq);
      //
      assert(test_memory_leak()==0);
    }
  }

  return 0;
}
