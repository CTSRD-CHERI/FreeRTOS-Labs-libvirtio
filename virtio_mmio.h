/*-
 * Copyright (c) 2014 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef	_VIRTIO_MMIO_H
#define	_VIRTIO_MMIO_H

#ifdef VIRTIO_USE_IOCAPS
#include "iocap/librust_caps_c.h"
#endif

#define	VIRTIO_MMIO_MAGIC_VALUE		0x000
#define	VIRTIO_MMIO_VERSION		0x004
#define	VIRTIO_MMIO_DEVICE_ID		0x008
#define	VIRTIO_MMIO_VENDOR_ID		0x00c
#define	VIRTIO_MMIO_HOST_FEATURES	0x010
#define	VIRTIO_MMIO_HOST_FEATURES_SEL	0x014
#define	VIRTIO_MMIO_GUEST_FEATURES	0x020
#define	VIRTIO_MMIO_GUEST_FEATURES_SEL	0x024
#define	VIRTIO_MMIO_GUEST_PAGE_SIZE	0x028	/* version 1 only */
#define	VIRTIO_MMIO_QUEUE_SEL		0x030
#define	VIRTIO_MMIO_QUEUE_NUM_MAX	0x034
#define	VIRTIO_MMIO_QUEUE_NUM		0x038
#define	VIRTIO_MMIO_QUEUE_ALIGN		0x03c	/* version 1 only */
#define	VIRTIO_MMIO_QUEUE_PFN		0x040	/* version 1 only */
#define	VIRTIO_MMIO_QUEUE_READY		0x044	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_NOTIFY	0x050
#define	VIRTIO_MMIO_INTERRUPT_STATUS	0x060
#define	VIRTIO_MMIO_INTERRUPT_ACK	0x064
#define	VIRTIO_MMIO_STATUS		0x070
#define	VIRTIO_MMIO_QUEUE_DESC_LOW	0x080	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_DESC_HIGH	0x084	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_AVAIL_LOW	0x090	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_AVAIL_HIGH	0x094	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_USED_LOW	0x0a0	/* requires version 2 */
#define	VIRTIO_MMIO_QUEUE_USED_HIGH	0x0a4	/* requires version 2 */
/** IOCap-specific start! */
#define VIRTIO_MMIO_QUEUE_IOCAP_TXT_WORD0   0x0b0
#define VIRTIO_MMIO_QUEUE_IOCAP_TXT_WORD1   0x0b4
#define VIRTIO_MMIO_QUEUE_IOCAP_TXT_WORD2   0x0b8
#define VIRTIO_MMIO_QUEUE_IOCAP_TXT_WORD3   0x0bc
#define VIRTIO_MMIO_QUEUE_IOCAP_SIG_WORD0   0x0c0
#define VIRTIO_MMIO_QUEUE_IOCAP_SIG_WORD1   0x0c4
#define VIRTIO_MMIO_QUEUE_IOCAP_SIG_WORD2   0x0c8
#define VIRTIO_MMIO_QUEUE_IOCAP_SIG_WORD3   0x0cc
/** IOCap-specific end! */
#define	VIRTIO_MMIO_CONFIG_GENERATION	0x100	/* requires version 2 */
#define	VIRTIO_MMIO_CONFIG		0x100
#define	VIRTIO_MMIO_INT_VRING		(1 << 0)
#define	VIRTIO_MMIO_INT_CONFIG		(1 << 1)
#define	VIRTIO_MMIO_VRING_ALIGN		4096


static inline uint64_t virtio_mmio_read64(uint32_t *base, size_t offset)
{
	return *((volatile uint64_t*) (((uintptr_t) base) + offset));
}

static inline uint32_t virtio_mmio_read32(uint32_t *base, size_t offset)
{
	return *((volatile uint32_t*) (((uintptr_t) base) + offset));
}

static inline uint16_t virtio_mmio_read16(uint32_t *base, size_t offset)
{
	return *((volatile uint16_t*) (((uintptr_t) base) + offset));
}

static inline uint8_t virtio_mmio_read8(uint32_t *base, size_t offset)
{
	return *((volatile uint8_t*) (((uintptr_t) base) + offset));
}

static inline void virtio_mmio_write32(uint32_t *base, size_t offset, uint32_t val)
{
	*((volatile uint32_t*) (((uintptr_t) base) + offset)) = val;
}

static inline void virtio_mmio_write64(uint32_t *base, size_t offset, uint64_t val)
{
	*((volatile uint64_t*) (((uintptr_t) base) + offset)) = val;
}

#ifdef VIRTIO_USE_IOCAPS
static inline void virtio_mmio_write128_group32(uint32_t *base, size_t offset, CCapU128 val)
{
	virtio_mmio_write32(
		base, offset,
		(((uint32_t)val[0]) << 0) |
		(((uint32_t)val[1]) << 8) |
		(((uint32_t)val[2]) << 16) |
		(((uint32_t)val[3]) << 24)
	);
	virtio_mmio_write32(
		base, offset + 4,
		(((uint32_t)val[4]) << 0) |
		(((uint32_t)val[5]) << 8) |
		(((uint32_t)val[6]) << 16) |
		(((uint32_t)val[7]) << 24)
	);
	virtio_mmio_write32(
		base, offset + 8,
		(((uint32_t)val[8]) << 0) |
		(((uint32_t)val[9]) << 8) |
		(((uint32_t)val[10]) << 16) |
		(((uint32_t)val[11]) << 24)
	);
	virtio_mmio_write32(
		base, offset + 12,
		(((uint32_t)val[12]) << 0) |
		(((uint32_t)val[13]) << 8) |
		(((uint32_t)val[14]) << 16) |
		(((uint32_t)val[15]) << 24)
	);
}

static inline void virtio_mmio_write128_group64(uint32_t *base, size_t offset, CCapU128 val)
{
	virtio_mmio_write64(
		base, offset,
		(((uint64_t)val[0]) << 0) |
		(((uint64_t)val[1]) << 8) |
		(((uint64_t)val[2]) << 16) |
		(((uint64_t)val[3]) << 24) |
		(((uint64_t)val[4]) << 32) |
		(((uint64_t)val[5]) << 40) |
		(((uint64_t)val[6]) << 48) |
		(((uint64_t)val[7]) << 56)
	);
	virtio_mmio_write64(
		base, offset + 8,
		(((uint64_t)val[8]) << 0) |
		(((uint64_t)val[9]) << 8) |
		(((uint64_t)val[10]) << 16) |
		(((uint64_t)val[11]) << 24) |
		(((uint64_t)val[12]) << 32) |
		(((uint64_t)val[13]) << 40) |
		(((uint64_t)val[14]) << 48) |
		(((uint64_t)val[15]) << 56)
	);
}
#endif /* VIRTIO_USE_IOCAPS */
#endif /* _VIRTIO_MMIO_H */
