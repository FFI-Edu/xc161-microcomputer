#ifndef _PLATFORM_TYPES
#define _PLATFORM_TYPES

//
// Platform Types für das MCT Praktikum
//
// Version 0.1 vom 2012-11-08: erstes Release
// Author: Prof. Dr. Ulrich Margull
//
// Beschreibung: die Platform Typen definieren Datentypen mit festgelegten Bitgrößen
// ensprechend dem AUTOSAR Standard gemäß folgendem Link:
// http://www.autosar.org/download/R2.0/AUTOSAR_SWS_PlatformTypes.pdf
// 

//
// Platform types for all platforms
//

#define CPU_TYPE_8        8
#define CPU_TYPE_16       16
#define CPU_TYPE_32       32

#define MSB_FIRST         0
#define LSB_FIRST         1

#define HIGH_BYTE_FIRST   0
#define LOW_BYTE_FIRST    1

//
// Platform: XC161
//

#define CPU_TYPE CPU_TYPE_16
#define CPU_BIT_ORDER LSB_FIRST
#define CPU_BYTE_ORDER LOW_BYTE_FIRST

typedef unsigned char boolean;
typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed long sint32;
typedef unsigned long uint32;

/* die folgenden Datentypen sollen nicht im MCT Praktikum verwendet werden:
// Begründung: least-Typen werden nicht gebraucht
typedef unsigned long uint8_least;
typedef unsigned long uint16_least;
typedef unsigned long uint32_least;
typedef signed long sint8_least;
typedef signed long sint16_least;
typedef signed long sint32_least;

// Begründung: floating point Datentypen werden von der Hardware nicht unterstützt
typedef float float32;
typedef double float64;
*/

#endif