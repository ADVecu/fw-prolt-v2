// PROLT-V2 - STM32F407VGT6 (U201) on board, 32-pin Molex connector (U101)
// Pin map traced pad by pad from PROLT-V2 Hardware/PROLT_V2.kicad_pcb (REV B).

#include "pch.h"
#include "board_overrides.h"
#include "defaults.h"

void setupBoardHardwareTestOverrides();

// D206 green = PD7, D207 blue = PE7, D208 yellow = PE8. D205 red = PD4 is the critical LED (board.mk)
Gpio getCommsLedPin() {
	return Gpio::E7;
}

Gpio getRunningLedPin() {
	return Gpio::D7;
}

Gpio getWarningLedPin() {
	return Gpio::E8;
}

static void setupInjectors() {
	// BTS3046 low-side drivers
	engineConfiguration->injectionPins[0] = Gpio::D3;	// E1 INJ1 (U601)
	engineConfiguration->injectionPins[1] = Gpio::A9;	// D1 INJ2 (U602)
	engineConfiguration->injectionPins[2] = Gpio::D11;	// C1 INJ3 (U605)
	engineConfiguration->injectionPins[3] = Gpio::D10;	// B1 INJ4 (U606)
}

static void setupIgnition() {
	// MIC4427 5V logic outputs for coils with built-in igniter
	engineConfiguration->ignitionPins[0] = Gpio::C13;	// A1 IGN1 (U701-A)
	engineConfiguration->ignitionPins[1] = Gpio::E5;	// A2 IGN2 (U701-B)
	// A3 is LS Out 3 (PA8, U604-1) by default; solder jumper JP101 can route IGN3 (PE4, U702) there instead
	engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
}

static void setupTrigger() {
	engineConfiguration->triggerInputPins[0] = Gpio::E1;	// F2/E2 VR+/VR- via MAX9924 (U801)
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;
	engineConfiguration->camInputs[0] = Gpio::E12;			// E3 CMP / Hall via 74LVC2G17 (U501)
}

static void setupAnalogInputs() {
	// MCP6004 buffer + 4.7k/4.7k divider: 0..5V sensor -> 0..2.5V at the ADC
	engineConfiguration->analogInputDividerCoefficient = 2.0f;
	engineConfiguration->adcVcc = 3.3f;	// REF3033 on VREF+

	engineConfiguration->tps1_1AdcChannel = EFI_ADC_4;		// PA4 <- C2 TPS
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_10;	// PC0 <- B4 MAP
	engineConfiguration->iat.adcChannel = EFI_ADC_12;		// PC2 <- B2 IAT
	engineConfiguration->clt.adcChannel = EFI_ADC_13;		// PC3 <- B3 CLT

	// Lua / aux inputs
	engineConfiguration->auxAnalogInputs[0] = EFI_ADC_0;	// PA0 <- C3 AUX1
	engineConfiguration->auxAnalogInputs[1] = EFI_ADC_1;	// PA1 <- C4 AUX2

	// R405 / R407 4.7k pull-up to +5VA
	setCommonNTCSensor(&engineConfiguration->clt, 4700);
	setCommonNTCSensor(&engineConfiguration->iat, 4700);

	setTPS1Calibration(100, 650);
}

static void setupOutputs() {
	engineConfiguration->tachOutputPin = Gpio::D2;		// A4 tach (Q602/Q601 high side)
	engineConfiguration->fanPin = Gpio::D13;			// G3 LS Out 1 (U603-1)
	engineConfiguration->fuelPumpPin = Gpio::C6;		// G4 LS Out 2 (U603-2)
	// Free for GPPWM / Lua: PA8 A3 LS Out 3 (default JP101 position), PD15 D4 LS Out 4 (U604-2)
}

static void setupCommunication() {
	engineConfiguration->canTxPin = Gpio::D1;	// U206 TJA1051T/3
	engineConfiguration->canRxPin = Gpio::D0;

	engineConfiguration->is_enabled_spi_1 = true;
	engineConfiguration->spi1sckPin = Gpio::B3;
	engineConfiguration->spi1misoPin = Gpio::B4;
	engineConfiguration->spi1mosiPin = Gpio::B5;
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_1;
	engineConfiguration->sdCardCsPin = Gpio::B6;
	engineConfiguration->isSdCardEnabled = true;

	// LPS22HB (U202), detected by lps25.cpp via WHO_AM_I 0xB1
	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
}

static void setupIdleStepper() {
	engineConfiguration->useRawOutputToDriveIdleStepper = true;
}

// Digital inputs D2 (PE13) and D3 (PE14) are left for clutch / Lua / VSS as the user needs.

static void customBoardDefaultConfiguration() {
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_3_4_2;
	// two coil outputs by default (A3 is a low-side output), so 4 cylinders run wasted spark
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->injectionMode = IM_BATCH;

	setupInjectors();
	setupIgnition();
	setupTrigger();
	setupAnalogInputs();
	setupOutputs();
	setupCommunication();
	setupIdleStepper();

	setCrankOperationMode();
}

// Hard-wired on the PCB, re-applied after every load and TunerStudio write.
// The matching TunerStudio fields are hidden in prepend.txt.
static void customBoardConfigOverrides() {
	// R308 33k / R309 6.8k from 12V key
	engineConfiguration->vbattDividerCoeff = (33.0f + 6.8f) / 6.8f;
	engineConfiguration->vbattAdcChannel = EFI_ADC_5;	// PA5

	// DRV8421 (U901) inputs -> H3 A+, H2 A-, H4 B+, H1 B-
	engineConfiguration->stepper_raw_output[0] = Gpio::B14;	// STEPPER_IN1 -> OUT1 A+
	engineConfiguration->stepper_raw_output[1] = Gpio::C7;	// STEPPER_IN2 -> OUT2 A-
	engineConfiguration->stepper_raw_output[2] = Gpio::C8;	// STEPPER_IN3 -> OUT3 B+
	engineConfiguration->stepper_raw_output[3] = Gpio::B15;	// STEPPER_IN4 -> OUT4 B-
}

void setup_custom_board_overrides() {
	setupBoardHardwareTestOverrides();

	custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
	custom_board_ConfigOverrides = customBoardConfigOverrides;
}
