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

#ifndef _IVRY_TRACKING_APP_H
#define _IVRY_TRACKING_APP_H

#include <windows.h>
#include <openvr_driver.h>

/** Private **/
class IvryTrackingApp_Private;

class IvryTrackingApp
{
public:
	/** Constructor/destructor */
	IvryTrackingApp();
	~IvryTrackingApp();

	/** Run tracker **/
	virtual DWORD Run() = 0;

	/** Open/close connection to driver **/
	bool Open();
	void Close();

	/** Driver is requesting tracking process quit **/
	virtual void OnQuit() {}

	/** Nofify driver that ext tracking has been enabled/disabled **/
	void TrackingEnabled(bool enable);

	/** Get min/max tracking rates (in Hz) **/
	virtual float GetMinTrackingRate() { return 0; }
	virtual float GetMaxTrackingRate() { return 0; }

	/** Get/Set tracking rate (in Hz) **/
	virtual float GetTrackingRate() { return 0; }
	virtual void SetTrackingRate(float rate) {}

	/** Request that driver recenters headset **/
	void RecenterDeviceOrientation();

	/** Enable/disable device orientation tracking **/
	void EnableDeviceOrientation(bool enable);

	/** Enable/disable tracking LEDs (if any) **/
	void EnableDeviceLeds(bool enable);

protected:
	/** Device orientation has been enabled/disabled by user **/
	virtual void OnDeviceOrientationEnabled(bool enable) {}

	/** Pose has been recevied from driver **/
	virtual void OnDevicePoseUpdated(const vr::DriverPose_t &pose) {}

	/** Send pose to driver **/
	void PoseUpdated(const vr::DriverPose_t &pose);

	/** Get device orientation **/
	vr::HmdQuaternion_t GetDeviceOrientation();

	/** Driver has recentered headset **/
	virtual void OnDeviceRecenter() {}

	/** Driver has changed headset yaw offset from SteamVR center (Room Setup) **/
	virtual void OnDeviceYawOffsetChanged(double offset) {}

	/** Get last error **/
	DWORD GetLastError();

	/** Send log message to driver **/
	void LogMessage(const char* message);

private:
	/** Private **/
	friend IvryTrackingApp_Private;
	IvryTrackingApp_Private *m_pPrivate;
};

#endif // _IVRY_TRACKING_APP_H