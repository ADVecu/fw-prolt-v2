#include "pch.h"
#include "board_overrides.h"
#include <array>

// PROLT-V2 outputs for the HW QC / bench test, in connector order
static std::array<Gpio, 12> OUTPUTS = {
	Gpio::D3,	// E1 INJ1
	Gpio::A9,	// D1 INJ2
	Gpio::D11,	// C1 INJ3
	Gpio::D10,	// B1 INJ4
	Gpio::C13,	// A1 IGN1
	Gpio::E5,	// A2 IGN2
	Gpio::E4,	// A3 IGN3 (JP101)
	Gpio::D13,	// G3 LS Out 1
	Gpio::C6,	// G4 LS Out 2
	Gpio::A8,	// A3 LS Out 3 (JP101)
	Gpio::D15,	// D4 LS Out 4
	Gpio::D2,	// A4 Tach
};

// release_20260812 provides the custom_board_getMeta* hooks in board_overrides.h;
// upstream owns getBoardMeta*(), so defining those here would be a duplicate symbol.
static int boardGetMetaOutputsCount() {
	return static_cast<int>(OUTPUTS.size());
}

static Gpio* boardGetMetaOutputs() {
	return OUTPUTS.data();
}

static int boardGetMetaDcOutputsCount() {
	return 0;	// no DC motor (ETB) outputs on PROLT-V2
}

void setupBoardHardwareTestOverrides() {
	custom_board_getMetaOutputsCount = boardGetMetaOutputsCount;
	custom_board_getMetaOutputs = boardGetMetaOutputs;
	custom_board_getMetaDcOutputsCount = boardGetMetaDcOutputsCount;
}
