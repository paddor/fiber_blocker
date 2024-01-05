#include "fiber_blocker.h"

VALUE rb_mFiberBlocker;


static VALUE
hello(void)
{
  return rb_str_new_cstr("Hello from FiberBlocker");
}

static VALUE
current_fiber_scheduler(VALUE _self)
{
  VALUE scheduler = rb_fiber_scheduler_current();

  return scheduler;
}

static VALUE
block_fiber(VALUE _self, VALUE blocker, VALUE timeout)
{
  VALUE result = Qnil;
  VALUE scheduler = rb_fiber_scheduler_current();

  if (RTEST(scheduler)) {
    printf("ext: blocking fiber\n");
    result = rb_fiber_scheduler_block(scheduler, blocker, timeout);
  } else {
    printf("no rb_fiber_scheduler_current()\n");
  }

  return result;
}

static VALUE
block_fiber2(VALUE _self, VALUE scheduler, VALUE blocker, VALUE timeout)
{
  VALUE result = Qnil;
  VALUE scheduler2 = rb_fiber_scheduler_current();

  VALUE logline = rb_sprintf("passed scheduler = %+"PRIsVALUE"\n", scheduler);
  rb_io_puts(1, &logline, rb_stdout);

  if (RTEST(scheduler)) {
    printf("ext: blocking fiber\n");
    result = rb_fiber_scheduler_block(scheduler, blocker, timeout);
  } else {
    printf("no rb_fiber_scheduler_current()\n");
  }

  return result;
}

static VALUE
unblock_fiber(VALUE _self, VALUE scheduler, VALUE blocker, VALUE fiber)
{
  printf("ext: unblocking fiber\n");
  VALUE result = rb_fiber_scheduler_unblock(scheduler, blocker, fiber);
  return result;
}

RUBY_FUNC_EXPORTED void
Init_fiber_blocker(void)
{
  rb_mFiberBlocker = rb_define_module("FiberBlocker");
  rb_define_singleton_method(rb_mFiberBlocker, "hello", hello, 0);
  rb_define_singleton_method(rb_mFiberBlocker, "current_fiber_scheduler", current_fiber_scheduler, 0);
  rb_define_singleton_method(rb_mFiberBlocker, "block_fiber", block_fiber, 2);
  rb_define_singleton_method(rb_mFiberBlocker, "block_fiber2", block_fiber2, 3);
  rb_define_singleton_method(rb_mFiberBlocker, "unblock_fiber", unblock_fiber, 3);
}
