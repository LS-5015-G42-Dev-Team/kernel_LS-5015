/*
<<<<<<< HEAD
 * Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
=======
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
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

#ifndef _MSM_AUDIO_EFFECTS_H
#define _MSM_AUDIO_EFFECTS_H

#include <sound/audio_effects.h>

<<<<<<< HEAD
#define MAX_PP_PARAMS_SZ   128

=======
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
bool msm_audio_effects_is_effmodule_supp_in_top(int effect_module,
						int topology);

int msm_audio_effects_reverb_handler(struct audio_client *ac,
				     struct reverb_params *reverb,
				     long *values);

int msm_audio_effects_bass_boost_handler(struct audio_client *ac,
					struct bass_boost_params *bass_boost,
					long *values);
<<<<<<< HEAD

int msm_audio_effects_pbe_handler(struct audio_client *ac,
					struct pbe_params *pbe,
					long *values);

=======
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
int msm_audio_effects_virtualizer_handler(struct audio_client *ac,
				struct virtualizer_params *virtualizer,
				long *values);

int msm_audio_effects_popless_eq_handler(struct audio_client *ac,
					 struct eq_params *eq,
					 long *values);

int msm_audio_effects_volume_handler(struct audio_client *ac,
				     struct soft_volume_params *vol,
				     long *values);

int msm_audio_effects_volume_handler_v2(struct audio_client *ac,
					struct soft_volume_params *vol,
					long *values, int instance);
#endif /*_MSM_AUDIO_EFFECTS_H*/
