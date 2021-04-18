#include "SPISlave.h"

// Arduino header
#include <variant.h>

SPISlaveClass::SPISlaveClass(Spi *spi, uint32_t id, InitCallbackType cb)
    :mSPI(spi), mId(id), mInitCb(cb) 
{
}

SPISlaveClass::~SPISlaveClass()
{
}

void SPISlaveClass::begin(InterruptCallbackType cb)
{
	init();
	mIntrCb = cb;
}

void SPISlaveClass::callIntrHandler()
{
	if (nullptr != mIntrCb)	mIntrCb();
}

void SPISlaveClass::init()
{
    if (mInitialized) return;
    mInitCb();
	SPI_Enable(mSPI);
	mInitialized = true;
}

void SPI0_Handler()
{
	SPISlave.callIntrHandler();
}


#if SPI_INTERFACES_COUNT > 0
static void SPI_0_Init(void) {
	//SPI serial recieve
	REG_PMC_PCER0 |= PMC_PCER0_PID24;		// Power up SPI clock
	REG_SPI0_WPMR = 0<<SPI_WPMR_WPEN;		//Unlock user interface for SPI

	PIO_Configure(
			g_APinDescription[PIN_SPI_MOSI].pPort,
			g_APinDescription[PIN_SPI_MOSI].ulPinType,
			g_APinDescription[PIN_SPI_MOSI].ulPin,
			g_APinDescription[PIN_SPI_MOSI].ulPinConfiguration);
	PIO_Configure(
			g_APinDescription[PIN_SPI_MISO].pPort,
			g_APinDescription[PIN_SPI_MISO].ulPinType,
			g_APinDescription[PIN_SPI_MISO].ulPin,
			g_APinDescription[PIN_SPI_MISO].ulPinConfiguration);
	PIO_Configure(
			g_APinDescription[PIN_SPI_SCK].pPort,
			g_APinDescription[PIN_SPI_SCK].ulPinType,
			g_APinDescription[PIN_SPI_SCK].ulPin,
			g_APinDescription[PIN_SPI_SCK].ulPinConfiguration);
    PIO_Configure(
            g_APinDescription[PIN_SPI_SS0].pPort,
            g_APinDescription[PIN_SPI_SS0].ulPinType,
            g_APinDescription[PIN_SPI_SS0].ulPin,
            g_APinDescription[PIN_SPI_SS0].ulPinConfiguration);

	REG_SPI0_MR = 0;						// Slave mode	
	SPI0->SPI_IER = SPI_IER_RDRF;			// Receive Data Register Full Interrupt
	
	NVIC_EnableIRQ(SPI0_IRQn);
	SPI0->SPI_CSR[0] = SPI_CSR_BITS_16_BIT;	// Shift on falling edge and transfer 16 bits.
}

SPISlaveClass SPISlave(SPI0, SPI_INTERFACE_ID, SPI_0_Init);
#endif