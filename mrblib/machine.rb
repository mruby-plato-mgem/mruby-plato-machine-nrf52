#
# PlatoPeach::Machine class
#

MRUBY_PLATFORM = 'nRF52'

# register nRF52 device
Plato::Machine.register_device(PlatoNRF52::Machine)
