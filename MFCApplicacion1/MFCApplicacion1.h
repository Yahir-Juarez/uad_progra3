
// MFCApplicacion1.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'pch.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CMFCApplicacion1App:
// Consulte MFCApplicacion1.cpp para obtener información sobre la implementación de esta clase
//

class CMFCApplicacion1App : public CWinApp
{
public:
	CMFCApplicacion1App();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicacion1App theApp;
