/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : ClockWatch
Version : 
Date    : 30.06.2016
Author  : 
Company : 
Comments: 


Chip type               : ATxmega32A4
Program type            : Application
AVR Core Clock frequency: 32,000000 MHz
Memory model            : Small
Data Stack size         : 1024
*******************************************************/

// I/O Registers definitions
#include <io.h>

// System Clocks initialization
void system_clocks_init(void)
{
unsigned char n,s;

// Optimize for speed
#pragma optsize- 
// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// Internal 32 MHz RC oscillator initialization
// Enable the internal 32 MHz RC oscillator
OSC.CTRL|=OSC_RC32MEN_bm;

// System Clock prescaler A division factor: 1
// System Clock prescalers B & C division factors: B:1, C:1
// ClkPer4: 32000,000 kHz
// ClkPer2: 32000,000 kHz
// ClkPer:  32000,000 kHz
// ClkCPU:  32000,000 kHz
n=(CLK.PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm | CLK_PSBCDIV0_bm))) |
	CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
CCP=CCP_IOREG_gc;
CLK.PSCTRL=n;

// Disable the auto-calibration of the internal 32 MHz RC oscillator
DFLLRC32M.CTRL&= ~DFLL_ENABLE_bm;

// Wait for the internal 32 MHz RC oscillator to stabilize
while ((OSC.STATUS & OSC_RC32MRDY_bm)==0);

// Select the system clock source: 32 MHz Internal RC Osc.
n=(CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC32M_gc;
CCP=CCP_IOREG_gc;
CLK.CTRL=n;

// Disable the unused oscillators: 2 MHz, internal 32 kHz, external clock/crystal oscillator, PLL
OSC.CTRL&= ~(OSC_RC2MEN_bm | OSC_RC32KEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm);

// ClkPer output disabled
PORTCFG.CLKEVOUT&= ~PORTCFG_CLKOUT_gm;
// Restore interrupts enabled/disabled state
SREG=s;
// Restore optimization for size if needed
#pragma optsize_default
}

// Ports initialization
void ports_init(void)
{
// PORTA initialization
// OUT register
PORTA.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Output
PORTA.DIR=0x80;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTA.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTA.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTA.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTA.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTA.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTA.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTA.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTA.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTA.INTCTRL=(PORTA.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTA.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTA.INT1MASK=0x00;

// PORTB initialization
// OUT register
PORTB.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
PORTB.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTB.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTB.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTB.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTB.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTB.INTCTRL=(PORTB.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
PORTB.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
PORTB.INT1MASK=0x00;

// PORTC initialization
// OUT register
PORTC.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTC.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTC.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTC.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTC.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTC.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTC.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTC.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTC.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTC.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTC.INTCTRL=(PORTC.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTC.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTC.INT1MASK=0x00;

// PORTD initialization
// OUT register
PORTD.OUT=0x00;
// Pin0: Output
// Pin1: Output
// Pin2: Output
// Pin3: Output
// Pin4: Output
// Pin5: Output
// Pin6: Output
// Pin7: Output
PORTD.DIR=0xFF;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTD.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTD.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTD.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTD.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTD.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTD.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTD.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTD.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTD.INTCTRL=(PORTD.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTD.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTD.INT1MASK=0x00;

// PORTE initialization
// OUT register
PORTE.OUT=0x00;
// Pin0: Output
// Pin1: Output
// Pin2: Output
// Pin3: Output
PORTE.DIR=0x0F;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTE.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTE.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTE.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTE.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTE.INTCTRL=(PORTE.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
PORTE.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
PORTE.INT1MASK=0x00;

// PORTR initialization
// OUT register
PORTR.OUT=0x00;
// Pin0: Input
// Pin1: Input
PORTR.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTR.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTR.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTR.INTCTRL=(PORTR.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
PORTR.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
PORTR.INT1MASK=0x00;
}

// Virtual Ports initialization
void vports_init(void)
{
// PORTA mapped to VPORT0
// PORTB mapped to VPORT1
PORTCFG.VPCTRLA=PORTCFG_VP1MAP_PORTB_gc | PORTCFG_VP0MAP_PORTA_gc;
// PORTC mapped to VPORT2
// PORTD mapped to VPORT3
PORTCFG.VPCTRLB=PORTCFG_VP3MAP_PORTD_gc | PORTCFG_VP2MAP_PORTC_gc;
}

// Disable a Timer/Counter type TC0
void tc0_disable(TC0_t *ptc)
{
// Timer/Counter off
ptc->CTRLA=TC_CLKSEL_OFF_gc;
// Issue a reset command
ptc->CTRLFSET=TC_CMD_RESET_gc;
}

// Timer/Counter TCC0 initialization
void tcc0_init(void)
{
unsigned char s;
unsigned char n;

// Note: The correct PORTC direction for the Compare Channels
// outputs is configured in the ports_init function.

// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// Disable and reset the timer/counter just to be sure
tc0_disable(&TCC0);
// Clock source: ClkPer/64
TCC0.CTRLA=TC_CLKSEL_DIV64_gc;
// Mode: Normal Operation, Overflow Int./Event on TOP
// Compare/Capture on channel A: Off
// Compare/Capture on channel B: Off
// Compare/Capture on channel C: Off
// Compare/Capture on channel D: Off
TCC0.CTRLB=(0<<TC0_CCDEN_bp) | (0<<TC0_CCCEN_bp) | (0<<TC0_CCBEN_bp) | (0<<TC0_CCAEN_bp) |
	TC_WGMODE_NORMAL_gc;
// Capture event source: None
// Capture event action: None
TCC0.CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

// Set Timer/Counter in Normal mode
TCC0.CTRLE=(0<<TC0_BYTEM_bp);

// Overflow interrupt: Medium Level
// Error interrupt: Disabled
TCC0.INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_MED_gc;

// Compare/Capture channel A interrupt: Disabled
// Compare/Capture channel B interrupt: Disabled
// Compare/Capture channel C interrupt: Disabled
// Compare/Capture channel D interrupt: Disabled
TCC0.INTCTRLB=TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

// High resolution extension: Off
HIRESC.CTRLA&= ~HIRES_HREN0_bm;

// Advanced Waveform Extension initialization
// Optimize for speed
#pragma optsize- 
// Disable locking the AWEX configuration registers just to be sure
n=MCU.AWEXLOCK & (~MCU_AWEXCLOCK_bm);
CCP=CCP_IOREG_gc;
MCU.AWEXLOCK=n;
// Restore optimization for size if needed
#pragma optsize_default

// Pattern generation: Off
// Dead time insertion: Off
AWEXC.CTRL=(0<<AWEX_PGM_bp) | (0<<AWEX_CWCM_bp) | (0<<AWEX_DTICCDEN_bp) | (0<<AWEX_DTICCCEN_bp) | 
	(0<<AWEX_DTICCBEN_bp) | (0<<AWEX_DTICCAEN_bp);

// Fault protection initialization
// Fault detection on OCD Break detection: On
// Fault detection restart mode: Latched Mode
// Fault detection action: None (Fault protection disabled)
AWEXC.FDCTRL=(AWEXC.FDCTRL & (~(AWEX_FDDBD_bm | AWEX_FDMODE_bm | AWEX_FDACT_gm))) |
	(0<<AWEX_FDDBD_bp) | (0<<AWEX_FDMODE_bp) | AWEX_FDACT_NONE_gc;
// Fault detect events: 
// Event channel 0: Off
// Event channel 1: Off
// Event channel 2: Off
// Event channel 3: Off
// Event channel 4: Off
// Event channel 5: Off
// Event channel 6: Off
// Event channel 7: Off
AWEXC.FDEMASK=0b00000000;
// Make sure the fault detect flag is cleared
AWEXC.STATUS|=AWEXC.STATUS & AWEX_FDF_bm;

// Clear the interrupt flags
TCC0.INTFLAGS=TCC0.INTFLAGS;
// Set Counter register
TCC0.CNT=0x0000;
// Set Period register
TCC0.PER=0x0000;
// Set channel A Compare/Capture register
TCC0.CCA=0x0000;
// Set channel B Compare/Capture register
TCC0.CCB=0x0000;
// Set channel C Compare/Capture register
TCC0.CCC=0x0000;
// Set channel D Compare/Capture register
TCC0.CCD=0x0000;

// Restore interrupts enabled/disabled state
SREG=s;
}

// RTC initialization
void rtcxm_init(void)
{
unsigned char s;

// RTC clock source: 1024 Hz from internal 32 kHz RC Oscillator
// Internal 32 kHz RC oscillator initialization
// Enable the internal 32 kHz RC oscillator
OSC.CTRL|=OSC_RC32KEN_bm;
// Wait for the internal 32 kHz RC oscillator to stabilize
while ((OSC.STATUS & OSC_RC32KRDY_bm)==0);

// Select the clock source and enable the RTC clock
CLK.RTCCTRL=(CLK.RTCCTRL & (~CLK_RTCSRC_gm)) | CLK_RTCSRC_RCOSC_gc | CLK_RTCEN_bm;
// Make sure that the RTC is stopped before initializing it
RTC.CTRL=RTC_PRESCALER_OFF_gc;

// Optimize for speed
#pragma optsize- 
// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// Wait until the RTC is not busy
while (RTC.STATUS & RTC_SYNCBUSY_bm);
// Set the RTC period register
RTC.PER=0x0400;
// Set the RTC count register
RTC.CNT=0x0000;
// Set the RTC compare register
RTC.COMP=0x0000;

// Restore interrupts enabled/disabled state
SREG=s;
// Restore optimization for size if needed
#pragma optsize_default

// Set the clock prescaler: RTC Clock/1
// and start the RTC
RTC.CTRL=RTC_PRESCALER_DIV1_gc;

// RTC overflow interrupt: Medium Level
// RTC compare interrupt: Disabled
RTC.INTCTRL=RTC_OVFINTLVL_MED_gc | RTC_COMPINTLVL_OFF_gc;
}




void init_main(void)
{
unsigned char n;

// Interrupt system initialization
// Optimize for speed
#pragma optsize- 
// Make sure the interrupts are disabled
#asm("cli")
// Low level interrupt: Off
// Round-robin scheduling for low level interrupt: Off
// Medium level interrupt: On
// High level interrupt: Off
// The interrupt vectors will be placed at the start of the Application FLASH section
n=(PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) |
	PMIC_MEDLVLEN_bm;
CCP=CCP_IOREG_gc;
PMIC.CTRL=n;
// Set the default priority for round-robin scheduling
PMIC.INTPRI=0x00;
// Restore optimization for size if needed
#pragma optsize_default

// System clocks initialization
system_clocks_init();

// Ports initialization
ports_init();

// Virtual Ports initialization
vports_init();

// Timer/Counter TCC0 initialization
tcc0_init();

// RTC initialization
rtcxm_init();

// Globally enable interrupts
#asm("sei")

}
