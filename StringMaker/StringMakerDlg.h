
// StringMakerDlg.h : header file
// Declararea tuturor claselor sau variabilelor care vor fi folosite ulterior.

#pragma once


// CStringMakerDlg dialog
class CStringMakerDlg : public CDialogEx
{
// Construction
public:
	CStringMakerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRINGMAKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_label;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCommandexit();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio9();

	// Variablila pentru input
	CString userInput;

	// Enumeratia pentru alegerea optiunii de formatare a textului.
	enum radioButtons
	{
		radioButtonCol_1Row1,
		radioButtonCol_1Row2,
		radioButtonCol_1Row3,
		radioButtonCol_1Row4,
		radioButtonCol_1Row5,
		radioButtonCol_2Row1,
		radioButtonCol_2Row2,
		radioButtonCol_2Row3,
		radioButtonCol_2Row4,
		radioButtonCol_2Row5
	};

	// Variabila a enumeratiei.
	radioButtons option;
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();

	// This goes to show output to user
	CString userOutput;
	CString instructionOutput;
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedButton1();
};
