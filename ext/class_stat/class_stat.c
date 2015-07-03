
#include <ruby/ruby.h>

void rb_objspace_each_objects(
    int (*callback)(void *start, void *end, size_t stride, void *data),
    void *data);

struct class_stat_struct {
    VALUE klass_iclassnum; /* { klass => iclassnum } */
    VALUE klass_msize;     /* { klass => method_count_size } */
};

#define RICLASS_IS_ORIGIN  FL_USER5

static void
countup(VALUE h, VALUE k, int n)
{
    VALUE cn = INT2FIX(0);

    if (!RBASIC_CLASS(k)) {
	k = rb_sprintf("#<hidden_class:%p>", (void *)k);
    }

    cn = rb_hash_lookup2(h, k, cn);
    cn = INT2FIX(FIX2INT(cn) + n);
    rb_hash_aset(h, k, cn);
}

static int
msize(VALUE klass)
{
#if RUBY_API_VERSION_MAJOR == 2 && (RUBY_API_VERSION_MINOR == 2 || RUBY_API_VERSION_MINOR == 1)
struct method_table_wrapper {
    st_table *tbl;
    size_t serial;
};
#define RCLASS_M_TBL_WRAPPER(c) (RCLASS(c)->m_tbl_wrapper)
#define RCLASS_M_TBL(c) (RCLASS_M_TBL_WRAPPER(c) ? RCLASS_M_TBL_WRAPPER(c)->tbl : 0)
#else
#define RCLASS_M_TBL(c) (RCLASS(c)->m_tbl)
#endif

    if (RCLASS_M_TBL(klass)) {
	return RCLASS_M_TBL(klass)->num_entries;
    }
    else {
	return 0;
    }
}

static int
stat_i(void *vstart, void *vend, size_t stride, void *data)
{
    struct class_stat_struct *d = (struct class_stat_struct *)data;
    VALUE v = (VALUE)vstart;

    for (;v != (VALUE)vend; v += stride) {
	if (RBASIC(v)->flags) {
	    switch (BUILTIN_TYPE(v)) {
	      case T_ICLASS: {
		  VALUE klass = RBASIC_CLASS(v);
		  if (FL_TEST(v, RICLASS_IS_ORIGIN)) {
		      countup(d->klass_msize, klass, msize(klass));
		  }
		  else {
		      countup(d->klass_iclassnum, klass, 1);
		  }
		  break;
	      }
	      case T_CLASS:
	      case T_MODULE:
		countup(d->klass_msize, v, msize(v));
		break;
	    }
	}
    }
    return 0;
}

static VALUE
class_stat(VALUE self)
{
    struct class_stat_struct data;
    data.klass_iclassnum = rb_hash_new();
    data.klass_msize =rb_hash_new();

    rb_objspace_each_objects(stat_i, &data);

    return rb_ary_new_from_args(2, data.klass_iclassnum, data.klass_msize);
}

void
Init_class_stat(void)
{
    VALUE mod = rb_define_module("ClassStat");
    rb_define_singleton_method(mod, "stat", class_stat, 0);
}
