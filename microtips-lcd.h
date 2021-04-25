#ifndef MICROTIPS_LCD_H
#define MICROTIPS_LCD_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <string.h>
#include "../Common/GenericTypeDefs.h"
#include "../dspic-common.h"
#include "glcd-driver.h"
#include "glcd.h"

/*********************************************************************
* Overview: Horizontal and vertical display resolution
*                  (from the glass datasheet).
*********************************************************************/
#define DISP_HOR_RESOLUTION             240
#define DISP_VER_RESOLUTION             320
/*********************************************************************/
/*********************************************************************
* Overview: Image orientation (can be 0, 90, 180, 270 degrees).
*********************************************************************/
#define DISP_ORIENTATION                90

#if (DISP_HOR_RESOLUTION % 8) != 0
#error Horizontal resolution must be divisible by 8.
#endif

#if (DISP_ORIENTATION != 0) && (DISP_ORIENTATION != 180) && (DISP_ORIENTATION != 90) && (DISP_ORIENTATION != 270)
#error The display orientation selected is not supported. It can be only 0,90,180 or 270.
#endif

#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)
#define   GetMaxX() (DISP_VER_RESOLUTION-1)
#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)
#define   GetMaxX() (DISP_HOR_RESOLUTION-1)
#endif

#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)
#define   GetMaxY() (DISP_HOR_RESOLUTION-1)
#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)
#define   GetMaxY() (DISP_VER_RESOLUTION-1)
#endif


#define glcd_address(a,b) ((DWORD)(GetMaxX() + 1) * b + a) << 1

/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
#define BLACK               RGBColor(0,    0,      0)
#define BRIGHTBLUE          RGBColor(0,    0,      255)
#define BRIGHTGREEN         RGBColor(0,    255,    0)
#define BRIGHTCYAN          RGBColor(0,    255,    255)
#define BRIGHTRED           RGBColor(255,  0,      0)
#define BRIGHTMAGENTA       RGBColor(255,  0,      255)
#define BRIGHTYELLOW        RGBColor(255,  255,    0)
#define BLUE                RGBColor(0,    0,      128)
#define GREEN               RGBColor(0,    128,    0)
#define CYAN                RGBColor(0,    128,    128)
#define RED                 RGBColor(128,  0,      0)
#define MAGENTA             RGBColor(128,  0,      128)
#define BROWN               RGBColor(255,  128,    0)
#define PINK                RGBColor(255,  51,    204)
#define SGS_ORANGE          RGBColor(255,  90,    0)//RGBColor(255,  102,    0)
#define SGS_DARKGRAY        RGBColor(54,  54,    54)
#define SGS_GRAY            RGBColor(132,  134,   133)
#define SGS_LIGHTGRAY       RGBColor(188,  188,    188)
#define LIGHTGRAY           RGBColor(128,  128,    128)
#define DARKGRAY            RGBColor(64,   64,     64)
#define LIGHTBLUE           RGBColor(128,  128,    255)
#define DARKORANGE          RGBColor(150,  70,     0)
#define LIGTHORANGE         RGBColor(255,  140,    0)
#define LIGHTGREEN          RGBColor(128,  255,    128)
#define LIGHTCYAN           RGBColor(128,  255,    255)
#define LIGHTRED            RGBColor(255,  128,    128)
#define LIGHTMAGENTA        RGBColor(255,  128,    255)
#define YELLOW              RGBColor(255,  255,    128)
#define WHITE               RGBColor(255,  255,    255)

#define GRAY0               RGBColor(224,  224,    224)
#define GRAY1               RGBColor(192,  192,    192)
#define GRAY2               RGBColor(160,  160,    160)
#define GRAY3               RGBColor(128,  128,    128)
#define GRAY4               RGBColor(96,   96,     96)
#define GRAY5               RGBColor(64,   64,     64)
#define GRAY6               RGBColor(32,   32,     32)

// SSD1926 registers names definitions

#define   Debug_Code_Reg           0x00
#define   Read_Dummy_Reg           0x01
#define   Config_Readback_Reg        0x02
#define   Product_Code_Reg           0x03
#define   Mem_Clock_Config_Reg        0x04
#define   Memory_status_Reg           0x05

#define   LUT_Blue_Write_Data_Reg     0x08
#define   LUT_Green_Write_Data_Reg     0x09
#define   LUT_Red_Write_Data_Reg     0x0A
#define   LUT_Write_Address_Reg     0x0B
#define   LUT_Blue_Read_Data_Reg     0x0C
#define   LUT_Green_Read_Data_Reg     0x0D
#define   LUT_Red_Read_Data_Reg     0x0E
#define   LUT_Read_Address_Reg     0x0F

#define   Panel_Type_Reg           0x10
#define   MOD_Rate_Reg              0x11
#define   Horiz_Total_Reg1           0x12
#define   Horiz_Total_Reg0           0x13
#define   Horiz_Display_Period_Reg     0x14
#define   HDispPeriod_StartPos_Reg0     0x16
#define   HDispPeriod_StartPos_Reg1     0x17
#define   Vertical_Total_Reg0           0x18
#define   Vertical_Total_Reg1           0x19
#define   Vert_Display_Period_Reg0     0x1C
#define   Vert_Display_Period_Reg1     0x1D
#define   V_Disp_Per_StartPos_Reg0     0x1E
#define   V_Disp_Per_StartPos_Reg1     0x1F

#define   LLINE_Pulse_Width_Reg        0x20
#define   LLINE_PStart_Spix_Pos_Reg     0x21
#define   LLINE_PStart_Position_Reg0     0x22
#define   LLINE_PStart_Position_Reg1     0x23
#define   LFRAME_Pulse_Width_Reg     0x24
#define   LFRAME_PStart_Posit_Reg0     0x26
#define   LFRAME_PStart_Posit_Reg1     0x27

#define   DispP_Saturat_Control_Reg     0x2C
#define   DispP_Brightn_Control_Reg     0x2D
#define   DispP_Contrast_Control_Reg     0x2E
#define   DispP_Control_Reg           0x2F

#define   LFRAME_PStart_Offs_Reg0     0x30
#define   LFRAME_PStart_Offs_Reg1     0x31
#define   LFRAME_PStop_Offs_Reg0     0x34
#define   LFRAME_PStop_Offs_Reg1     0x35

#define   LSHIFT_Polarity_Reg        0x38

#define   RGB_sequence_Reg        0x42

#define   STNColorDepth_Control_Reg     0x45

#define   Interrupt_Status_Flag_Reg     0x48
#define   Interrupt_Enable_Reg        0x4A

#define   Dithering_FRC_Control_Reg     0x50

#define   Display_Mode_Reg           0x70
#define   Special_Effects_Reg        0x71

#define   MWindowDisp_StAddr_Reg0  0x74
#define   MWindowDisp_StAddr_Reg1  0x75
#define   MWindowDisp_StAddr_Reg2  0x76
#define   MWindLine_AddrOffs_Reg0     0x78
#define   MWindLine_AddrOffs_Reg1     0x79

#define   FWindDisp_StartAddr_Reg0     0x7C
#define   FWindDisp_StartAddr_Reg1     0x7D
#define   FWindDisp_StartAddr_Reg2     0x7E
#define   FWindLine_AddrOffs_Reg0     0x80
#define   FWindLine_AddrOffs_Reg1     0x81
#define   FWindow_StartPos_X_Reg0     0x84
#define   FWindow_StartPos_X_Reg1     0x85
#define   FWindow_StartPos_Y_Reg0     0x88
#define   FWindow_StartPos_Y_Reg1     0x89
#define   FWindow_EndPos_X_Reg0     0x8C
#define   FWindow_EndPos_X_Reg1     0x8D
#define   FWindow_EndPos_Y_Reg0     0x90
#define   FWindow_EndPos_Y_Reg1     0x91

#define   Power_Saving_Config_Reg     0xA0
#define   Pwrsave_frame_count_Reg     0xA1
#define   SW_Reset_Reg              0xA2

#define   Scratch_define_Reg0           0xA4
#define   Scratch_define_Reg1           0xA5

#define   GPIO_Pins_Config_Reg0        0xA8
#define   GPIO_Pins_Config_Reg1        0xA9
#define   GPIO_LDPins__Config_Reg0     0xAA
#define   GPIO_LDPins__Config_Reg1     0xAB
#define   GPIO_Pins_StatusC_Reg        0xAC
#define   LCD_Power_Control_Reg     0xAD
#define   GPIO_LDPins__StatusC_Reg     0xAE

#define   Cursor_Feature_Reg        0xC0

#define   Cursor1_Blink_Total_Reg0     0xC4
#define   Cursor1_Blink_Total_Reg1     0xC5
#define   Cursor1_Blink_On_Reg0        0xC8
#define   Cursor1_Blink_On_Reg1        0xC9
#define   Cursor1_Mem_Start_Reg0     0xCC
#define   Cursor1_Mem_Start_Reg1     0xCD
#define   Cursor1_Mem_Start_Reg2     0xCE
#define   Cursor1_Pos_X_Reg0        0xD0
#define   Cursor1_Pos_X_Reg1        0xD1
#define   Cursor1_Pos_Y_Reg0        0xD4
#define   Cursor1_Pos_Y_Reg1        0xD5
#define   Cursor1_Horiz_Size_Reg0     0xD8
#define   Cursor1_Horiz_Size_Reg1     0xD9
#define   Cursor1_Vert_Size_Reg0     0xDC
#define   Cursor1_Vert_Size_Reg1     0xDD
#define   Cursor1_Color_Index1_Reg0     0xE0
#define   Cursor1_Color_Index1_Reg1     0xE1
#define   Cursor1_Color_Index1_Reg2     0xE2
#define   Cursor1_Color_Index1_Reg3     0xE3
#define   Cursor1_Color_Index2_Reg0     0xE4
#define   Cursor1_Color_Index2_Reg1     0xE5
#define   Cursor1_Color_Index2_Reg2     0xE6
#define   Cursor1_Color_Index2_Reg3     0xE7
#define   Cursor1_Color_Index3_Reg0     0xE8
#define   Cursor1_Color_Index3_Reg1     0xE9
#define   Cursor1_Color_Index3_Reg2     0xEA
#define   Cursor1_Color_Index3_Reg3     0xEB

#define   Cursor2_Blink_Total_Reg0     0xEC
#define   Cursor2_Blink_Total_Reg1     0xED
#define   Cursor2_Blink_On_Reg0        0xF0
#define   Cursor2_Blink_On_Reg1        0xF1
#define   Cursor2_Mem_Start_Reg0     0xF4
#define   Cursor2_Mem_Start_Reg1     0xF5
#define   Cursor2_Mem_Start_Reg2     0xF6
#define   Cursor2_Pos_X_Reg0        0xF8
#define   Cursor2_Pos_X_Reg1        0xF9
#define   Cursor2_Pos_Y_Reg0        0xFC
#define   Cursor2_Pos_Y_Reg1        0xFD
#define   Cursor2_Horiz_Size_Reg0   0x100
#define   Cursor2_Horiz_Size_Reg1   0x101
#define   Cursor2_Vert_Size_Reg0   0x104
#define   Cursor2_Vert_Size_Reg1   0x105
#define   Cursor2_Color_Index1_Reg0   0x108
#define   Cursor2_Color_Index1_Reg1   0x109
#define   Cursor2_Color_Index1_Reg2   0x10A
#define   Cursor2_Color_Index1_Reg3   0x10B
#define   Cursor2_Color_Index2_Reg0   0x10C
#define   Cursor2_Color_Index2_Reg1   0x10D
#define   Cursor2_Color_Index2_Reg2   0x10E
#define   Cursor2_Color_Index2_Reg3   0x10F
#define   Cursor2_Color_Index3_Reg0   0x110
#define   Cursor2_Color_Index3_Reg1   0x111
#define   Cursor2_Color_Index3_Reg2   0x112
#define   Cursor2_Color_Index3_Reg3   0x113

#define   PLL_Clock_Setting_Reg0   0x126
#define   PLL_Clock_Setting_Reg1   0x127
#define   PLL_Clock_Setting_Reg2   0x12B
#define   PCLK_Freq_Ratio_Reg0      0x158
#define   PCLK_Freq_Ratio_Reg1      0x159
#define   PCLK_Freq_Ratio_Reg2      0x15A

#define   RGB_Setting_Register      0x1A4

#define   MOD_Time_Period_Reg0      0x340
#define   MOD_Time_Pattern_Reg0   0x342
#define   MOD_Time_Pattern_Reg1   0x343

#define   LSHIFT_sig_StartPos_Reg0   0x350
#define   LSHIFT_sig_StartPos_Reg1   0x351
#define   LSHIFT_sig_EndPos_Reg0   0x354
#define   LSHIFT_sig_EndPos_Reg1   0x355

#define   TFT_FRC_Enable_Bit_Reg   0x346

void NewMicrotipsLCD(glcd_driver* drv);
void MicrotipsLCDInit(glcd_device* dev);

int RGBColor(int r, int g, int b);

void ConfigureScreen();
void LCDBacklight(char on);

//const char* __(int);

void SetColor(glcd_device* dev, WORD color);
void SetBgColor(glcd_device* dev, WORD color);
void ClcdTextSize(glcd_device* dev, WORD size);
void ClcdGoToXY(glcd_device* dev, int x, int y);

void ClearDevice(glcd_device* dev);
void PutPixel(glcd_device* dev, int x, int y);
WORD GetPixel(glcd_device* dev, int x, int y);

void ClcdPrint(glcd_device* dev, const char* str,
               ...);// __attribute__((format(printf, 1, 2)));
void ClcdPuts(glcd_device* dev, const char* str);
void ClcdXYPuts(glcd_device* dev, int xpos, int ypos, const char* str);

void PutRectangle(glcd_device* dev, int height, int width);
void PutHLine(glcd_device* dev, int length);
void PutVLine(glcd_device* dev, int length);

#ifdef  __cplusplus
}
#endif

#endif  // MICROTIPS_LCD_H

