/*
 *  Copyright (c) 2009 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

/*
 *  ======== Boot.xdc ========
 *
 */

package ti.catalog.arm.lm3init;

import xdc.rov.ViewInfo;

@Template("./Boot.xdt")

metaonly module Boot
{
    metaonly struct ModuleView {
        Bool    configureClock;
        Bool    sysClockDivEnable;
        String  sysClockDiv;
        Bool    pwmClockDivEnable;
        String  pwmClockDiv;
        String  xtal;
        String  oscSrc;
        Bool    pllBypass;
        Bool    pllOutEnable;
        Bool    ioscDisable;
        Bool    moscDisable;
        Bool    configureLdo;
        String  ldoOut;
    }

    @Facet
    metaonly config ViewInfo.Instance rovViewInfo = 
        ViewInfo.create({
            viewMap: [
            [
                'Module',
                {
                    type: ViewInfo.MODULE,
                    viewInitFxn: 'viewInitModule',
                    structName: 'ModuleView'
                }
            ],
            ]
        });
    

    enum SysDiv {
        SYSDIV_1     = 0x00000000,  /* System clock /1 */
        SYSDIV_2     = 0x00800000,  /* System clock /2 */
        SYSDIV_3     = 0x01000000,  /* System clock /3 */
        SYSDIV_4     = 0x01800000,  /* System clock /4 */
        SYSDIV_5     = 0x02000000,  /* System clock /5 */
        SYSDIV_6     = 0x02800000,  /* System clock /6 */
        SYSDIV_7     = 0x03000000,  /* System clock /7 */
        SYSDIV_8     = 0x03800000,  /* System clock /8 */
        SYSDIV_9     = 0x04000000,  /* System clock /9 */
        SYSDIV_10    = 0x04800000,  /* System clock /10 */
        SYSDIV_11    = 0x05000000,  /* System clock /11 */
        SYSDIV_12    = 0x05800000,  /* System clock /12 */
        SYSDIV_13    = 0x06000000,  /* System clock /13 */
        SYSDIV_14    = 0x06800000,  /* System clock /14 */
        SYSDIV_15    = 0x07000000,  /* System clock /15 */
        SYSDIV_16    = 0x07800000   /* System clock /16 */
    }

    enum PwmDiv {
        PWMDIV_2     = 0x00000000,  /* PWM clock /2 */
        PWMDIV_4     = 0x00020000,  /* PWM clock /4 */
        PWMDIV_8     = 0x00040000,  /* PWM clock /8 */
        PWMDIV_16    = 0x00060000,  /* PWM clock /16 */
        PWMDIV_32    = 0x00080000,  /* PWM clock /32 */
        PWMDIV_64    = 0x000A0000   /* PWM clock /64 */
    }

    enum XtalFreq {
        XTAL_1MHZ    = 0x00000000,  /* Using a 1MHz crystal */
        XTAL_1_84MHZ = 0x00000040,  /* Using a 1.8432MHz crystal */
        XTAL_2MHZ    = 0x00000080,  /* Using a 2MHz crystal */
        XTAL_2_45MHZ = 0x000000C0,  /* Using a 2.4576MHz crystal */
        XTAL_3_57MHZ = 0x00000100,  /* Using a 3.579545MHz crystal */
        XTAL_3_68MHZ = 0x00000140,  /* Using a 3.6864MHz crystal */
        XTAL_4MHZ    = 0x00000180,  /* Using a 4MHz crystal */
        XTAL_4_09MHZ = 0x000001C0,  /* Using a 4.096MHz crystal */
        XTAL_4_91MHZ = 0x00000200,  /* Using a 4.9152MHz crystal */
        XTAL_5MHZ    = 0x00000240,  /* Using a 5MHz crystal */
        XTAL_5_12MHZ = 0x00000280,  /* Using a 5.12MHz crystal */
        XTAL_6MHZ    = 0x000002C0,  /* Using a 6MHz crystal */
        XTAL_6_14MHZ = 0x00000300,  /* Using a 6.144MHz crystal */
        XTAL_7_37MHZ = 0x00000340,  /* Using a 7.3728MHz crystal */
        XTAL_8MHZ    = 0x00000380,  /* Using a 8MHz crystal */
        XTAL_8_19MHZ = 0x000003C0,  /* Using a 8.192MHz crystal */
        XTAL_10MHZ   = 0x00000400,  /* 10.0 MHz (USB) */
        XTAL_12MHZ   = 0x00000440,  /* 12.0 MHz (USB) */
        XTAL_12_2MHZ = 0x00000480,  /* 12.288 MHz */
        XTAL_13_5MHZ = 0x000004C0,  /* 13.56 MHz */
        XTAL_14_3MHZ = 0x00000500,  /* 14.31818 MHz */
        XTAL_16MHZ   = 0x00000540,  /* 16.0 MHz (USB) */
        XTAL_16_3MHZ = 0x00000580   /* 16.384 MHz */
    }

    enum OscSrc {
        OSCSRC_MAIN  = 0x00000000,  /* Use the main oscillator */
        OSCSRC_INT   = 0x00000010,  /* Use the internal oscillator */
        OSCSRC_INT4  = 0x00000020,  /* Use the internal oscillator / 4 */
        OSCSRC_30    = 0x00000030   /* 30 KHz internal oscillator */
    }

    enum LdoOut {
        LDOPCTL_2_55V    = 0x0000001F,  /* LDO output of 2.55V */
        LDOPCTL_2_60V    = 0x0000001E,  /* LDO output of 2.60V */
        LDOPCTL_2_65V    = 0x0000001D,  /* LDO output of 2.65V */
        LDOPCTL_2_70V    = 0x0000001C,  /* LDO output of 2.70V */
        LDOPCTL_2_75V    = 0x0000001B,  /* LDO output of 2.75V */
        LDOPCTL_2_25V    = 0x00000005,  /* LDO output of 2.25V */
        LDOPCTL_2_30V    = 0x00000004,  /* LDO output of 2.30V */
        LDOPCTL_2_35V    = 0x00000003,  /* LDO output of 2.35V */
        LDOPCTL_2_40V    = 0x00000002,  /* LDO output of 2.40V */
        LDOPCTL_2_45V    = 0x00000001,  /* LDO output of 2.45V */
        LDOPCTL_2_50V    = 0x00000000   /* LDO output of 2.50V */
    }

    /*! 
     *  Clock configuration flag, default is false.
     *
     *  Set to true to automatically configure the Clock.
     */
    config Bool configureClock = false;

    /*! SYS Clock Divide Enable, default is false */
    config Bool sysClockDivEnable = false;

    /*! SYS Clock Divisor */
    config SysDiv sysClockDiv = SYSDIV_1;

    /*! PWM Clock Divide Enable, default is false */
    config Bool pwmClockDivEnable = false;

    /*! PWM Clock Divisor */
    config PwmDiv pwmClockDiv = PWMDIV_2;

    /*! Crystal Value */
    config XtalFreq xtal = XTAL_1MHZ;

    /*! Oscillator Source */
    config OscSrc oscSrc = OSCSRC_MAIN;

    /*! PLL Bypass flag */
    config Bool pllBypass = false;

    /*! PLL Output Enable flag */
    config Bool pllOutEnable = false;

    /*! Internal Oscillator Disable flag */
    config Bool ioscDisable = false;

    /*! Main Oscillator Disable flag */
    config Bool moscDisable = false;

    /*! 
     *  LDO configuration flag, default is false.
     *
     *  Set to true to automatically configure the LDO.
     */
    config Bool configureLdo = false;

    /*! 
     *  LDO VADJ setting, default is 2.5V
     */
    config LdoOut ldoOut = LDOPCTL_2_50V;

    /*! 
     *  Code section that Boot module code is in.
     *
     *  To place this section into a memory segment yourself, add the 
     *  following to you configuration file: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadSegment = "yourBootCodeMemorySegment";
     *  @p
     *
     *  or to place the code at a specific address: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadAdress = yourBootCodeAddress;
     *  @p
     *
     */
    readonly config String bootCodeSection = ".bootCodeSection";

    /*! 
     *  @_nodoc
     *  computed RCC value based on settings
     */
    config UInt ulConfig;
};
/*
 *  @(#) ti.catalog.arm.lm3init; 1, 0, 0,28; 12-9-2009 17:20:12; /db/ztree/library/trees/platform/platform-k27x/src/
 */

