<<<<<<< HEAD
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/slab.h>
#include <sound/apr_audio-v2.h>
#include <sound/q6asm-v2.h>
#include <sound/compress_params.h>
#include <sound/msm-audio-effects-q6-v2.h>

<<<<<<< HEAD
#define GET_NEXT(ptr, upper_limit, rc)                                  \
({                                                                      \
	if (((ptr) + 1) > (upper_limit)) {                              \
		pr_err("%s: param list out of boundary\n", __func__);   \
		(rc) = -EINVAL;                                         \
	}                                                               \
	((rc) == 0) ? *(ptr)++ :  -EINVAL;                              \
})

#define CHECK_PARAM_LEN(len, max_len, tag, rc)                          \
do {                                                                    \
	if ((len) > (max_len)) {                                        \
		pr_err("%s: params length overflows\n", (tag));         \
		(rc) = -EINVAL;                                         \
	}                                                               \
} while (0)


=======
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
bool msm_audio_effects_is_effmodule_supp_in_top(int effect_module,
						int topology)
{
	switch (effect_module) {
	case VIRTUALIZER_MODULE:
	case REVERB_MODULE:
	case BASS_BOOST_MODULE:
<<<<<<< HEAD
	case PBE_MODULE:
=======
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
	case EQ_MODULE:
		switch (topology) {
		case ASM_STREAM_POSTPROC_TOPO_ID_SA_PLUS:
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_PLUS:
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_MASTER:
			return true;
		default:
			return false;
		}
	case DTS_EAGLE_MODULE:
		switch (topology) {
		case ASM_STREAM_POSTPROC_TOPO_ID_DTS_HPX:
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_PLUS:
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_MASTER:
			return true;
		default:
			return false;
		}
	case SOFT_VOLUME2_MODULE:
		switch (topology) {
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_PLUS:
		case ASM_STREAM_POSTPROC_TOPO_ID_HPX_MASTER:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}

int msm_audio_effects_virtualizer_handler(struct audio_client *ac,
				struct virtualizer_params *virtualizer,
				long *values)
{
<<<<<<< HEAD
	long *param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	char *params = NULL;
	int rc = 0;
	int devices = GET_NEXT(values, param_max_offset, rc);
	int num_commands = GET_NEXT(values, param_max_offset, rc);
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);

	pr_debug("%s\n", __func__);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
=======
	int devices = *values++;
	int num_commands = *values++;
	char *params;
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
	int rc = 0;

	pr_debug("%s\n", __func__);
	if (!ac) {
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		pr_err("%s: cannot set audio effects\n", __func__);
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s: device: %d\n", __func__, devices);
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
<<<<<<< HEAD
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
=======
		uint32_t command_id = *values++;
		uint32_t command_config_state = *values++;
		uint32_t index_offset = *values++;
		uint32_t length = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		switch (command_id) {
		case VIRTUALIZER_ENABLE:
			if (length != 1 || index_offset != 0) {
				pr_err("VIRT ENABLE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			prev_enable_flag = virtualizer->enable_flag;
<<<<<<< HEAD
			virtualizer->enable_flag =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s:VIRT ENABLE prev:%d, new:%d\n", __func__,
				prev_enable_flag, virtualizer->enable_flag);
			if (prev_enable_flag != virtualizer->enable_flag) {
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_ENABLE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VIRT ENABLE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
				AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
				AUDPROC_PARAM_ID_VIRTUALIZER_ENABLE;
				*updt_params++ =
				VIRTUALIZER_ENABLE_PARAM_SZ;
				*updt_params++ =
				virtualizer->enable_flag;
=======
			virtualizer->enable_flag = *values++;
			pr_debug("%s:VIRT ENABLE prev:%d, new:%d\n", __func__,
				prev_enable_flag, virtualizer->enable_flag);
			if (prev_enable_flag != virtualizer->enable_flag) {
				*updt_params++ = AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_VIRTUALIZER_ENABLE;
				*updt_params++ = VIRTUALIZER_ENABLE_PARAM_SZ;
				*updt_params++ = virtualizer->enable_flag;
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_ENABLE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case VIRTUALIZER_STRENGTH:
			if (length != 1 || index_offset != 0) {
				pr_err("VIRT STRENGTH:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			virtualizer->strength =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: VIRT STRENGTH val: %d\n",
					__func__, virtualizer->strength);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_STRENGTH_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VIRT STRENGTH", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_VIRTUALIZER_STRENGTH;
				*updt_params++ =
					VIRTUALIZER_STRENGTH_PARAM_SZ;
				*updt_params++ =
					virtualizer->strength;
=======
			virtualizer->strength = *values++;
			pr_debug("%s: VIRT STRENGTH val: %d\n",
					__func__, virtualizer->strength);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_VIRTUALIZER_STRENGTH;
				*updt_params++ = VIRTUALIZER_STRENGTH_PARAM_SZ;
				*updt_params++ = virtualizer->strength;
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_STRENGTH_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case VIRTUALIZER_OUT_TYPE:
			if (length != 1 || index_offset != 0) {
				pr_err("VIRT OUT_TYPE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			virtualizer->out_type =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: VIRT OUT_TYPE val:%d\n",
				__func__, virtualizer->out_type);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_OUT_TYPE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VIRT OUT_TYPE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_VIRTUALIZER_OUT_TYPE;
				*updt_params++ =
					VIRTUALIZER_OUT_TYPE_PARAM_SZ;
				*updt_params++ =
					virtualizer->out_type;
=======
			virtualizer->out_type = *values++;
			pr_debug("%s: VIRT OUT_TYPE val:%d\n",
				__func__, virtualizer->out_type);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_VIRTUALIZER_OUT_TYPE;
				*updt_params++ = VIRTUALIZER_OUT_TYPE_PARAM_SZ;
				*updt_params++ = virtualizer->out_type;
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_OUT_TYPE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case VIRTUALIZER_GAIN_ADJUST:
			if (length != 1 || index_offset != 0) {
				pr_err("VIRT GAIN_ADJUST: invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			virtualizer->gain_adjust =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: VIRT GAIN_ADJUST val:%d\n",
				__func__, virtualizer->gain_adjust);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_GAIN_ADJUST_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VIRT GAIN_ADJUST", rc);
				if (rc != 0)
					break;
				*updt_params++ =
				AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
				AUDPROC_PARAM_ID_VIRTUALIZER_GAIN_ADJUST;
				*updt_params++ =
				VIRTUALIZER_GAIN_ADJUST_PARAM_SZ;
				*updt_params++ =
				virtualizer->gain_adjust;
=======
			virtualizer->gain_adjust = *values++;
			pr_debug("%s: VIRT GAIN_ADJUST val:%d\n",
				__func__, virtualizer->gain_adjust);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_VIRTUALIZER;
				*updt_params++ =
				       AUDPROC_PARAM_ID_VIRTUALIZER_GAIN_ADJUST;
				*updt_params++ =
					VIRTUALIZER_GAIN_ADJUST_PARAM_SZ;
				*updt_params++ = virtualizer->gain_adjust;
				params_length += COMMAND_PAYLOAD_SZ +
					VIRTUALIZER_GAIN_ADJUST_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		default:
			pr_err("%s: Invalid command to set config\n", __func__);
			break;
		}
	}
<<<<<<< HEAD
	if (params_length && (rc == 0))
=======
	if (params_length)
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

int msm_audio_effects_reverb_handler(struct audio_client *ac,
				     struct reverb_params *reverb,
				     long *values)
{
<<<<<<< HEAD
	long *param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	char *params = NULL;
	int rc = 0;
	int devices = GET_NEXT(values, param_max_offset, rc);
	int num_commands = GET_NEXT(values, param_max_offset, rc);
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);

	pr_debug("%s\n", __func__);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
=======
	int devices = *values++;
	int num_commands = *values++;
	char *params;
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
	int rc = 0;

	pr_debug("%s\n", __func__);
	if (!ac) {
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		pr_err("%s: cannot set audio effects\n", __func__);
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s: device: %d\n", __func__, devices);
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
<<<<<<< HEAD
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
=======
		uint32_t command_id = *values++;
		uint32_t command_config_state = *values++;
		uint32_t index_offset = *values++;
		uint32_t length = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		switch (command_id) {
		case REVERB_ENABLE:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_ENABLE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			prev_enable_flag = reverb->enable_flag;
<<<<<<< HEAD
			reverb->enable_flag =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s:REVERB_ENABLE prev:%d,new:%d\n", __func__,
					prev_enable_flag, reverb->enable_flag);
			if (prev_enable_flag != reverb->enable_flag) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ENABLE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_ENABLE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_ENABLE;
				*updt_params++ =
					REVERB_ENABLE_PARAM_SZ;
				*updt_params++ =
					reverb->enable_flag;
=======
			reverb->enable_flag = *values++;
			pr_debug("%s:REVERB_ENABLE prev:%d,new:%d\n", __func__,
					prev_enable_flag, reverb->enable_flag);
			if (prev_enable_flag != reverb->enable_flag) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ = AUDPROC_PARAM_ID_REVERB_ENABLE;
				*updt_params++ = REVERB_ENABLE_PARAM_SZ;
				*updt_params++ = reverb->enable_flag;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ENABLE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_MODE:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_MODE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->mode =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_MODE val:%d\n",
				__func__, reverb->mode);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_MODE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_MODE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_MODE;
				*updt_params++ =
					REVERB_MODE_PARAM_SZ;
				*updt_params++ =
					reverb->mode;
=======
			reverb->mode = *values++;
			pr_debug("%s: REVERB_MODE val:%d\n",
				__func__, reverb->mode);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ = AUDPROC_PARAM_ID_REVERB_MODE;
				*updt_params++ = REVERB_MODE_PARAM_SZ;
				*updt_params++ = reverb->mode;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_MODE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_PRESET:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_PRESET:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->preset =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_PRESET val:%d\n",
					__func__, reverb->preset);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_PRESET_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_PRESET", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_PRESET;
				*updt_params++ =
					REVERB_PRESET_PARAM_SZ;
				*updt_params++ =
					reverb->preset;
=======
			reverb->preset = *values++;
			pr_debug("%s: REVERB_PRESET val:%d\n",
					__func__, reverb->preset);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ = AUDPROC_PARAM_ID_REVERB_PRESET;
				*updt_params++ = REVERB_PRESET_PARAM_SZ;
				*updt_params++ = reverb->preset;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_PRESET_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_WET_MIX:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_WET_MIX:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->wet_mix =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_WET_MIX val:%d\n",
				__func__, reverb->wet_mix);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_WET_MIX_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_WET_MIX", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_WET_MIX;
				*updt_params++ =
					REVERB_WET_MIX_PARAM_SZ;
				*updt_params++ =
					reverb->wet_mix;
=======
			reverb->wet_mix = *values++;
			pr_debug("%s: REVERB_WET_MIX val:%d\n",
				__func__, reverb->wet_mix);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_WET_MIX;
				*updt_params++ = REVERB_WET_MIX_PARAM_SZ;
				*updt_params++ = reverb->wet_mix;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_WET_MIX_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_GAIN_ADJUST:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_GAIN_ADJUST:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->gain_adjust =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_GAIN_ADJUST val:%d\n",
					__func__, reverb->gain_adjust);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_GAIN_ADJUST_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_GAIN_ADJUST", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_GAIN_ADJUST;
				*updt_params++ =
					REVERB_GAIN_ADJUST_PARAM_SZ;
				*updt_params++ =
					reverb->gain_adjust;
=======
			reverb->gain_adjust = *values++;
			pr_debug("%s: REVERB_GAIN_ADJUST val:%d\n",
					__func__, reverb->gain_adjust);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_GAIN_ADJUST;
				*updt_params++ = REVERB_GAIN_ADJUST_PARAM_SZ;
				*updt_params++ = reverb->gain_adjust;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_GAIN_ADJUST_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_ROOM_LEVEL:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_ROOM_LEVEL:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->room_level =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_ROOM_LEVEL val:%d\n",
				__func__, reverb->room_level);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ROOM_LEVEL_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_ROOM_LEVEL", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_ROOM_LEVEL;
				*updt_params++ =
					REVERB_ROOM_LEVEL_PARAM_SZ;
				*updt_params++ =
					reverb->room_level;
=======
			reverb->room_level = *values++;
			pr_debug("%s: REVERB_ROOM_LEVEL val:%d\n",
				__func__, reverb->room_level);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_ROOM_LEVEL;
				*updt_params++ = REVERB_ROOM_LEVEL_PARAM_SZ;
				*updt_params++ = reverb->room_level;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ROOM_LEVEL_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_ROOM_HF_LEVEL:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_ROOM_HF_LEVEL:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->room_hf_level =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_ROOM_HF_LEVEL val%d\n",
				__func__, reverb->room_hf_level);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ROOM_HF_LEVEL_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_ROOM_HF_LEVEL", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_ROOM_HF_LEVEL;
				*updt_params++ =
					REVERB_ROOM_HF_LEVEL_PARAM_SZ;
				*updt_params++ =
					reverb->room_hf_level;
=======
			reverb->room_hf_level = *values++;
			pr_debug("%s: REVERB_ROOM_HF_LEVEL val%d\n",
				__func__, reverb->room_hf_level);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_ROOM_HF_LEVEL;
				*updt_params++ = REVERB_ROOM_HF_LEVEL_PARAM_SZ;
				*updt_params++ = reverb->room_hf_level;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_ROOM_HF_LEVEL_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_DECAY_TIME:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_DECAY_TIME:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->decay_time =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_DECAY_TIME val:%d\n",
				__func__, reverb->decay_time);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DECAY_TIME_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_DECAY_TIME", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DECAY_TIME;
				*updt_params++ =
					REVERB_DECAY_TIME_PARAM_SZ;
				*updt_params++ =
					reverb->decay_time;
=======
			reverb->decay_time = *values++;
			pr_debug("%s: REVERB_DECAY_TIME val:%d\n",
				__func__, reverb->decay_time);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DECAY_TIME;
				*updt_params++ = REVERB_DECAY_TIME_PARAM_SZ;
				*updt_params++ = reverb->decay_time;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DECAY_TIME_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_DECAY_HF_RATIO:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_DECAY_HF_RATIOinvalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->decay_hf_ratio =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_DECAY_HF_RATIO val%d\n",
				__func__, reverb->decay_hf_ratio);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DECAY_HF_RATIO_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_DECAY_HF_RATIO", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DECAY_HF_RATIO;
				*updt_params++ =
					REVERB_DECAY_HF_RATIO_PARAM_SZ;
				*updt_params++ =
					reverb->decay_hf_ratio;
=======
			reverb->decay_hf_ratio = *values++;
			pr_debug("%s: REVERB_DECAY_HF_RATIO val%d\n",
				__func__, reverb->decay_hf_ratio);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DECAY_HF_RATIO;
				*updt_params++ = REVERB_DECAY_HF_RATIO_PARAM_SZ;
				*updt_params++ = reverb->decay_hf_ratio;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DECAY_HF_RATIO_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_REFLECTIONS_LEVEL:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_REFLECTION_LVLinvalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->reflections_level =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_REFLECTIONS_LEVEL val:%d\n",
				__func__, reverb->reflections_level);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_REFLECTIONS_LEVEL_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_REFLECTIONS_LEVEL", rc);
				if (rc != 0)
					break;
				*updt_params++ =
				AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
				AUDPROC_PARAM_ID_REVERB_REFLECTIONS_LEVEL;
				*updt_params++ =
				REVERB_REFLECTIONS_LEVEL_PARAM_SZ;
				*updt_params++ =
				reverb->reflections_level;
=======
			reverb->reflections_level = *values++;
			pr_debug("%s: REVERB_REFLECTIONS_LEVEL val:%d\n",
				__func__, reverb->reflections_level);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
				      AUDPROC_PARAM_ID_REVERB_REFLECTIONS_LEVEL;
				*updt_params++ =
					REVERB_REFLECTIONS_LEVEL_PARAM_SZ;
				*updt_params++ = reverb->reflections_level;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_REFLECTIONS_LEVEL_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_REFLECTIONS_DELAY:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_REFLECTION_DLYinvalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->reflections_delay =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_REFLECTIONS_DELAY val:%d\n",
				__func__, reverb->reflections_delay);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_REFLECTIONS_DELAY_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_REFLECTIONS_DELAY", rc);
				if (rc != 0)
					break;
				*updt_params++ =
				AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
				AUDPROC_PARAM_ID_REVERB_REFLECTIONS_DELAY;
				*updt_params++ =
				REVERB_REFLECTIONS_DELAY_PARAM_SZ;
				*updt_params++ =
				reverb->reflections_delay;
=======
			reverb->reflections_delay = *values++;
			pr_debug("%s: REVERB_REFLECTIONS_DELAY val:%d\n",
				__func__, reverb->reflections_delay);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
				      AUDPROC_PARAM_ID_REVERB_REFLECTIONS_DELAY;
				*updt_params++ =
					REVERB_REFLECTIONS_DELAY_PARAM_SZ;
				*updt_params++ = reverb->reflections_delay;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_REFLECTIONS_DELAY_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_LEVEL:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_LEVEL:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->level =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_LEVEL val:%d\n",
				__func__, reverb->level);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_LEVEL_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_LEVEL", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_LEVEL;
				*updt_params++ =
					REVERB_LEVEL_PARAM_SZ;
				*updt_params++ =
					reverb->level;
=======
			reverb->level = *values++;
			pr_debug("%s: REVERB_LEVEL val:%d\n",
				__func__, reverb->level);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ = AUDPROC_PARAM_ID_REVERB_LEVEL;
				*updt_params++ = REVERB_LEVEL_PARAM_SZ;
				*updt_params++ = reverb->level;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_LEVEL_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_DELAY:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_DELAY:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->delay =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s:REVERB_DELAY val:%d\n",
					__func__, reverb->delay);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DELAY_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_DELAY", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DELAY;
				*updt_params++ =
					REVERB_DELAY_PARAM_SZ;
				*updt_params++ =
					reverb->delay;
=======
			reverb->delay = *values++;
			pr_debug("%s:REVERB_DELAY val:%d\n",
					__func__, reverb->delay);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ = AUDPROC_PARAM_ID_REVERB_DELAY;
				*updt_params++ = REVERB_DELAY_PARAM_SZ;
				*updt_params++ = reverb->delay;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DELAY_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_DIFFUSION:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_DIFFUSION:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->diffusion =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_DIFFUSION val:%d\n",
				__func__, reverb->diffusion);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DIFFUSION_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_DIFFUSION", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DIFFUSION;
				*updt_params++ =
					REVERB_DIFFUSION_PARAM_SZ;
				*updt_params++ =
					reverb->diffusion;
=======
			reverb->diffusion = *values++;
			pr_debug("%s: REVERB_DIFFUSION val:%d\n",
				__func__, reverb->diffusion);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DIFFUSION;
				*updt_params++ = REVERB_DIFFUSION_PARAM_SZ;
				*updt_params++ = reverb->diffusion;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DIFFUSION_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case REVERB_DENSITY:
			if (length != 1 || index_offset != 0) {
				pr_err("REVERB_DENSITY:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			reverb->density =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: REVERB_DENSITY val:%d\n",
				__func__, reverb->density);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DENSITY_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"REVERB_DENSITY", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DENSITY;
				*updt_params++ =
					REVERB_DENSITY_PARAM_SZ;
				*updt_params++ =
					reverb->density;
=======
			reverb->density = *values++;
			pr_debug("%s: REVERB_DENSITY val:%d\n",
				__func__, reverb->density);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_REVERB;
				*updt_params++ =
					AUDPROC_PARAM_ID_REVERB_DENSITY;
				*updt_params++ = REVERB_DENSITY_PARAM_SZ;
				*updt_params++ = reverb->density;
				params_length += COMMAND_PAYLOAD_SZ +
					REVERB_DENSITY_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		default:
			pr_err("%s: Invalid command to set config\n", __func__);
			break;
		}
	}
<<<<<<< HEAD
	if (params_length && (rc == 0))
=======
	if (params_length)
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

int msm_audio_effects_bass_boost_handler(struct audio_client *ac,
					struct bass_boost_params *bass_boost,
					long *values)
{
<<<<<<< HEAD
	long *param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	char *params = NULL;
	int rc = 0;
	int devices = GET_NEXT(values, param_max_offset, rc);
	int num_commands = GET_NEXT(values, param_max_offset, rc);
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);

	pr_debug("%s\n", __func__);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
=======
	int devices = *values++;
	int num_commands = *values++;
	char *params;
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
	int rc = 0;

	pr_debug("%s\n", __func__);
	if (!ac) {
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		pr_err("%s: cannot set audio effects\n", __func__);
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s: device: %d\n", __func__, devices);
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
<<<<<<< HEAD
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
=======
		uint32_t command_id = *values++;
		uint32_t command_config_state = *values++;
		uint32_t index_offset = *values++;
		uint32_t length = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		switch (command_id) {
		case BASS_BOOST_ENABLE:
			if (length != 1 || index_offset != 0) {
				pr_err("BASS_BOOST_ENABLE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			prev_enable_flag = bass_boost->enable_flag;
<<<<<<< HEAD
			bass_boost->enable_flag =
				GET_NEXT(values, param_max_offset, rc);
=======
			bass_boost->enable_flag = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			pr_debug("%s: BASS_BOOST_ENABLE prev:%d new:%d\n",
				__func__, prev_enable_flag,
				bass_boost->enable_flag);
			if (prev_enable_flag != bass_boost->enable_flag) {
<<<<<<< HEAD
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_ENABLE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"BASS_BOOST_ENABLE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_ENABLE;
				*updt_params++ =
					BASS_BOOST_ENABLE_PARAM_SZ;
				*updt_params++ =
					bass_boost->enable_flag;
=======
				*updt_params++ = AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_ENABLE;
				*updt_params++ = BASS_BOOST_ENABLE_PARAM_SZ;
				*updt_params++ = bass_boost->enable_flag;
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_ENABLE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case BASS_BOOST_MODE:
			if (length != 1 || index_offset != 0) {
				pr_err("BASS_BOOST_MODE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			bass_boost->mode =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: BASS_BOOST_MODE val:%d\n",
				__func__, bass_boost->mode);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_MODE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"BASS_BOOST_MODE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_MODE;
				*updt_params++ =
					BASS_BOOST_MODE_PARAM_SZ;
				*updt_params++ =
					bass_boost->mode;
=======
			bass_boost->mode = *values++;
			pr_debug("%s: BASS_BOOST_MODE val:%d\n",
				__func__, bass_boost->mode);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_MODE;
				*updt_params++ = BASS_BOOST_MODE_PARAM_SZ;
				*updt_params++ = bass_boost->mode;
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_MODE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case BASS_BOOST_STRENGTH:
			if (length != 1 || index_offset != 0) {
				pr_err("BASS_BOOST_STRENGTH:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			bass_boost->strength =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: BASS_BOOST_STRENGTH val:%d\n",
				__func__, bass_boost->strength);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_STRENGTH_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"BASS_BOOST_STRENGTH", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_STRENGTH;
				*updt_params++ =
					BASS_BOOST_STRENGTH_PARAM_SZ;
				*updt_params++ =
					bass_boost->strength;
			}
			break;
		default:
			pr_err("%s: Invalid command to set config\n", __func__);
			break;
		}
	}
	if (params_length && (rc == 0))
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

int msm_audio_effects_pbe_handler(struct audio_client *ac,
					struct pbe_params *pbe,
					long *values)
{
	long *param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	char *params = NULL;
	int rc = 0;
	int devices = GET_NEXT(values, param_max_offset, rc);
	int num_commands = GET_NEXT(values, param_max_offset, rc);
	int *updt_params, i, j, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);

	pr_debug("%s\n", __func__);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
		pr_err("%s: cannot set audio effects\n", __func__);
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s: device: %d\n", __func__, devices);
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
		switch (command_id) {
		case PBE_ENABLE:
			pr_debug("%s: PBE_ENABLE\n", __func__);
			if (length != 1 || index_offset != 0) {
				pr_err("no valid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			prev_enable_flag = pbe->enable_flag;
			pbe->enable_flag =
				GET_NEXT(values, param_max_offset, rc);
			if (prev_enable_flag != pbe->enable_flag) {
				params_length += COMMAND_PAYLOAD_SZ +
					PBE_ENABLE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"PBE_ENABLE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_PBE;
				*updt_params++ =
					AUDPROC_PARAM_ID_PBE_ENABLE;
				*updt_params++ =
					PBE_ENABLE_PARAM_SZ;
				*updt_params++ =
					pbe->enable_flag;
			}
			break;
		case PBE_CONFIG:
			pr_debug("%s: PBE_PARAM length %u\n", __func__, length);
			if (length > sizeof(struct pbe_config_t) ||
				length < PBE_CONFIG_PARAM_LEN ||
				index_offset != 0) {
				pr_err("no valid params, len %d\n", length);
				rc = -EINVAL;
				goto invalid_config;
			}
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ + length;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"PBE_PARAM", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_PBE;
				*updt_params++ =
					AUDPROC_PARAM_ID_PBE_PARAM_CONFIG;
				*updt_params++ =
					length;
				for (j = 0; j < length; ) {
					j += sizeof(*updt_params);
					*updt_params++ =
						GET_NEXT(
						values,
						param_max_offset,
						rc);
				}
=======
			bass_boost->strength = *values++;
			pr_debug("%s: BASS_BOOST_STRENGTHi val:%d\n",
				__func__, bass_boost->strength);
			if (command_config_state == CONFIG_SET) {
				*updt_params++ = AUDPROC_MODULE_ID_BASS_BOOST;
				*updt_params++ =
					AUDPROC_PARAM_ID_BASS_BOOST_STRENGTH;
				*updt_params++ = BASS_BOOST_STRENGTH_PARAM_SZ;
				*updt_params++ = bass_boost->strength;
				params_length += COMMAND_PAYLOAD_SZ +
					BASS_BOOST_STRENGTH_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		default:
			pr_err("%s: Invalid command to set config\n", __func__);
			break;
		}
	}
<<<<<<< HEAD
	if (params_length && (rc == 0))
=======
	if (params_length)
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

int msm_audio_effects_popless_eq_handler(struct audio_client *ac,
					 struct eq_params *eq,
					 long *values)
{
<<<<<<< HEAD
	long *param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	char *params = NULL;
	int rc = 0;
	int devices = GET_NEXT(values, param_max_offset, rc);
	int num_commands = GET_NEXT(values, param_max_offset, rc);
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);

	pr_debug("%s\n", __func__);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
=======
	int devices = *values++;
	int num_commands = *values++;
	char *params;
	int *updt_params, i, prev_enable_flag;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
	int rc = 0;

	pr_debug("%s\n", __func__);
	if (!ac) {
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		pr_err("%s: cannot set audio effects\n", __func__);
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s: device: %d\n", __func__, devices);
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
<<<<<<< HEAD
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t idx;
		int j;
=======
		uint32_t command_id = *values++;
		uint32_t command_config_state = *values++;
		uint32_t index_offset = *values++;
		uint32_t length = *values++;
		int idx, j;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		switch (command_id) {
		case EQ_ENABLE:
			if (length != 1 || index_offset != 0) {
				pr_err("EQ_ENABLE:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			prev_enable_flag = eq->enable_flag;
<<<<<<< HEAD
			eq->enable_flag =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: EQ_ENABLE prev:%d new:%d\n", __func__,
				prev_enable_flag, eq->enable_flag);
			if (prev_enable_flag != eq->enable_flag) {
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_ENABLE_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"EQ_ENABLE", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_EQ_ENABLE;
				*updt_params++ =
					EQ_ENABLE_PARAM_SZ;
				*updt_params++ =
					eq->enable_flag;
=======
			eq->enable_flag = *values++;
			pr_debug("%s: EQ_ENABLE prev:%d new:%d\n", __func__,
				prev_enable_flag, eq->enable_flag);
			if (prev_enable_flag != eq->enable_flag) {
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ = AUDPROC_PARAM_ID_EQ_ENABLE;
				*updt_params++ = EQ_ENABLE_PARAM_SZ;
				*updt_params++ = eq->enable_flag;
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_ENABLE_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case EQ_CONFIG:
			if (length < EQ_CONFIG_PARAM_LEN || index_offset != 0) {
				pr_err("EQ_CONFIG:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			pr_debug("%s: EQ_CONFIG bands:%d, pgain:%d, pset:%d\n",
				 __func__, eq->config.num_bands,
				eq->config.eq_pregain, eq->config.preset_id);
			for (idx = 0; idx < MAX_EQ_BANDS; idx++)
				eq->per_band_cfg[idx].band_idx = -1;
<<<<<<< HEAD
			eq->config.eq_pregain =
				GET_NEXT(values, param_max_offset, rc);
			eq->config.preset_id =
				GET_NEXT(values, param_max_offset, rc);
			eq->config.num_bands =
				GET_NEXT(values, param_max_offset, rc);
=======
			eq->config.eq_pregain = *values++;
			eq->config.preset_id = *values++;
			eq->config.num_bands = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			if (eq->config.num_bands > MAX_EQ_BANDS) {
				pr_err("EQ_CONFIG:invalid num of bands\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			if (eq->config.num_bands &&
			    (((length - EQ_CONFIG_PARAM_LEN)/
				EQ_CONFIG_PER_BAND_PARAM_LEN)
				!= eq->config.num_bands)) {
				pr_err("EQ_CONFIG:invalid length per band\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			for (j = 0; j < eq->config.num_bands; j++) {
<<<<<<< HEAD
				idx = GET_NEXT(values, param_max_offset, rc);
=======
				idx = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				if (idx >= MAX_EQ_BANDS) {
					pr_err("EQ_CONFIG:invalid band index\n");
					rc = -EINVAL;
					goto invalid_config;
				}
				eq->per_band_cfg[idx].band_idx = idx;
<<<<<<< HEAD
				eq->per_band_cfg[idx].filter_type =
					GET_NEXT(values, param_max_offset, rc);
				eq->per_band_cfg[idx].freq_millihertz =
					GET_NEXT(values, param_max_offset, rc);
				eq->per_band_cfg[idx].gain_millibels =
					GET_NEXT(values, param_max_offset, rc);
				eq->per_band_cfg[idx].quality_factor =
					GET_NEXT(values, param_max_offset, rc);
=======
				eq->per_band_cfg[idx].filter_type = *values++;
				eq->per_band_cfg[idx].freq_millihertz =
								*values++;
				eq->per_band_cfg[idx].gain_millibels =
								*values++;
				eq->per_band_cfg[idx].quality_factor =
								*values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			if (command_config_state == CONFIG_SET) {
				int config_param_length = EQ_CONFIG_PARAM_SZ +
					(EQ_CONFIG_PER_BAND_PARAM_SZ*
					 eq->config.num_bands);
<<<<<<< HEAD
				params_length += COMMAND_PAYLOAD_SZ +
						config_param_length;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"EQ_CONFIG", rc);
				if (rc != 0)
					break;
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_EQ_CONFIG;
				*updt_params++ =
					config_param_length;
				*updt_params++ =
					eq->config.eq_pregain;
				*updt_params++ =
					eq->config.preset_id;
				*updt_params++ =
					eq->config.num_bands;
=======
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ = AUDPROC_PARAM_ID_EQ_CONFIG;
				*updt_params++ = config_param_length;
				*updt_params++ = eq->config.eq_pregain;
				*updt_params++ = eq->config.preset_id;
				*updt_params++ = eq->config.num_bands;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				for (idx = 0; idx < MAX_EQ_BANDS; idx++) {
					if (eq->per_band_cfg[idx].band_idx < 0)
						continue;
					*updt_params++ =
<<<<<<< HEAD
					eq->per_band_cfg[idx].filter_type;
					*updt_params++ =
					eq->per_band_cfg[idx].freq_millihertz;
					*updt_params++ =
					eq->per_band_cfg[idx].gain_millibels;
					*updt_params++ =
					eq->per_band_cfg[idx].quality_factor;
					*updt_params++ =
					eq->per_band_cfg[idx].band_idx;
				}
=======
					  eq->per_band_cfg[idx].filter_type;
					*updt_params++ =
					  eq->per_band_cfg[idx].freq_millihertz;
					*updt_params++ =
					  eq->per_band_cfg[idx].gain_millibels;
					*updt_params++ =
					  eq->per_band_cfg[idx].quality_factor;
					*updt_params++ =
					  eq->per_band_cfg[idx].band_idx;
				}
				params_length += COMMAND_PAYLOAD_SZ +
						config_param_length;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case EQ_BAND_INDEX:
			if (length != 1 || index_offset != 0) {
				pr_err("EQ_BAND_INDEX:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
<<<<<<< HEAD
			idx = GET_NEXT(values, param_max_offset, rc);
=======
			idx = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			if (idx > MAX_EQ_BANDS) {
				pr_err("EQ_BAND_INDEX:invalid band index\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			eq->band_index = idx;
			pr_debug("%s: EQ_BAND_INDEX val:%d\n",
				__func__, eq->band_index);
			if (command_config_state == CONFIG_SET) {
<<<<<<< HEAD
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_BAND_INDEX_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"EQ_BAND_INDEX", rc);
				if (rc != 0)
					break;
=======
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_EQ_BAND_INDEX;
<<<<<<< HEAD
				*updt_params++ =
					EQ_BAND_INDEX_PARAM_SZ;
				*updt_params++ =
					eq->band_index;
=======
				*updt_params++ = EQ_BAND_INDEX_PARAM_SZ;
				*updt_params++ = eq->band_index;
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_BAND_INDEX_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case EQ_SINGLE_BAND_FREQ:
			if (length != 1 || index_offset != 0) {
				pr_err("EQ_SINGLE_BAND_FREQ:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			if (eq->band_index > MAX_EQ_BANDS) {
				pr_err("EQ_SINGLE_BAND_FREQ:invalid index\n");
				break;
			}
<<<<<<< HEAD
			eq->freq_millihertz =
				GET_NEXT(values, param_max_offset, rc);
			pr_debug("%s: EQ_SINGLE_BAND_FREQ idx:%d, val:%d\n",
				__func__, eq->band_index, eq->freq_millihertz);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_SINGLE_BAND_FREQ_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"EQ_SINGLE_BAND_FREQ", rc);
				if (rc != 0)
					break;
=======
			eq->freq_millihertz = *values++;
			pr_debug("%s: EQ_SINGLE_BAND_FREQ idx:%d, val:%d\n",
				__func__, eq->band_index, eq->freq_millihertz);
			if (command_config_state == CONFIG_SET) {
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				*updt_params++ =
					AUDPROC_MODULE_ID_POPLESS_EQUALIZER;
				*updt_params++ =
					AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ;
<<<<<<< HEAD
				*updt_params++ =
					EQ_SINGLE_BAND_FREQ_PARAM_SZ;
				*updt_params++ =
					eq->freq_millihertz;
=======
				*updt_params++ = EQ_SINGLE_BAND_FREQ_PARAM_SZ;
				*updt_params++ = eq->freq_millihertz;
				params_length += COMMAND_PAYLOAD_SZ +
					EQ_SINGLE_BAND_FREQ_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		default:
			pr_err("%s: Invalid command to set config\n", __func__);
			break;
		}
	}
<<<<<<< HEAD
	if (params_length && (rc == 0))
=======
	if (params_length)
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

static int __msm_audio_effects_volume_handler(struct audio_client *ac,
					      struct soft_volume_params *vol,
					      long *values,
					      int instance)
{
	int devices;
	int num_commands;
<<<<<<< HEAD
	char *params = NULL;
	int *updt_params, i;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
	long *param_max_offset;
=======
	char *params;
	int *updt_params, i;
	uint32_t params_length = (MAX_INBAND_PARAM_SZ);
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
	int rc = 0;

	pr_debug("%s: instance: %d\n", __func__, instance);
	if (!values) {
		pr_err("%s: set audio effects failed, no valid data\n",
			__func__);
		return -EINVAL;
	}
<<<<<<< HEAD
	param_max_offset = values + MAX_PP_PARAMS_SZ - 1;
	devices = GET_NEXT(values, param_max_offset, rc);
	num_commands = GET_NEXT(values, param_max_offset, rc);
	if (!ac || (devices == -EINVAL) || (num_commands == -EINVAL)) {
		pr_err("%s: cannot set audio effects\n", __func__);
=======
	if (!ac) {
		pr_err("%s: cannot set audio effects as audio client is NULL\n",
			__func__);
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		return -EINVAL;
	}
	params = kzalloc(params_length, GFP_KERNEL);
	if (!params) {
		pr_err("%s, params memory alloc failed\n", __func__);
		return -ENOMEM;
	}
<<<<<<< HEAD
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
		uint32_t command_id =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t command_config_state =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t index_offset =
			GET_NEXT(values, param_max_offset, rc);
		uint32_t length =
			GET_NEXT(values, param_max_offset, rc);
=======
	devices = *values++;
	num_commands = *values++;
	updt_params = (int *)params;
	params_length = 0;
	for (i = 0; i < num_commands; i++) {
		uint32_t command_id = *values++;
		uint32_t command_config_state = *values++;
		uint32_t index_offset = *values++;
		uint32_t length = *values++;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		switch (command_id) {
		case SOFT_VOLUME_GAIN_2CH:
		case SOFT_VOLUME2_GAIN_2CH:
			if (length != 2 || index_offset != 0) {
<<<<<<< HEAD
				pr_err("VOLUME_GAIN_2CH: invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			vol->left_gain = GET_NEXT(values, param_max_offset, rc);
			vol->right_gain =
				GET_NEXT(values, param_max_offset, rc);
			vol->master_gain = 0x2000;
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
						SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				params_length += COMMAND_PAYLOAD_SZ +
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VOLUME/VOLUME2_GAIN_2CH",
						rc);
				if (rc != 0)
					break;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL;
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN;
				*updt_params++ =
					SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				*updt_params++ =
					(vol->left_gain << 16) |
						vol->right_gain;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL;
=======
				pr_err("VOLUME_GAIN_2CH/VOLUME2_GAIN_2CH:invalid params\n");
				rc = -EINVAL;
				goto invalid_config;
			}
			vol->left_gain = *values++;
			vol->right_gain = *values++;
			vol->master_gain = 0x2000;
			if (command_config_state == CONFIG_SET) {
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
							ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ = ASM_MODULE_ID_VOL_CTRL;
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN;
				*updt_params++ = SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				*updt_params++ = (vol->left_gain << 16) |
						 vol->right_gain;
				params_length += COMMAND_PAYLOAD_SZ +
						SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
							ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ = ASM_MODULE_ID_VOL_CTRL;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_MASTER_GAIN;
				*updt_params++ =
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
<<<<<<< HEAD
				*updt_params++ =
					vol->master_gain;
=======
				*updt_params++ = vol->master_gain;
				params_length += COMMAND_PAYLOAD_SZ +
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		case SOFT_VOLUME_GAIN_MASTER:
		case SOFT_VOLUME2_GAIN_MASTER:
			if (length != 1 || index_offset != 0) {
<<<<<<< HEAD
				pr_err("VOLUME_GAIN_MASTER: invalid params\n");
=======
				pr_err("VOLUME_GAIN_MASTER/VOLUME2_GAIN_MASTER:invalid params\n");
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				rc = -EINVAL;
				goto invalid_config;
			}
			vol->left_gain = 0x2000;
			vol->right_gain = 0x2000;
<<<<<<< HEAD
			vol->master_gain =
				GET_NEXT(values, param_max_offset, rc);
			if (command_config_state == CONFIG_SET) {
				params_length += COMMAND_PAYLOAD_SZ +
						SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				params_length += COMMAND_PAYLOAD_SZ +
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
				CHECK_PARAM_LEN(params_length,
						MAX_INBAND_PARAM_SZ,
						"VOLUME/VOLUME2_GAIN_MASTER",
						rc);
				if (rc != 0)
					break;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL;
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN;
				*updt_params++ =
					SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				*updt_params++ =
					(vol->left_gain << 16) |
						vol->right_gain;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ =
						ASM_MODULE_ID_VOL_CTRL;
=======
			vol->master_gain = *values++;
			if (command_config_state == CONFIG_SET) {
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
							ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ = ASM_MODULE_ID_VOL_CTRL;
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN;
				*updt_params++ = SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				*updt_params++ = (vol->left_gain << 16) |
						 vol->right_gain;
				params_length += COMMAND_PAYLOAD_SZ +
						SOFT_VOLUME_GAIN_2CH_PARAM_SZ;
				if (instance == SOFT_VOLUME_INSTANCE_2)
					*updt_params++ =
							ASM_MODULE_ID_VOL_CTRL2;
				else
					*updt_params++ = ASM_MODULE_ID_VOL_CTRL;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				*updt_params++ =
					ASM_PARAM_ID_VOL_CTRL_MASTER_GAIN;
				*updt_params++ =
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
<<<<<<< HEAD
				*updt_params++ =
					vol->master_gain;
=======
				*updt_params++ = vol->master_gain;
				params_length += COMMAND_PAYLOAD_SZ +
					SOFT_VOLUME_GAIN_MASTER_PARAM_SZ;
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
			}
			break;
		default:
			pr_err("%s: Invalid command id: %d to set config\n",
				__func__, command_id);
			break;
		}
	}
<<<<<<< HEAD
	if (params_length && (rc == 0))
=======
	if (params_length)
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
		q6asm_send_audio_effects_params(ac, params,
						params_length);
invalid_config:
	kfree(params);
	return rc;
}

int msm_audio_effects_volume_handler(struct audio_client *ac,
				     struct soft_volume_params *vol,
				     long *values)
{
	return __msm_audio_effects_volume_handler(ac, vol, values,
						  SOFT_VOLUME_INSTANCE_1);
}

int msm_audio_effects_volume_handler_v2(struct audio_client *ac,
					struct soft_volume_params *vol,
					long *values, int instance)
{
	return __msm_audio_effects_volume_handler(ac, vol, values, instance);
}
