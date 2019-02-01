#include "mruby.h"
#include "mruby/string.h"

static mrb_value
mrb_delay(mrb_state *mrb, mrb_value self)
{
  mrb_int ms;
  mrb_get_args(mrb, "i", &ms);

  // wait for ms milliseconds
  // TODO
	
  return mrb_nil_value();
}

static mrb_value
mrb_delay_us(mrb_state *mrb, mrb_value self)
{
  mrb_int us;
  mrb_get_args(mrb, "i", &us);

  // wait for us microseconds
  // TODO

  return mrb_nil_value();
}

static mrb_value
mrb_millis(mrb_state *mrb, mrb_value self)
{
  mrb_int ms = 0;

  // get tick-count (milliseconds)
  // TODO

  return mrb_fixnum_value(ms);
}

// static mrb_value
// mrb_micros(mrb_state *mrb, mrb_value self)
// {
//   mrb_int us = 0;

//   // TODO: get tick-count (microseconds)

//   return mrb_fixnum_value(us);
// }

void
mrb_mruby_plato_machine_nrf52_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb_define_module(mrb, "PlatoNRF52");
  struct RClass *mach = mrb_define_class_under(mrb, mod, "Machine", mrb->object_class);

  mrb_define_class_method(mrb, mach, "delay",     mrb_delay,    MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mach, "delay_us",  mrb_delay_us, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mach, "millis",    mrb_millis,   MRB_ARGS_NONE());
  // mrb_define_class_method(mrb, mach, "micros",    mrb_micros,   MRB_ARGS_NONE());
}

void
mrb_mruby_plato_machine_nrf52_gem_final(mrb_state *mrb)
{
}
