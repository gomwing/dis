﻿/* $Id: etc.h,v 1.1 1996/10/24 04:27:44 ryo freeze $
 *
 *	ソースコードジェネレータ
 *	雑用ルーチンヘッダファイル
 *	Copyright (C) 1989,1990 K.Abe
 *	All rights reserved.
 *	Copyright (C) 1997-2010 Tachibana
 *
 */

#ifndef	ETC_H
#define	ETC_H

#include <stdio.h>		/* for __byte_swap_* */
#include <stdint.h>

#include "global.h"


#if defined (__mc68000__) && !defined (__BIG_ENDIAN__)
#define __BIG_ENDIAN__ 1
#endif

#ifndef	__LIBC__
extern int		eprintf (const char*, ...);
#endif
extern int		eputc (int);

extern ULONG		atox (char*);
extern void		err (const char*, ...) /*__attribute__ ((noreturn))*/;
extern void*		Malloc (ULONG);
extern void*		Realloc (void*, int);

#ifdef MFREE_NO_MACRO
extern void		Mfree (void*);
#else
#include	<stdlib.h>
#define Mfree(ptr)	free (ptr)
#endif

#ifndef HAVE_STRUPR
char* strupr (char* str);
#endif

USEOPTION   option_q;
#define charout(a) { if (!option_q) eputc (a); }
//#define charout(a) if (!option_q) eputc(a);


#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifdef __GNUC__
#define min(a, b)	({ typeof (a) _a = (a), _b = (b); (_a < _b) ? _a : _b; })
#define max(a, b)	({ typeof (a) _a = (a), _b = (b); (_a > _b) ? _a : _b; })
#else
//extern ULONG	min (ULONG, ULONG);
//extern ULONG	max (ULONG, ULONG);
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#endif


#ifdef HAVE_JCTYPE_H
#include <jctype.h>
#else

#define iskanji(c)	((0x81 <= (c) && (c) <= 0x9f) || \
			 (0xe0 <= (c) && (c) <= 0xfc))
#define iskanji2(c)	((0x40 <= (c) && (c) <= 0xfc) && (c) != 0x7f)
#define isprkana(c)	((0x20 <= (c) && (c) <= 0x7e) || \
			 (0xa1 <= (c) && (c) <= 0xdf))

#endif /* !HAVE_JCTYPE_H */


#ifdef __BIG_ENDIAN__
#define peekw(p) (*(uint16_t *) (p))
#define peekl(p) (*(uint32_t *) (p))

#else /* __LITTLE_ENDIAN__ */

#ifdef __byte_swap_word
#define peekw(p) ((uint16_t) __byte_swap_word (*(uint16_t*) (p)))
#else
static INLINE uint16_t
peekw (const void* ptr)
{
	const uint8_t* p = ptr;

	return (p[0] << 8) + p[1];
}
#endif

#ifdef __byte_swap_long
#define peekl(p) ((uint32_t) __byte_swap_long (*(uint32_t*) (p)))
#else
static INLINE uint32_t
peekl (const void* ptr)
{
	const uint8_t* p = ptr;

	return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
}
#endif

#endif /* !__BIG_ENDIAN__ */

#endif	/* ETC_H */
