/*
<<<<<<< HEAD
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
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

#ifndef _LINUX_MSM_AUDIO_ION_H
#define _LINUX_MSM_AUDIO_ION_H
<<<<<<< HEAD
#include <sound/q6asm-v2.h>
=======
#ifdef CONFIG_SND_SOC_QDSP6V2
#include <sound/q6asm-v2.h>
#else
#include <sound/q6asm.h>
#endif
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
#include <sound/pcm.h>
#include <linux/msm_ion.h>


int msm_audio_ion_alloc(const char *name, struct ion_client **client,
			struct ion_handle **handle, size_t bufsz,
			ion_phys_addr_t *paddr, size_t *pa_len, void **vaddr);

int msm_audio_ion_import(const char *name, struct ion_client **client,
			struct ion_handle **handle, int fd,
			unsigned long *ionflag, size_t bufsz,
			ion_phys_addr_t *paddr, size_t *pa_len, void **vaddr);
int msm_audio_ion_free(struct ion_client *client, struct ion_handle *handle);
int msm_audio_ion_mmap(struct audio_buffer *substream,
		       struct vm_area_struct *vma);

bool msm_audio_ion_is_smmu_available(void);
int msm_audio_ion_cache_operations(struct audio_buffer *abuff, int cache_op);

<<<<<<< HEAD
=======
#ifdef CONFIG_SND_SOC_QDSP6V2
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
struct ion_client *msm_audio_ion_client_create(const char *name);
void msm_audio_ion_client_destroy(struct ion_client *client);
int msm_audio_ion_import_legacy(const char *name, struct ion_client *client,
			struct ion_handle **handle, int fd,
			unsigned long *ionflag, size_t bufsz,
			ion_phys_addr_t *paddr, size_t *pa_len, void **vaddr);
int msm_audio_ion_free_legacy(struct ion_client *client,
			struct ion_handle *handle);
<<<<<<< HEAD
u32 populate_upper_32_bits(ion_phys_addr_t pa);
=======
#else
static struct ion_client *msm_audio_ion_client_create(const char *name)
{ return NULL; }
static void msm_audio_ion_client_destroy(struct ion_client *client)
{}
static int msm_audio_ion_import_legacy(const char *name,
			struct ion_client *client,
			struct ion_handle **handle, int fd,
			unsigned long *ionflag, size_t bufsz,
			ion_phys_addr_t *paddr, size_t *pa_len, void **vaddr)
{ return 0; }
static int msm_audio_ion_free_legacy(struct ion_client *client,
			struct ion_handle *handle)
{ return 0; }

#endif /* CONFIG_MSM_QDSP6V2_CODECS */
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
#endif /* _LINUX_MSM_AUDIO_ION_H */

