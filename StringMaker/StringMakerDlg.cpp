
// StringMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringMaker.h"
#include "StringMakerDlg.h"
#include "afxdialogex.h"
#include <string>
#include <string.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog pentru Dialogul "About".

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

/*
	Implementarea clasei ajutatoare pentru encriptarea textului.
*/
class EncryptionHelper
{
private:
	// Text variable pentru encryption.
	std::string text;

	// Destructorul clasei care este privat.
	~EncryptionHelper()
	{
		this->text = '/0';
	}
public:
	// Constructorul clasei.
	EncryptionHelper(std::string text)
	{
		this->text = text;
	}

	// Functia de encriptare a textului.
	std::string encrypt()
	{
		if (text.length() < 1)
			return this->text;
		for (int i = 0; (i < this->text.length() && this->text[i] != '\0'); i++)
			this->text[i] = this->text[i] - 25;
		return this->text;
	}
};


/*
	Declararea clasei proprii unde au fost incluse toate functiile
	statice folosite pentru procesarea textului.
*/
class StringRemakers
{

public:

	// Functia de inversare a textului.
	static std::string reverse(std::string str)
	{
		if (str.length() < 1)
			return str;
		int len = str.length();

		// Se interschimba elementul din ultima pozitie cu cel din prima pozitie.
		// Se mareste prima pozitie interschimbata cu ultima pozitie, decrementata cu o unitate si aceasta.
		// Se repeta pana la jumatatea vectorului.
		for (int i = 0; i < len/2; i++)
		{
			str.at(i) = str.at(i) ^ str.at(len - 1 - i);
			str.at(len - 1 - i) = str.at(i) ^ str.at(len - 1 - i);
			str.at(i) = str.at(i) ^ str.at(len - 1 - i);
		}
		return str;
	}

	// Metoda utilizata pentru compresarea textului.
	static std::string compression(std::string str)
	{
		if (str.length() < 1)
			return str;
		int len = str.length();
		// Crearea unui string nou.
		std::string newStr;
		for (int i = 0; i < len; i++)
		{
			// Se scrie elementul in noul string.
			char compressedChar = str.at(i);
			if (compressedChar != '@')
			{
				newStr+= compressedChar;
			}
			else
			{
				return "INVALID INPUT! No \"@\" symbol permited.";
			}
			int index = i+1;

			// In caz ca se repeta elementul dat, se umara aparitia lui.
			if (index < len)
			{
				int charsInARow =0;
				while (index<len && str.at(index) == compressedChar)
				{
					charsInARow++;
					index++;
				}

				// Dupa numararea caracterelor care se repeta, ele sunt introduse in noul stirng.
				if (charsInARow)
				{
					newStr += "@"+std::to_string(charsInARow+1);
				}
				i += charsInARow;
			}
		}
		return newStr;
	}

	// Metoda utilizata pentru decompresarea textului.
	static std::string decompression(std::string str)
	{
		if (str.length() < 1)
			return str;
		int len = str.length();
		std::string newStr;
		for (int i = 0; i < len;)
		{
			char checkedChar = str.at(i);

			// Se cauta elementul '@' care e simbolul unic a compresarii.
			if (checkedChar == '@')
			{
				if (!isdigit(str.at(i + 1)))
				{
					return "INVALID INPUT! No digit detected after \"@\" symbol.";
				}
				char previousChar = str.at(i - 1);
				int times = atoi(&str.at(i + 1));
				for (int j = 1; j < times; j++)
				{
					newStr += previousChar;
				}
				i += 2;
			}
			else
			{
				newStr += checkedChar;
				i++;
			}
		}
		return newStr;
	}

	// Metoda pentru schimbarea case-lui literelor.
	static std::string changeCase(std::string str)
	{
		if (str.length() < 1)
			return str;
		std::string lower= "qwertyuiopasdfghjklzxcvbnm";
		std::string upper = "QWERTYUIOPLKJHGFDSAZXCVBNM";

		int len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (lower.find(str.at(i)) != -1)
			{
				str.at(i) = str.at(i)-32;
				continue;
			}
			if (upper.find(str.at(i)) != -1)
			{
				str.at(i) = str.at(i) + 32;
			}
		}

		return str;
	}

	// Inversarea cuvintelor in text.
	static std::string reverseWords(std::string str)
	{
		if (str.length() < 1)
			return str;
		std::string newStr;
		for (int i = str.length()-1; i >=0;)
		{
			if (isalpha(str.at(i)) || isdigit(str.at(i)))
			{

				int index = i;
				
				//Se numara urmatoarele litere a stringului si creste valoarea cat timp e litera/cifra.
				while (index >= 0 && (isalpha(str.at(index)) || isdigit(str.at(index))))
				{
					index--;
				}

				//Se introduce cuvantul detectat in noul string.
				for (int j = index+1; j <= i; j++)
					newStr += str.at(j);
				i = index;
			}
			else
			{
				int index = i;
				//
				// Se cauta toate simbolurile consecutive.
				while (index >= 0 && (!isalpha(str.at(index)) && !isdigit(str.at(index))))
				{
					index--;
				}
				
				// Se introduc in noul stirng.
				for (int j = index + 1; j <= i; j++)
					newStr += str.at(j);
				i = index;
			}
		}

		return newStr;
	}

	// Metoda pentru numerotarea vocalelor.
	static std::string countVowels(std::string str)
	{
		if (str.length() < 1)
			return str;
		// Se declara un vector container al vocalelor.
		std::string vowels("aeiou");
		int len = str.length();
		int countVowels = 0;

		//Se cauta vocalele in text si se numara.
		for (int i = 0; i < len; i++)
		{
			if (vowels.find(str.at(i))!=-1)
			{
				countVowels++;
			}
		}

		return "Text has " + std::to_string(countVowels) + " vowels.";
	}

	// Metoda pentru numararea consoanelor.
	static std::string countConsons(std::string str)
	{
		if (str.length() < 1)
			return str;
		// Se declara un vector container al consoanelor.
		std::string consons("qwrtyplkjhgfdszxcvbnm");
		int len = str.length();
		int countConsons = 0;

		//Se cauta consoanele in text si se numara.
		for (int i = 0; i < len; i++)
		{
			if (consons.find(str.at(i)) != -1)
			{
				countConsons++;
			}
		}

		return "Text has " + std::to_string(countConsons) + " consons.";
	}

	// Metoda de numarare a cuvintelor se face pe baza spatiilor gasite intre cuvinte.
	static std::string countWords(std::string str)
	{
		// Se verifica daca textul nu este null.
		if (str.length() < 1)
			return str;
		int nSpaces = 0;
		unsigned int i = 0;

		// Sare peste primele spatii.
		while (isspace(str.at(i)))
			i++;

		// Se numara fiecare spatiu.
		for (; i < str.length(); i++)
		{
			if (isspace(str.at(i)))
			{
				nSpaces++;

				// Se sare peste spatiile multiple.
				while (isspace(str.at(i++)) && i < str.length());
					
			}
		}

		// Daca ultimul element e spatiu, atunci se decrementeaza variabila nSpaces.
		if (isspace(str.at(str.length() - 1)))
			nSpaces--;
		return "Text has "+std::to_string(nSpaces + 1)+" words.";
	}

	// Metoda de encriptare a textului.
	static std::string encrypt(std::string str)
	{
		EncryptionHelper *encryptor = new EncryptionHelper(str);
		return encryptor->encrypt();
	}

	// Metoda de decriptare a textului.
	static std::string decrypt(std::string str)
	{
		if (str.length() < 1)
			return str;
		for (int i = 0; (i < str.length() && str[i] != '\0'); i++)
			str[i] = str[i] + 25;
		return str;
	}

};


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

/*
	Focusarea dialogurilor de pornire / oprire a programului.
*/
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


/*
	Initialiazarea variabilelor folosite in acest dialog.
*/
CStringMakerDlg::CStringMakerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STRINGMAKER_DIALOG, pParent)
	, userOutput(_T("Output goes here."))
	, userInput(_T("Enter your text here."))
	, instructionOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


/*
	Asignarea variabilelor cu elementele formei.
	De asemenea declararea unui font, folosit pentru textul static din titlu.
*/
void CStringMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_STRING, m_label);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 21;                      // request a 12-pixel-height font
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE,
		_T("Tahoma"), 21);                    // request a face name "Arial"
	VERIFY(font.CreateFontIndirect(&lf));

	m_label.SetFont(&font, TRUE);
	DDX_Text(pDX, IDC_EDIT1, userInput);
	DDX_Text(pDX, IDC_EDIT2, userOutput);
}

/*
	Definirea metodelor de manipulare a elementelor de pe forma.
*/
BEGIN_MESSAGE_MAP(CStringMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(NULL, &CStringMakerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO7, &CStringMakerDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO11, &CStringMakerDlg::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO3, &CStringMakerDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CStringMakerDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO10, &CStringMakerDlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDOK, &CStringMakerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStringMakerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CStringMakerDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CStringMakerDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CStringMakerDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO9, &CStringMakerDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO8, &CStringMakerDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO4, &CStringMakerDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CStringMakerDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CStringMakerDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CStringMakerDlg::OnBnClickedMfcbutton2)
END_MESSAGE_MAP()


/*
	Initializarea formei.
*/
BOOL CStringMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Selectarea butonului implicit la pornirea formei.
	CWnd::CheckRadioButton(IDC_RADIO2, IDC_RADIO11, IDC_RADIO7);
	option = radioButtonCol_1Row1;

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*
	Forma "about". Nu se utilizeaza.
*/
void CStringMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStringMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStringMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CStringMakerDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

/*
	Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio7()
{
	option = radioButtonCol_1Row1;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//change instruction text
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option counts all the words from the text and shows their number."));
	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio11()
{
	option = radioButtonCol_1Row5;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option decrypts the input text with the default key and shows its content."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio3()
{
	option = radioButtonCol_2Row2;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option compresses the multiple symbols which are in a row (more than 2). '@' symbol is forbidden.\nIt generates an '@' symbol followed by a number which represents how many symbols were in a row.\nExample: \"zoo\" is converted in \"zo@2\" where \"oo\" is converted into \"o@2\" which means there were 2 'o' symbol in a row."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio2()
{
	option = radioButtonCol_2Row1;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option switches letters cases. Upper case letter becomes lower case and vice versa."));

	// TODO: Add your control notification handler code here
}


/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio10()
{
	option = radioButtonCol_1Row4;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//	
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option encrypts the input text with a built-in key and shows its content."));

}

/*
	Codul pentru butonul "Make it". 
	Contine un switch pentru schimbarea optiunii, in dependenta de butonul radio selectat.
	Dupa asta, dupa care reformateaza textul si il afiseaza in Edit Box-ul de la output.
*/
void CStringMakerDlg::OnBnClickedOk()
{
	UpdateData();
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);

	// Transforming input to userOutput
	switch (option)
	{


	case radioButtonCol_1Row1:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::countWords(in)).c_str();

		break;
	}


	case radioButtonCol_1Row2:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::countVowels(in)).c_str();

		break;
	}


	case radioButtonCol_1Row3:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::countConsons(in)).c_str();

		break;
	}


	case radioButtonCol_1Row4:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::encrypt(in)).c_str();

		break;
	}


	case radioButtonCol_1Row5:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::decrypt(in)).c_str();

		break;
	}


	case radioButtonCol_2Row1:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::changeCase(in)).c_str();

		break;
	}


	case radioButtonCol_2Row2:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::compression(in)).c_str();

		break;
	}


	case radioButtonCol_2Row3:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::decompression(in)).c_str();

		break;
	}


	case radioButtonCol_2Row4:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::reverse(in)).c_str();

		break;
	}


	case radioButtonCol_2Row5:
	{
		CT2CA pszConvertedAnsiString(userInput);
		std::string in(pszConvertedAnsiString);
		userOutput = (StringRemakers::reverseWords(in)).c_str();

		break;
	}


		break;
	default:
		break;
	}
	GetDlgItem(IDC_MFCBUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(userOutput);
}

/*
	Butonul de inchidere a programului.
*/
void CStringMakerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

/*
	Nu se utilizeaza.
	@deprecated
*/
void CStringMakerDlg::OnBnClickedCommandexit()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::On
}


void CStringMakerDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

/*
Codul pentru Text Box-ul de input.
*/
void CStringMakerDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

/*
	Codul pentru Text Box-ul de output.
*/
void CStringMakerDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio9()
{
	option = radioButtonCol_1Row3;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//Editam sectiunea pentru instrctiune.
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option counts all the consons from the input text and shows their number."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio8()
{
	option = radioButtonCol_1Row2;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option counts all the vowels from the input text and shows thier number."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio4()
{
	option = radioButtonCol_2Row3;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option will decompress an already compressed text.\nNote: Characters after '@' symbol are not allowed. Also check out \"Compression text\" instruction for more details."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio5()
{
	option = radioButtonCol_2Row4;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option reverses the text and shows its reversed version."));

	// TODO: Add your control notification handler code here
}

/*
Codul pentru butonul radio.
*/
void CStringMakerDlg::OnBnClickedRadio6()
{
	option = radioButtonCol_2Row5;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->BringWindowToTop();
	//
	GetDlgItem(IDC_STATIC3)->SetWindowText(TEXT("Instruction: This option reverses words from the text.\nExample: \"I do coding.\" becomes \".coding do I\""));

	// TODO: Add your control notification handler code here
}

/*
	Codul pentru butonul de schimb al textului.
	Acest buton schimba codul de la input, cu cel de la output, si sterge textul de la output.
*/
void CStringMakerDlg::OnBnClickedMfcbutton2()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	userInput = userOutput;
	userOutput = "";
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(userInput);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(userOutput);

	//userInput(_T("Enter your text here."));


}
