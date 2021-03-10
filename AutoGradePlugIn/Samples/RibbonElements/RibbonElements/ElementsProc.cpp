#include "stdafx.h"
#include "ElementsProc.h"
#include "resource.h"
#include "PropertySheetPageDlg.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


void InsertTextObj(FPD_Page FPDPage, FPD_TextState textState, FPD_ColorState colorState,
	FS_ByteString csDisplay, float x, float y)
{
	FPD_PageObject pTextObject = FPDTextObjectNew();
	FPDTextObjectSetTextState(pTextObject, textState);
	FPDPageObjectSetColorState(pTextObject, colorState);
	FPDTextObjectSetText(pTextObject, csDisplay);
	FPDTextObjectSetPosition(pTextObject, x, y);
	//FS_POSITION pos = FPDPageGetLastObjectPosition(FPDPage);
	FS_POSITION pos = FPDPageGetFirstObjectPosition(FPDPage);
	
	FPDPageInsertObject(FPDPage, NULL, pTextObject);
}

void InsertWrongAnswers(wstring word2, float posx, float posy)
{
	FPD_Document m_FPDDocument = NULL;
	FPD_Object m_FPDPageDict = NULL;
	FPD_Page m_FPDPage = NULL;
	FPD_FontEncoding m_FPDFontEncoding = NULL;
	FPD_Font m_FPDFont = NULL;
	FPD_TextState m_FPDTextState = NULL;
	FPD_ColorSpace m_FPDColorSpace = NULL;
	FPD_ColorState m_FPDColorState = NULL;

	
	string s(word2.begin(), word2.end());
	FS_LPCSTR ptr1 = s.c_str();
	const FS_ByteString bstext1 = FSByteStringNew3(ptr1, strlen(ptr1));
	
	FR_Document pFRDoc = FRAppGetActiveDocOfPDDoc();
	m_FPDDocument = FRDocGetPDDoc(pFRDoc);
	FR_DocView pDocView = FRDocGetCurrentDocView(pFRDoc);
	FR_PageView pPageView = FRDocViewGetPageView(pDocView, 0);
	m_FPDPage = FRPageViewGetPDPage(pPageView);

	//font 
	m_FPDFontEncoding = FPDFontEncodingNew2(FPD_FONT_ENCODING_WINANSI);
	m_FPDFont = FPDDocAddStandardFont(m_FPDDocument, "TimesNewRoman", m_FPDFontEncoding);
	m_FPDTextState = FPDTextStateNew();
	FPDTextStateSetFont(m_FPDTextState, m_FPDFont);
	FPDTextStateSetFontSize(m_FPDTextState, 12);

	// color
	float* colorSpaceBuff = new float[3];
	memset(colorSpaceBuff, 0, 3 * sizeof(float));
	m_FPDColorSpace = FPDColorSpaceGetStockCS(FPD_CS_DEVICERGB);
	FPDColorSpaceSetRGB(m_FPDColorSpace, colorSpaceBuff, 255, 0, 0);
	m_FPDColorState = FPDColorStateNew();
	FPDColorStateSetFillColor(m_FPDColorState, m_FPDColorSpace, colorSpaceBuff, 3);
	delete[] colorSpaceBuff;

	// insert Text obj
	FS_FLOAT height = FPDPageGetPageHeight(m_FPDPage);
	FS_FLOAT width = FPDPageGetPageWidth(m_FPDPage);
	InsertTextObj(m_FPDPage, m_FPDTextState, m_FPDColorState, bstext1, posx, posy);
	FPDPageGenerateContent(m_FPDPage);
	FRDocViewDrawNow(pDocView);
}

void Testdemo(int score, int max_score)
{
	FPD_Document m_FPDDocument = NULL;
	FPD_Object m_FPDPageDict = NULL;
	FPD_Page m_FPDPage = NULL;
	FPD_FontEncoding m_FPDFontEncoding = NULL;
	FPD_Font m_FPDFont = NULL;
	FPD_TextState m_FPDTextState = NULL;
	FPD_ColorSpace m_FPDColorSpace = NULL;
	FPD_ColorState m_FPDColorState = NULL;
	FS_LPCSTR ptr1 = "Total Score: ";
	
	char buffer[50];
	_itoa_s(score, buffer, 50, 10);
	FS_LPCSTR ptr2 = buffer;
	
	FS_LPCSTR display = "Max Score: ";
	
	char buffer2[50];
	_itoa_s(max_score, buffer2, 50, 10);
	FS_LPCSTR ptr3 = buffer2;
	
	const FS_ByteString bstext1 = FSByteStringNew3(ptr1, strlen(ptr1));
	const FS_ByteString bstext2 = FSByteStringNew3(ptr2, strlen(ptr2));
	const FS_ByteString bstext3 = FSByteStringNew3(display, strlen(display));
	const FS_ByteString bstext4 = FSByteStringNew3(ptr3, strlen(ptr3));

	FR_Document pFRDoc = FRAppGetActiveDocOfPDDoc();
	m_FPDDocument = FRDocGetPDDoc(pFRDoc);
	FR_DocView pDocView = FRDocGetCurrentDocView(pFRDoc);
	FR_PageView pPageView = FRDocViewGetPageView(pDocView, 0);
	m_FPDPage = FRPageViewGetPDPage(pPageView);

	//font 
	m_FPDFontEncoding = FPDFontEncodingNew2(FPD_FONT_ENCODING_WINANSI);
	m_FPDFont = FPDDocAddStandardFont(m_FPDDocument, "TimesNewRoman", m_FPDFontEncoding);
	m_FPDTextState = FPDTextStateNew();
	FPDTextStateSetFont(m_FPDTextState, m_FPDFont);
	FPDTextStateSetFontSize(m_FPDTextState, 12);

	// color
	float* colorSpaceBuff = new float[3];
	memset(colorSpaceBuff, 0, 3 * sizeof(float));
	m_FPDColorSpace = FPDColorSpaceGetStockCS(FPD_CS_DEVICERGB);
	FPDColorSpaceSetRGB(m_FPDColorSpace, colorSpaceBuff, 255, 0, 0);
	m_FPDColorState = FPDColorStateNew();
	FPDColorStateSetFillColor(m_FPDColorState, m_FPDColorSpace, colorSpaceBuff, 3);
	delete[] colorSpaceBuff;

	// insert Text obj
	FS_FLOAT height = FPDPageGetPageHeight(m_FPDPage);
	FS_FLOAT width = FPDPageGetPageWidth(m_FPDPage);
	InsertTextObj(m_FPDPage, m_FPDTextState, m_FPDColorState, bstext1, width - 120, height - 30); 
	InsertTextObj(m_FPDPage, m_FPDTextState, m_FPDColorState, bstext2, width - 50, height - 30);
	InsertTextObj(m_FPDPage, m_FPDTextState, m_FPDColorState, bstext3, width - 120, height - 45);
	InsertTextObj(m_FPDPage, m_FPDTextState, m_FPDColorState, bstext4, width - 50, height - 45);
	FPDPageGenerateContent(m_FPDPage);
	FRDocViewDrawNow(pDocView);
}

CElementsProc::CElementsProc(void)
{
}


CElementsProc::~CElementsProc(void)
{
}

void CElementsProc::OnSliderExecuteProc(void* clientData)
{
	//Do something when the slider is executed.
	FR_RibbonSlider fr_Slider = (FR_RibbonSlider)clientData;
	FS_INT32 nPos = FRRibbonSliderGetPos(fr_Slider);
	if (nPos == 50)
	{
		FRSysShowMessageBox((FS_LPCWSTR)L"Slider Pos = 50", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	}
	else if (nPos == 100)
	{
		FRSysShowMessageBox((FS_LPCWSTR)L"Slider Pos = 100", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	}

}

FS_BOOL CElementsProc::OnSliderMarkedProc(void* clientData)
{
	return FALSE;
}

FS_BOOL CElementsProc::OnSliderEnabledProc(void* clientData)
{
	//Used to determine whether the slider is enabled.
	return TRUE;
}
void CElementsProc::OnButtonFreeData(void* clientDate)
{
	FS_WideString fsButtonData = (FS_WideString)clientDate;
	FS_LPCWSTR str = FSWideStringCastToLPCWSTR(fsButtonData);
	FSWideStringDestroy(fsButtonData);
}


void CElementsProc::OnButtonExecuteProc(void* clientDate)
{

	FS_WideString fsButtonData = (FS_WideString)clientDate;		
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	const wchar_t* inputfile = L"";
	FR_Document frDocument = NULL;
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		CString filepath = dlgFile.GetPathName();
		inputfile = filepath.GetString();
		frDocument = FRDocOpenFromFile(inputfile, (FS_LPCSTR)L"", true, true); //shows how to load a PDF and display it
	}

	if (!frDocument) {
		return;
	}
	FPD_Document frdDocument = FRDocGetPDDoc(frDocument);
	FR_DocView docView = FRDocGetCurrentDocView(frDocument);
	int nPageViews = FRDocViewCountPageViews(docView);

	wofstream file(L"Test.txt");
	int count = 0;
	for (int i = 0; i != nPageViews; ++i)
	{	
		FR_PageView pageView = FRDocViewGetPageView(docView, i);
		FPD_Page fpdPage = FRPageViewGetPDPage(pageView);
		FPD_InterForm fpdInterform = FPDInterFormNew(frdDocument, true);
		FS_INT32 formcount=  FPDInterFormCountPageControls(fpdInterform, fpdPage);
		auto formdataarray = new const wchar_t*[formcount][2];
		
		
		for (int j = 0; j != formcount; ++j)
		{
			FPD_FormControl fpdFormControl = FPDInterFormGetPageControl(fpdInterform, fpdPage, j);
			FPD_FormField fpdFormField= FPDFormControlGetField(fpdFormControl);
			FS_WideString fieldName = FSWideStringNew();
			FPDFormFieldGetFullName(fpdFormField,&fieldName);
			formdataarray[j][1] = FSWideStringCastToLPCWSTR(fieldName);
			FS_WideString value = FSWideStringNew();
			FPDFormFieldGetValue(fpdFormField,&value);
			formdataarray[j][2] = FSWideStringCastToLPCWSTR(value);
			wstring string1(formdataarray[j][1]);
			wstring string2(formdataarray[j][2]);
			
			if (string2 != L"" && string1!= L"Score") {
				count++;
			}
			file << formdataarray[j][1] << " "<< formdataarray[j][2]<<"\n";
		}
	}
	file << L"Max" << " " << to_wstring(count)  << "\n";
	FS_LPCWSTR display = L" question and answers have been processed. \nIf the number of questions processed is wrong, please ensure the pdf is properly annotated and try again. \nNext, please click on autograde and select the PDFs to grade. ";
	std::wstring mywstring(display);
	std::wstring concatted_stdstr = to_wstring(count) + mywstring;
	LPCWSTR concatted = concatted_stdstr.c_str();
	FRSysShowMessageBox(concatted, MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}

void CElementsProc::OnButtonExecuteProc2(void* clientDate)
{
	FS_WideString fsButtonData = (FS_WideString)clientDate;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	const wchar_t* inputfile = L"";
	FR_Document frDocument = NULL;
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		CString filepath = dlgFile.GetPathName();
		inputfile = filepath.GetString();
		frDocument = FRDocOpenFromFile(inputfile, (FS_LPCSTR)L"", true, true); //shows how to load a PDF and display it
	}
	if (!frDocument) {
		return;
	}
	FPD_Document frdDocument = FRDocGetPDDoc(frDocument);
	FR_DocView docView = FRDocGetCurrentDocView(frDocument);
	int nPageViews = FRDocViewCountPageViews(docView);

	wfstream file(L"Test.txt");
	if (!file.is_open()) {
		FRSysShowMessageBox(L"File is corrupted or does not exist. Please re-generate the answer key.", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	}
	int score = 0;
	wstring max_score;
	for (int i = 0; i != nPageViews; ++i)
	{
		FRDocParsePage(frDocument, i);
		FR_PageView pageView = FRDocViewGetPageView(docView, i);
		FPD_Page fpdPage = FRPageViewGetPDPage(pageView);
		FPD_InterForm fpdInterform = FPDInterFormNew(frdDocument, true);
		FS_INT32 formcount = FPDInterFormCountPageControls(fpdInterform, fpdPage);
		auto formdataarray = new const wchar_t*[formcount][2];	

		for (int j = 0; j != formcount; ++j)
		{
			FPD_FormControl fpdFormControl = FPDInterFormGetPageControl(fpdInterform, fpdPage, j);
			FPD_FormField fpdFormField = FPDFormControlGetField(fpdFormControl);
			FS_WideString fieldName = FSWideStringNew();
			FPDFormFieldGetFullName(fpdFormField, &fieldName);
			formdataarray[j][1] = FSWideStringCastToLPCWSTR(fieldName);
			FS_WideString value = FSWideStringNew();
			FPDFormFieldGetValue(fpdFormField, &value);
			formdataarray[j][2] = FSWideStringCastToLPCWSTR(value);
			wstring word1, word2;
			file >> word1;
			file >> word2;

			if (word1 == formdataarray[j][1] && word1 != L"Score" && word1 != L"ScorePage") {
				if (word2 == formdataarray[j][2]){
					score++;
				}
				else {
					FS_FloatRect rect;
					FS_FloatRect *out = (FS_FloatRect*)malloc(sizeof(rect));
					FPDFormControlGetRect(fpdFormControl ,out); 
					InsertWrongAnswers(L"X", out->left - 15, out->top-10);
					InsertWrongAnswers(L"Correct: "+word2, out->left - 45, out->top-25);
					free(out);
				}
			}
			if (word1 == L"Max") {
				max_score = word2;
			}
		}
	}
	Testdemo(score, stoi(max_score));
	
	//Aim to save all the changes in the current file.
	bool a = FPDDocSave(frdDocument,
		(FS_LPSTR)inputfile, //Currently any static file location will work,
		FPD_SAVE_DEFAULT,
		false
	);

	/*if (a) {
		FRSysShowMessageBox(L"Saved", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	}
	else {
		FRSysShowMessageBox(L"Not Saved", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	}*/
}



FS_BOOL CElementsProc::OnButtonMarkedProc(void* clientDate)
{
	return FALSE;
}
FS_BOOL CElementsProc::OnButtonEnableProc(void* clientDate)
{
	return TRUE;
}

HWND CElementsProc::FRRibbonBackstageCreateProc(HWND hParentWnd, void* clientData)
{
	PropertySheetPageDlg *pPage = new PropertySheetPageDlg();
	if (pPage)
	{
		BOOL bCreate = pPage->Create(IDD_DLG_PROPERTYSHEETPAGE, CWnd::FromHandle(hParentWnd));
		if (bCreate)
		{
			return pPage->GetSafeHwnd();
		}
	}	
	return NULL;

}

void CElementsProc::FRRibbonBackstageDestoryProc(void* pDialog, void* clientData)
{
	PropertySheetPageDlg* pPage = (PropertySheetPageDlg*)clientData;
	if (NULL != pPage)
	{
		delete pPage;
		pPage = NULL;
	}
}
