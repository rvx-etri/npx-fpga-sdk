#include <stdint.h>
#include <stddef.h>
#include "ervp_variable_allocation.h"
#include "ervp_malloc.h"
#include "verify_app_preprocess_cfg_file.h"
#ifndef GENERATE_HEX_USING_GCC
#include "platform_info.h"
#endif

const uint8_t verify_app_preprocess_cfg_file_raw[] ALIGNED_DATA BIG_DATA = {
0x5b,0x70,0x72,0x65,0x70,0x72,0x6f,0x63,0x65,0x73,0x73,0x5d,0xa,0x69,0x6e,0x70,0x75,0x74,0x3d,0x6d,0x6e,0x69,0x73,0x74,0x5f,0x6f,0x70,0x65,0x6e,0x64,0x61,0x74,0x61,0x73,0x65,0x74,0xa,0x74,0x69,0x6d,0x65,0x73,0x74,0x65,0x70,0x73,0x3d,0x34,0xa,0x73,0x74,0x65,0x70,0x5f,0x67,0x65,0x6e,0x65,0x72,0x61,0x74,0x69,0x6f,0x6e,0x3d,0x64,0x69,0x72,0x65,0x63,0x74,0xa
};

static char verify_app_preprocess_cfg_file_filename[] = "verify_app_preprocess.cfg";
static fakefile_chunk_t verify_app_preprocess_cfg_file_fakefile_chunk;
static FAKEFILE verify_app_preprocess_cfg_file;

#ifdef USE_FAKEFILE
static void __attribute__ ((constructor)) construct_verify_app_preprocess_cfg_file()
{
	fakefile_chunk_init_(&verify_app_preprocess_cfg_file_fakefile_chunk);
	verify_app_preprocess_cfg_file_fakefile_chunk.data = (uint8_t*)verify_app_preprocess_cfg_file_raw;
	verify_app_preprocess_cfg_file_fakefile_chunk.size = sizeof(verify_app_preprocess_cfg_file_raw);
	verify_app_preprocess_cfg_file_fakefile_chunk.current_size = sizeof(verify_app_preprocess_cfg_file_raw);
	fakefile_init_(&verify_app_preprocess_cfg_file);
	verify_app_preprocess_cfg_file.status = FILE_STATUS_READ_ONLY;
	verify_app_preprocess_cfg_file.name = verify_app_preprocess_cfg_file_filename;
	verify_app_preprocess_cfg_file.head = &verify_app_preprocess_cfg_file_fakefile_chunk;
	fakefile_dict_add(&verify_app_preprocess_cfg_file);
};
static void __attribute__ ((destructor)) destruct_verify_app_preprocess_cfg_file()
{
};
#endif