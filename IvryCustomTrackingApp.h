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

#ifndef _IVRY_CUSTOM_TRACKING_APP_H
#define _IVRY_CUSTOM_TRACKING_APP_H

#include "IvryTrackingApp.h"

class IvryCustomTrackingApp : public IvryTrackingApp
{
public:
	/** Constructor/destructor **/
	IvryCustomTrackingApp();
	~IvryCustomTrackingApp();

	/** Run tracker **/
	virtual DWORD Run();

protected:
	/** Pose has been recevied from driver **/
	virtual void OnDevicePoseUpdated(const vr::DriverPose_t &pose);

	/** Device orientation has been enabled/disabled by user **/
	virtual void OnDeviceOrientationEnabled(bool enable);

	/** Driver is requesting tracking process quit **/
	virtual void OnQuit();

private:
	/** Used to signal process must quit **/
	HANDLE m_hQuitEvent;

	/** Simulated position **/
	double m_afPosition[3];

	/** Use device orientation tracking? **/
	bool m_bUseDeviceOrientation;
};

#endif // _IVRY_CUSTOM_TRACKING_APP_H