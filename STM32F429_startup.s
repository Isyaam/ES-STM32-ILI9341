;
; STM32F429_startup.s
;

; <<< Use Configuration Wizard in Context Menu >>>

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:256>
; </h>

RawStackSize    EQU     0x00000400
StackSize       EQU     RawStackSize - 8

                AREA    CCM, NOINIT, READWRITE, ALIGN=3
                ; Der Stack liegt bevorzugt im CCM (s. linker ccatter file).
                ; TOS muss an einer 8-Byte-Grenze ausgerichtet sein!
StackGuard_1    SPACE   4
StackGuard_2    SPACE   4
StackMem        SPACE   StackSize
__initial_sp
                EXPORT  StackGuard_1
                EXPORT  StackGuard_2

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:256>
; </h>

HeapSize        EQU     0x00010000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
HeapMem         SPACE   HeapSize
__heap_limit

                PRESERVE8
                THUMB

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                ; Top of Stack
                DCD     IRQ_Reset                   ; Reset Handler
                DCD     IRQ_NMI                     ; NMI Handler
                DCD     IRQ_HrdFlt                  ; Hard Fault Handler
                DCD     IRQ_MemFlt                  ; MPU Fault Handler
                DCD     IRQ_BusFlt                  ; Bus Fault Handler
                DCD     IRQ_UsgFlt                  ; Usage Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     IRQ_SVC                     ; SVCall Handler
                DCD     IRQ_DebMon                  ; Debug Monitor Handler
                DCD     0                           ; Reserved
                DCD     IRQ_PSV                     ; PendSV Handler
                DCD     IRQ_STK                     ; SysTick Handler

                ; External Interrupts
                
                DCD     IRQ_WWDG                    ; Window WatchDog                                        
                DCD     IRQ_PVD                     ; PVD through EXTI Line detection                        
                DCD     IRQ_TAMP                    ; Tamper and TimeStamps through the EXTI line            
                DCD     IRQ_RTC_WKUP                ; RTC Wakeup through the EXTI line                       
                DCD     IRQ_FLASH                   ; FLASH                                           
                DCD     IRQ_RCC                     ; RCC                                             
                DCD     IRQ_EXTI00                  ; EXTI Line0                                             
                DCD     IRQ_EXTI01                  ; EXTI Line1                                             
                DCD     IRQ_EXTI02                  ; EXTI Line2                                             
                DCD     IRQ_EXTI03                  ; EXTI Line3                                             
                DCD     IRQ_EXTI04                  ; EXTI Line4                                             
                DCD     IRQ_DMA1_STREAM0            ; DMA1 Stream 0                                   
                DCD     IRQ_DMA1_STREAM1            ; DMA1 Stream 1                                   
                DCD     IRQ_DMA1_STREAM2            ; DMA1 Stream 2                                   
                DCD     IRQ_DMA1_STREAM3            ; DMA1 Stream 3                                   
                DCD     IRQ_DMA1_STREAM4            ; DMA1 Stream 4                                   
                DCD     IRQ_DMA1_STREAM5            ; DMA1 Stream 5                                   
                DCD     IRQ_DMA1_STREAM6            ; DMA1 Stream 6                                   
                DCD     IRQ_ADC                     ; ADC1, ADC2 and ADC3s                            
                DCD     IRQ_CAN1_TX                 ; CAN1 TX                                                
                DCD     IRQ_CAN1_RX0                ; CAN1 RX0                                               
                DCD     IRQ_CAN1_RX1                ; CAN1 RX1                                               
                DCD     IRQ_CAN1_SCE                ; CAN1 SCE                                               
                DCD     IRQ_EXTI05TO09              ; External Line[9:5]s                                    
                DCD     IRQ_TIM01_BK_TIM09          ; TIM01 Break and TIM09                   
                DCD     IRQ_TIM01_UE_TIM10          ; TIM01 Update and TIM10                 
                DCD     IRQ_TIM01_TR_TIM11          ; TIM01 Trigger and Commutation and TIM11
                DCD     IRQ_TIM01_CC                ; TIM01 Capture Compare                                   
                DCD     IRQ_TIM02                   ; TIM02                                            
                DCD     IRQ_TIM03                   ; TIM03                                            
                DCD     IRQ_TIM04                   ; TIM04                                            
                DCD     IRQ_I2C1_EV                 ; I2C1 Event                                             
                DCD     IRQ_I2C1_ER                 ; I2C1 Error                                             
                DCD     IRQ_I2C2_EV                 ; I2C2 Event                                             
                DCD     IRQ_I2C2_ER                 ; I2C2 Error                                               
                DCD     IRQ_SPI1                    ; SPI1                                            
                DCD     IRQ_SPI2                    ; SPI2                                            
                DCD     IRQ_USART1                  ; USART1                                          
                DCD     IRQ_USART2                  ; USART2                                          
                DCD     IRQ_USART3                  ; USART3                                          
                DCD     IRQ_EXTI10TO15              ; External Line[15:10]s                                  
                DCD     IRQ_RTC_ALARM               ; RTC Alarm (A and B) through EXTI Line                  
                DCD     IRQ_OTG_FS_WKUP             ; USB OTG FS Wakeup through EXTI line                        
                DCD     IRQ_TIM08_BK_TIM12          ; TIM08 Break and TIM12                  
                DCD     IRQ_TIM08_UE_TIM13          ; TIM08 Update and TIM13                 
                DCD     IRQ_TIM08_TR_TIM14          ; TIM08 Trigger and Commutation and TIM14
                DCD     IRQ_TIM08_CC                ; TIM08 Capture Compare                                   
                DCD     IRQ_DMA1_STREAM7            ; DMA1 Stream7                                           
                DCD     IRQ_FMC                     ; FMC                                            
                DCD     IRQ_SDIO                    ; SDIO                                            
                DCD     IRQ_TIM05                   ; TIM05                                            
                DCD     IRQ_SPI3                    ; SPI3                                            
                DCD     IRQ_UART4                   ; UART4                                           
                DCD     IRQ_UART5                   ; UART5                                           
                DCD     IRQ_TIM06_DAC               ; TIM06 and DAC1&2 underrun errors                   
                DCD     IRQ_TIM07                   ; TIM07                   
                DCD     IRQ_DMA2_STREAM0            ; DMA2 Stream 0                                   
                DCD     IRQ_DMA2_STREAM1            ; DMA2 Stream 1                                   
                DCD     IRQ_DMA2_STREAM2            ; DMA2 Stream 2                                   
                DCD     IRQ_DMA2_STREAM3            ; DMA2 Stream 3                                   
                DCD     IRQ_DMA2_STREAM4            ; DMA2 Stream 4                                   
                DCD     IRQ_ETH                     ; Ethernet                                        
                DCD     IRQ_ETH_WKUP                ; Ethernet Wakeup through EXTI line                      
                DCD     IRQ_CAN2_TX                 ; CAN2 TX                                                
                DCD     IRQ_CAN2_RX0                ; CAN2 RX0                                               
                DCD     IRQ_CAN2_RX1                ; CAN2 RX1                                               
                DCD     IRQ_CAN2_SCE                ; CAN2 SCE                                               
                DCD     IRQ_OTG_FS                  ; USB OTG FS                                      
                DCD     IRQ_DMA2_STREAM5            ; DMA2 Stream 5                                   
                DCD     IRQ_DMA2_STREAM6            ; DMA2 Stream 6                                   
                DCD     IRQ_DMA2_STREAM7            ; DMA2 Stream 7                                   
                DCD     IRQ_USART6                  ; USART6                                           
                DCD     IRQ_I2C3_EV                 ; I2C3 event                                             
                DCD     IRQ_I2C3_ER                 ; I2C3 error                                             
                DCD     IRQ_OTG_HS_EP1_OUT          ; USB OTG HS End Point 1 Out                      
                DCD     IRQ_OTG_HS_EP1_IN           ; USB OTG HS End Point 1 In                       
                DCD     IRQ_OTG_WKUP                ; USB OTG HS Wakeup through EXTI                         
                DCD     IRQ_OTG_HS                  ; USB OTG HS                                      
                DCD     IRQ_DCMI                    ; DCMI                                            
                DCD     IRQ_CRYP                    ; CRYP crypto                                     
                DCD     IRQ_HASH_RNG                ; Hash and Rng 
                DCD     IRQ_FPU                 
                DCD     IRQ_UART7               
                DCD     IRQ_UART8               
                DCD     IRQ_SPI4                
                DCD     IRQ_SPI5                
                DCD     IRQ_SPI6                
                DCD     IRQ_SAI1                
                DCD     IRQ_LTDC                
                DCD     IRQ_LTDC_ERR            
                DCD     IRQ_DMA2D               
__Vectors_End
__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

IRQ_Reset       PROC
                EXPORT  IRQ_Reset               [WEAK]
                IMPORT  VeryFirstInit
                IMPORT  __main

                LDR     R0, =VeryFirstInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

IRQ_NMI         PROC
                EXPORT  IRQ_NMI                 [WEAK]
                B       .
                ENDP

IRQ_HrdFlt      PROC
                IMPORT  HandleHrdFlt
                TST     LR, #4
                MRSEQ   R0, MSP
                MRSNE   R0, PSP
                B       HandleHrdFlt
                ENDP
                
IRQ_MemFlt      PROC
                IMPORT  HandleMemFlt
                TST     LR, #4
                MRSEQ   R0, MSP
                MRSNE   R0, PSP
                B       HandleMemFlt
                ENDP
                
IRQ_BusFlt      PROC
                IMPORT  HandleBusFlt
                TST     LR, #4
                MRSEQ   R0, MSP
                MRSNE   R0, PSP
                B       HandleBusFlt
                ENDP
                
IRQ_UsgFlt      PROC
                IMPORT  HandleUsgFlt
                TST     LR, #4
                MRSEQ   R0, MSP
                MRSNE   R0, PSP
                B       HandleUsgFlt
                ENDP

IRQ_SVC         PROC
                IMPORT  HandleSVC
                TST     LR, #4
                MRSEQ   R0, MSP
                MRSNE   R0, PSP
                B       HandleSVC
                ENDP

IRQ_DebMon      PROC
                EXPORT  IRQ_DebMon              [WEAK]
                B       .
                ENDP
                
IRQ_PSV         PROC
                EXPORT  IRQ_PSV                 [WEAK]
                B       .
                ENDP
                
IRQ_STK         PROC
                EXPORT  IRQ_STK                 [WEAK]
                B       .
                ENDP

UndefinedIRQ    PROC
                EXPORT  UndefinedIRQ            [WEAK]
                B       .
                ENDP

IRQ_Default     PROC
                EXPORT  IRQ_WWDG                [WEAK]                                        
                EXPORT  IRQ_PVD                 [WEAK]                      
                EXPORT  IRQ_TAMP                [WEAK]         
                EXPORT  IRQ_RTC_WKUP            [WEAK]                     
                EXPORT  IRQ_FLASH               [WEAK]                                         
                EXPORT  IRQ_RCC                 [WEAK]                                            
                EXPORT  IRQ_EXTI00              [WEAK]                                            
                EXPORT  IRQ_EXTI01              [WEAK]                                             
                EXPORT  IRQ_EXTI02              [WEAK]                                            
                EXPORT  IRQ_EXTI03              [WEAK]                                           
                EXPORT  IRQ_EXTI04              [WEAK]                                            
                EXPORT  IRQ_DMA1_STREAM0        [WEAK]                                
                EXPORT  IRQ_DMA1_STREAM1        [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM2        [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM3        [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM4        [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM5        [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM6        [WEAK]                                   
                EXPORT  IRQ_ADC                 [WEAK]                         
                EXPORT  IRQ_CAN1_TX             [WEAK]                                                
                EXPORT  IRQ_CAN1_RX0            [WEAK]                                               
                EXPORT  IRQ_CAN1_RX1            [WEAK]                                                
                EXPORT  IRQ_CAN1_SCE            [WEAK]                                                
                EXPORT  IRQ_EXTI05TO09          [WEAK]                                    
                EXPORT  IRQ_TIM01_BK_TIM09      [WEAK]                  
                EXPORT  IRQ_TIM01_UE_TIM10      [WEAK]                
                EXPORT  IRQ_TIM01_TR_TIM11      [WEAK] 
                EXPORT  IRQ_TIM01_CC            [WEAK]                                   
                EXPORT  IRQ_TIM02               [WEAK]                                            
                EXPORT  IRQ_TIM03               [WEAK]                                            
                EXPORT  IRQ_TIM04               [WEAK]                                            
                EXPORT  IRQ_I2C1_EV             [WEAK]                                             
                EXPORT  IRQ_I2C1_ER             [WEAK]                                             
                EXPORT  IRQ_I2C2_EV             [WEAK]                                            
                EXPORT  IRQ_I2C2_ER             [WEAK]                                               
                EXPORT  IRQ_SPI1                [WEAK]                                           
                EXPORT  IRQ_SPI2                [WEAK]                                            
                EXPORT  IRQ_USART1              [WEAK]                                          
                EXPORT  IRQ_USART2              [WEAK]                                          
                EXPORT  IRQ_USART3              [WEAK]                                         
                EXPORT  IRQ_EXTI10TO15          [WEAK]                                  
                EXPORT  IRQ_RTC_ALARM           [WEAK]                  
                EXPORT  IRQ_OTG_FS_WKUP         [WEAK]                        
                EXPORT  IRQ_TIM08_BK_TIM12      [WEAK]                 
                EXPORT  IRQ_TIM08_UE_TIM13      [WEAK]                 
                EXPORT  IRQ_TIM08_TR_TIM14      [WEAK] 
                EXPORT  IRQ_TIM08_CC            [WEAK]                                   
                EXPORT  IRQ_DMA1_STREAM7        [WEAK]                                          
                EXPORT  IRQ_FMC                 [WEAK]                                             
                EXPORT  IRQ_SDIO                [WEAK]                                             
                EXPORT  IRQ_TIM05               [WEAK]                                             
                EXPORT  IRQ_SPI3                [WEAK]                                             
                EXPORT  IRQ_UART4               [WEAK]                                            
                EXPORT  IRQ_UART5               [WEAK]                                            
                EXPORT  IRQ_TIM06_DAC           [WEAK]                   
                EXPORT  IRQ_TIM07               [WEAK]                    
                EXPORT  IRQ_DMA2_STREAM0        [WEAK]                                  
                EXPORT  IRQ_DMA2_STREAM1        [WEAK]                                   
                EXPORT  IRQ_DMA2_STREAM2        [WEAK]                                    
                EXPORT  IRQ_DMA2_STREAM3        [WEAK]                                    
                EXPORT  IRQ_DMA2_STREAM4        [WEAK]                                 
                EXPORT  IRQ_ETH                 [WEAK]                                         
                EXPORT  IRQ_ETH_WKUP            [WEAK]                     
                EXPORT  IRQ_CAN2_TX             [WEAK]                                               
                EXPORT  IRQ_CAN2_RX0            [WEAK]                                               
                EXPORT  IRQ_CAN2_RX1            [WEAK]                                               
                EXPORT  IRQ_CAN2_SCE            [WEAK]                                               
                EXPORT  IRQ_OTG_FS              [WEAK]                                       
                EXPORT  IRQ_DMA2_STREAM5        [WEAK]                                   
                EXPORT  IRQ_DMA2_STREAM6        [WEAK]                                   
                EXPORT  IRQ_DMA2_STREAM7        [WEAK]                                   
                EXPORT  IRQ_USART6              [WEAK]                                           
                EXPORT  IRQ_I2C3_EV             [WEAK]                                              
                EXPORT  IRQ_I2C3_ER             [WEAK]                                              
                EXPORT  IRQ_OTG_HS_EP1_OUT      [WEAK]                      
                EXPORT  IRQ_OTG_HS_EP1_IN       [WEAK]                      
                EXPORT  IRQ_OTG_WKUP            [WEAK]                        
                EXPORT  IRQ_OTG_HS              [WEAK]                                      
                EXPORT  IRQ_DCMI                [WEAK]                                             
                EXPORT  IRQ_CRYP                [WEAK]                                     
                EXPORT  IRQ_HASH_RNG            [WEAK]
                EXPORT  IRQ_FPU                 [WEAK]
                EXPORT  IRQ_UART7               [WEAK]
                EXPORT  IRQ_UART8               [WEAK]
                EXPORT  IRQ_SPI4                [WEAK]
                EXPORT  IRQ_SPI5                [WEAK]
                EXPORT  IRQ_SPI6                [WEAK]
                EXPORT  IRQ_SAI1                [WEAK]
                EXPORT  IRQ_LTDC                [WEAK]
                EXPORT  IRQ_LTDC_ERR            [WEAK]
                EXPORT  IRQ_DMA2D               [WEAK]

IRQ_WWDG                                                       
IRQ_PVD                                      
IRQ_TAMP                  
IRQ_RTC_WKUP                                
IRQ_FLASH                                                       
IRQ_RCC                                                            
IRQ_EXTI00                                                          
IRQ_EXTI01                                                           
IRQ_EXTI02                                                          
IRQ_EXTI03                                                         
IRQ_EXTI04                                                          
IRQ_DMA1_STREAM0                                       
IRQ_DMA1_STREAM1                                          
IRQ_DMA1_STREAM2                                          
IRQ_DMA1_STREAM3                                          
IRQ_DMA1_STREAM4                                          
IRQ_DMA1_STREAM5                                          
IRQ_DMA1_STREAM6                                          
IRQ_ADC                                         
IRQ_CAN1_TX                                                            
IRQ_CAN1_RX0                                                          
IRQ_CAN1_RX1                                                           
IRQ_CAN1_SCE                                                           
IRQ_EXTI05TO09                                                
IRQ_TIM01_BK_TIM09                        
IRQ_TIM01_UE_TIM10                      
IRQ_TIM01_TR_TIM11  
IRQ_TIM01_CC                                               
IRQ_TIM02                                                           
IRQ_TIM03                                                           
IRQ_TIM04                                                           
IRQ_I2C1_EV                                                         
IRQ_I2C1_ER                                                         
IRQ_I2C2_EV                                                        
IRQ_I2C2_ER                                                           
IRQ_SPI1                                                          
IRQ_SPI2                                                           
IRQ_USART1                                                       
IRQ_USART2                                                       
IRQ_USART3                                                      
IRQ_EXTI10TO15                                            
IRQ_RTC_ALARM                            
IRQ_OTG_FS_WKUP                                
IRQ_TIM08_BK_TIM12                      
IRQ_TIM08_UE_TIM13                       
IRQ_TIM08_TR_TIM14  
IRQ_TIM08_CC                                               
IRQ_DMA1_STREAM7                                                 
IRQ_FMC                                                            
IRQ_SDIO                                                            
IRQ_TIM05                                                            
IRQ_SPI3                                                            
IRQ_UART4                                                          
IRQ_UART5                                                          
IRQ_TIM06_DAC                            
IRQ_TIM07                              
IRQ_DMA2_STREAM0                                         
IRQ_DMA2_STREAM1                                          
IRQ_DMA2_STREAM2                                           
IRQ_DMA2_STREAM3                                           
IRQ_DMA2_STREAM4                                        
IRQ_ETH                                                         
IRQ_ETH_WKUP                                
IRQ_CAN2_TX                                                           
IRQ_CAN2_RX0                                                          
IRQ_CAN2_RX1                                                          
IRQ_CAN2_SCE                                                          
IRQ_OTG_FS                                                    
IRQ_DMA2_STREAM5                                          
IRQ_DMA2_STREAM6                                          
IRQ_DMA2_STREAM7                                          
IRQ_USART6                                                        
IRQ_I2C3_EV                                                          
IRQ_I2C3_ER                                                          
IRQ_OTG_HS_EP1_OUT                           
IRQ_OTG_HS_EP1_IN                            
IRQ_OTG_WKUP                                
IRQ_OTG_HS                                                   
IRQ_DCMI                                                            
IRQ_CRYP                                                    
IRQ_HASH_RNG                                    
IRQ_FPU           
IRQ_UART7
IRQ_UART8
IRQ_SPI4
IRQ_SPI5
IRQ_SPI6
IRQ_SAI1
IRQ_LTDC
IRQ_LTDC_ERR
IRQ_DMA2D

                LDR     R0, =UndefinedIRQ
                BLX     R0
                B       .

                ENDP

                ALIGN

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_setup_stackheap
                 
__user_setup_stackheap

                LDR     R0, =  HeapMem
                LDR     R1, = (StackMem + StackSize)
                LDR     R2, = (HeapMem +  HeapSize)
                LDR     R3, =  StackMem
                BX      LR

                ALIGN

                ENDIF

                END

