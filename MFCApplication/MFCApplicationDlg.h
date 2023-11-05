
// MFCApplicationDlg.h: archivo de encabezado
//

#pragma once


// Cuadro de diálogo de CMFCApplicationDlg
class CMFCApplicationDlg : public CDialogEx
{
// Construcción
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox SizewWindow;
	CComboBox m_sizeWindow;
	afx_msg void OnSelchangeCombo1();
};
