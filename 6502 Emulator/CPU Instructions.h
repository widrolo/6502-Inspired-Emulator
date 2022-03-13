#pragma once

static constexpr Byte INST_LDA_INTERM = 0xA9; // Load A Intermediate
static constexpr Byte INST_LDX_INTERM = 0xA2; // Load X Intermediate
static constexpr Byte INST_LDY_INTERM = 0xA0; // Load Y Intermediate
static constexpr Byte INST_LDA_ABS = 0xAD; // Load A Absolute
static constexpr Byte INST_LDX_ABS = 0xAE; // Load X Absolute
static constexpr Byte INST_LDY_ABS = 0xAC; // Load Y Absolute
static constexpr Byte INST_LDA_ZP = 0xA5; // Load A from Zero Page
static constexpr Byte INST_LDX_ZP = 0xA6; // Load X from Zero Page
static constexpr Byte INST_LDY_ZP = 0xA4; // Load Y from Zero Page
static constexpr Byte INST_STA_ABS = 0x8D; // Store A Absolute
static constexpr Byte INST_STX_ABS = 0x8E; // Store X Absolute
static constexpr Byte INST_STY_ABS = 0x8C; // Store Y Absolute
static constexpr Byte INST_STA_ZP = 0x85; // Store A into Zero Page
static constexpr Byte INST_STX_ZP = 0x86; // Store X into Zero Page
static constexpr Byte INST_STY_ZP = 0x84; // Store Y into Zero Page
static constexpr Byte INST_JSR = 0x20; // Jump To Subroutine
static constexpr Byte INST_RTS = 0x60; // Return from Subroutine
static constexpr Byte INST_JMP = 0x4C; // Jump
static constexpr Byte INST_ADD = 0x69; // Adds the Accumulator and a memory location
static constexpr Byte INST_SUB = 0xE9; // Subtracts a memory location from the Accumulator
static constexpr Byte INST_BEQ = 0xF0; // Branches if zero flag is set
static constexpr Byte INST_BNE = 0xD0; // Branches if zero flag is clear