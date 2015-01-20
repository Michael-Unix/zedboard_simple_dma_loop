#include "xaxidma.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "xdebug.h"

#define DMA_DEV_ID XPAR_AXIDMA_0_DEVICE_ID

#define MEM_BASE_ADDR		0x00100000

#define TX_BUFFER_BASE (MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE (MEM_BASE_ADDR + 0x00300000)

#define MAX_LEN 0x4000
#define TEST_START_VALUE 0xC

int XAxiDma_Simple(u16 DeviceId);
static int CheckData(void);

XAxiDma AxiDma;

int main()
{
	int Status;

	xil_printf("\r\n--- Entering main() --- \r\n");

	Status = XAxiDma_Simple(DMA_DEV_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("XAxiDma_Simple: Failed\r\n");
		return XST_FAILURE;
	}
	xil_printf("XAxiDma_Simple: Passed\r\n");
	xil_printf("--- Exiting main() --- \r\n");

	return XST_SUCCESS;
}

int XAxiDma_Simple(u16 DeviceId)
{
	XAxiDma_Config *CfgPtr;
	int Status;
	int Index;
	u8 *TxBufferPtr;
	u8 *RxBufferPtr;
	u8 Value;

	TxBufferPtr = (u8 *)TX_BUFFER_BASE ;
	RxBufferPtr = (u8 *)RX_BUFFER_BASE;

	// Initialize the configure
	CfgPtr = XAxiDma_LookupConfig(DeviceId);
	if (!CfgPtr) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

	// Initialize the AXI DMA driver
	Status = XAxiDma_CfgInitialize(&AxiDma, CfgPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed: %d\r\n", Status);
		return XST_FAILURE;
	}

	if(XAxiDma_HasSg(&AxiDma)){
		xil_printf("Device configured as SG mode \r\n");
		return XST_FAILURE;
	}

	// Disable interrupts, we use polling mode
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	Value = TEST_START_VALUE;

	for(Index = 0; Index < MAX_LEN; Index ++) {
			TxBufferPtr[Index] = Value;
			Value = (Value + 1) & 0xFF;
	}
	/* Flush the SrcBuffer before the DMA transfer, in case the Data Cache
	 * is enabled
	 */
	Xil_DCacheFlushRange((u32)TxBufferPtr, MAX_LEN);

	// Start receive
	Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) RxBufferPtr, MAX_LEN, XAXIDMA_DEVICE_TO_DMA);
	if (Status != XST_SUCCESS) {
		xil_printf("Start receive failed: %d\r\n", Status);
		return XST_FAILURE;
	}

	// Start transfer
	Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) TxBufferPtr, MAX_LEN, XAXIDMA_DMA_TO_DEVICE);
	if (Status != XST_SUCCESS) {
		xil_printf("Start transfer failed: %d\r\n", Status);
		return XST_FAILURE;
	}




	// wait DMA end
	while ((XAxiDma_Busy(&AxiDma,XAXIDMA_DEVICE_TO_DMA)) ||
		(XAxiDma_Busy(&AxiDma,XAXIDMA_DMA_TO_DEVICE))) {
			/* Wait */
	}

	Status = CheckData();
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


static int CheckData(void)
{
	u8 *RxPacket;
	int Index = 0;
	u8 Value;

	RxPacket = (u8 *) RX_BUFFER_BASE;
	Value = TEST_START_VALUE;

	/* Invalidate the DestBuffer before receiving the data, in case the
	 * Data Cache is enabled
	 */
	Xil_DCacheInvalidateRange((u32)RxPacket, MAX_LEN);

	for(Index = 0; Index < MAX_LEN; Index++) {
		if (RxPacket[Index] != Value) {
			xil_printf("Data error %d: %x/%x\r\n", Index, RxPacket[Index], Value);
			return XST_FAILURE;
		}
		Value = (Value + 1) & 0xFF;
	}

	return XST_SUCCESS;
}
