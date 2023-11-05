
// MFCApplicacion1Dlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicacion1.h"
#include "MFCApplicacion1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CMFCApplicacion1Dlg



CMFCApplicacion1Dlg::CMFCApplicacion1Dlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_MFCAPPLICACION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicacion1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CBsizeWondow);
	DDX_Control(pDX, IDC_COMBO2, m_CBarquitectura);
	DDX_Control(pDX, IDC_COMBO4, m_CBconfiguracion);
	DDX_Control(pDX, IDC_COMBO5, m_CBclaseUP3);
	DDX_Control(pDX, IDC_COMBO3, m_CMubicacionArchivo);
	DDX_Control(pDX, IDC_BUTTON1, m_Bstart);
}

BEGIN_MESSAGE_MAP(CMFCApplicacion1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplicacion1Dlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicacion1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Controladores de mensajes de CMFCApplicacion1Dlg

BOOL CMFCApplicacion1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.
	CComboBox* pCBsizeWindows = (CComboBox*)GetDlgItem(IDC_COMBO1);
	pCBsizeWindows->AddString(_T("800x600"));
	pCBsizeWindows->AddString(_T("1024x768"));
	pCBsizeWindows->AddString(_T("1280x1024"));
	CComboBox* pCBarquitectura = (CComboBox*)GetDlgItem(IDC_COMBO2);
	pCBarquitectura->AddString(_T("32bits"));
	pCBarquitectura->AddString(_T("64bits"));
	CComboBox* pCBconfiguracion = (CComboBox*)GetDlgItem(IDC_COMBO3);
	pCBconfiguracion->AddString(_T("Debug"));
	pCBconfiguracion->AddString(_T("Release"));
	CComboBox* pCBinstanceClass = (CComboBox*)GetDlgItem(IDC_COMBO4);
	pCBinstanceClass->AddString(_T("CAppParcial-1"));
	pCBinstanceClass->AddString(_T("CAppParcial-2"));
	CComboBox* pCBubicacion = (CComboBox*)GetDlgItem(IDC_COMBO5);

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CMFCApplicacion1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CMFCApplicacion1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMFCApplicacion1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicacion1Dlg::OnSelchangeCombo1()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	m_CBsizeWondow.GetWindowText(strSizeWindow);
	m_CBarquitectura.GetWindowText(strArquitectura);
	m_CBsizeWondow.GetWindowText(strSizeWindow);
	m_CBsizeWondow.GetWindowText(strInstanceClass);

	CString strCmdLine;
}


void CMFCApplicacion1Dlg::OnCbnSelchangeCombo6()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}


void CMFCApplicacion1Dlg::OnBnClickedButton1()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	 // Declaración de variables
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// Inicializar las estructuras STARTUPINFO y PROCESS_INFORMATION
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	// Especificar la ruta al ejecutable y los argumentos si es necesario
	LPCTSTR applicationName = L"C:\Users\super\OneDrive\Escritorio\Progra 4\Progra 4\uad_progra3\uad_progra3\Binaries\Exe\x64\Debug\uad_progra3.exe";  // Ruta al ejecutable
	LPWSTR commandLine = NULL;  // Puedes agregar argumentos aquí si es necesario

	CreateProcessW(applicationName, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// Crear el proceso
	if (CreateProcess(applicationName, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		int i = 0;
	}
	else
	{
		int b = 1;
	}
}
