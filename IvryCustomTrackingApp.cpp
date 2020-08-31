/*************************************************************************
*
* Copyright (C) 2016-2020 Mediator Software and/or its subsidiary(-ies).
* All rights reserved.
* Contact: Mediator Software (info@mediator-software.com)
*
* NOTICE:  All information contained herein is, and remains the property of
* Mediator Software and its suppliers, if any.
* The intellectual and technical concepts contained herein are proprietary
* to Mediator Software and its suppliers and may be covered by U.S. and
* Foreign Patents, patents in process, and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Mediator Software.
*
* If you have questions regarding the use of this file, please contact
* Mediator Software (info@mediator-software.com).
*
***************************************************************************/

#include <winsock2.h>
#include <Ws2tcpip.h>
#include "IvryCustomTrackingApp.h"

// Socket prerequisites
// ==========================================
#pragma comment(lib, "Ws2_32.lib")

int WinsockInit(void) {
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(1, 1), &wsa_data);
}

int WinsockQuit(void) {
	return WSACleanup();
}

SOCKET udp_socket;

int ReadAvail() {
	int status;
	u_long n = 0;

	status = ioctlsocket(udp_socket, FIONREAD, &n);

	if (status != 0)
		return 0;

	return (int)n;
}
// ==========================================

// Global variables that will override the position
double XPosOverride = 0;
double YPosOverride = 1;
double ZPosOverride = 0;

IvryCustomTrackingApp::IvryCustomTrackingApp()
	: m_hQuitEvent(INVALID_HANDLE_VALUE)
	, m_bUseDeviceOrientation(true)
{
	// Start position 1m off the ground at origin
	m_afPosition[0] = m_afPosition[2] = 0;
	m_afPosition[1] = 1;
}

IvryCustomTrackingApp::~IvryCustomTrackingApp()
{
	if (m_hQuitEvent != INVALID_HANDLE_VALUE)
	{
		// Make sure event is signalled before deleting
		::SetEvent(m_hQuitEvent);
		::CloseHandle(m_hQuitEvent);
	}
}

/** Run tracker **/
DWORD IvryCustomTrackingApp::Run()
{
	DWORD result = ERROR_SUCCESS;

	// Init our socket subsystem
	WinsockInit();

	// Create a UDP socket
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// Bind it (messy)
	struct addrinfo addr;
	struct addrinfo *addr_result;
	
	memset(&addr, 0, sizeof(addr));

	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_DGRAM;
	//addr.ai_protocol = 0;
	addr.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "8021", &addr, &addr_result);

	int status = bind(udp_socket, addr_result->ai_addr, (int)addr_result->ai_addrlen);

	if (status == SOCKET_ERROR) {
		LogMessage("Failed to bind to port 8021\n");
	}

	int length = 0;
	double position_data[6] = { 0.0 };
	// 0 - X
	// 1 - Y
	// 2 - Z
	// 3 - Pitch?
	// 4 - Yaw?
	// 6 - Roll?

	// Open connection to driver
	if (Open())
	{
		// Create 'exiting' event
		m_hQuitEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (m_hQuitEvent != INVALID_HANDLE_VALUE)
		{
			// NOTE: in an external tracking process disabling device orientation and
			// enabling external tracking would normally be done once the external 
			// tracking had actually begun, to avoid no tracking being active

			// Disable device orientation
			EnableDeviceOrientation(false);

			// Enable external tracking
			TrackingEnabled(true);

			while (1) {
				// Wait 10 ms for quit event on each iteration
				if (::WaitForSingleObject(m_hQuitEvent, 10) != WAIT_TIMEOUT)
					break;

				// Loop to consume all available data in the socket
				// We'll end up with the last and the most recent message
				while (ReadAvail())
					length = recv(udp_socket, (char *)&position_data[0], sizeof(double) * 6, 0);
				

				if (length == sizeof(double) * 6) {
					// If the length checks out, apply the values
					XPosOverride = position_data[0] / 10.0;
					YPosOverride = position_data[1] / 10.0;
					ZPosOverride = -(position_data[2] / 10.0);
				}
			}

			// Disable external tracking
			TrackingEnabled(false);

			// Enable device orientation
			EnableDeviceOrientation(true);
		}
		else
		{
			// Get last error code from Windows
			result = ::GetLastError();
		}

		// Close connection to driver
		Close();
	}
	else
	{
		// Get last error code from library
		result = this->GetLastError();
	}

	// Socket cleanup
	WinsockQuit();

	return result;
}

/** Pose has been recevied from driver **/
void IvryCustomTrackingApp::OnDevicePoseUpdated(const vr::DriverPose_t &pose)
{
	vr::DriverPose_t updatedPose = pose;

	// Not using device orientation?
	if (!m_bUseDeviceOrientation)
	{
		// Use tracker orientation
		updatedPose.qRotation = { 1, 0, 0, 0 };
	}

	// Use the overriden positions
	updatedPose.vecPosition[0] = XPosOverride;
	updatedPose.vecPosition[1] = YPosOverride;
	updatedPose.vecPosition[2] = ZPosOverride;

	// Send tracker pose to driver
	PoseUpdated(updatedPose);
}

/** Device orientation has been enabled/disabled by user **/
void IvryCustomTrackingApp::OnDeviceOrientationEnabled(bool enable)
{
	m_bUseDeviceOrientation = enable;
}

/** Driver is requesting tracking process quit **/
void IvryCustomTrackingApp::OnQuit()
{
	if (m_hQuitEvent != INVALID_HANDLE_VALUE)
	{
		// Signal that Run() can exit
		::SetEvent(m_hQuitEvent);
	}

	LogMessage("Shutting down\n");
}

