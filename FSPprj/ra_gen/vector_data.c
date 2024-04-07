/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI7 RXI (Receive data full) */
            [1] = sci_uart_txi_isr, /* SCI7 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI7 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI7 ERI (Receive error) */
            [4] = sci_uart_rxi_isr, /* SCI6 RXI (Receive data full) */
            [5] = sci_uart_txi_isr, /* SCI6 TXI (Transmit data empty) */
            [6] = sci_uart_tei_isr, /* SCI6 TEI (Transmit end) */
            [7] = sci_uart_eri_isr, /* SCI6 ERI (Receive error) */
            [8] = gpt_counter_overflow_isr, /* GPT4 COUNTER OVERFLOW (Overflow) */
            [9] = sci_spi_rxi_isr, /* SCI3 RXI (Receive data full) */
            [10] = sci_spi_txi_isr, /* SCI3 TXI (Transmit data empty) */
            [11] = sci_spi_tei_isr, /* SCI3 TEI (Transmit end) */
            [12] = sci_spi_eri_isr, /* SCI3 ERI (Receive error) */
            [13] = spi_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [14] = spi_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [15] = spi_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [16] = spi_eri_isr, /* SPI0 ERI (Error) */
            [17] = sci_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [18] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [19] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [20] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [21] = sci_uart_rxi_isr, /* SCI8 RXI (Receive data full) */
            [22] = sci_uart_txi_isr, /* SCI8 TXI (Transmit data empty) */
            [23] = sci_uart_tei_isr, /* SCI8 TEI (Transmit end) */
            [24] = sci_uart_eri_isr, /* SCI8 ERI (Receive error) */
            [25] = sci_uart_rxi_isr, /* SCI4 RXI (Receive data full) */
            [26] = sci_uart_txi_isr, /* SCI4 TXI (Transmit data empty) */
            [27] = sci_uart_tei_isr, /* SCI4 TEI (Transmit end) */
            [28] = sci_uart_eri_isr, /* SCI4 ERI (Receive error) */
            [29] = sci_uart_rxi_isr, /* SCI5 RXI (Receive data full) */
            [30] = sci_uart_txi_isr, /* SCI5 TXI (Transmit data empty) */
            [31] = sci_uart_tei_isr, /* SCI5 TEI (Transmit end) */
            [32] = sci_uart_eri_isr, /* SCI5 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI7_RXI,GROUP0), /* SCI7 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI7_TXI,GROUP1), /* SCI7 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI7_TEI,GROUP2), /* SCI7 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI7_ERI,GROUP3), /* SCI7 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_SCI6_RXI,GROUP4), /* SCI6 RXI (Receive data full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SCI6_TXI,GROUP5), /* SCI6 TXI (Transmit data empty) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI6_TEI,GROUP6), /* SCI6 TEI (Transmit end) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI6_ERI,GROUP7), /* SCI6 ERI (Receive error) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_GPT4_COUNTER_OVERFLOW,GROUP0), /* GPT4 COUNTER OVERFLOW (Overflow) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_SCI3_RXI,GROUP1), /* SCI3 RXI (Receive data full) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_SCI3_TXI,GROUP2), /* SCI3 TXI (Transmit data empty) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_SCI3_TEI,GROUP3), /* SCI3 TEI (Transmit end) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_SCI3_ERI,GROUP4), /* SCI3 ERI (Receive error) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_SPI0_RXI,GROUP5), /* SPI0 RXI (Receive buffer full) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TXI,GROUP6), /* SPI0 TXI (Transmit buffer empty) */
            [15] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TEI,GROUP7), /* SPI0 TEI (Transmission complete event) */
            [16] = BSP_PRV_VECT_ENUM(EVENT_SPI0_ERI,GROUP0), /* SPI0 ERI (Error) */
            [17] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP1), /* SCI9 RXI (Receive data full) */
            [18] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP2), /* SCI9 TXI (Transmit data empty) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP3), /* SCI9 TEI (Transmit end) */
            [20] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP4), /* SCI9 ERI (Receive error) */
            [21] = BSP_PRV_VECT_ENUM(EVENT_SCI8_RXI,GROUP5), /* SCI8 RXI (Receive data full) */
            [22] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TXI,GROUP6), /* SCI8 TXI (Transmit data empty) */
            [23] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TEI,GROUP7), /* SCI8 TEI (Transmit end) */
            [24] = BSP_PRV_VECT_ENUM(EVENT_SCI8_ERI,GROUP0), /* SCI8 ERI (Receive error) */
            [25] = BSP_PRV_VECT_ENUM(EVENT_SCI4_RXI,GROUP1), /* SCI4 RXI (Receive data full) */
            [26] = BSP_PRV_VECT_ENUM(EVENT_SCI4_TXI,GROUP2), /* SCI4 TXI (Transmit data empty) */
            [27] = BSP_PRV_VECT_ENUM(EVENT_SCI4_TEI,GROUP3), /* SCI4 TEI (Transmit end) */
            [28] = BSP_PRV_VECT_ENUM(EVENT_SCI4_ERI,GROUP4), /* SCI4 ERI (Receive error) */
            [29] = BSP_PRV_VECT_ENUM(EVENT_SCI5_RXI,GROUP5), /* SCI5 RXI (Receive data full) */
            [30] = BSP_PRV_VECT_ENUM(EVENT_SCI5_TXI,GROUP6), /* SCI5 TXI (Transmit data empty) */
            [31] = BSP_PRV_VECT_ENUM(EVENT_SCI5_TEI,GROUP7), /* SCI5 TEI (Transmit end) */
            [32] = BSP_PRV_VECT_ENUM(EVENT_SCI5_ERI,FIXED), /* SCI5 ERI (Receive error) */
        };
        #endif
        #endif