include $(BOARD_DIR)/firmware/firmware.mk

BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# PROLT-V2: STM32F407VGT6 (U201) on board, no Hellen module

# no electronic throttle and no transmission control hardware
DDEFS += -DEFI_ELECTRONIC_THROTTLE_BODY=FALSE
DDEFS += -DEFI_TCU=FALSE

# no knock circuit on PROLT-V2 (PA2 IN_KNOCK is not routed): software knock stays compiled in
# like on PRO-MS6 (the STM32 ADC driver needs ADC3 / knock_config.h) and is hidden in TunerStudio

# critical LED: D205 red on PD4 (default PD14 is not used on this board)
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::D4

# status LEDs are active-low: +3.3V -> RN201 -> LED -> MCU pin
DDEFS += -DLED_PIN_MODE=OM_INVERTED

# EGT chip
#un-comment to enable
#DDEFS += -DEFI_MAX_31855=TRUE
