/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/

#include "stdafx.h"
#include "utils.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
static HANDLE outputWinHandle = NULL;

void createWinConsole(int width, int height)
{
	COORD coord;

	AllocConsole();
	SetConsoleTitle("Output Window");
	outputWinHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	coord.X = width;
	coord.Y = height;
	SetConsoleScreenBufferSize(outputWinHandle, coord);

#if 0
	SMALL_RECT rect;
	rect.Top		= 0;
	rect.Left		= 0;
	rect.Right	= width;
	rect.Bottom = height;
	SetConsoleWindowInfo(outputWinHandle, FALSE, &rect);
#endif
}

void freeWinConsole(void)
{
	FreeConsole();
}

void debugPrint(char * str, ...)
{
	DWORD cCharsWritten;
	char msg_buf[256];
	va_list list;

	va_start(list, str);
	vsprintf(msg_buf, str, list);
	va_end(list);

	if (outputWinHandle)
		WriteConsole(outputWinHandle, msg_buf, strlen(msg_buf), &cCharsWritten, NULL);

	OutputDebugString(msg_buf);
}


BOOL doesFileExist(CString &string)
{
	CFile file;

	if (!file.Open(string, CFile::modeRead)) {
		return (FALSE);
	}

	file.Close();

	return (TRUE);
}


BOOL verifyFileExtension(CString &file, char *ext)
{
	CString temp;
	CString temp1;

	//copy and uppercase extension
	temp1 = ext;
	temp1.MakeUpper();

	temp = file.Right(3);
	temp.MakeUpper();

	if (temp == temp1) {
		return (TRUE);
	}

	return (FALSE);
}


int setDialogControlCurrentSelection(CWnd *control, int index)
{
	return ( ((CComboBox *) control)->SetCurSel(index) );
}

int getDialogControlCurrentSelection(CWnd *control)
{
	return ( ((CComboBox *) control)->GetCurSel() );
}



#if 0
int setComboBoxCurrentSelection(CComboBox *cBox, int index)
{
	return (cBox->SetCurSel(index));
}
#endif


BOOL addStringToComboBox(CComboBox	&cBox, CString &string)
{
	if ((cBox.FindStringExact(0, string)) == LB_ERR) {

		debugPrint("Adding %s to ComboBox\n", string);

		cBox.AddString(string);

		//added new item
		return (TRUE);
	}

	//item already existed
	return (FALSE);
}

void floatToString(CString &string, float val)
{
	string.Format("%4.2f", val);
}

void longToString(CString &string, long val)
{
	string.Format("%d", val);
}

void charToString(CString &string, unsigned char val)
{
	string.Format("%d", (short) val);
}


void setEditBoxInputToFloat(CEdit *edit)
{
	CString string;
	float val;

	//grab string
	edit->GetWindowText(string);

	//convert to float
	val = (float) atof(string);

	//reformat for display
	//removes any garbage chars
	string.Format("%4.2f", val);

	//set new string
	edit->SetWindowText(string);
}

void setFloatToEditBox(CEdit *edit, float *val)
{
	CString string;

	//convert float to string
	floatToString(string, *val);

	//set new string
	edit->SetWindowText(string);
}

void setEditBoxInputToLong(CEdit *edit)
{
	CString string;
	long val;

	//grab string
	edit->GetWindowText(string);

	//convert to float
	val = atoi(string);

	//reformat for display
	//removes any garbage chars
	string.Format("%d", val);

	//set new string
	edit->SetWindowText(string);
}


void setLongToEditBox(CEdit *edit, long *val)
{
	CString string;

	//convert float to string
	longToString(string, *val);

	//set new string
	edit->SetWindowText(string);
}


void setStringToFloatValue(CString &string, float val)
{
	//convert float to string
	floatToString(string, val);
}


void setStringToFloat(CString &string)
{
	float val;

	val = (float) atof(string);

	//reformat for display
	//removes any garbage chars
	string.Format("%4.2f", val);
}


void setStringToCharValue(CString &string, unsigned char val)
{
	if (val < 0)
		val = 0;

	else if (val > 255)
		val = 255;

	//reformat for display
	//removes any garbage chars
	string.Format("%d", (short) val);
}


void setStringToChar(CString &string)
{
	short val;

	val = atoi(string);

	if (val < 0)
		val = 0;

	else if (val > 255)
		val = 255;

	//reformat for display
	//removes any garbage chars
	string.Format("%d", (short) val);

}


void setEditBoxInputToChar(CEdit *edit)
{
	CString string;
	short val;

	//grab string
	edit->GetWindowText(string);

	//convert to float
	val = atoi(string);

	if (val < 0)
		val = 0;

	else if (val > 255)
		val = 255;

	//reformat for display
	//removes any garbage chars
	string.Format("%d", (short) val);

	//set new string
	edit->SetWindowText(string);
}


void setCharToEditBox(CEdit *edit, unsigned char *val)
{
	CString string;
	short temp;

	temp = *val;

	if (temp < 0)
		temp = 0;

	else if (temp > 255)
		temp = 255;

	//convert float to string
	charToString(string, (unsigned char) temp);

	//set new string
	edit->SetWindowText(string);
}







#if 0

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void lighting_dlg::setEditBoxStringToFloat(int ID, float *value)
{
	CString string;

	((CEdit *) GetDlgItem(ID))->GetWindowText(string);

	//convert to float and asign
	*value = (float) atof(string);

	//reformat for display
	//removes any garbage chars
	string.Format("%4.2f", *value);

	((CEdit *) GetDlgItem(ID))->SetWindowText(string);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void lighting_dlg::setFloatToEditBox(int ID, float *val)
{
	CString string;

	//convert float to string
	floatToString(string, *val);

	//assign to box
	((CEdit *) GetDlgItem(ID))->SetWindowText(string);
}


void debug_Print(char *msg, ...)
{
	DWORD cCharsWritten;
	char s[256];
	va_list argptr;
	//int cnt;

	va_start(argptr, msg);
	vsprintf(s, msg, argptr);
	va_end(argptr);

	if (outputWinHandle)
		WriteConsole(outputWinHandle, s, strlen(s), &cCharsWritten, NULL);
}
#endif

