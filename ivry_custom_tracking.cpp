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

#include "IvryCustomTrackingApp.h"
#include <tchar.h>

/** Use correct version of library for compiler **/
#if !defined(_MSC_VER) || _MSC_VER < 1800
# error Unsupported Compiler!
#elif _MSC_VER == 1800
# pragma comment (lib, "IvryTrackingApp_VS2013")
#elif _MSC_VER == 1900
# pragma comment (lib, "IvryTrackingApp_VS2015")
#elif _MSC_VER > 1900 && _MSC_VER < 1920
# pragma comment (lib, "IvryTrackingApp_VS2017")
#elif _MSC_VER >= 1920
# pragma comment (lib, "IvryTrackingApp_VS2019")
#endif

/** Entry point **/
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	// Run the app
	IvryCustomTrackingApp theApp;
	return theApp.Run();
}

