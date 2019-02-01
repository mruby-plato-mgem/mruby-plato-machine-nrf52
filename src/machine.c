#include "stdint.h"
#include "stdbool.h"
#include "mruby.h"
#include "mruby/string.h"

#ifdef SOFTDEVICE_PRESENT
  #include "nordic_common.h"
  #include "nrf_delay.h"
  #include "nrf_log.h"
  #include "nrf_log_ctrl.h"
  #include "nrf_pwr_mgmt.h"
  #include "app_timer.h"

  APP_TIMER_DEF(_mruby_timer_id);
#endif


static volatile uint32_t _tick = 0;
static volatile bool _started = false;

#ifdef SOFTDEVICE_PRESENT
// timer event handler
static void mruby_timer_event_handler(void * p_context)
{
#ifdef SOFTDEVICE_PRESENT
  UNUSED_PARAMETER(p_context);
#endif
  _tick++;
}

// start timer (at first time)
static void start_timer(void)
{
  if (!_started) {
    uint32_t err_code;

    err_code = app_timer_create(&_mruby_timer_id, APP_TIMER_MODE_REPEATED, mruby_timer_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(_mruby_timer_id, APP_TIMER_TICKS(1.0), NULL);
    APP_ERROR_CHECK(err_code);

    _started = true;
  }
}
#endif

static mrb_value
mrb_delay(mrb_state *mrb, mrb_value self)
{
  mrb_int ms;
  uint32_t target = 0;
  mrb_get_args(mrb, "i", &ms);

#ifdef SOFTDEVICE_PRESENT
  start_timer();

  // wait for ms milliseconds
  target = _tick + (uint32_t)ms;
  while (target > _tick) {
    if (NRF_LOG_PROCESS() == false) {
      nrf_pwr_mgmt_run();
    }
  }
#endif

  return mrb_nil_value();
}

// static mrb_value
// mrb_delay_us(mrb_state *mrb, mrb_value self)
// {
//   mrb_int us;
//   mrb_get_args(mrb, "i", &us);

//   // wait for us microseconds
//   // TODO

//   return mrb_nil_value();
// }

static mrb_value
mrb_millis(mrb_state *mrb, mrb_value self)
{
  mrb_int ms = 0;
#ifdef SOFTDEVICE_PRESENT
  start_timer();
  ms = (mrb_int)_tick;
#endif
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
  // mrb_define_class_method(mrb, mach, "delay_us",  mrb_delay_us, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mach, "millis",    mrb_millis,   MRB_ARGS_NONE());
  // mrb_define_class_method(mrb, mach, "micros",    mrb_micros,   MRB_ARGS_NONE());
}

void
mrb_mruby_plato_machine_nrf52_gem_final(mrb_state *mrb)
{
}
