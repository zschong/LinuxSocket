#ifndef __PACKET_TYPE_H__
#define __PACKET_TYPE_H__

typedef enum
{
	//Send Board Info
	PKT_BoardInfoSend = 0x00,
	PKT_BoardInfoRecv = 0x01,

	//Hand Shake Count Download
	PKT_ConfigBeginSend = 0x02,
	PKT_ConfigBeginRecv = 0x03,

	//Hand Shake Packet Download
	PKT_ConfigPacketFailedSend = 0x04,
	PKT_ConfigPacketRecv = 0x05,

	//Hand Shake Finish Download
	PKT_ConfigFinishSend = 0x06,
	PKT_ConfigFinishRecv = 0x07,

	//Hand Shake Count Upload
	PKT_CacheBeginSend = 0x08,
	PKT_CacheBeginRecv = 0x09,

	//Hand Shake Packet Upload
	PKT_CachePacketSend = 0x0A,
	PKT_CachePacketFailedRecv = 0x0B,

	//Hand Shake Finish Upload
	PKT_CacheFinishSend = 0x0C,
	PKT_CacheFinishRecv = 0x0D,

	//Heartbeat
	PKT_HeartBeatSend = 0x0E,
	PKT_HeartBeatRecv = 0x0F,

	//Realtime Data
	PKT_RealtimeDataSend = 0x10,
	PKT_RealtimeDataRecv = 0x11,

	//Input Instruction
	PKT_InputInstructionSend = 0x12,
	PKT_InputInstructionRecv = 0x13,

	//Output Instruction
	PKT_OutputInstructionSend = 0x14,
	PKT_OutputInstructionRecv = 0x15,

	//Variable Instruction
	PKT_VariableInstructionSend = 0x16,
	PKT_VariableInstructionRecv = 0x17,

	//Send Device Infomation
	PKT_SendDeviceInfoSend = 0x18,
	PKT_SendDeviceInfoRecv = 0x19,

	//Basic Debug Mode 
	PKT_BasicDebugModeSend = 0x1A,
	PKT_BasicDebugModeRecv = 0x1B,

	//Basic Instruction,Auto,Run
	PKT_BasicInstructionSend = 0x1C,
	PKT_BasicInstructionRecv = 0x1D,

	//Basic Conent Count
	PKT_BasicContentCountSend = 0x1E,
	PKT_BasicContentCountRecv = 0x1F,

	//Basic Content
	PKT_BasicContentFailedSend = 0x20,
	PKT_BasicContentRecv = 0x21,

	//Basic Content Finish
	PKT_BasicContentFinishSend = 0x22,
	PKT_BasicContentFinishRecv = 0x23,

	//Basic Error
	PKT_BasicStatSend = 0x24,
	PKT_BasicStatRecv = 0x25,

	//Basic Debug Message
	PKT_BasicDebugMessageSend = 0x26,
	PKT_BasicDebugMessageRecv = 0x27,

	//Week Auto Value
	PKT_WeekInstructionSend = 0x28,
	PKT_WeekInstructionRecv = 0x29,

	//Year Auto Value
	PKT_YearInstructionSend = 0x2A,
	PKT_YearInstructionRecv = 0x2B,

	//Week Content
	PKT_WeekConfigSend = 0x2C,
	PKT_WeekConfigRecv = 0x2D,

	//Year Content
	PKT_YearConfigSend = 0x2E,
	PKT_YearConfigRecv = 0x2F,

	//PID 
	PKT_PidInstructionSend = 0x30,
	PKT_PidInstructionRecv = 0x31,

	//Runtime
	PKT_RuntimeConfigSend = 0x32,
	PKT_RuntimeConfigRecv = 0x33,
	
	//DataSource Config 
	PKT_DataSourceConfigSend = 0x34,
	PKT_DataSourceConfigRecv = 0x35,

	//Control Config
	PKT_ControlConfigSend = 0x36,
	PKT_ControlConfigRecv = 0x37,

	//Input Confing
	PKT_InputConfigSend = 0x38,
	PKT_InputConfigRecv = 0x39,

	//Output Config
	PKT_OutputConfigSend = 0x3A,
	PKT_OutputConfigRecv = 0x3B,

	//Variable Config
	PKT_VariableConfigSend = 0x3C,
	PKT_VariableConfigRecv = 0x3D,

	//MainBoard Config
	PKT_MainBoardConfigSend = 0x3E,
	PKT_MainBoardConfigRecv = 0x3F,

	//Basic Dmsg 
	PKT_BasicDmsgSend = 0x40,
	PKT_BasicDmsgRecv = 0x41,

	//serial runtime message
	PKT_ComMsgSend = 0x42,
	PKT_ComMsgRecv = 0x43,

	//net runtime message
	PKT_NetMsgSend = 0x44,
	PKT_NetMsgRecv = 0x45,

	//system runtime message
	PKT_SystemMsgSend = 0x46,
	PKT_SystemMsgRecv = 0x47,
}PacketType;


#endif//__PACKET_TYPE_H__
