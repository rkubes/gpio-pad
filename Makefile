#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WRKDIR = `pwd`
MAKE = make

all: gpio_pad_gpio_pad

gpio_pad_gpio_pad: 
	$(MAKE) -C gpio-pad all -f gpio-pad.cbp.mak

clean: clean_gpio_pad_gpio_pad

clean_gpio_pad_gpio_pad: 
	$(MAKE) -C gpio-pad clean -f gpio-pad.cbp.mak

.PHONY: clean_gpio_pad_gpio_pad

