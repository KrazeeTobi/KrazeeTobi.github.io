/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _UTILS_H
#define _UTILS_H

/*-------------------------- defines ------------------------------ */
#define ENABLE_DLG_WINDOW(id) GetDlgItem(id)->EnableWindow(TRUE)
#define DISABLE_DLG_WINDOW(id) GetDlgItem(id)->EnableWindow(FALSE)

#define SET_DLG_WINDOW_FOCUS(id) GetDlgItem(id)->SetFocus()

#define SET_COMBO_BOX_INDEX(id)

/*-------------------------- structs ------------------------------ */
typedef struct _rgba
{
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short a;
} RGBA;

/*-------------------------- external functs -----------------------*/
void debugPrint(char * str, ...);

void createWinConsole(int width, int height);


BOOL doesFileExist(CString &string);
BOOL verifyFileExtension(CString &file, char *ext);

BOOL addStringToComboBox(CComboBox	&cBox, CString &string);

void floatToString(CString &string, float val);
void longToString(CString &string, long val);
void charToString(CString &string, unsigned char val);

void setFloatToEditBox(CEdit *edit, float *val);
void setEditBoxInputToFloat(CEdit *edit);

void setLongToEditBox(CEdit *edit, long *val);
void setEditBoxInputToLong(CEdit *edit);

void setCharToEditBox(CEdit *edit, unsigned char *val);
void setEditBoxInputToChar(CEdit *edit);

void setStringToFloat(CString &string);
void setStringToChar(CString &string);

void setStringToFloatValue(CString &string, float val);
void setStringToCharValue(CString &string, unsigned char val);

int setDialogControlCurrentSelection(CWnd *control, int index);
int getDialogControlCurrentSelection(CWnd *control);


/*-------------------------- external vars -------------------------*/

#endif //!_UTILS_H


