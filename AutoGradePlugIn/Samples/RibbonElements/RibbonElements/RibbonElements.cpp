/*********************************************************************

 Copyright (C) 2010 Foxit Corporation
 All rights reserved.

 NOTICE: Foxit permits you to use, modify, and distribute this file
 in accordance with the terms of the Foxit license agreement
 accompanying it. If you have received this file from a source other
 than Foxit, then your use, modification, or distribution of it
 requires the prior written permission of Foxit.

 ---------------------------------------------------------------------

RibbonElements.cpp

 - Defines the entry point for the DLL application, the entry point is PlugInMain.

*********************************************************************/

#include "stdafx.h"
#include "RibbonElements.h"
#include "ElementsProc.h"
#include "PropertySheetPageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CRibbonElementsApp

BEGIN_MESSAGE_MAP(CRibbonElementsApp, CWinApp)
END_MESSAGE_MAP()


// CRibbonElementsApp construction

CRibbonElementsApp::CRibbonElementsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CRibbonElementsApp object

CRibbonElementsApp theApp;

/** 
	This sample gives an explanation about how to use the ribbon element.
*/

FS_DIBitmap CRibbonElementsApp::GetBmpFromRes(UINT uID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HRSRC hRes = ::FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(uID), _T("PDF"));//RT_RCDATA);
	if (hRes == NULL) return NULL;
	DWORD dwLength = ::SizeofResource(AfxGetInstanceHandle(), hRes);
	HGLOBAL hGlobal = ::LoadResource(AfxGetInstanceHandle(), hRes);
	if (hGlobal == NULL) return NULL;
	LPVOID pData = ::LockResource(hGlobal);
	if (pData == NULL) return NULL;


	//create bmp
	FS_DIBitmap pBmp = FSDIBitmapNew();
	FSDIBitmapCreate(pBmp, 32, 32, FS_DIB_Argb, NULL, 0);
	FSDIBitmapClear(pBmp, 0xffffff);
	FPD_RenderDevice pDC = FPDFxgeDeviceNew();
	FPDFxgeDeviceAttach(pDC, pBmp, 0);
	FPD_Document pPDFDoc = FPDDocOpenMemDocument(pData, dwLength, NULL);
	FPD_Object pDict = FPDDocGetPage(pPDFDoc, 0);
	FPD_Page pPage = FPDPageNew();
	FPDPageLoad(pPage, pPDFDoc, pDict, TRUE);
	FPDPageParseContent(pPage, NULL);
	FS_AffineMatrix matrix = FPDPageGetDisplayMatrix(pPage, 0, 0, 32, 32, 0);
	FPD_RenderContext pContext = FPDRenderContextNew(pPage, TRUE);
	FPDRenderContextAppendPage(pContext, pPage, matrix);
	FPDRenderContextRender(pContext, pDC, NULL, NULL);
	FPDRenderContextDestroy(pContext);
	FPDPageDestroy(pPage);
	FPDDocClose(pPDFDoc);
	FPDFxgeDeviceDestroy(pDC);

	return pBmp;
}



void CRibbonElementsApp::CreateElementsToNewCategory()
{
	FS_DIBitmap fs_bitmap = CRibbonElementsApp::GetBmpFromRes(IDR_PDF1);

	FR_RibbonBar fr_Bar = FRAppGetRibbonBar(NULL); //The RibbonBar will free by Foixt Reader or Phantom.
	FR_RibbonCategory fr_Category = FRRibbonBarAddCategory(fr_Bar, "RibbonCategory", (FS_LPCWSTR)L"RibbonCategory");	
	FR_RibbonPanel fr_Panel = FRRibbonCategoryAddPanel(fr_Category, "RibbonPanel_1", (FS_LPCWSTR)L"Autograder", NULL);
	

	//Create a Ribbon button
	FS_INT32 nElementCount = FRRibbonPanelGetElementCount(fr_Panel);
	FR_RibbonButton fr_Button =  (FR_RibbonButton)FRRibbonPanelAddElement(fr_Panel, FR_RIBBON_BUTTON,
		"RibbonButton", (FS_LPCWSTR)L"Generate Answer Key", nElementCount);
	
	FR_RibbonElement fr_ElementButton = FRRibbonPanelGetElementByName(fr_Panel, "RibbonButton");
	FRRibbonElementSetImage(fr_ElementButton, fs_bitmap, fs_bitmap);
	FRRibbonElementSetTooltip(fr_ElementButton, (FS_LPCWSTR)L"The Ribbon button Tooltip");
	FRRibbonElementSetExecuteProc(fr_ElementButton, CElementsProc::OnButtonExecuteProc);

//New
	FS_INT32 nElementCount2 = FRRibbonPanelGetElementCount(fr_Panel);
	FR_RibbonButton fr_Button2 =  (FR_RibbonButton)FRRibbonPanelAddElement(fr_Panel, FR_RIBBON_BUTTON,
		"RibbonButton2", (FS_LPCWSTR)L"Autograde Documents", nElementCount2);
	
	FR_RibbonElement fr_ElementButton2 = FRRibbonPanelGetElementByName(fr_Panel, "RibbonButton2");
	FRRibbonElementSetImage(fr_ElementButton2, fs_bitmap, fs_bitmap);
	FRRibbonElementSetTooltip(fr_ElementButton2, (FS_LPCWSTR)L"The Ribbon button Tooltip");
	FRRibbonElementSetExecuteProc(fr_ElementButton2, CElementsProc::OnButtonExecuteProc2);

	
	//Newend
	
	
	FSDIBitmapDestroy(fs_bitmap);
}

void CRibbonElementsApp::AddMenuToFilePage()
{
	FR_RibbonBar fr_Bar = FRAppGetRibbonBar(NULL); //The RibbonBar will free by Foixt Reader or Phantom.
	FR_RibbonBackStageViewItem fr_Backstage = FRRibbonBarAddBackStageViewItem(fr_Bar, "BackstageItem", (FS_LPCWSTR)L"BackstageItem", 0);
	FRRibbonBackStageViewItemAddPropertySheetPage(fr_Backstage, (FS_LPCSTR)"PropertySheetPage1", (FS_LPCWSTR)L"PropertySheetPage1",
		NULL, 0, NULL, NULL, NULL);

	FRRibbonBackStageViewItemAddPropertySheetPage(fr_Backstage, (FS_LPCSTR)"PropertySheetPage2", (FS_LPCWSTR)L"PropertySheetPage2",
		NULL, 1, CElementsProc::FRRibbonBackstageCreateProc, CElementsProc::FRRibbonBackstageDestoryProc, NULL);
	
}

//////////////////////////////////////////////////////////////////////////
/* PIExportHFTs
** ------------------------------------------------------
**/
/** 
** Create and Add the extension HFT's.
**
** @return true to continue loading plug-in,
** false to cause plug-in loading to stop.
*/
FS_BOOL PIExportHFTs(void)
{
	return TRUE;
}

/** 
The application calls this function to allow it to
<ul>
<li> Import HFTs supplied by other plug-ins.
<li> Replace functions in the HFTs you're using (where allowed).
<li> Register to receive notification events.
</ul>
*/
FS_BOOL PIImportReplaceAndRegister(void)
{
	return TRUE;
}

/* Plug-ins can use their Initialization procedures to hook into Foxit Reader's 
	 * user interface by adding menu items, toolbar buttons, windows, and so on.
	 * It is also acceptable to modify Foxit Reader's user interface later when the plug-in is running.
	 */	

void PILoadRibbonUI(void* pParentWnd)
{
	theApp.CreateElementsToNewCategory();
	theApp.AddMenuToFilePage();
}

void PILoadStatusBarUI(void* pParentWnd)
{

}
/* PIInit
** ------------------------------------------------------
**/
/** 
	The main initialization routine.
	
	@return true to continue loading the plug-in, 
	false to cause plug-in loading to stop.
*/
FS_BOOL PIInit(void)
{
	return TRUE;
}

/* PIUnload
** ------------------------------------------------------
**/
/** 
	The unload routine.
	Called when your plug-in is being unloaded when the application quits.
	Use this routine to release any system resources you may have
	allocated.

	Returning false will cause an alert to display that unloading failed.
	@return true to indicate the plug-in unloaded.
*/
FS_BOOL PIUnload(void)
{	
	return TRUE;
}

/*
DictionaryExecuteProc is the action for the new menu created by DictionaryProc.
This gets the current document, gets the user selected text, and display it in the message box.
*/
void DictionaryExecuteProc(void* clientData) {
	FR_Document pDoc = FRAppGetActiveDocOfPDDoc();
	FR_TextSelectTool textSelectTool = FRDocGetTextSelectTool(pDoc);
	FS_WideString wtext = FSWideStringNew(); //Initialize FS_WideString
	FRTextSelectToolGetSelectedText(textSelectTool, &wtext);
	const wchar_t* ctext = FSWideStringCastToLPCWSTR(wtext);//convert to a a data type that can output the in a message box.
	FS_WideString fswsShowMsg = FSWideStringNew3(ctext, wcslen(ctext) * sizeof(WCHAR));
	//switch out for QT UI or MFC.
	FRSysShowMessageBox(FSWideStringCastToLPCWSTR(fswsShowMsg), MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());

}

/*
DictionaryProc is used for the Text Select right click context menu.  
See the PIHandshake and how it calls FRAppRegisterForContextMenuAddition to register this action.
This action retrives the Text Select FR_Menu and adds a new menu and the menu's action DictionaryExecuteProc.

*/
void DictionaryProc(void *pClientData, FR_Menu popUpMenu)
{
	int nMenuItemCount = FRMenuGetMenuItemCount(popUpMenu);
	FR_MenuItem menuItem = FRMenuItemNew((const char *)L"Dictionary", (const wchar_t *)L"Dictionary", NULL, false, NULL);
	FRMenuAddMenuItem(popUpMenu, menuItem, nMenuItemCount);
	FRMenuItemSetExecuteProc(menuItem, &DictionaryExecuteProc);
	//FRSysShowMessageBox((FS_LPCWSTR)L"DictionaryProc", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}


/** PIHandshake
	function provides the initial interface between your plug-in and the application.
	This function provides the callback functions to the application that allow it to 
	register the plug-in with the application environment.

	Required Plug-in handshaking routine:
	
	@param handshakeVersion the version this plug-in works with. 
	@param handshakeData OUT the data structure used to provide the primary entry points for the plug-in. These
	entry points are used in registering the plug-in with the application and allowing the plug-in to register for 
	other plug-in services and offer its own.
	@return true to indicate success, false otherwise (the plug-in will not load).
*/
FS_BOOL PIHandshake(FS_INT32 handshakeVersion, void *handshakeData)
{
	if(handshakeVersion != HANDSHAKE_V0100)
		return FALSE;
	
	/* Cast handshakeData to the appropriate type */
	PIHandshakeData_V0100* pData = (PIHandshakeData_V0100*)handshakeData;
	
	/* Set the name we want to go by */
	pData->PIHDRegisterPlugin(pData, "RibbonElements", (FS_LPCWSTR)L"RibbonElements");

	/* If you export your own HFT, do so in here */
	pData->PIHDSetExportHFTsCallback(pData, &PIExportHFTs);
		
	/*
	** If you import plug-in HFTs, replace functionality, and/or want to register for notifications before
	** the user has a chance to do anything, do so in here.
	*/
	pData->PIHDSetImportReplaceAndRegisterCallback(pData, &PIImportReplaceAndRegister);

	/* Perform your plug-in's initialization in here */
	pData->PIHDSetInitDataCallback(pData, &PIInit);
	PIInitUIProcs initUIProcs;
	INIT_CALLBACK_STRUCT(&initUIProcs, sizeof(PIInitUIProcs));
	initUIProcs.lStructSize = sizeof(PIInitUIProcs);
	initUIProcs.PILoadRibbonUI = PILoadRibbonUI;
	initUIProcs.PILoadStatusBarUI = PILoadStatusBarUI;
	pData->PIHDSetInitUICallbacks(pData, &initUIProcs);	

	//Register a right select menu item
	FRAppRegisterForContextMenuAddition("Select", &DictionaryProc, "clientData");

	/* Perform any memory freeing or state saving on "quit" in here */
	pData->PIHDSetUnloadCallback(pData, &PIUnload);

	return TRUE;
}
