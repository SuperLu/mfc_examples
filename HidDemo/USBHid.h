/*
 *
 *
 *
 */
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <Hidsdi.h>
#include <Hidpi.h>
#include "stdafx.h"
#include <vector>
#ifndef _USB_HID_H_
#define _USB_HID_H_

using namespace std;

#pragma comment(lib,"setupapi.lib")

typedef struct _HID_DEVICE {
	PCHAR                DevicePath;
	HANDLE               HidDevice; // A file handle to the hid device.
	HIDP_CAPS            Caps; // The Capabilities of this hid device.
	HIDD_ATTRIBUTES      Attributes;
} HID_DEVICE, *PHID_DEVICE;

typedef struct _HID_DEVICE_INFO
{
	HIDD_ATTRIBUTES attributes;
	WCHAR serial_number[127];
	CHAR device_path[MAX_PATH];
}HID_DEVICE_INFO,*P_HID_DEVICE_INFO;

#define HID_DECLARE_FUNC(func, rettype, args)   typedef rettype (__stdcall *PFn_##func) args;  PFn_##func      func;
#define HID_RESOLVE_FUNC(func)  func = (PFn_##func)::GetProcAddress(m_hHidLib, #func)

class CUSBHid
{
public:
    CUSBHid();
    virtual ~CUSBHid(); 

    GUID GetHIDGuid() { return m_guidHID; }

	BOOL DeviceDataGet(PBYTE data,DWORD& len);
	BOOL EnumHidDeviceInfo(vector<HID_DEVICE_INFO> &hid_device_info);

private:
    HMODULE m_hHidLib;
    HID_DECLARE_FUNC(HidD_GetHidGuid,            void,    (GUID *hidGuid));
    HID_DECLARE_FUNC(HidD_SetNumInputBuffers,    BOOLEAN, (HANDLE hidDev, ULONG numberBuffers));
    HID_DECLARE_FUNC(HidD_GetFeature,            BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
    HID_DECLARE_FUNC(HidD_SetFeature,            BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
    HID_DECLARE_FUNC(HidD_GetAttributes,         BOOLEAN, (HANDLE hidDev, HIDD_ATTRIBUTES *attributes));
    HID_DECLARE_FUNC(HidD_GetManufacturerString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
    HID_DECLARE_FUNC(HidD_GetProductString,      BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
    HID_DECLARE_FUNC(HidD_GetSerialNumberString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
    HID_DECLARE_FUNC(HidD_GetPreparsedData,      BOOLEAN, (HANDLE hidDev, PHIDP_PREPARSED_DATA *preparsedData));
    HID_DECLARE_FUNC(HidD_FreePreparsedData,     BOOLEAN, (PHIDP_PREPARSED_DATA preparsedData));
    HID_DECLARE_FUNC(HidP_GetCaps,               NTSTATUS,(PHIDP_PREPARSED_DATA preparsedData, HIDP_CAPS* caps));
    
private:
    BOOL GetUSBDeviceName(CHAR *pName, DWORD dwLen);
    BOOL SetFeatureReport(PBYTE data, DWORD len);
    BOOL GetFeatureReport(PBYTE data, DWORD len);
private:
    GUID m_guidHID;    
};

#endif /* _VIR_USBCMDIMPL_H_ */
