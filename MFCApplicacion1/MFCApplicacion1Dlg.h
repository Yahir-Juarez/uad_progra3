
// MFCApplicacion1Dlg.h: archivo de encabezado
//

#pragma once


// Cuadro de diálogo de CMFCApplicacion1Dlg
class CMFCApplicacion1Dlg : public CDialogEx
{
// Construcción
public:
	CMFCApplicacion1Dlg(CWnd* pParent = nullptr);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICACION1_DIALOG };
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
	CComboBox m_CBsizeWondow;
	afx_msg void OnSelchangeCombo1();
	CComboBox m_CBarquitectura;
	CComboBox m_CBconfiguracion;
	CComboBox m_CBclaseUP3;
	CComboBox m_CMubicacionArchivo;
	CString strSizeWindow, strArquitectura, strConfiguracion, strInstanceClass;
	afx_msg void OnCbnSelchangeCombo6();
	CButton m_Bstart;
	afx_msg void OnBnClickedButton1();
};
