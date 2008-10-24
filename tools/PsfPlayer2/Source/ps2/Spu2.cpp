#include "Spu2.h"
#include "Log.h"

#define LOG_NAME ("spu2")

using namespace PS2;
using namespace PS2::Spu2;
using namespace std;
using namespace std::tr1;
using namespace std::tr1::placeholders;
using namespace Framework;

/*
#define SD_BASE_REG(reg)				((volatile u16 *)(0xBF900000 + reg))

#define SD_VP_REG(core, voice, reg)		SD_BASE_REG(((core) << 10) + ((voice) << 4) + (reg))
#define SD_VP_VOLL(core, voice)			SD_VP_REG((core), (voice), 0x00)
#define SD_VP_VOLR(core, voice)			SD_VP_REG((core), (voice), 0x02)
#define SD_VP_PITCH(core, voice)		SD_VP_REG((core), (voice), 0x04)
#define SD_VP_ADSR1(core, voice)		SD_VP_REG((core), (voice), 0x06)
#define SD_VP_ADSR2(core, voice)		SD_VP_REG((core), (voice), 0x08)
#define SD_VP_ENVX(core, voice)			SD_VP_REG((core), (voice), 0x0A)
#define SD_VP_VOLXL(core, voice)		SD_VP_REG((core), (voice), 0x0C)
#define SD_VP_VOLXR(core, voice)		SD_VP_REG((core), (voice), 0x0E)

#define SD_S_REG(core, reg)				SD_BASE_REG(0x180 + ((core) << 10) + (reg)) 
#define SD_S_PMON_HI(core)				SD_S_REG((core), 0x00)
#define SD_S_PMON_LO(core)				SD_S_REG((core), 0x02)
#define SD_S_NON_HI(core)				SD_S_REG((core), 0x04)
#define SD_S_NON_LO(core)				SD_S_REG((core), 0x06)
#define SD_S_VMIXL_HI(core)				SD_S_REG((core), 0x08)
#define SD_S_VMIXL_LO(core)				SD_S_REG((core), 0x0A)
#define SD_S_VMIXEL_HI(core)			SD_S_REG((core), 0x0C)
#define SD_S_VMIXEL_LO(core)			SD_S_REG((core), 0x0E)
#define SD_S_VMIXR_HI(core)				SD_S_REG((core), 0x10)
#define SD_S_VMIXR_LO(core)				SD_S_REG((core), 0x12)
#define SD_S_VMIXER_HI(core)			SD_S_REG((core), 0x14)
#define SD_S_VMIXER_LO(core)			SD_S_REG((core), 0x16)
#define SD_P_MMIX(core)					SD_S_REG((core), 0x18)
#define SD_CORE_ATTR(core)				SD_S_REG((core), 0x1A)
#define SD_CORE_IRQA(core)				SD_S_REG((core), 0x1C)

#define SD_A_REG(core, reg)				SD_BASE_REG(0x1A0 + ((core) << 10) + (reg)) 
#define SD_A_KON_HI(core)				SD_A_REG((core), 0x00) // Key on (start sound generation)
#define SD_A_KON_LO(core)				SD_A_REG((core), 0x02)
#define SD_A_KOFF_HI(core)				SD_A_REG((core), 0x04) // Key off (end sound generation)
#define SD_A_KOFF_LO(core)				SD_A_REG((core), 0x06) 
#define SD_A_TSA_HI(core)				SD_A_REG((core), 0x08) // Transfer start address
#define SD_A_TSA_LO(core)				SD_A_REG((core), 0x0A) 
#define SD_A_STD(core)					SD_A_REG((core), 0x0C) // Sound Transfer Data

#define SD_VA_REG(core, voice, reg)		SD_BASE_REG(0x1C0 + ((core) << 10) + ((voice) * 12) + (reg))
#define SD_VA_SSA_HI(core, voice)		SD_VA_REG((core), (voice), 0x00)
#define SD_VA_SSA_LO(core, voice)		SD_VA_REG((core), (voice), 0x02)
#define SD_VA_LSAX(core, voice)			SD_VA_REG((core), (voice), 0x04)
#define SD_VA_NAX(core, voice)			SD_VA_REG((core), (voice), 0x08)

//#define SD_C_STATX(core)				((volatile u16*)(0xBF900334 + ((core) << 10))) // This is not the official name

#define SD_S_ENDX_HI(core)				((volatile u16*)(0xBF900340 + ((core) << 10)))
#define SD_S_ENDX_LO(core)				((volatile u16*)(0xBF900342 + ((core) << 10)))

#define SD_P_REG(core, reg)				SD_BASE_REG(0x760 + ((core) * 40) + (reg))
#define SD_P_MVOLL(core)				SD_P_REG((core), 0x00)
#define SD_P_MVOLR(core)				SD_P_REG((core), 0x02)
#define SD_P_EVOLL(core)				SD_P_REG((core), 0x04)
#define SD_P_EVOLR(core)				SD_P_REG((core), 0x06)
#define SD_P_AVOLL(core)				SD_P_REG((core), 0x08)
#define SD_P_AVOLR(core)				SD_P_REG((core), 0x0A)
#define SD_P_BVOLL(core)				SD_P_REG((core), 0x0C)
#define SD_P_BVOLR(core)				SD_P_REG((core), 0x0E)
#define SD_P_MVOLXL(core)				SD_P_REG((core), 0x10)
#define SD_P_MVOLXR(core)				SD_P_REG((core), 0x12)

#define SD_C_SPDIF_OUT					((volatile u16*)0xBF9007C0)
#define SD_C_IRQINFO					((volatile u16*)0xBF9007C2)
#define SD_C_SPDIF_MODE					((volatile u16*)0xBF9007C6)
#define SD_C_SPDIF_MEDIA				((volatile u16*)0xBF9007C8)

// Reverb / Effect Registers
#define SD_R_REG(core, reg)				SD_BASE_REG(0x2E0 + ((core) << 10) + reg)
// These registers are 1 word long, but low/high is accessed as halfwords
#define SD_A_ESA_HI(core)				SD_R_REG((core), 0x00)
#define SD_A_ESA_LO(core)				SD_R_REG((core), 0x02)
#define SD_R_FB_SRC_A(core)				SD_R_REG((core), 0x04)
#define SD_R_FB_SRC_B(core)				SD_R_REG((core), 0x08)
#define SD_R_IIR_DEST_A0(core)			SD_R_REG((core), 0x0C)
#define SD_R_IIR_DEST_A1(core)			SD_R_REG((core), 0x10)
#define SD_R_ACC_SRC_A0(core)			SD_R_REG((core), 0x14)
#define SD_R_ACC_SRC_A1(core)			SD_R_REG((core), 0x18)
#define SD_R_ACC_SRC_B0(core)			SD_R_REG((core), 0x1C)
#define SD_R_ACC_SRC_B1(core)			SD_R_REG((core), 0x20)
#define SD_R_IIR_SRC_A0(core)			SD_R_REG((core), 0x24)
#define SD_R_IIR_SRC_A1(core)			SD_R_REG((core), 0x28)
#define SD_R_IIR_DEST_B0(core)			SD_R_REG((core), 0x2C)
#define SD_R_IIR_DEST_B1(core)			SD_R_REG((core), 0x30)
#define SD_R_ACC_SRC_C0(core)			SD_R_REG((core), 0x34)
#define SD_R_ACC_SRC_C1(core)			SD_R_REG((core), 0x38)
#define SD_R_ACC_SRC_D0(core)			SD_R_REG((core), 0x3C)
#define SD_R_ACC_SRC_D1(core)			SD_R_REG((core), 0x40)
#define SD_R_IIR_SRC_B1(core)			SD_R_REG((core), 0x44)
#define SD_R_IIR_SRC_B0(core)			SD_R_REG((core), 0x48)
#define SD_R_MIX_DEST_A0(core)			SD_R_REG((core), 0x4C)
#define SD_R_MIX_DEST_A1(core)			SD_R_REG((core), 0x50)
#define SD_R_MIX_DEST_B0(core)			SD_R_REG((core), 0x54)
#define SD_R_MIX_DEST_B1(core)			SD_R_REG((core), 0x58)
#define SD_A_EEA_HI(core)				SD_R_REG((core), 0x5C)
#define SD_A_EEA_LO(core)				SD_R_REG((core), 0x5E)
// Halfwords
#define SD_R_IIR_ALPHA(core)			SD_P_REG((core), 0x14)
#define SD_R_ACC_COEF_A(core)			SD_P_REG((core), 0x16)
#define SD_R_ACC_COEF_B(core)			SD_P_REG((core), 0x18)
#define SD_R_ACC_COEF_C(core)			SD_P_REG((core), 0x1A)
#define SD_R_ACC_COEF_D(core)			SD_P_REG((core), 0x1C)
#define SD_R_IIR_COEF(core)				SD_P_REG((core), 0x1E)
#define SD_R_FB_ALPHA(core)				SD_P_REG((core), 0x20)
#define SD_R_FB_X(core)					SD_P_REG((core), 0x22)
#define SD_R_IN_COEF_L(core)			SD_P_REG((core), 0x24)
#define SD_R_IN_COEF_R(core)			SD_P_REG((core), 0x26)

// SPU DMA Channels 0,1 - 1088 bytes apart
#define SD_DMA_ADDR(ch)					((volatile u32*)(0xBF8010C0+(ch*1088)))
#define SD_DMA_MODE(ch)					((volatile u16*)(0xBF8010C4+(ch*1088)))
#define SD_DMA_SIZE(ch)					((volatile u16*)(0xBF8010C6+(ch*1088)))
#define SD_DMA_MSIZE(ch)				((volatile u32*)(0xBF8010C4+(ch*1088)))
#define SD_DMA_CHCR(ch)					((volatile u32*)(0xBF8010C8+(ch*1088)))
// CHCR
#define SD_DMA_CS						(1 << 9) // Continuous stream
#define SD_DMA_START					(1 << 24)
#define SD_DMA_DIR_SPU2IOP				0
#define SD_DMA_DIR_IOP2SPU				1
*/

//Global stuff
enum
{
    SD_VP_REG_BASE_0    = 0x1F900000,
    SD_VP_REG_BASE_1    = 0x1F900400,
    SD_S_REG_BASE_0     = 0x1F900180,
    SD_S_REG_BASE_1     = 0x1F900580,
    SD_A_REG_BASE_0     = 0x1F9001A0,
    SD_A_REG_BASE_1     = 0x1F9005A0,
    SD_P_REG_BASE_0     = 0x1F900760,
    SD_P_REG_BASE_1     = 0x1F900760 + 40,
    SD_C_SPDIF_OUT      = 0x1F9007C0,
    SD_C_IRQINFO        = 0x1F9007C2,
    SD_C_SPDIF_MODE     = 0x1F9007C6,
    SD_C_SPDIF_MEDIA    = 0x1F9007C8,
};

//SD_S_REG
enum
{
    SD_S_PMON_HI        = 0x00,
    SD_S_PMON_LO        = 0x02,
    SD_S_NON_HI         = 0x04,
    SD_S_NON_LO         = 0x06,
    SD_S_VMIXL_HI       = 0x08,
    SD_S_VMIXL_LO       = 0x0A,
    SD_S_VMIXEL_HI      = 0x0C,
    SD_S_VMIXEL_LO      = 0x0E,
    SD_S_VMIXR_HI       = 0x10,
    SD_S_VMIXR_LO       = 0x12,
    SD_S_VMIXER_HI      = 0x14,
    SD_S_VMIXER_LO      = 0x16,
    SD_P_MMIX           = 0x18,
    SD_CORE_ATTR        = 0x1A,
    SD_CORE_IRQA        = 0x1C,
};

//SD_A_REG
enum
{
    SD_A_KON_HI     = 0x00,
    SD_A_KON_LO     = 0x02,
    SD_A_KOFF_HI    = 0x04,
    SD_A_KOFF_LO    = 0x06,
    SD_A_TSA_HI     = 0x08,
    SD_A_TSA_LO     = 0x0A, 
    SD_A_STD        = 0x0C,
};

//SD_P_REG
enum
{
    SD_P_MVOLL      = 0x00,
    SD_P_MVOLR      = 0x02,
    SD_P_EVOLL      = 0x04,
    SD_P_EVOLR      = 0x06,
    SD_P_AVOLL      = 0x08,
    SD_P_AVOLR      = 0x0A,
    SD_P_BVOLL      = 0x0C,
    SD_P_BVOLR      = 0x0E,
    SD_P_MVOLXL     = 0x10,
    SD_P_MVOLXR     = 0x12,
};


CSpu2::CSpu2(uint32 baseAddress) :
m_baseAddress(baseAddress)
{
	for(unsigned int i = 0; i < CORE_NUM; i++)
	{
		m_core[i] = new CCore(i);
	}

	m_readDispatchInfo.global = bind(&CSpu2::ReadRegisterImpl, this, _1, _2);
	m_writeDispatchInfo.global = bind(&CSpu2::WriteRegisterImpl, this, _1, _2);
	for(unsigned int i = 0; i < CORE_NUM; i++)
	{
		m_readDispatchInfo.core[i] = bind(&CCore::ReadRegister, m_core[i], _1, _2);
		m_writeDispatchInfo.core[i] = bind(&CCore::WriteRegister, m_core[i], _1, _2);
	}
}

CSpu2::~CSpu2()
{

}

uint32 CSpu2::ReadRegister(uint32 address)
{
	return ProcessRegisterAccess(m_readDispatchInfo, address, 0);
}

uint32 CSpu2::WriteRegister(uint32 address, uint32 value)
{
	return ProcessRegisterAccess(m_writeDispatchInfo, address, value);
}

uint32 CSpu2::ProcessRegisterAccess(const REGISTER_DISPATCH_INFO& dispatchInfo, uint32 address, uint32 value)
{
    uint32 tmpAddress = address - m_baseAddress;
    if(tmpAddress < 0x760)
    {
		unsigned int coreId = (tmpAddress & 0x400) ? 1 : 0;
		address &= ~0x400;
		return dispatchInfo.core[coreId](address, value);
    }
	return dispatchInfo.global(address, value);
}

uint32 CSpu2::ReadRegisterImpl(uint32 address, uint32 value)
{
	LogRead(address);
	return 0;
}

uint32 CSpu2::WriteRegisterImpl(uint32 address, uint32 value)
{
	LogWrite(address, value);
	return 0;
}

void CSpu2::LogRead(uint32 address)
{
	switch(address)
	{
	default:
		CLog::GetInstance().Print(LOG_NAME, "Read an unknown register 0x%0.8X.\r\n", address);
		break;
	}
}

void CSpu2::LogWrite(uint32 address, uint32 value)
{
	switch(address)
	{
	default:
		CLog::GetInstance().Print(LOG_NAME, "Wrote 0x%0.8X to unknown register 0x%0.8X.\r\n", value, address);
		break;
	}
}
