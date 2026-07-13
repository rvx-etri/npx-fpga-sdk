#ifndef __MAP_DCA_NEUGEMM_HW_H__
#define __MAP_DCA_NEUGEMM_HW_H__

#include "ervp_matrix.h"
#include "ervp_matrix_op_sw.h"

extern ervp_blocked_matrix_info_t *blocked_info_neugemm;

void mop_use_dca_neugemm(ervp_mop_mapping_t *mop_mapping);

#endif