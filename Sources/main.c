/* ###################################################################
**     Filename    : main.c
**     Project     : keaz128_can
**     Processor   : SKEAZ128MLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-23, 13:17, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "CAN1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned int i=0,j=0;

volatile bool DataFrameTxFlg;
volatile bool DataFrameRxFlg = FALSE;
LDD_TDeviceData *MyCANPtr;
LDD_TError Error;
LDD_CAN_TFrame Frame;
uint8_t OutData[8] = {0x00U, 0x01U, 0x02U, 0x03U};           //,0X04U,0X05U,0X06U,0X07U     /* Initialization of output data buffer */
uint8_t InpData[8];

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  // Disable standby
   GPIOB_PDDR |= (1<<16);
   GPIOB_PCOR = (1<<16);

   MyCANPtr = CAN1_Init(NULL);                                     /* Initialization of CAN2 component */

     Frame.MessageID = 0x123U;                                       /* Set Tx ID value - standard */
     Frame.FrameType = LDD_CAN_DATA_FRAME;                           /* Specyfying type of Tx frame - Data frame */
     Frame.Length = sizeof(OutData);                                 /* Set number of bytes in data frame - 4B */
     Frame.Data = OutData;                                           /* Set pointer to OutData buffer */
     DataFrameTxFlg = FALSE;                                         /* Initialization of DataFrameTxFlg */

     Error = CAN1_SendFrame(MyCANPtr, 1U, &Frame);                   /* Sends the data frame over buffer 0 */
     while (!DataFrameTxFlg) {                                       /* Wait until data frame is transmitted */
     }

     Frame.MessageID = (0x123456U | LDD_CAN_MESSAGE_ID_EXT);         /* Set Tx ID value - extended */
     Frame.FrameType = LDD_CAN_DATA_FRAME;                           /* Specyfying type of Tx frame - Data frame */
     Frame.Length = sizeof(OutData);                                 /* Set number of bytes in data frame - 4B */
     Frame.Data = OutData;                                           /* Set pointer to OutData buffer */
     DataFrameTxFlg = FALSE;                                         /* Clear DataFrameTxFlg */
     Error = CAN1_SendFrame(MyCANPtr, 1U, &Frame);                   /* Sends the data frame over buffer 0 */
     while (!DataFrameTxFlg) {                                       /* Wait until data frame is transmitted */
     }


     while (!DataFrameRxFlg) {                                       /* Wait until data frame is received */
      }
      Frame.Data = InpData;                                           /* Set pointer to InpData buffer */
      Error = CAN1_ReadFrame(MyCANPtr, 0U, &Frame);

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
