//------------------------------------------------------------------------------
// Copyright © 1995-1998, Xendra Software (http://www.xendra.com).
// All Rights Reserved.
//------------------------------------------------------------------------------
// THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO AS
// "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL
// XENDRA SOFTWARE OR ITS SUPPLIERS BE LIABLE FOR ANY DAMAGES WHATSOEVER
// INCLUDING DIRECT, INDIRECT, INCIDENTAL, CONSEQUENTIAL, LOSS OF BUSINESS
// PROFITS OR SPECIAL DAMAGES, EVEN IF XENDRA SOFTWARE OR ITS SUPPLIERS HAVE
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// This Software may be copied and distributed royalty-free subject to the
// following conditions:
//
// 1. You must copy all Software without modification and must include all
//    pages, if the Software is to be distributed without inclusion in your
//    software product.  If you are incorporating the Software in conjunction
//    with and as part of your software product which adds substantial value,
//    you may modify and include portions of the Software.  Any modifications
//    or additions to the Software should be sent to submit@xendra.com in
//    order to be incorporated into  the Software for the benefit of all those
//    who may use the Software.
//
// 2. You must place all copyright notices and other protective disclaimers
//    and notices contained on the Software on all copies of the Software and
//    your software product.  If you are incorporating the Software in
//    conjunction with and as part of your software product which adds
//    substantial value, you must display the following statement somewhere
//    that is easily assessable by the User of your product:
//
//     "Extensions Copyright © 1995-1998,
//      Xendra Software (http://www.xendra.com). All Rights Reserved."
//
// 3. Unless the Software is incorporated in your software product which
//    adds substantial value, you may not distribute this Software for
//    profit.
//
// 4. You may not incorporate the Software into any product that would
//    compete against the Software.
//
// 5. You agree to indemnify, hold harmless, and defend Xendra Software
//    and its suppliers from and against any claims or lawsuits, including
//    attorneys' fees, that arise or result from the use or distribution of
//    your software product and any modifications to the Software.
// ------------------------------------------------------------------------------

#include "stdafx.h"
#include "XSmain.h"

#if 0
#include "XSError.h"
#include "XSPalApi.h"
#include "XSDibApi.h"
#endif

// -------------------------------------------------------------
// XSDib_Create
//  Parameters:
//      DWORD dwWidth   - Width for new bitmap, in pixels
//      DWORD dwHeight  - Height for new bitmap
//      WORD  wBitCount - Bit Count for new DIB (1, 4, 8, 24,
//                        or 36)
//  Return Value:
//      HDIB            - Handle to new DIB
//  Description:
//      This function allocates memory for and initializes a
//      new DIB by filling in the BITMAPINFOHEADER, allocating
//      memory for the color table, and allocating memory for
//      the bitmap bits.  As with all HDIBs, the header, color
//      table and bits are all in one contiguous memory block.
//      This function is similar to the CreateBitmap() Windows
//      API.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount)
{
    BITMAPINFOHEADER bi;     // Bitmap header
    LPBITMAPINFOHEADER lpbi; // Pointer to BITMAPINFOHEADER
    DWORD dwLen;             // Size of memory block
    HDIB hDib;               // Handle for new DIB
    DWORD dwBytesPerLine;    // Number of bytes per scanline

    // Make sure bits per pixel is valid
    if (wBitCount <= 1)
        wBitCount = 1;
    else if (wBitCount <= 4)
        wBitCount = 4;
    else if (wBitCount <= 8)
        wBitCount = 8;
    else if (wBitCount <= 24)
        wBitCount = 24;
    else if (wBitCount <= 36)
        wBitCount = 36;
    else
        wBitCount = 4;  // Set default value to 4
                        // if parameter is bogus

    // Initialize BITMAPINFOHEADER
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = dwWidth;      // Fill in width from parameter
    bi.biHeight = dwHeight;    // Fill in height from parameter
    bi.biPlanes = 1;           // Must be 1
    bi.biBitCount = wBitCount; // From parameter
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;        // 0's here mean "default"
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Calculate size of memory block required to store the
    // DIB. This block should be big enough to hold the
    // BITMAPINFOHEADER, the color table, and the bits
    dwBytesPerLine = macDibWidthBytes(wBitCount * dwWidth);
    dwLen = bi.biSize + ::XSDib_PaletteSize(&bi) +
        (dwBytesPerLine * dwHeight);

    // Alloc memory block to store our bitmap
    if (!(hDib = (HDIB)::GlobalAlloc(GHND, dwLen)))
    {
        ::XSError_Set(XSERR_MEMORY);
        return NULL;
    }

    // Lock memory and get pointer to it
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hDib);

    // Use our bitmap info structure to fill in first part of
    // our DIB with the BITMAPINFOHEADER
    *lpbi = bi;

    // Since we don't know what the color table and bits
    // should contain, just leave these blank.  Unlock
    // the DIB and return the HDIB.
    ::GlobalUnlock(hDib);

    // Set error to no error
    ::XSError_Set(XSERR_NOERROR);

    // Return handle to the DIB
    return hDib;
}

// -------------------------------------------------------------
// XSDib_Template
//  Parameters:
//      BITMAPINFOHEADER - bitmap info header stucture
//      HBITMAP          - handle to the bitmap
//  Return Value:
//      HDIB             - handle to memory block
//  Description:
//      This routine takes a BITMAPINOHEADER, and returns a
//      handle to global memory which can contain a DIB with
//      that header.  It also initializes the header portion of
//      the global memory.  GetDIBits() is used to determine
//      the amount of room for the DIB's bits.  The total amount
//      of memory needed = sizeof(BITMAPINFOHEADER)
//      + size of color table + size of bits.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_Template(BITMAPINFOHEADER& bi, HBITMAP hBitmap)
{
    DWORD              dwLen;
    HDIB               hDib;
    HDC                hDC;
    LPBITMAPINFOHEADER lpbi;
    HDIB               hDibTemp;

    // Figure out the size needed to hold the BITMAPINFO
    // structure (which includes the BITMAPINFOHEADER and
    // the color table).
    dwLen = bi.biSize + ::XSDib_PaletteSize(&bi);
    hDib  = (HDIB)::GlobalAlloc(GHND, dwLen);

    // Check that DIB handle is valid
    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return NULL;
    }

    // Set up the BITMAPINFOHEADER in the newly allocated
    // global memory, then call GetDIBits() with
    // lpBits = NULL to have it fill in the biSizeImage
    // field for us.
    lpbi  = (LPBITMAPINFOHEADER)::GlobalLock(hDib);
    *lpbi = bi;

    hDC   = ::GetDC(NULL);
    ::GetDIBits(hDC, hBitmap, 0, (WORD) bi.biHeight, NULL,
        (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
    ::ReleaseDC(NULL, hDC);

    // If the driver did not fill in the biSizeImage field,
    // fill it in -- NOTE: there is a bug in some drivers!
    if (lpbi->biSizeImage == 0)
        lpbi->biSizeImage = macDibWidthBytes((DWORD)lpbi->biWidth
        * lpbi->biBitCount) * lpbi->biHeight;

    // Get the size of the memory block we need
    dwLen = lpbi->biSize + ::XSDib_PaletteSize(&bi)
        + lpbi->biSizeImage;

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    // ReAlloc the buffer big enough to hold all the bits
    if (hDibTemp = (HDIB)::GlobalReAlloc(hDib, dwLen, 0))
    {
        ::XSError_Set(XSERR_MEMORY);
        return hDibTemp;
    }
    else
    {
        ::XSError_Set(XSERR_NOERROR);

        // Else free the memory block and return failure
        ::GlobalFree(hDib);
        return NULL;
    }
}

// -------------------------------------------------------------
// XSBmp_Load
//  Parameters:
//      HINSTANCE hInst - Specifies the HINSTANCE to load a DDB
//      UINT nID - ID for the resource to load
//  Return Value:
//      HBITMAP - the handle to the loaded bitmap, NULL on
//        failure
//  Description:
//      Loads the specified BMP from the resources of the
//      specified HINSTANCE
// -------------------------------------------------------------
HBITMAP XSFUNC
XSBmp_Load(HINSTANCE hInst, UINT nID)
{
    HBITMAP hBitmap = NULL;

    hBitmap = (HBITMAP)::LoadImage(hInst, MAKEINTRESOURCE(nID),
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    // Set error number
    if (!hBitmap)
        ::XSError_Set(XSERR_CREATEBITMAP);
    else
        ::XSError_Set(XSERR_NOERROR);

    return hBitmap;
}

// -------------------------------------------------------------
// XSDib_Load
//  Parameters:
//      CString strFileName - Specifies the DIB file
//  Return Value:
//      HDIB of the loaded DIB or NULL on failure
//  Description:
//      Loads the specified DIB from a file, allocates memory
//      for it, and reads the disk file into the memory.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_Load(CString strFileName)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    HDIB hDib = NULL;   // Handle to new DIB
    CFile file;         // File handling class
    CFileException e;   // File exception catcher

    // Set the cursor to a hourglass, in case the loading
    // operation takes more than a sec, the user will know
    // what's going on.
    CWaitCursor wait;

    if (!file.Open(strFileName,
        CFile::modeRead|CFile::shareDenyNone, &e))
    {
#ifdef _DEBUG
        afxDump << "File (" << strFileName <<
            ") could not be opened: " << e.m_cause << "\n";
#endif
        ::XSError_Set(XSERR_OPEN);
        return NULL;
    }
    else
    {
        hDib = ::XSDib_ReadFile(file, 0L);
        file.Close();

        // Set error to no error
        ::XSError_Set(XSERR_NOERROR);

        return hDib;
    }
}

// -------------------------------------------------------------
// XSDib_ReadFile
//  Parameters:
//      CFile& file - Reference to an already open CFile object
//       that has opened a DIB (*.BMP) file for reading.
//      DWORD dwOffset - The offset from the beginning of the
//       file to where the reading begins.
//  Return Value:
//      HDIB on success or NULL on failure.
//  Description:
//      Reads in the specified DIB file into a global chunk of
//      memory.
//      BITMAPFILEHEADER is stripped off of the DIB.  Everything
//      from the end of the BITMAPFILEHEADER structure on is
//      returned in the global memory handle.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_ReadFile(CFile& file, DWORD dwOffset)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    BITMAPFILEHEADER bmfHeader;
    HDIB hDib;
    UINT nNumColors;            // Number of colors in DIB
    HDIB hDibtmp;                // Used for GlobalRealloc()
    LPBITMAPINFOHEADER lpbi;
    DWORD offBits;

    // Allocate memory for header & color table. We'll enlarge
    // this memory as needed.
    hDib = (HDIB)::GlobalAlloc(GHND,
        (DWORD)(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)));
    if (!hDib)
    {
        ::XSError_Set(XSERR_MEMORY);
        return NULL;
    }

    lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);
    if (!lpbi)
    {
        ::GlobalFree(hDib);
        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // read the BITMAPFILEHEADER from the file
    if (sizeof(BITMAPFILEHEADER) !=
        file.Read((LPVOID)&bmfHeader, sizeof(BITMAPFILEHEADER)))
    {
        ::XSError_Set(XSERR_OPEN);
        goto ErrExit;
    }

    // Verify BITMAP type
    if (bmfHeader.bfType != macDibHeaderMarker)
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        goto ErrExit;
    }

    // read the BITMAPINFOHEADER from the file
    if (sizeof(BITMAPINFOHEADER) !=
        file.Read((LPVOID)lpbi, sizeof(BITMAPINFOHEADER)))
    {
        ::XSError_Set(XSERR_READ);
        goto ErrExit;
    }

    // Check to see that it's a Windows DIB -- an OS/2 DIB
    // would cause strange problems with the rest of the
    // DIB API since the fields in the header are different
    // and the color table entries are smaller.
    //
    // If it's not a Windows DIB (e.g. if biSize is wrong),
    // return NULL.
    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        goto ErrExit;
    }

    // Now determine the size of the color table and read it.
    // Since the bitmap bits are offset in the file by
    // bfOffBits, we need to do some special processing here
    // to make sure the bits directly follow the color table
    // (because that's the format we are susposed to pass back)
    if (!(nNumColors = (UINT)lpbi->biClrUsed))
    {
        // No color table for 24-bit, default size otherwise
        if (lpbi->biBitCount != 24)
        {
            // Standard size table
            nNumColors = 1 << lpbi->biBitCount;
        }
    }

    // Fill in some default values if they are zero
    if (lpbi->biClrUsed == 0)
        lpbi->biClrUsed = nNumColors;

    if (lpbi->biSizeImage == 0)
    {
        lpbi->biSizeImage = ((((lpbi->biWidth *
            (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3) *
            lpbi->biHeight;
    }

    // Get a proper-sized buffer for header,
    // color table and bits
    ::GlobalUnlock(hDib);
    hDibtmp = (HDIB)::GlobalReAlloc(hDib, lpbi->biSize +
        nNumColors * sizeof(RGBQUAD) + lpbi->biSizeImage, 0);

    if (!hDibtmp) // can't resize buffer for loading
    {
        ::XSError_Set(XSERR_MEMORY);
        goto ErrExitNoUnlock;
    }
    else
        hDib = hDibtmp;

    lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);

    // Read the color table
    file.Read((LPVOID)((LPSTR)(lpbi) + lpbi->biSize),
        nNumColors * sizeof(RGBQUAD));

    // Offset to the bits from start of DIB header
    offBits = lpbi->biSize + nNumColors * sizeof(RGBQUAD);

    // If the bfOffBits field is non-zero, then the bits might
    // *not* be directly following the color table in the file.
    // Use the value in bfOffBits to seek the bits.
    if (bmfHeader.bfOffBits != 0L)
        file.Seek(dwOffset + bmfHeader.bfOffBits, SEEK_SET);

    if (file.Read((LPVOID)((LPBYTE)lpbi + offBits),
        lpbi->biSizeImage))
        goto OKExit;

ErrExit:
    ::GlobalUnlock(hDib);
ErrExitNoUnlock:
    ::GlobalFree(hDib);
    return NULL;

OKExit:
    ::GlobalUnlock(hDib);

    // Set error to no error
    ::XSError_Set(XSERR_NOERROR);

    return hDib;
}

// -------------------------------------------------------------
// XSDib_Save
//  Parameters:
//      HDIB hDib - Handle to the DIB to save to a file
//      CString strFileName - File name of the DIB to save to
//  Return Value:
//      XSERR_NOERROR - if successful
//      XSERR_HANDLENULL - the hDib handle was NULL
//      XSERR_OPEN - Unable to open file
//      XSERR_LOCK - Unable to lock memory
//      XSERR_INVALIDFORMAT - Invalid DIB format
//  Description:
//      Saves the specified DIB into the specified file name on
//      disk. No error checking is done, so if the file already
//      exists, it will be over written.
// -------------------------------------------------------------
WORD XSFUNC
XSDib_Save(HDIB hDib, CString strFileName)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    ::XSError_Set(XSERR_NOERROR);

    CFile file;
    CFileException e;

    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return XSERR_HANDLENULL;
    }

    if (!file.Open(strFileName,
        CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive,
        &e))
    {
#ifdef _DEBUG
        afxDump << "File (" << strFileName <<
            ") could not be created: " << e.m_cause << "\n";
#endif
        ::XSError_Set(XSERR_OPEN);
        return XSERR_OPEN;
    }

    WORD wResult = ::XSDib_WriteFile(hDib, file);
    file.Close();

    return wResult;
}

// -------------------------------------------------------------
// XSDib_WriteFile
//  Parameters:
//      HDIB hDib - Handle to the DIB to save to a file
//      CFile& file - Reference to an already open CFile object
//       that has opened a DIB (*.BMP) file for writing.
//  Return Value:
//      XSERR_NOERROR - if successful
//      XSERR_HANDLENULL - the hDib handle was NULL
//      XSERR_OPEN - Unable to open file
//      XSERR_LOCK - Unable to lock memory
//      XSERR_INVALIDFORMAT - Invalid DIB format
//  Description:
//      Saves the specified DIB into already opened file handle
// -------------------------------------------------------------
WORD XSFUNC
XSDib_WriteFile(HDIB hDib, CFile& file)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    BITMAPFILEHEADER bmfHdr;   // Header for Bitmap file
    LPBITMAPINFOHEADER lpBI;   // Pointer to DIB info structure
    DWORD dwDIBSize;

    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return XSERR_HANDLENULL;
    }

    // Get a pointer to the DIB memory, the first of which
    // contains a BITMAPINFO structure
    lpBI = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);
    if (!lpBI)
    {
        ::XSError_Set(XSERR_LOCK);
        return XSERR_LOCK;
    }

    // Check to see if we're dealing with an OS/2 DIB.  If so, 
    // don't save it because our functions aren't written to 
    // deal with these DIBs.
    if (lpBI->biSize != sizeof(BITMAPINFOHEADER))
    {
        ::GlobalUnlock(hDib);
        ::XSError_Set(XSERR_INVALIDFORMAT);
        return XSERR_INVALIDFORMAT;
    }

    //Fill in the fields of the file header

    // Fill in file type 
    // (first 2 bytes must be "BM" for a bitmap)
    bmfHdr.bfType = macDibHeaderMarker;  // "BM"

    // Calculating the size of the DIB is a bit tricky (if we 
    // want to do it right).  The easiest way to do this is to 
    // call GlobalSize() on our global handle, but since the 
    // size of our global memory may have been padded a few 
    // bytes, we may end up writing out a few too many bytes 
    // to the file (which may cause problems with some apps)
    //
    // So, instead let's calculate the size manually.
    //
    // To do this, find size of header plus size of color 
    // table.  Since the first DWORD in both BITMAPINFOHEADER 
    // and BITMAPCOREHEADER contains the size of the structure, 
    // let's use this.

    // Partial Calculation
    dwDIBSize = *(LPDWORD)lpBI + ::XSDib_PaletteSize(lpBI);  

    // Now calculate the size of the image
    if ((lpBI->biCompression == BI_RLE8) || 
        (lpBI->biCompression == BI_RLE4)) 
    {
        // It's an RLE bitmap, we can't calculate size, so 
        // trust the biSizeImage field
        dwDIBSize += lpBI->biSizeImage;
    }
    else 
    {
        DWORD dwBmBitsSize;  // Size of Bitmap Bits only

        // It's not RLE, so size is 
        // Width (DWORD aligned) * Height
        dwBmBitsSize = macDibWidthBytes((lpBI->biWidth) *
            ((DWORD)lpBI->biBitCount)) * lpBI->biHeight;

        dwDIBSize += dwBmBitsSize;

        // Now, since we have calculated the correct size, why 
        // don't we fill in the biSizeImage field (this will 
        // fix any .BMP files which  have this field incorrect).
        lpBI->biSizeImage = dwBmBitsSize;
    }

    // Calculate the file size by adding the DIB size 
    // to sizeof(BITMAPFILEHEADER)
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;

    // Now, calculate the offset the actual bitmap bits will 
    // be in the file -- It's the Bitmap file header plus the 
    // DIB header, plus the size of the color table.
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
        lpBI->biSize + ::XSDib_PaletteSize(lpBI);

    try
    {
        // Write the file header
        file.Write(&bmfHdr, sizeof(BITMAPFILEHEADER));

        // Write the DIB header and the bits
        file.Write(lpBI, dwDIBSize);
    }
    catch (CFileException* e)
    {
#ifdef _DEBUG
        afxDump << "Could not write to file (" << 
            file.GetFilePath() << "): " << e->m_cause << "\n";
#endif
        e->Delete();
        ::GlobalUnlock(hDib);
        ::XSError_Set(XSERR_WRITE);
        return XSERR_WRITE; // error in the write
    }

    ::GlobalUnlock(hDib);

    ::XSError_Set(XSERR_NOERROR);
    return XSERR_NOERROR; // Success code
}

// -------------------------------------------------------------
// XSDib_Destroy
//  Parameters:
//      HDIB hDib - The handle to the DIB to be freed
//  Return Value:
//      None
//  Description:
//      Frees memory associated with a DIB
// -------------------------------------------------------------
void XSFUNC 
XSDib_Destroy(HDIB hDib)
{
    if (hDib)
    {
        ::GlobalFree(hDib);
        hDib = NULL;
    }
    
    ::XSError_Set(XSERR_NOERROR);
}

// -------------------------------------------------------------
// XSDib_Width
//  Parameters:
//      LPVOID lpDib - pointer to a packed DIB memory block
//  Return Value:
//      LONG - the width of the DIB, -1 on error
//  Description:
//      Returns the width of the DIB
// -------------------------------------------------------------
LONG XSFUNC 
XSDib_Width(LPVOID lpDib)
{
    ASSERT(lpDib);

    return ((LPBITMAPINFOHEADER)lpDib)->biWidth;
}

// -------------------------------------------------------------
// XSDib_Width
//  Parameters:
//      HDIB hDib - The handle to a DIB
//  Return Value:
//      LONG - the width of the DIB, -1 on error
//  Description:
//      Returns the width of the DIB
// -------------------------------------------------------------
LONG XSFUNC 
XSDib_Width(HDIB hDib)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // Pointer to BITMAPINFOHEADER

    ::XSError_Set(XSERR_NOERROR);

    // Lock the memory block
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return -1;
    }

    // Call the function
    LONG lWidth = ::XSDib_Width(lpDIBHdr);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    return lWidth;
}

// -------------------------------------------------------------
// XSDib_Height
//  Parameters:
//      LPVOID lpDib - pointer to a packed DIB memory block
//  Return Value:
//      LONG - the height of the DIB, -1 on error
//  Description:
//      Returns the height of the DIB
// -------------------------------------------------------------
LONG XSFUNC 
XSDib_Height(LPVOID lpDib)
{
    ASSERT(lpDib);

    return ((LPBITMAPINFOHEADER)lpDib)->biHeight;
}

// -------------------------------------------------------------
// XSDib_Height
//  Parameters:
//      HDIB hDib - The handle to a DIB
//  Return Value:
//      LONG - the height of the DIB, -1 on error
//  Description:
//      Returns the height of the DIB
// -------------------------------------------------------------
LONG XSFUNC 
XSDib_Height(HDIB hDib)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // Pointer to BITMAPINFOHEADER

    ::XSError_Set(XSERR_NOERROR);

    // Lock the memory block
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return -1;
    }

    // Call the function
    LONG lHeight = ::XSDib_Height(lpDIBHdr);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    return lHeight;
}

// -------------------------------------------------------------
// XSDib_PaletteSize
//  Parameters:
//      LPVOID lpDib - pointer to a packed DIB memory block
//  Return Value:
//      WORD - the size of the associated palette, -1 on error
//  Description:
//      Returns the size of the palette  
//      This function gets the size required to store the 
//      DIB's palette by multiplying the number of colors by 
//      the size of an RGBQUAD
// -------------------------------------------------------------
WORD XSFUNC 
XSDib_PaletteSize(LPVOID lpDib)
{
    ASSERT(lpDib);

    ::XSError_Set(XSERR_NOERROR);

    // Calculate the size required by the palette
    if (macIsWinDib(lpDib))
        return (::XSDib_NumColors(lpDib) * sizeof(RGBQUAD));
    else
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        return -1;
    }
}

// -------------------------------------------------------------
// XSDib_PaletteSize
//  Parameters:
//      HDIB hDib - The handle to a DIB
//  Return Value:
//      WORD - the size of the associated palette, -1 on error
//  Description:
//      Returns the size of the palette  
//      This function gets the size required to store the 
//      DIB's palette by multiplying the number of colors by 
//      the size of an RGBQUAD
// -------------------------------------------------------------
WORD XSFUNC 
XSDib_PaletteSize(HDIB hDib)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // Pointer to BITMAPINFOHEADER

    ::XSError_Set(XSERR_NOERROR);

    // Lock the memory block
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return -1;
    }

    // Call the function
    WORD wPalSize = ::XSDib_PaletteSize(lpDIBHdr);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    return wPalSize;
}

// -------------------------------------------------------------
// XSDib_NumColors
//  Parameters:
//      LPVOID lpDib - pointer to a packed DIB memory block
//  Return Value:
//      WORD - the number of colors in the DIB's color, 
//      -1 on error
//  Description:
//      Returns the number of colors in the DIB's color table.
//      This function calculates the number of colors in the 
//      DIB's color table by finding the bits per pixel for the 
//      DIB (whether Win3.0 or other-style DIB). If bits per 
//      pixel is 1: colors=2, if 4: colors=16, if 8: colors=256, 
//      if 24, no colors in color table.
// -------------------------------------------------------------
WORD XSFUNC 
XSDib_NumColors(LPVOID lpDib)
{
    ASSERT(lpDib);

    WORD wBitCount;  // DIB bit count
    
    ::XSError_Set(XSERR_NOERROR);

    // If this is a Windows-style DIB, the number of colors in 
    // the color table can be less than the number of bits per 
    // pixel allows for (i.e. lpbi->biClrUsed can be set to 
    // some value). If this is the case, return the appropriate 
    // value.
    if (macIsWinDib(lpDib))
    {
        DWORD dwClrUsed;

        dwClrUsed = ((LPBITMAPINFOHEADER)lpDib)->biClrUsed;
        if (dwClrUsed)
            return (WORD)dwClrUsed;
    }

    // Calculate the number of colors in the color table based 
    // on the number of bits per pixel for the DIB.
    if (macIsWinDib(lpDib))
        wBitCount = ((LPBITMAPINFOHEADER)lpDib)->biBitCount;
    else
        wBitCount = ((LPBITMAPCOREHEADER)lpDib)->bcBitCount;

    // return number of colors based on bits per pixel
    if (wBitCount > 8) 
        return 0;  // Since biClrUsed is 0, 
    else           // we don't have a an optimal palette
        return (1 << wBitCount); 
}

// -------------------------------------------------------------
// XSDib_NumColors
//  Parameters:
//      HDIB hDib - The handle to a DIB
//  Return Value:
//      WORD - the number of colors in the DIB's color, 
//      -1 on error
//  Description:
//      Returns the number of colors in the DIB's color table.
//      This function calculates the number of colors in the 
//      DIB's color table by finding the bits per pixel for the 
//      DIB (whether Win3.0 or other-style DIB). If bits per 
//      pixel is 1: colors=2, if 4: colors=16, if 8: colors=256, 
//      if 24, no colors in color table.
// -------------------------------------------------------------
WORD XSFUNC 
XSDib_NumColors(HDIB hDib)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // Pointer to BITMAPINFOHEADER

    // Lock the memory block
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return -1;
    }

    // Call the function
    WORD wNumColors = ::XSDib_NumColors(lpDIBHdr);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    return wNumColors;
}

// -------------------------------------------------------------
// XSDib_FindBits
//  Parameters:
//      LPVOID lpDib - pointer to a packed DIB memory block
//  Return Value:
//      LPVOID - pointer to the DIB's bits, NULL on error
//  Description:
//      Returns a pointer to the DIB's bits
//      This function calculates the address of the DIB's bits 
//      and returns a pointer to the DIB bits.
// -------------------------------------------------------------
LPVOID XSFUNC 
XSDib_FindBits(LPVOID lpDib)
{
    ASSERT(lpDib);

    ::XSError_Set(XSERR_NOERROR);

    if (!lpDib)
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        return NULL;
    }

    LPVOID lpBits = ((LPSTR)lpDib + *(LPDWORD)lpDib + 
        ::XSDib_PaletteSize(lpDib));

    if (!lpBits)
        ::XSError_Set(XSERR_GETBITS);

    return lpBits;
}

// -------------------------------------------------------------
// XSDib_FindBits
//  Parameters:
//      HDIB hDib - The handle to a DIB
//  Return Value:
//      LPVOID - pointer to the DIB's bits, NULL on error
//  Description:
//      Returns a pointer to the DIB's bits
//      This function calculates the address of the DIB's bits 
//      and returns a pointer to the DIB bits.
// -------------------------------------------------------------
LPVOID XSFUNC 
XSDib_FindBits(HDIB hDib)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // Pointer to BITMAPINFOHEADER

    ::XSError_Set(XSERR_NOERROR);

    // Lock the memory block
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // Call the function
    LPVOID lpBits = ::XSDib_FindBits(lpDIBHdr);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    return lpBits;
}

// -------------------------------------------------------------
// XSDib_CalcPadding
//  Parameters:
//        DWORD - Count of BPP (Bits Per Pixel)
//        DWORD - Source width
//  Return Value:
//      DWORD - Returns the new destination width
//  Description:
//      Calculate the padding required to align on DWORDs since 
//      DIB scanlines are aligned on DWORD boundaries.
// -------------------------------------------------------------
DWORD XSFUNC
XSDib_CalcPadding(DWORD dwBitsPerPixel, DWORD dwPixels)
{
    DWORD dwBits;
    DWORD dwPadBits;

    dwBits    = dwBitsPerPixel * dwPixels;
    
    // Check to see if we are already DWORD aligned
    if ((dwBits % 32) == 0)
    {
        // Already DWORD aligned, no padding needed
        return 0;
    }
    else
        dwPadBits = 32 - (dwBits % 32);
    
    // Figure out how many more bytes are needed to make 
    // this line DWORD aligned
    return (dwPadBits / 8 + (((dwPadBits % 8) > 0) ? 1 : 0));
}

// -------------------------------------------------------------
// XSDib_CalcBytesPerLine
//  Parameters:
//        DWORD - count of BPP (Bits Per Pixel)
//        DWORD - source width
//  Return Value:
//      DWORD - needed bytes per line, DWORD aligned
//  Description:
//      Calculate the bytes per line required to align on 
//      DWORDs since DIB scanlines are aligned on DWORD 
//      boundaries.
// -------------------------------------------------------------
DWORD XSFUNC
XSDib_CalcBytesPerLine(DWORD dwBitsPerPixel, DWORD dwWidth)
{
    DWORD dwBits, dwPadBits;

    dwBits    = dwBitsPerPixel * dwWidth;

    if ((dwBits % 32) == 0)
    {
        // Already DWORD aligned, no padding needed
        return (dwBits / 8);
    }
    else
        dwPadBits = 32 - (dwBits % 32);

    return (dwBits / 8 + dwPadBits / 8 + (((dwPadBits % 8) > 0) ? 1 : 0));
}

// -------------------------------------------------------------
// XSDib_LastByte
//  Parameters:
//        DWORD - count of BPP (Bits Per Pixel)
//        DWORD - the number of pixels in this scanline
//  Return Value:
//        DWORD - the byte offset of the last pixel
//  Description:
//      Returns the byte of the last pixel based on number of 
//      pixels and BPP.
// -------------------------------------------------------------
DWORD XSFUNC
XSDib_LastByte(DWORD dwBitsPerPixel, DWORD dwPixels)
{
    DWORD dwBits, extraBits, numBytes;

    dwBits = dwBitsPerPixel * dwPixels;
        numBytes  = dwBits / 8;

        extraBits = dwBits - numBytes * 8;
        if((extraBits % 8) > 0)
                numBytes++;

    return (numBytes);
}

// -------------------------------------------------------------
// XSDib_CreatePalette
//  Parameters:
//      hDib - handle to a DIB
//  Return Value:
//      HPALETTE - handle to new palette, NULL on error
//  Description:
//      Returns a handle to an HPALETTE created from the 
//      associated DIB.
//      This function creates a palette from a DIB by allocating 
//      memory for the logical palette, reading and storing the 
//      colors from the DIB's color table into the logical 
//      palette, creating a palette from this logical palette, 
//      and then returning the palette's handle. This allows the 
//      DIB to be displayed using the best possible colors 
//      (important for DIBs with 256 or more colors).
// -------------------------------------------------------------
HPALETTE XSFUNC 
XSDib_CreatePalette(HDIB hDib)
{
    ASSERT(hDib);

    // pointer to a logical palette
    LPLOGPALETTE lpPal = NULL;     

    // handle to a logical palette
    HANDLE hLogPal = NULL;         

    // handle to a palette
    HPALETTE hPal = NULL;          

    // loop index, number of colors in color table
    int i, wNumColors;             

    // pointer to packed-DIB
    LPVOID lpbi = NULL;            

    // pointer to BITMAPINFO structure (Win3.0)
    LPBITMAPINFO lpbmi = NULL;     

    // flag which signifies whether this is a Win3.0 DIB
    BOOL bWinStyleDib;

    // if handle to DIB is invalid, return a half tone palette
    if (!hDib)
    {
        HDC hDC = ::GetDC(NULL);
        hPal = ::CreateHalftonePalette(hDC);
        ::ReleaseDC(NULL, hDC);
        ::XSError_Set(XSERR_HANDLENULL);
        return hPal;
    }

    // lock DIB memory block and get a pointer to it
    lpbi = ::GlobalLock((HGLOBAL)hDib);
    ASSERT(lpbi);  // sanity check
    if (!lpbi)
    {
        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // get pointer to BITMAPINFO (Win 3.0)
    lpbmi = (LPBITMAPINFO)lpbi;

    // get the number of colors in the DIB
    wNumColors = ::XSDib_NumColors(lpbi);

    // is this a Win 3.0 DIB?
    bWinStyleDib = macIsWinDib(lpbi);

    // We're not handling OS/2 bitmap
    if (!bWinStyleDib)
        return FALSE;

    if (wNumColors)
    {
        // allocate memory block for logical palette
        hLogPal = ::GlobalAlloc(GHND, sizeof(LOGPALETTE) + 
            sizeof(PALETTEENTRY) * wNumColors);

        // if not enough memory, clean up and return NULL
        if (!hLogPal)
        {
            ::GlobalUnlock(hDib);
            ::XSError_Set(XSERR_MEMORY);
            return NULL;
        }

        // lock memory block and get pointer to it
        lpPal = (LPLOGPALETTE)::GlobalLock((HGLOBAL)hLogPal);
        if (!lpPal)
        {
            ::GlobalUnlock(hDib);
            ::XSError_Set(XSERR_LOCK);
            return NULL;
        }

        // set version and number of palette entries
        lpPal->palVersion = PALVERSION;
        lpPal->palNumEntries = wNumColors;

        // store RGB triples into palette
        for (i = 0; i < wNumColors; i++)
        {
            lpPal->palPalEntry[i].peRed = 
                lpbmi->bmiColors[i].rgbRed;
            lpPal->palPalEntry[i].peGreen = 
                lpbmi->bmiColors[i].rgbGreen;
            lpPal->palPalEntry[i].peBlue = 
                lpbmi->bmiColors[i].rgbBlue;
            lpPal->palPalEntry[i].peFlags = 0;
        }

        // create the palette and get handle to it
        hPal = ::CreatePalette(lpPal);

        // if error getting handle to palette, clean up and 
        // return NULL
        if (!hPal)
        {
            ::GlobalUnlock(hLogPal);
            ::GlobalFree(hLogPal);
            ::XSError_Set(XSERR_CREATEPAL);
            return NULL;
        }
    }
    else
    {
        HDC hDC = ::GetDC(NULL);
        hPal = ::CreateHalftonePalette(hDC);
        ::ReleaseDC(NULL, hDC);
    }

    // clean up
    if (hLogPal)
    {
        ::GlobalUnlock(hLogPal);
        ::GlobalFree(hLogPal);
    }

    ::GlobalUnlock(hDib);

    ::XSError_Set(XSERR_NOERROR);

    // return handle to DIB's palette
    return hPal;
}

// -------------------------------------------------------------
// XSBmp_ToDib
//  Parameters:
//      HBITMAP - handle to a Bitmap that the DIB is to be 
//       created from
//      HPALETTE - palette to use in creation of DIB
//  Return Value:
//      HDIB - handle of the DIB created from the Bitmap, NULL
//       on error
//  Description:
//      Returns an HDIB created from an HBITMAP.
//      This function creates a DIB from a bitmap using the 
//      specified palette.
// -------------------------------------------------------------
HDIB XSFUNC 
XSBmp_ToDib(HBITMAP hBitmap, HPALETTE hPal)
{
    ASSERT(hBitmap);

    BITMAP bm;               // bitmap structure
    BITMAPINFOHEADER bi;     // bitmap header
    LPBITMAPINFOHEADER lpbi; // pointer to BITMAPINFOHEADER
    DWORD dwLen;             // size of memory block
    HDIB hDib, h;            // handle to DIB, temp handle
    HDC hDC;                 // handle to DC
    WORD biBits;             // bits per pixel
    UINT wLineLen;
    DWORD dwSize;
    DWORD wColSize;

    // check if bitmap handle is valid
    if (!hBitmap)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return NULL;
    }

    // fill in BITMAP structure, return NULL if it didn't work
    if (!::GetObject(hBitmap, sizeof(bm), &bm))
    {
        ::XSError_Set(XSERR_GETOBJECT);
        return NULL;
    }

    // if no palette is specified, use default palette
    if (hPal == NULL)
        hPal = (HPALETTE)::GetStockObject(DEFAULT_PALETTE);

    // calculate bits per pixel
    biBits = bm.bmPlanes * bm.bmBitsPixel;

    wLineLen = ( bm.bmWidth * biBits + 31 ) / 32 * 4;
    wColSize = sizeof(RGBQUAD) * (( biBits <= 8 ) ? 
        1 << biBits : 0 );
    dwSize = sizeof( BITMAPINFOHEADER ) + wColSize +
        (DWORD)(UINT)wLineLen * (DWORD)(UINT)bm.bmHeight;

    // make sure bits per pixel is valid
    if (biBits <= 1)
        biBits = 1;
    else if (biBits <= 4)
        biBits = 4;
    else if (biBits <= 8)
        biBits = 8;
    else // if greater than 8-bit, force to 24-bit
        biBits = 24;

    // initialize BITMAPINFOHEADER
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bm.bmWidth;
    bi.biHeight = bm.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = biBits;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = ( biBits <= 8 ) ? 1 << biBits : 0;    
    bi.biClrImportant = 0;

    // calculate size of memory block required to store BITMAPINFO
    dwLen = bi.biSize + ::XSDib_PaletteSize(&bi);

    // get a DC
    hDC = ::GetDC(NULL);

    // select and realize our palette
    hPal = ::SelectPalette(hDC, hPal, FALSE);
    ::RealizePalette(hDC);

    // alloc memory block to store our bitmap
    hDib = (HDIB)::GlobalAlloc(GHND, dwLen);

    // if we couldn't get memory block
    if (!hDib)
    {
        // clean up and return NULL
        ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);

        ::XSError_Set(XSERR_MEMORY);
        return NULL;
    }

    // lock memory and get pointer to it
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);
    if (!lpbi)
    {
        // clean up and return NULL
        ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);

        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // use our bitmap info. to fill BITMAPINFOHEADER
    *lpbi = bi;

    // call GetDIBits with a NULL lpBits param, so it will 
    // calculate the biSizeImage field for us
    ::GetDIBits(hDC, hBitmap, 0, (WORD)bi.biHeight, NULL, 
        (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

    // get the info. returned by GetDIBits and unlock 
    // memory block
    bi = *lpbi;
    bi.biClrUsed = ( biBits <= 8 ) ? 1 << biBits : 0;
    ::GlobalUnlock(hDib);

    // if the driver did not fill in the biSizeImage field, 
    // make one up
    if (bi.biSizeImage == 0)
        bi.biSizeImage = 
        macDibWidthBytes((DWORD)bm.bmWidth * biBits) * bm.bmHeight;

    // realloc the buffer big enough to hold all the bits
    dwLen = bi.biSize + ::XSDib_PaletteSize(&bi) + 
        bi.biSizeImage;
    if (h = (HDIB)::GlobalReAlloc(hDib, dwLen, 0))
        hDib = h;
    else
    {
        // clean up and return NULL
        ::GlobalFree(hDib);
        hDib = NULL;

        ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);

        ::XSError_Set(XSERR_MEMORY);
        return NULL;
    }

    // lock memory block and get pointer to it
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);
    if (!lpbi)
    {
        // clean up and return NULL
        ::GlobalFree(hDib);
        hDib = NULL;

        ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);

        ::XSError_Set(XSERR_MEMORY);
        return NULL;
    }

    // call GetDIBits with a NON-NULL lpBits param, and 
    // actualy get the bits this time
    if (::GetDIBits(hDC, hBitmap, 0, (WORD)bi.biHeight, 
        (LPSTR)lpbi + (WORD)lpbi->biSize + 
        ::XSDib_PaletteSize(lpbi), (LPBITMAPINFO)lpbi, 
        DIB_RGB_COLORS) == 0)
    {
        // clean up and return NULL
        ::GlobalUnlock(hDib);
        hDib = NULL;

        ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);

        ::XSError_Set(XSERR_GETBITS);
        return NULL;
    }

    bi = *lpbi;

    // clean up
    ::GlobalUnlock(hDib);
    ::SelectPalette(hDC, hPal, TRUE);
    ::RealizePalette(hDC);
    ::ReleaseDC(NULL, hDC);

    ::XSError_Set(XSERR_NOERROR);

    // return handle to the DIB
    return hDib;
}

// -------------------------------------------------------------
// XSDib_ToBmp
//  Parameters:
//      HDIB - handle to a DIB that the Bitmap (DDB) is to be 
//       created from
//      HPALETTE - palette to use in creation of bitmap (DDB)
//  Return Value:
//      HBITMAP - handle of the Bitmap created from the DIB,
//       NULL on error
//  Description:
//      Returns an HBITMAP created from an HDIB.
//      This function creates a bitmap from a DIB using the 
//      specified palette. If no palette is specified, one is 
//      created, used for the conversion, and then deleted.
//
//      The bitmap returned from this funciton is always a 
//      bitmap compatible with the screen (e.g. same 
//      bits/pixel and color planes) rather than a bitmap 
//      with the same attributes as the DIB.
//
//      This behavior is by design, and occurs because this 
//      function calls CreateDIBitmap to do its work, and 
//      CreateDIBitmap always creates a bitmap compatible with 
//      the hDC parameter passed in (because it in turn calls 
//      CreateCompatibleBitmap).
//
//      So for instance, if your DIB is a monochrome DIB and 
//      you call this function, you will not get back a 
//      monochrome HBITMAP -- you will get an HBITMAP 
//      compatible with the screen DC, but with only 2 colors 
//      used in the bitmap.
//
//      If your application requires a monochrome HBITMAP 
//      returned for a monochrome DIB, use the function 
//      SetDIBits().
// -------------------------------------------------------------
HBITMAP XSFUNC 
XSDib_ToBmp(HDIB hDib, HPALETTE hPal)
{
    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // pointer to DIB header
    LPVOID lpDIBBits = NULL; // pointer to DIB bits
    HBITMAP hBitmap = NULL;  // handle to DDB
    HDC hDC = NULL;          // handle to DC
    HPALETTE hOldPal = NULL; // handle to a palette
    BOOL bPalCreated = FALSE;

    ::XSError_Set(XSERR_NOERROR);

    // if invalid handle, return NULL
    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return NULL;
    }

    // lock memory block and get a pointer to it
    lpDIBHdr = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // get a pointer to the DIB bits
    lpDIBBits = ::XSDib_FindBits(lpDIBHdr);
    if (!lpDIBBits)
        return NULL;

    // get a DC
    hDC = ::GetDC(NULL);
    if (!hDC)
    {
        // clean up and return NULL
        ::GlobalUnlock(hDib);

        ::XSError_Set(XSERR_GETDC);
        return NULL;
    }

    // select and realize palette
    if (!hPal)
    {
        hPal = ::XSDib_CreatePalette(hDib);
        bPalCreated = TRUE;
    }
    hOldPal = ::SelectPalette(hDC, hPal, FALSE);
    ::RealizePalette(hDC);

    // create bitmap from DIB info. and bits
    hBitmap = ::CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)lpDIBHdr, 
        CBM_INIT, lpDIBBits, (LPBITMAPINFO)lpDIBHdr, 
        DIB_RGB_COLORS);
    if (!hBitmap)
    {
        if (hOldPal)
            ::SelectPalette(hDC, hOldPal, FALSE);
        ::DeleteObject(hPal);
        ::XSError_Set(XSERR_CREATEBITMAP);
        return NULL;
    }

    // restore previous palette
    if (hOldPal)
        ::SelectPalette(hDC, hOldPal, FALSE);

    // if we created the palette then we clean it up
    if (bPalCreated && hPal)
        ::DeleteObject(hPal);

    // clean up
    ::ReleaseDC(NULL, hDC);
    ::GlobalUnlock(hDib);

    // return handle to the bitmap
    return hBitmap;
}

// -------------------------------------------------------------
// XSDib_Paint
//  Parameters:
//      HDC hDC - DC to do output to
//      CRect rcDim - rectangle on DC to do output to
//      HDIB hDib - handle to global memory with a DIB spec in 
//       it followed by the DIB bits
//      CRect rcDib - rectangle of DIB to output into DC
//  Return Value:
//      BOOL - TRUE if DIB was drawn, FALSE otherwise
//  Description:
//      Painting routine for a DIB.  Calls StretchDIBits() or
//      SetDIBitsToDevice() to paint the DIB.  The DIB is
//      output to the specified DC, at the coordinates given
//      in lpDCRect.  The area of the DIB to be output is
//      given by lpDIBRect.
//
//      This function always selects the palette as 
//      background. Before calling this function, be sure your 
//      palette is selected to desired priority (foreground 
//      or background).
// -------------------------------------------------------------
BOOL XSFUNC
XSDib_Paint(HDC hDC, CRect rcDim, HDIB hDib, CRect rcDib, 
                 HPALETTE hPal)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC 
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    ASSERT(hDib);

    LPVOID lpDIBHdr = NULL;  // pointer to DIB header
    LPVOID lpDIBBits = NULL; // pointer to DIB bits
    BOOL bSuccess = FALSE;   // Success/fail flag
    HPALETTE hOldPal = NULL; // Previous palette

    // Check for valid DIB handle
    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return FALSE;
    }

    // Lock the DIB, and get a pointer to the beginning 
    // of the bit buffer
    lpDIBHdr  = ::GlobalLock((HGLOBAL)hDib);
    if (!lpDIBHdr)
    {
        ::XSError_Set(XSERR_LOCK);
        return FALSE;
    }

    lpDIBBits = ::XSDib_FindBits(lpDIBHdr);
    if (!lpDIBBits)
        return FALSE;

    // Select and realize our palette as background
    if (hPal)
    {
        hOldPal = ::SelectPalette(hDC, hPal, TRUE);
        ::RealizePalette(hDC);
    }

    // Make sure to use the stretching mode best for color 
    // pictures
    ::SetStretchBltMode(hDC, COLORONCOLOR);

    // Determine whether to call StretchDIBits() or 
    // SetDIBitsToDevice()
    if ((rcDim.Width()  == rcDib.Width()) && 
        (rcDim.Height() == rcDib.Height()))
    {
        bSuccess = ::SetDIBitsToDevice(hDC, rcDim.left, rcDim.top, 
            rcDim.Width(), rcDim.Height(), rcDib.left, 
            (int)::XSDib_Height(lpDIBHdr) - rcDib.top - 
            rcDib.Height(), 0, ::XSDib_Height(lpDIBHdr), 
            lpDIBBits, (LPBITMAPINFO)lpDIBHdr, DIB_RGB_COLORS);
    }
    else 
    {
        bSuccess = ::StretchDIBits(hDC, rcDim.left, rcDim.top, 
            rcDim.Width(), rcDim.Height(), rcDib.left, rcDib.top,
            rcDib.Width(), rcDib.Height(), lpDIBBits, 
            (LPBITMAPINFO)lpDIBHdr, DIB_RGB_COLORS, SRCCOPY);
    }

    if (bSuccess)
        ::XSError_Set(XSERR_NOERROR);
    else
        ::XSError_Set(XSERR_PAINT);

    // Unlock the memory block
    ::GlobalUnlock(hDib);

    // Reselect old palette
    if (hOldPal)
        ::SelectPalette(hDC, hOldPal, FALSE);

    // Return with success/fail flag
    return bSuccess;
}

// -------------------------------------------------------------
// XSBmp_ChangeFormat
//  Parameters:
//        HBITMAP - handle to a bitmap
//        WORD - desired bits per pixel (BPP)
//          - May be 0 if you pass BI_RLE4 or BI_RLE8
//        DWORD - desired compression format
//          BI_RLE4 - Use with 4-bit BPP
//          BI_RLE8 - Use with 8-bit BPP
//          BI_RGB - Use with 1, 4, 8, 16, or 32-bit BPP
//        HPALETTE - handle to palette
//  Return Value:
//        HDIB - handle to the new DIB if successful, else NULL
//  Description:
//        This function will convert a bitmap to the specified 
//        bits per pixel and compression format. The bitmap and 
//        it's palette will remain after calling this function.
// -------------------------------------------------------------
HDIB XSFUNC
XSBmp_ChangeFormat(HBITMAP hBitmap, WORD wBitCount, DWORD dwCompression, HPALETTE hPal)
{
    HDC                hDC;          // Screen DC
    HDIB               hNewDIB=NULL; // Handle to new DIB
    BITMAP             bm;           // BITMAP data structure
    BITMAPINFOHEADER   bi;           // Bitmap info. header
    LPBITMAPINFOHEADER lpbi;         // Pointer to bitmap header
    HPALETTE           hOldPal=NULL; // Handle to palette
    WORD               NewBPP;       // New bits per pixel
    DWORD              NewComp;      // New compression format

    // Check for a valid bitmap handle 
    if (!hBitmap)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return NULL;
    }

    // Validate wBitCount and dwCompression
    // They must match correctly (i.e., BI_RLE4 and 4 BPP or
    // BI_RLE8 and 8BPP, etc.) or we return failure
    if (wBitCount == 0)
    {
        NewComp = dwCompression;
        if (NewComp == BI_RLE4)
            NewBPP = 4;
        else if (NewComp == BI_RLE8)
            NewBPP = 8;
        else // Not enough info
        {
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return NULL;
        }
    }
    else if (wBitCount == 1 && dwCompression == BI_RGB)
    {
        NewBPP = wBitCount;
        NewComp = BI_RGB;
    }
    else if (wBitCount == 4)
    {
        NewBPP = wBitCount;
        if (dwCompression == BI_RGB || dwCompression == BI_RLE4)
            NewComp = dwCompression;
        else
        {
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return NULL;
        }
    }
    else if (wBitCount == 8)
    {
        NewBPP = wBitCount;
        if (dwCompression == BI_RGB || dwCompression == BI_RLE8)
            NewComp = dwCompression;
        else
        {
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return NULL;
        }
    }
    else if ((wBitCount == 24 || wBitCount == 36) 
        && dwCompression == BI_RGB)
    {
        NewBPP = wBitCount;
        NewComp = BI_RGB;
    }
    else
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        return NULL;
    }

    // Get info about the bitmap 
    ::GetObject(hBitmap, sizeof(BITMAP), &bm);

    // Fill in the BITMAPINFOHEADER appropriately
    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = NewBPP;
    bi.biCompression        = NewComp;
    bi.biSizeImage          = 0;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = 0;
    bi.biClrImportant       = 0;

    // Go allocate room for the new DIB
    hNewDIB = ::XSDib_Template(bi, hBitmap);
    if (!hNewDIB)
        return NULL;

    // Get a pointer to the new DIB
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hNewDIB);
    if (!lpbi)
    {
        ::XSError_Set(XSERR_LOCK);
        return NULL;
    }

    // If we have a palette, get a DC and select/realize it
    if (hPal)
    {
        hDC  = ::GetDC(NULL);
        hOldPal = ::SelectPalette(hDC, hPal, FALSE);
        ::RealizePalette(hDC);
    }

    // Call GetDIBits and get the new DIB bits
    if (!GetDIBits(hDC, hBitmap, 0, (WORD) lpbi->biHeight, 
        (LPSTR)lpbi + (WORD)lpbi->biSize 
        + ::XSDib_PaletteSize(lpbi),
        (LPBITMAPINFO)lpbi, DIB_RGB_COLORS))
    {
        ::GlobalUnlock(hNewDIB);
        ::GlobalFree(hNewDIB);
        hNewDIB = NULL;
    }

    // Clean up and return
    if (hOldPal)
    {
        ::SelectPalette(hDC, hOldPal, TRUE);
        ::RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);
    }

    if (hNewDIB)
    {
        // Unlock the new DIB's memory block
        ::GlobalUnlock(hNewDIB);
    }

    ::XSError_Set(XSERR_NOERROR);
    return hNewDIB;
}

// -------------------------------------------------------------
// XSDib_ChangeFormat
//  Parameters:
//        HDIB - handle to packed-DIB in memory
//        WORD - desired bits per pixel
//        DWORD - desired compression format
//  Return Value:
//        HDIB - handle to the new DIB if successful, else NULL
//  Description:
//      Formats a DIB to a new BPP.
//        This function will convert the bits per pixel and/or the 
//      compression format of the specified DIB. Note: If the 
//      conversion was unsuccessful, we return NULL. The 
//      original DIB is left alone. Don't use code like the 
//      following:
//
//      hMyDIB = XSDib_ChangeFormat(hMyDIB, 8, BI_RLE4);
//
//      The conversion will fail, but hMyDIB will now be NULL 
//      and the original DIB will now hang around in memory. We 
//      could have returned the old DIB, but we wanted to allow 
//      the programmer to check whether this conversion 
//      succeeded or failed.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_ChangeFormat(HDIB hDib, WORD wBitCount, DWORD dwCompression)
{
    HDC                hDC;             // Handle to DC
    HBITMAP            hBitmap;         // Handle to bitmap
    BITMAP             bm;              // BITMAP data structure
    BITMAPINFOHEADER   bi;              // Bitmap info header
    LPBITMAPINFOHEADER lpbi;            // Pointer to bitmap info
    HDIB               hNewDIB = NULL;  // Handle to new DIB
    HPALETTE           hPal, hOldPal;   // Handle to palette, prev pal
    WORD               DIBBPP, NewBPP;  // DIB bits per pixel, new bpp
    DWORD              DIBComp, NewComp;// DIB compression, new 
                                        // compression

    // Check for a valid DIB handle
    if (!hDib)
    {
        ::XSError_Set(XSERR_HANDLENULL);
        return NULL;
    }

    // Get the old DIB's bits per pixel and compression format
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hDib);
    DIBBPP = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
    DIBComp = ((LPBITMAPINFOHEADER)lpbi)->biCompression;
    ::GlobalUnlock(hDib);

    // Validate wBitCount and dwCompression
    // They must match correctly (i.e., BI_RLE4 and 4 BPP or
    // BI_RLE8 and 8BPP, etc.) or we return failure 
    if (wBitCount == 0)
    {
        NewBPP = DIBBPP;
        if ((dwCompression == BI_RLE4 && NewBPP == 4) ||
            (dwCompression == BI_RLE8 && NewBPP == 8) ||
            (dwCompression == BI_RGB))
            NewComp = dwCompression;
        else
        {
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return NULL;
        }
    }
    else if (wBitCount == 1 && dwCompression == BI_RGB)
    {
        NewBPP = wBitCount;
        NewComp = BI_RGB;
    }
    else if (wBitCount == 4)
    {
        NewBPP = wBitCount;
        if (dwCompression == BI_RGB || dwCompression == BI_RLE4)
            NewComp = dwCompression;
        else
        {
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return NULL;
        }
    }
    else if (wBitCount == 8)
    {
        NewBPP = wBitCount;
        if (dwCompression == BI_RGB || dwCompression == BI_RLE8)
            NewComp = dwCompression;
        else
        {
            ::XSError_Set(XSERR_NOERROR);
            return NULL;
        }
    }
    else if ((wBitCount == 24 || wBitCount == 36 )
        && dwCompression == BI_RGB)
    {
        NewBPP = wBitCount;
        NewComp = BI_RGB;
    }
    else
    {
        ::XSError_Set(XSERR_INVALIDFORMAT);
        return NULL;
    }

    // Save the old DIB's palette 
    hPal = ::XSDib_CreatePalette(hDib);
    if (!hPal)
    {
        ::XSError_Set(XSERR_CREATEPAL);
        return NULL;
    }

    // Convert old DIB to a bitmap 
    hBitmap = ::XSDib_ToBmp(hDib, hPal);
    if (!hBitmap)
    {
        ::DeleteObject(hPal);
        ::XSError_Set(XSERR_CREATEBITMAP);
        return NULL;
    }

    // Get info about the bitmap 
    ::GetObject(hBitmap, sizeof(BITMAP), &bm);

    // Fill in the BITMAPINFOHEADER appropriately 
    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = NewBPP;
    bi.biCompression        = NewComp;
    bi.biSizeImage          = 0;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = 0;
    bi.biClrImportant       = 0;

    // Go allocate room for the new DIB 
    hNewDIB = ::XSDib_Template(bi, hBitmap);
    if (!hNewDIB)
        return NULL;

    // Get a pointer to the new DIB 
    lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hNewDIB);
    if (!lpbi)
    {
        ::XSError_Set(XSERR_NOERROR);
        return NULL;
    }

    // Get a DC and select/realize our palette in it 
    hDC  = ::GetDC(NULL);
    hOldPal = ::SelectPalette(hDC, hPal, FALSE);
    ::RealizePalette(hDC);

    // Call GetDIBits and get the new DIB bits 
    if (!::GetDIBits(hDC, hBitmap, 0, (WORD) lpbi->biHeight, 
        (LPSTR)lpbi + (WORD)lpbi->biSize 
        + ::XSDib_PaletteSize(lpbi), 
        (LPBITMAPINFO)lpbi, DIB_RGB_COLORS))
    {
        ::GlobalUnlock(hNewDIB);
        ::GlobalFree(hNewDIB);
        hNewDIB = NULL;
    }

    // Clean up and return 
    ::SelectPalette(hDC, hOldPal, TRUE);
    ::RealizePalette(hDC);
    ::ReleaseDC(NULL, hDC);

    // Unlock the new DIB's memory block 
    if (hNewDIB)
        ::GlobalUnlock(hNewDIB);

    ::DeleteObject(hBitmap);
    ::DeleteObject(hPal);

    ::XSError_Set(XSERR_NOERROR);
    return hNewDIB;
}

// -------------------------------------------------------------
// XSDib_Rotate
//  Parameters:
//        HDIB - handle to a DIB
//        BOOL - TRUE to rotate clockwise, FALSE for 
//               counter-clockwise
//  Return Value:
//        HDIB - handle to the new DIB if successful, else NULL
//  Description:
//        This function will rotate the passed DIB in 90 degree 
//      increments and return the handle to the new DIB.
// -------------------------------------------------------------
HDIB XSFUNC
XSDib_Rotate(HDIB hDibSrc, BOOL bClockwise)
{
#ifdef _USRDLL
    // if this code is in a user DLL, we need to set up the MFC 
    // state if we use MFC in this function
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    DWORD       dwSrcWidth;     // DIB src width
    DWORD        dwSrcHeight;    // DIB src height
    DWORD       dwPadWidth;     // Needed padding width
    DWORD       x, y, z;
    WORD        i;
    WORD        wBitCount;      // DIB src BPP
    WORD        wNumColors;     // DIB src number of colors
    BYTE        lpSrcByte;
    BYTE        lpDestByte;
    LPSTR       lpSrcBits;
    LPSTR        lpDestBits;
    LPSTR        lpSrc;
    LPSTR       lpDest;
    LPSTR       lpTmp;
    HDIB        hDibDest;       // Destination DIB (rotated)
    LPRGBQUAD    lpSrcColor;     // Pointer to src color table
    LPRGBQUAD    lpDestColor;    // Pointer to dest color table

    ASSERT(hDibSrc);

    CWaitCursor wait;

    // Get pointer to source DIB and it's bits
    lpSrc     = (LPSTR)::GlobalLock(hDibSrc);
    lpSrcBits = (LPSTR)::XSDib_FindBits(lpSrc);

    // Get some useful info about our source DIB
    dwSrcWidth   = ((LPBITMAPINFOHEADER)lpSrc)->biWidth;
    dwSrcHeight  = ((LPBITMAPINFOHEADER)lpSrc)->biHeight;
    wBitCount  = ((LPBITMAPINFOHEADER)lpSrc)->biBitCount;
    wNumColors = ::XSDib_NumColors(lpSrc);

    // Create a new dib that will contain the rotated bits
    hDibDest = ::XSDib_Create(dwSrcHeight, dwSrcWidth, wBitCount);
    if (!hDibDest)
    {
        ::GlobalUnlock(hDibSrc);
        return NULL;
    }

    lpDest     = (LPSTR)::GlobalLock(hDibDest);
    lpDestBits = (LPSTR)::XSDib_FindBits(lpDest);

    // Copy source DIB's color table to destination DIB
    lpSrcColor  = (LPRGBQUAD)(lpSrc + (sizeof(BITMAPINFOHEADER)));
    lpDestColor = (LPRGBQUAD)(lpDest + (sizeof(BITMAPINFOHEADER)));
    for (i = 0; i < wNumColors; i++)
    {
        *lpDestColor++ = *lpSrcColor++;
    }

    // Calculate the padding required to align on DWORDs
    // since DIB scanlines are aligned on DWORD boundaries
    // Padding for the height is required since rotating by
    // 90 degrees turns our source height into the destination's
    // width, which would need to be DWORD aligned too
    dwPadWidth  = ::XSDib_CalcPadding(wBitCount, dwSrcWidth);

    // Copy the source bits to the destination while rotating each scanline
    DWORD dwScanline = ::XSDib_CalcBytesPerLine(wBitCount, dwSrcHeight);
    switch (wBitCount)
    {
        case 1: // monochrome DIBs
        {
            BYTE BitMask = 0x80;
            long destPos;
            BYTE destBit;
            memset((void *)lpDestBits, 0, (size_t)(dwScanline * dwSrcWidth));

            if (bClockwise) 
            { 
                // Clockwise
                for (y = 0; y < dwSrcHeight; y++) 
                {
                    destPos = (y % 8);
                    destBit = (unsigned char)(BitMask >> destPos);
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Mask off the bit we want from the src
                        if (*lpSrcBits & (BitMask >> (x % 8))) 
                        {
                            // Get the destination byte
                            lpTmp = lpDestBits + ((dwSrcWidth - x - 1) * 
                                dwScanline);
                            
                            // Set the destination bit
                            *lpTmp |= (BitMask >> destPos);                                                                                 
                        }

                        if (((x + 1) % 8) == 0)
                        {
                            // Point to next source byte
                            lpSrcBits++;
                        }
                    }

                    // Skip bytes in the source to pad to a DWORD
                    lpSrcBits += dwPadWidth;

                    if (((y + 1) % 8) == 0)
                    {
                        // Point to next column in the destination
                        lpDestBits++;
                    }
                }
            } 
            else 
            {  
                // Counter-clockwise
                lpDestBits += (::XSDib_LastByte(wBitCount, 
                    dwSrcHeight) - 1);
                
                for (y = 0; y < dwSrcHeight; y++)
                {
                    destPos = ((dwSrcHeight - y - 1) % 8);  
                    destBit = (unsigned char)(BitMask >> destPos);
                    
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Shift src bit to dest bit's position
                        if (*lpSrcBits & (BitMask >> (x % 8))) 
                        {
                            // Get the destination byte
                            lpTmp = lpDestBits + 
                                (x * dwScanline);

                            // Set the destination bit
                            *lpTmp |= (BitMask >> destPos);
                        }
                        
                        if (((x + 1) % 8) == 0)
                        {
                            // Point to next source byte
                            lpSrcBits++;
                        }
                    }
                 
                    // Skip bytes in the source to pad 
                    // to a DWORD
                    lpSrcBits += dwPadWidth;

                    if (destPos == 0)
                    {
                        // Point to next column in the 
                        // destination
                        lpDestBits--;
                    }
                }
            }
        }
        break;

        case 4: // 16-color DIBs
        {
            BYTE LoMask    = 0x0F;
            BYTE HiMask    = 0xF0;
            BOOL bLoNibble = FALSE;

            if (bClockwise) 
            { 
                // Clockwise
                for (y = 0; y < dwSrcHeight; y++)
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Get the source byte
                        lpSrcByte = *lpSrcBits;

                        // Mask off the nibble we want
                        if (x % 2)
                        {
                            if (bLoNibble)
                                lpSrcByte &= LoMask;
                            else
                                lpSrcByte = (unsigned char)
                                ((lpSrcByte << wBitCount) & HiMask);
                        }
                        else
                        {
                            if (bLoNibble)
                                lpSrcByte = (unsigned char)
                                ((lpSrcByte >> wBitCount) & LoMask);
                            else
                                lpSrcByte &= HiMask;
                        }

                        // Get the destination byte
                        lpTmp = lpDestBits + 
                            ((dwSrcWidth - x - 1) * dwScanline);
                        lpDestByte = *lpTmp;

                        // Mask off the unneeded nibble
                        if (bLoNibble)
                            lpDestByte &= HiMask;
                        else
                            lpDestByte = 0x00;

                        // Set the dest nibble
                        *lpTmp = (char)(lpSrcByte | lpDestByte);

                        if (x % 2)
                        {
                            // Point to next source byte
                            lpSrcBits++;
                        }
                    }

                    // Skip bytes in the source to pad 
                    // to a DWORD
                    lpSrcBits += dwPadWidth;

                    if (y % 2)
                    {
                        // Point to next column in the destination
                        lpDestBits++;
                    }

                    // Toggle LoNibble flag
                    bLoNibble = !bLoNibble;
                }
            }
            else 
            {  
                // Counter-clockwise
                lpDestBits += (::XSDib_LastByte(wBitCount, 
                    dwSrcHeight) - 1);
                if((dwSrcHeight % 2) == 0)
                    bLoNibble = TRUE;

                for (y = 0; y < dwSrcHeight; y++)
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Get the source byte
                        lpSrcByte = *lpSrcBits;

                        // Mask off the nibble we want
                        if (x % 2)
                        {
                            if (bLoNibble)
                                lpSrcByte &= LoMask;   // 2
                            else
                                lpSrcByte = (unsigned char)
                                    ((lpSrcByte << wBitCount) 
                                    & HiMask);        // 4
                        }
                        else
                        {
                            if (bLoNibble)            // 3
                                lpSrcByte = (unsigned char)
                                    ((lpSrcByte >> wBitCount) 
                                    & LoMask);
                            else
                                lpSrcByte &= HiMask;    // 1
                        }

                        // Get the destination byte
                        lpTmp = lpDestBits + (x * dwScanline);
                        lpDestByte = *lpTmp;

                        // Mask off the unneeded nibble
                        if (bLoNibble)
                            lpDestByte = 0x00;
                        else
                            lpDestByte &= LoMask;

                        // Set the dest nibble
                        *lpTmp = (char)(lpSrcByte | lpDestByte);

                        if (x % 2)
                        {
                            // Point to next source byte
                            lpSrcBits++;
                        }
                    }

                    // Skip bytes in the source to pad 
                    // to a DWORD
                    lpSrcBits += dwPadWidth;

                    if ((dwSrcHeight - y) % 2)
                    {
                        // Point to next column in the destination
                        lpDestBits--;
                    }

                    // Toggle LoNibble flag
                    bLoNibble = !bLoNibble;
                }
            }
        }
        break;

        case 8: // 256-color DIBs
        {
            if (bClockwise) 
            { 
                // clockwise
                for (y = 0; y < dwSrcHeight; y++)
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Get the source byte
                        lpSrcByte = *lpSrcBits++;

                        // Set the destination byte
                        lpTmp  = lpDestBits + 
                            ((dwSrcWidth - x - 1) * dwScanline);
                        *lpTmp = lpSrcByte;
                    }

                    // Skip bytes in the source 
                    // to pad to a DWORD.
                    lpSrcBits += dwPadWidth;

                    // Next column in the destination. 
                    // Only for 90 degree rotations.
                    lpDestBits++;
                }
            }
            else 
            { 
                // counter clockwise
                lpDestBits += (::XSDib_LastByte(wBitCount, 
                    dwSrcHeight) - 1);
                for (y = 0; y < dwSrcHeight; y++)
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Get the source byte
                        lpSrcByte = *lpSrcBits++;

                        // Set the destination byte
                        lpTmp  = lpDestBits + (x * dwScanline);
                        *lpTmp = lpSrcByte;
                    }

                    // Skip bytes in the source to pad 
                    // to a DWORD.
                    lpSrcBits += dwPadWidth;

                    // Next column in the destination. 
                    // Only for 90 degree rotations.
                    lpDestBits--;
                }
            }
        }
        break;

        case 16:
        case 24:
        case 32:
        {
            if (bClockwise) 
            {
                for (y = 0; y < dwSrcHeight; y++)
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        // Get the source byte
                        // lpSrcByte = *lpSrcBits++;

                        // Set the destination byte
                        lpTmp  = lpDestBits + 
                            ((dwSrcWidth - x - 1) * dwScanline);
                        for (z = 0; z < 3; z++) 
                        {
                            lpSrcByte = *lpSrcBits++;
                            *lpTmp++ = lpSrcByte;
                        }
                    }

                    // Skip bytes in the source to pad to a DWORD.
                    lpSrcBits += dwPadWidth;

                    // Next column in the destination. 
                    // Only for 90 degree rotations.
                    lpDestBits += 3;
                }
            }
            else
            {
                lpDestBits += (::XSDib_LastByte(wBitCount, 
                    dwSrcHeight) - 3);
                for (y = 0; y < dwSrcHeight; y++) 
                {
                    for (x = 0; x < dwSrcWidth; x++)
                    {
                        lpTmp = lpDestBits + (x * dwScanline);
                        for (z=0; z<3; z++) 
                        {
                            lpSrcByte = *lpSrcBits++;
                            *lpTmp++ = lpSrcByte;
                        }
                    }
                    
                    lpSrcBits += dwPadWidth;
                    lpDestBits -= 3;
                }
            }
        }
        break;

        default: // Unsupported format
            ::GlobalUnlock(hDibSrc);
            ::GlobalUnlock(hDibDest);
            ::XSDib_Destroy(hDibDest);
            ::AfxMessageBox(_T("Rotate: Error, unsupported bit format."), 
                MB_OK);
            ::XSError_Set(XSERR_INVALIDFORMAT);
            return FALSE;
    }
    
    // When we get here, a rotated DIB is available.
    ::GlobalUnlock(hDibSrc);
    ::GlobalUnlock(hDibDest);
    ::XSError_Set(XSERR_NOERROR);

    return hDibDest;
}

