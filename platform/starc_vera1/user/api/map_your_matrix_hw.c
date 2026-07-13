#include "platform_info.h"
#include "ervp_assert.h"
#include "ervp_printf.h"
#include "ervp_matrix_op_transform.h"
#include "ervp_blocked_matrix_op.h"

#include "ip_instance_info.h"
#include "map_your_matrix_hw.h"
#include "map_dca_neugemm.h"

const char matrix_hw_name[] = "DCA";

void map_your_matrix_function(ervp_mop_mapping_t *mop_mapping)
{
  /* map your own functions */
  mop_use_dca_neugemm(mop_mapping);
}
