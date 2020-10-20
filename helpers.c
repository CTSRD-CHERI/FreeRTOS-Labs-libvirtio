/******************************************************************************
 * Copyright (c) 2020 Hesham Almatary
 * See LICENSE_CHERI for license details.
 *****************************************************************************/

/******************************************************************************
 * Copyright (c) 2007, 2012, 2013 IBM Corporation
 * All rights reserved.
 * This program and the accompanying materials
 * are made available under the terms of the BSD License
 * which accompanies this distribution, and is available at
 * http://www.opensource.org/licenses/bsd-license.php
 *
 * Contributors:
 *     IBM Corporation - initial implementation
 *****************************************************************************/
/*
 * All functions concerning interface to slof
 */

#include <stdio.h>
#include "helpers.h"

#include <FreeRTOS.h>

void *SLOF_alloc_mem(long size)
{
	return pvPortMalloc(size);
}

void *SLOF_alloc_mem_aligned(long size, long align)
{
	unsigned long addr = (unsigned long)SLOF_alloc_mem(size);

	if (addr % align) {
		SLOF_free_mem((void *)addr, size);
		addr = (unsigned long)SLOF_alloc_mem(size + align - 1);
		addr = addr + align - 1;
		addr = addr & ~(align - 1);
	}

	return (void *)addr;
}

void SLOF_free_mem(void *addr, long size)
{
	vPortFree(addr);
}

long SLOF_dma_map_in(void *virt, long size, int cacheable)
{
	// FIXME Empty as only used if IOMMU and VIRTIO_VERSION1 are supported
	(void) size;
	(void) cacheable;
	return virt;
}

void SLOF_dma_map_out(long phys, void *virt, long size)
{
	// FIXME Empty as only used if IOMMU and VIRTIO_VERSION1 are supported
	(void) size;
	(void) phys;
	(void) virt;
}
