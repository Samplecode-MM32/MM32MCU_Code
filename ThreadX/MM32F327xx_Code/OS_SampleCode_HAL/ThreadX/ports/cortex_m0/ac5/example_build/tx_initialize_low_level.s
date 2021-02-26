;/**************************************************************************/
;/*                                                                        */
;/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
;/*                                                                        */
;/*       This software is licensed under the Microsoft Software License   */
;/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
;/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
;/*       and in the root directory of this software.                      */
;/*                                                                        */
;/**************************************************************************/
;
;
;/**************************************************************************/
;/**************************************************************************/
;/**                                                                       */
;/** ThreadX Component                                                     */
;/**                                                                       */
;/**   Initialize                                                          */
;/**                                                                       */
;/**************************************************************************/
;/**************************************************************************/
;
;
    IMPORT  _tx_thread_system_stack_ptr
    IMPORT  _tx_initialize_unused_memory
    IMPORT  _tx_timer_interrupt
    IMPORT  __main
    IMPORT  __tx_PendSVHandler
    IMPORT __Vectors
    IMPORT __initial_sp
;
;
SYSTEM_CLOCK        EQU     96000000
SYSTICK_CYCLES      EQU     ((SYSTEM_CLOCK / 10000) -1)
;
;
    AREA ||.text||, CODE, READONLY
;VOID   _tx_initialize_low_level(VOID)
;{
    EXPORT  _tx_initialize_low_level
_tx_initialize_low_level
;
;    /* Ensure that interrupts are disabled.  */
;
    CPSID   i                                       ; Disable interrupts
;
;    /* Set base of available memory to end of non-initialised RAM area.  */
;
    LDR     r0, =_tx_initialize_unused_memory       ; Build address of unused memory pointer
    LDR     r1, =__initial_sp                ; Build first free address
    ADDS    r1, r1, #4                              ;
    STR     r1, [r0]                                ; Setup first unused memory pointer
;
;    /* Setup Vector Table Offset Register.  */
;
    LDR     r0, =0xE000ED08                         ; Build address of NVIC registers
    LDR     r1, =__Vectors                       ; Pickup address of vector table
    STR     r1, [r0]                                ; Set vector table address
;
;    /* Enable the cycle count register.  */
;
;    LDR     r0, =0xE0001000                         ; Build address of DWT register
;    LDR     r1, [r0]                                ; Pickup the current value
;    MOVS    r2, #1
;    ORRS    r1, r1, r2                              ; Set the CYCCNTENA bit
;    STR     r1, [r0]                                ; Enable the cycle count register
;
;    /* Setup Vector Table Offset Register.  */
;
    LDR     r0, =0xE000E000                         ; Build address of NVIC registers
    LDR     r2, =0xD08                              ; Offset to vector base register
    ADD     r0, r0, r2                              ; Build vector base register
    LDR     r1, =__Vectors                       ; Pickup address of vector table
    STR     r1, [r0]                                ; Set vector table address
;
;    /* Set system stack pointer from vector value.  */
;
    LDR     r0, =_tx_thread_system_stack_ptr        ; Build address of system stack pointer
    LDR     r1, =__Vectors                       ; Pickup address of vector table
    LDR     r1, [r1]                                ; Pickup reset stack pointer
    STR     r1, [r0]                                ; Save system stack pointer
;
;    /* Configure SysTick.  */
;
    LDR     r0, =0xE000E000                         ; Build address of NVIC registers
    LDR     r1, =SYSTICK_CYCLES
    STR     r1, [r0, #0x14]                         ; Setup SysTick Reload Value
    MOVS    r1, #0x7                                ; Build SysTick Control Enable Value
    STR     r1, [r0, #0x10]                         ; Setup SysTick Control
;
;    /* Configure handler priorities.  */
;
    LDR     r1, =0x00000000                         ; Rsrv, UsgF, BusF, MemM
    LDR     r0, =0xE000E000                         ; Build address of NVIC registers
    LDR     r2, =0xD18                              ;
    ADD     r0, r0, r2                              ;
    STR     r1, [r0]                                ; Setup System Handlers 4-7 Priority Registers

    LDR     r1, =0xFF000000                         ; SVCl, Rsrv, Rsrv, Rsrv
    LDR     r0, =0xE000E000                         ; Build address of NVIC registers
    LDR     r2, =0xD1C                              ;
    ADD     r0, r0, r2                              ;
    STR     r1, [r0]                                ; Setup System Handlers 8-11 Priority Registers
                                                    ; Note: SVC must be lowest priority, which is 0xFF

    LDR     r1, =0x40FF0000                         ; SysT, PnSV, Rsrv, DbgM
    LDR     r0, =0xE000E000                         ; Build address of NVIC registers
    LDR     r2, =0xD20                              ;
    ADD     r0, r0, r2                              ;
    STR     r1, [r0]                                ; Setup System Handlers 12-15 Priority Registers
                                                    ; Note: PnSV must be lowest priority, which is 0xFF
;
;    /* Return to caller.  */
;
    BX      lr
;}
;
;

;    /* Generic context switching PendSV handler.  */
;     

    EXPORT  SysTick_Handler
    EXPORT  __tx_SysTickHandler
__tx_SysTickHandler
SysTick_Handler
; VOID TimerInterruptHandler (VOID)
; {
;
    PUSH    {r0, lr}
    BL      _tx_timer_interrupt
    POP     {r0, r1}
    MOV     lr, r1
    BX      lr
; }
    ALIGN
    LTORG
    END
