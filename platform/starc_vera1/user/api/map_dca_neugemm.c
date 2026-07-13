#include "platform_info.h"
#include "ervp_assert.h"
#include "ervp_printf.h"
#include "ervp_blocked_matrix_op.h"
#include "ervp_matrix_op_sw.h"
#include "ervp_matrix_op_transform.h"

#include "ip_instance_info.h"
#include "dca_neugemm.h"

static const int PRINT_DCA_NEUGEMM_FUNCTION = 0;

ervp_blocked_matrix_info_t *blocked_info_neugemm;

ervp_hwtask_busy_fx_t i_dca_neugemm00_add(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  return dca_neugemm_add(mop_mapping, i_dca_neugemm00_info, ma_info, mb_info, mc_info, options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_sub(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  return dca_neugemm_sub(mop_mapping, i_dca_neugemm00_info, ma_info, mb_info, mc_info, options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_ewmult(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  return dca_neugemm_ewmult(mop_mapping, i_dca_neugemm00_info, ma_info, mb_info, mc_info, options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_mult(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  return dca_neugemm_mult(mop_mapping, i_dca_neugemm00_info, ma_info, mb_info, mc_info, options);
}

////////////////////////////////////////////////////////////////////////////

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv_oneblock(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int conv_options)
{
  return dca_neugemm_conv_oneblock(mop_mapping, i_dca_neugemm00_info, ma_info, mb_info, mc_info, conv_options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv_oneblock_sharedinput(ervp_mop_mapping_t *mop_mapping, int num_output, const ErvpMatrixInfo *input_info, const ErvpMatrixInfo **kernel_info_list, ErvpMatrixInfo **output_info_list, int conv_options)
{
  return dca_neugemm_conv_oneblock_sharedinput(mop_mapping, i_dca_neugemm00_info, num_output, input_info, kernel_info_list, output_info_list, conv_options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv_oneblock_sharedoutput(ervp_mop_mapping_t *mop_mapping, int num_input, const ErvpMatrixInfo **input_info_list, const ErvpMatrixInfo **kernel_info_list, ErvpMatrixInfo *output_info, int conv_options, int init_ouptut)
{
  return dca_neugemm_conv_oneblock_sharedoutput(mop_mapping, i_dca_neugemm00_info, num_input, input_info_list, kernel_info_list, output_info, conv_options, init_ouptut);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv(ervp_mop_mapping_t *mop_mapping, const ErvpMatrixInfo *ma_info, const ErvpMatrixInfo *mb_info, ErvpMatrixInfo *mc_info, int conv_options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  trackedvar_smart_flush(3, ma_info->addr, mb_info->addr, mc_info->addr);
  return blocked_matrix_conv(blocked_info_neugemm, ma_info, mb_info, mc_info, conv_options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv_sharedinput(ervp_mop_mapping_t *mop_mapping, int num_output, const ErvpMatrixInfo *input_info, const ErvpMatrixInfo **kernel_info_list, ErvpMatrixInfo **output_info_list, int conv_options)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  trackedvar_smart_flush(3, input_info->addr, kernel_info_list[0]->addr, output_info_list[0]->addr);
  return blocked_matrix_conv_sharedinput(blocked_info_neugemm, num_output, input_info, kernel_info_list, output_info_list, conv_options);
}

ervp_hwtask_busy_fx_t i_dca_neugemm00_conv_sharedoutput(ervp_mop_mapping_t *mop_mapping, int num_input, const ErvpMatrixInfo **input_info_list, const ErvpMatrixInfo **kernel_info_list, ErvpMatrixInfo *output_info, int conv_options, int init_ouptut)
{
  if (PRINT_DCA_NEUGEMM_FUNCTION)
    printf_function();
  trackedvar_smart_flush(3, input_info_list[0]->addr, kernel_info_list[0]->addr, output_info->addr);
  return blocked_matrix_conv_sharedoutput(blocked_info_neugemm, num_input, input_info_list, kernel_info_list, output_info, conv_options, init_ouptut);
}

////////////////////////////////////////////////////////////////////////////

static void __attribute__((constructor)) construct_map_dca_neugemm()
{
  blocked_info_neugemm = blocked_matrix_info_alloc();
  blocked_info_neugemm->block_size = i_dca_neugemm00_info->num_col;
  blocked_info_neugemm->subop_mapping = matrix_op_mapping_alloc();

  blocked_info_neugemm->subop_mapping->matrix_add = i_dca_neugemm00_add;
  blocked_info_neugemm->subop_mapping->matrix_sub = i_dca_neugemm00_sub;
  blocked_info_neugemm->subop_mapping->matrix_ewmult = i_dca_neugemm00_ewmult;
  blocked_info_neugemm->subop_mapping->matrix_mult = i_dca_neugemm00_mult;

  blocked_info_neugemm->subop_mapping->matrix_conv = i_dca_neugemm00_conv_oneblock;
  blocked_info_neugemm->subop_mapping->matrix_conv_sharedinput = i_dca_neugemm00_conv_oneblock_sharedinput;
  blocked_info_neugemm->subop_mapping->matrix_conv_sharedoutput = i_dca_neugemm00_conv_oneblock_sharedoutput;
}

void mop_use_dca_neugemm(ervp_mop_mapping_t *mop_mapping)
{
  assert(mop_mapping != NULL);
  mop_mapping->matrix_add = i_dca_neugemm00_add;
  mop_mapping->matrix_sub = i_dca_neugemm00_sub;
  mop_mapping->matrix_ewmult = i_dca_neugemm00_ewmult;
  mop_mapping->matrix_mult = i_dca_neugemm00_mult;
  if (mop_mapping->matrix_conv == _matrix_conv_sw)
    mop_mapping->matrix_conv = i_dca_neugemm00_conv;
  if (mop_mapping->matrix_conv_sharedinput == matrix_conv_sharedinput_tf)
    mop_mapping->matrix_conv_sharedinput = i_dca_neugemm00_conv_sharedinput;
  if (mop_mapping->matrix_conv_sharedoutput == matrix_conv_sharedoutput_tf)
    mop_mapping->matrix_conv_sharedoutput = i_dca_neugemm00_conv_sharedoutput;
}
