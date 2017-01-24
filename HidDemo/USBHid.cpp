/*
*
*
*
*/
#include "stdafx.h"
#include "USBHid.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <Setupapi.h>
#include <Psapi.h>
#include <dbt.h>  

CUSBHid::CUSBHid()
{
    m_hHidLib = ::LoadLibraryA("hid.dll");

    HID_RESOLVE_FUNC(HidD_GetHidGuid);
    HID_RESOLVE_FUNC(HidD_SetNumInputBuffers);
    HID_RESOLVE_FUNC(HidD_GetFeature);
    HID_RESOLVE_FUNC(HidD_SetFeature);
    HID_RESOLVE_FUNC(HidD_GetAttributes);
    HID_RESOLVE_FUNC(HidD_GetManufacturerString);
    HID_RESOLVE_FUNC(HidD_GetProductString);
    HID_RESOLVE_FUNC(HidD_GetSerialNumberString);
    HID_RESOLVE_FUNC(HidD_GetPreparsedData);
    HID_RESOLVE_FUNC(HidD_FreePreparsedData);
    HID_RESOLVE_FUNC(HidP_GetCaps);
    if (HidD_GetHidGuid)
        HidD_GetHidGuid(&m_guidHID);    

}

CUSBHid::~CUSBHid()
{
    FreeLibrary(m_hHidLib);
}

BOOL CUSBHid::GetUSBDeviceName(CHAR *pName, DWORD dwLen)
{
    BOOL b_ret = FALSE;
    HDEVINFO hdevInfoSet;
    HIDD_ATTRIBUTES attr;
    SP_DEVICE_INTERFACE_DATA interfaceData;
    SP_INTERFACE_DEVICE_DETAIL_DATA_A* pData = NULL;
    HANDLE hHidDev = INVALID_HANDLE_VALUE;
    GUID hidGuid;
    int deviceIndex;
    DWORD detailSize;

    HidD_GetHidGuid(&hidGuid);
    interfaceData.cbSize = sizeof(interfaceData);
    // Get handle to info data set describing all available HIDs.
    hdevInfoSet = SetupDiGetClassDevsA(&hidGuid, NULL, NULL, DIGCF_INTERFACEDEVICE | DIGCF_PRESENT);
    if (hdevInfoSet == INVALID_HANDLE_VALUE)
    {
        goto Error;
    }

    for (deviceIndex = 0; SetupDiEnumDeviceInterfaces(hdevInfoSet, NULL, &hidGuid, deviceIndex, &interfaceData); deviceIndex++)
    {
        detailSize = 0;
        // SetupDiGetDeviceInterfaceDetailA returns "not enough buffer error code" doe size request. Just check valid size.
        if (SetupDiGetDeviceInterfaceDetailA(hdevInfoSet, &interfaceData, NULL, 0, &detailSize, NULL) && detailSize > 0)
        {
            continue;
        }
        pData = (SP_INTERFACE_DEVICE_DETAIL_DATA_A *) new BYTE[detailSize];
        pData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA_A);
        if (SetupDiGetDeviceInterfaceDetailA(hdevInfoSet, &interfaceData, pData, detailSize, NULL, NULL) && pData)
        {
            hHidDev = CreateFileA(pData->DevicePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
            if (hHidDev != INVALID_HANDLE_VALUE)
            {
                attr.Size = sizeof(attr);
                if (HidD_GetAttributes(hHidDev, &attr))
                {
					if ((attr.VendorID == 0x2833 && attr.ProductID == 0x0001))
                    {
						
                        if (pName && dwLen > strlen(pData->DevicePath))
                        {
                            strcpy(pName, pData->DevicePath);
                        }
                        b_ret = TRUE;
                        break;
                    }
                }
                CloseHandle(hHidDev);
                hHidDev = INVALID_HANDLE_VALUE;
            }
        }
        delete pData;
        pData = NULL;
    }

Error:

    if (pData)
    {
        delete pData;
    }
	if (hdevInfoSet != INVALID_HANDLE_VALUE)
	{
		SetupDiDestroyDeviceInfoList(hdevInfoSet);
	}
    if (hHidDev != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hHidDev);
        hHidDev = INVALID_HANDLE_VALUE;
    }
    return b_ret;
}

BOOL CUSBHid::SetFeatureReport(PBYTE data, DWORD len)
{
    BOOL bRet = FALSE;
    CHAR sDevName[MAX_PATH];
    HANDLE hHidDev = INVALID_HANDLE_VALUE;
    DWORD dwError;

    if (!GetUSBDeviceName(sDevName, MAX_PATH))
    {
        goto Error;
    }


    hHidDev = CreateFileA(sDevName, 
                                        GENERIC_WRITE | GENERIC_READ, 
                                        FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                        NULL, 
                                        OPEN_EXISTING, 
                                        FILE_FLAG_OVERLAPPED, 0);    
    if (hHidDev == INVALID_HANDLE_VALUE)
    {
        goto Error;
    }

    if (!HidD_SetFeature(hHidDev, data, len))
    {
        dwError = GetLastError();
        TRACE(TEXT("usb device GetFeature failed, error 0x%x\r\n"), dwError);        
        goto Error;
    }

    bRet = TRUE;

Error:

    if (hHidDev != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hHidDev);
        hHidDev = INVALID_HANDLE_VALUE;
    }   
    return bRet;
}

BOOL CUSBHid::GetFeatureReport(PBYTE data, DWORD len)
{
    BOOL bRet = FALSE;
    CHAR sDevName[MAX_PATH];
    HANDLE hHidDev = INVALID_HANDLE_VALUE;
    DWORD dwError;

    if (!GetUSBDeviceName(sDevName, MAX_PATH))
    {
        goto Error;
    }

    hHidDev = CreateFileA(sDevName, 
                                        GENERIC_WRITE | GENERIC_READ, 
                                        FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                        NULL, 
                                        OPEN_EXISTING, 
                                        FILE_FLAG_OVERLAPPED, 0);    
    if (hHidDev == INVALID_HANDLE_VALUE)
    {
        goto Error;
    }

    if (!HidD_GetFeature(hHidDev, data, len))
    {
        dwError = GetLastError();
        TRACE(TEXT("usb device GetFeature failed, error 0x%x\r\n"), dwError);    
        goto Error;
    }

    bRet = TRUE;

Error:

    if (hHidDev != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hHidDev);
        hHidDev = INVALID_HANDLE_VALUE;
    }
    return bRet;
}



BOOL CUSBHid::DeviceDataGet(PBYTE data, DWORD& len)
{
	enum { ReadBufferSize = 96, WriteBufferSize = 96 };
	BOOL bRet = FALSE;
	CHAR sDevName[MAX_PATH];
	HANDLE hHidDev = INVALID_HANDLE_VALUE;
	OVERLAPPED readOverlapped;
	PHIDP_PREPARSED_DATA preparsedData = 0;
	HIDP_CAPS caps;
	DWORD dwEndTick;
	memset(&readOverlapped, 0, sizeof(OVERLAPPED));
	if (!GetUSBDeviceName(sDevName, MAX_PATH))
	{
		goto Error;
	}

	hHidDev = CreateFileA(sDevName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	if (hHidDev == INVALID_HANDLE_VALUE)
	{
		goto Error;
	}

	if (!HidD_SetNumInputBuffers(hHidDev, 128))
	{
		goto Error;
	}

	if (!HidD_GetPreparsedData(hHidDev, &preparsedData))
	{
		goto Error;
	}

	if (HidP_GetCaps(preparsedData, &caps) != HIDP_STATUS_SUCCESS)
	{
		HidD_FreePreparsedData(preparsedData);
		goto Error;
	}
	HidD_FreePreparsedData(preparsedData);

	if (ReadBufferSize < caps.InputReportByteLength || WriteBufferSize < caps.OutputReportByteLength)
	{
		goto Error;
	}

	readOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!readOverlapped.hEvent)
	{
		goto Error;
	}
	dwEndTick = GetTickCount() + 6;
	//bRet = TRUE;
	do
	{
		len = 0;
		while (ReadFile(hHidDev, data, caps.InputReportByteLength, &len, &readOverlapped))
		{
			if (GetOverlappedResult(hHidDev, &readOverlapped, &len, FALSE))
			{
				bRet = TRUE;
				//DebugMsg(_T("%x %x %x %x %x %x %x\r\n"), data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
				break;
			}
			else
			{
				DWORD dwErr = GetLastError();
				if (dwErr != ERROR_IO_PENDING)
				{
					DEBUGMSG(ZONE_ERROR,(_T("GetOverlappedResult error %d\r\n"), dwErr));
					break;
				}
			}
			// Sleep(1);
		}

		if (WaitForSingleObject(readOverlapped.hEvent, 1000) == WAIT_OBJECT_0)
		{
			if (GetOverlappedResult(hHidDev, &readOverlapped, &len, FALSE))
			{
				bRet = TRUE;
				//DebugMsg(_T("%x %x %x %x %x %x %x\r\n"), data[0], data[1], data[2], data[3], data[4], data[5],data[6]);
				break;
			}
			else
			{
				DWORD dwErr = GetLastError();
				if (dwErr != ERROR_IO_PENDING)
				{
					DEBUGMSG(ZONE_ERROR,(_T("GetOverlappedResult error %d\r\n"), dwErr));
					break;
				}
			}
		}

	}while (bRet && dwEndTick < GetTickCount());
Error:

	if (hHidDev != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hHidDev);
		hHidDev = INVALID_HANDLE_VALUE;
	}

	if (!readOverlapped.hEvent)
	{
		CloseHandle(readOverlapped.hEvent);
	}

	return bRet;
}

BOOL CUSBHid::EnumHidDeviceInfo(vector<HID_DEVICE_INFO> &hid_device_info)
{
	BOOL b_ret = FALSE;
	HDEVINFO hdevInfoSet;
	HID_DEVICE_INFO device_info;
	SP_DEVICE_INTERFACE_DATA interfaceData;
	SP_INTERFACE_DEVICE_DETAIL_DATA_A* pData = NULL;
	HANDLE hHidDev = INVALID_HANDLE_VALUE;
	GUID hidGuid;
	int deviceIndex;
	DWORD detailSize;

	HidD_GetHidGuid(&hidGuid);
	interfaceData.cbSize = sizeof(interfaceData);
	// Get handle to info data set describing all available HIDs.
	hdevInfoSet = SetupDiGetClassDevsA(&hidGuid, NULL, NULL, DIGCF_INTERFACEDEVICE | DIGCF_PRESENT);
	if (hdevInfoSet == INVALID_HANDLE_VALUE)
	{
		goto Error;
	}

	for (deviceIndex = 0; SetupDiEnumDeviceInterfaces(hdevInfoSet, NULL, &hidGuid, deviceIndex, &interfaceData); deviceIndex++)
	{
		detailSize = 0;
		// SetupDiGetDeviceInterfaceDetailA returns "not enough buffer error code" doe size request. Just check valid size.
		if (SetupDiGetDeviceInterfaceDetailA(hdevInfoSet, &interfaceData, NULL, 0, &detailSize, NULL) && detailSize > 0)
		{
			continue;
		}
		pData = (SP_INTERFACE_DEVICE_DETAIL_DATA_A *) new BYTE[detailSize];
		pData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA_A);
		if (SetupDiGetDeviceInterfaceDetailA(hdevInfoSet, &interfaceData, pData, detailSize, NULL, NULL) && pData)
		{
			hHidDev = CreateFileA(pData->DevicePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
			if (hHidDev != INVALID_HANDLE_VALUE)
			{
				memset(device_info.serial_number, 0, sizeof(device_info.serial_number));
				if (!HidD_GetSerialNumberString(hHidDev, device_info.serial_number, sizeof(device_info.serial_number)))
				{
					//goto Error;
				}

				device_info.attributes.Size = sizeof(device_info.attributes);
				if (HidD_GetAttributes(hHidDev, &device_info.attributes))
				{
#if 0
					if ((attr.VendorID == 0x2833 && attr.ProductID == 0x0001))
					{

						if (pName && dwLen > strlen(pData->DevicePath))
						{
							strcpy(pName, pData->DevicePath);
						}
						b_ret = TRUE;
						break;
					}
#else
					
					strcpy(device_info.device_path, pData->DevicePath);
					hid_device_info.push_back(device_info);
					b_ret = TRUE;
#endif
				}
				CloseHandle(hHidDev);
				hHidDev = INVALID_HANDLE_VALUE;
			}
		}
		delete pData;
		pData = NULL;
	}

Error:

	if (pData)
	{
		delete pData;
	}
	if (hdevInfoSet != INVALID_HANDLE_VALUE)
	{
		SetupDiDestroyDeviceInfoList(hdevInfoSet);
	}
	if (hHidDev != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hHidDev);
		hHidDev = INVALID_HANDLE_VALUE;
	}
	return b_ret;
}
