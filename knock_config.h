/**
 * @file knock_config.h
 *
 * Required by the STM32 ADC driver even though PROLT-V2 has no knock circuit
 * (EFI_SOFTWARE_KNOCK=FALSE in board.mk). The schematic reserves PA2 (IN_KNOCK)
 * for a future knock input, but it is not routed on REV B.
 */

#pragma once

#define KNOCK_ADC ADCD3

// knock 1 - pin PA2 (ADC123_IN2), not routed on REV B
#define KNOCK_ADC_CH1 ADC_CHANNEL_IN2
#define KNOCK_PIN_CH1 Gpio::A2

// Sample rate & time - depends on the exact MCU
#define KNOCK_SAMPLE_TIME ADC_SAMPLE_84
#define KNOCK_SAMPLE_RATE (STM32_PCLK2 / (4 * (84 + 12)))
