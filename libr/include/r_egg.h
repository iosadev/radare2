#ifndef _INCLUDE_R_EGG_H_
#define _INCLUDE_R_EGG_H_

#include <r_asm.h>
#include <r_util.h>

typedef struct r_egg_t {
	RBuffer *src;
	RBuffer *buf;
	RBuffer *bin;
	RList *list;
	RAsm *rasm;
	struct r_egg_emit_t *emit;
	int endian;
	int bits;
} REgg;

typedef struct r_egg_emit_t {
	const char *arch;
	int size; /* in bytes.. 32bit arch is 4, 64bit is 8 .. */
	//const char *syscall_body;
	const char* (*regs)(REgg *egg, int idx);
	void (*call)(REgg *egg, const char *addr, int ptr);
	//void (*sc)(int num);
	void (*frame)(REgg *egg, int sz);
	char* (*syscall)(REgg *egg, int num);
	void (*trap)(REgg *egg);
	void (*frame_end)(REgg *egg, int sz, int ctx);
	void (*comment)(REgg *egg, const char *fmt, ...);
	void (*push_arg)(REgg *egg, int xs, int num, const char *str);
	void (*set_string)(REgg *egg, const char *dstvar, const char *str, int j);
	void (*equ)(REgg *egg, const char *key, const char *value);
	void (*get_result)(REgg *egg, const char *ocn);
	void (*restore_stack)(REgg *egg, int size);
	void (*syscall_args)(REgg *egg, int nargs);
	void (*get_var)(REgg *egg, int type, char *out, int idx);
	void (*while_end)(REgg *egg, const char *label);
	void (*load)(REgg *egg, const char *str, int sz);
	void (*load_ptr)(REgg *egg, const char *str);
	void (*branch)(REgg *egg, char *b, char *g, char *e, char *n, int sz, const char *dst);
	void (*mathop)(REgg *egg, int ch, int sz, int type, const char *eq, const char *p);
	void (*get_while_end)(REgg *egg, char *out, const char *ctxpush, const char *label);
} REggEmit;

typedef struct r_egg_lang_t {
	int nsyscalls;
	int nargs;
	int docall;
} REggLang;

#ifdef R_API
R_API REgg *r_egg_new ();
R_API char *r_egg_to_string (REgg *egg);
R_API void r_egg_free (REgg *egg);
R_API void r_egg_reset (REgg *egg);
R_API int r_egg_setup(REgg *egg, const char *arch, int bits, int endian, const char *os);
R_API int r_egg_include(REgg *egg, const char *file, int format);
R_API void r_egg_syscall(REgg *egg, const char *arg, ...);
R_API void r_egg_alloc(REgg *egg, int n);
R_API void r_egg_label(REgg *egg, const char *name);
R_API void r_egg_raw(REgg *egg, const ut8 *b, int len);
R_API void r_egg_if(REgg *egg, const char *reg, char cmp, int v);
R_API void r_egg_printf(REgg *egg, const char *fmt, ...);
R_API int r_egg_compile(REgg *egg);
R_API RBuffer *r_egg_get_bin(REgg *egg);
//R_API int r_egg_dump (REgg *egg, const char *file) { }
R_API char *r_egg_get_source(REgg *egg);
R_API RBuffer *r_egg_get_bin(REgg *egg);
R_API char *r_egg_get_assembly(REgg *egg);

/* lang.c */
R_API char *r_egg_mkvar(REgg *egg, char *out, const char *_str, int delta);
R_API int r_egg_lang_parsechar(REgg *egg, char c);
#endif
#endif
