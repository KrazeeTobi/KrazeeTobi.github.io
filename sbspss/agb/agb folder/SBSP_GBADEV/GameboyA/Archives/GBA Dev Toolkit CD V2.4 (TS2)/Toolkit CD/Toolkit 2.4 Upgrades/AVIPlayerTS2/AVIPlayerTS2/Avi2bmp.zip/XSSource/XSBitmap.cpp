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
#include "XSDibApi.h"
#include "XSPalApi.h"
#include "XSPalette.h"
#include "XSBitmap.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CXSBitmap, CBitmap, XS_DIB_SCHEMA)

///////////////////////////////////////////////////////////
// class CXSBitmap : public CBitmap

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::CXSBitmap
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSBitmap::CXSBitmap()
{
    memset(&m_bm, '\0', sizeof(BITMAP));
}

// -------------------------------------------------------------
// Function  :
//     CXSBitmap::~CXSBitmap
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSBitmap::~CXSBitmap()
{
    // clean up
    DoDeleteObject();
}

// -------------------------------------------------------------
// Function  :
//     CXSBitmap::DoDeleteObject
// Purpose   :
//    Cleans up memory
// -------------------------------------------------------------
BOOL
CXSBitmap::DoDeleteObject()
{
    ASSERT_VALID(this);

    memset(&m_bm, 0, sizeof(BITMAP));
    m_Palette.DeleteObject();
    ::XSError_Set(XSERR_NOERROR);
    return CBitmap::DeleteObject();
}

// -------------------------------------------------------------
// Function  :
//     CXSBitmap::DoAttach
// Purpose   :
//    Converts the passed HDIB to an HBITMAP and attaches it to
//    the underlying CGdiObject. Also, attaches the HPALETTE to
//    the CPalette associated with this object.  If the HPALETTE
//    is NULL, a halftone palette will be created.  Destroys the
//    passed HDIB when it return successfully, otherwise on
//    failure it does not destroy the passed DIB.
// Parameters:
//    HDIB hDib - The DIB to convert and attach
//    HPALETTE hPal - the associated palette
// Returns   :
//     TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoAttach(HDIB hDib, HPALETTE hPal)
{
    ASSERT_VALID(this);
    ASSERT(hDib);  // must be valid

    HBITMAP hBitmap = NULL;
    BOOL bResult = FALSE;
    HPALETTE hPalette = hPal;

    // See if palette is valid. If not, create one to use
    if (!hPalette)
    {
        hPalette = ::XSDib_CreatePalette(hDib);
        if (!hPalette)
        {
            HDC hDC = ::GetDC(NULL);
            hPalette = ::CreateHalftonePalette(hDC);
            ::ReleaseDC(NULL, hDC);
        }
    }

    // Convert DIB to a Bitmap
    hBitmap = ::XSDib_ToBmp(hDib, hPalette);

    // Kill any existing bitmap and palette
    // attached to this object
    DoDeleteObject();

    // Attach the palette
    m_Palette.Attach(hPalette);

    // Attach the new bitmap
    // Call base class as this is a DDB now
    if (hBitmap && CBitmap::Attach(hBitmap))
    {
        // Destroy the passed DIB
        ::XSDib_Destroy(hDib);

        // Calculate image size
        Size();

        bResult = TRUE;
        ::XSError_Set(XSERR_NOERROR);
    }
    else
    {
        // If we couldn't Attach, clean up memory
		// Only delete the palette if we created it
        if (!hPal)
            DoDeleteObject();

        ::XSError_Set(XSERR_CREATEBITMAP);
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoLoad
// Purpose   :
//    Loads a bitmap from resource of the specified HINSTANCE.
//    Uses a DIB Section to create the proper palette
// Parameters:
//    HINSTANCE hInst - where to load from
//    UINT nID - ID of the bitmap to load
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoLoad(HINSTANCE hInst, UINT nID)
{
    ASSERT_VALID(this);

    HBITMAP hBitmap = NULL;
    HDIB hDib = NULL;
    BOOL bResult = FALSE;

    ::XSError_Set(XSERR_CREATEBITMAP);

    // load the Bitmap from specified HINSTANCE,
    // creating a DIB Section
    hBitmap = ::XSBmp_Load(hInst, nID);
    if (hBitmap)
    {
        // make a temporary DIB
        HDIB hDib = ::XSBmp_ToDib(hBitmap, NULL);
        ASSERT(hDib);  // sanity check

        // Kill the Bitmap
        ::DeleteObject(hBitmap);

        // Attach the bitmap to the GDI object
        // Attach creates a palette for us
        if (DoAttach(hDib))
        {
            bResult = TRUE;
            ::XSError_Set(XSERR_NOERROR);
        }
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoLoad
// Purpose   :
//    Finds the bitmap ID and loads it
// Parameters:
//    UINT nID - ID of the bitmap to load
// Note      :
//    This function calls MFC's AfxFindResourceHandle to get the
//    HINSTANCE of where the resource with the specified ID
//    lives.  It finds the first bitmap with the specified ID,
//    which may not be the one you want.
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoLoad(UINT nID)
{
    // find HINSTANCE with specified resource ID
    HINSTANCE hInstApp =
        AfxFindResourceHandle(MAKEINTRESOURCE(nID), RT_BITMAP);
    return DoLoad(hInstApp, nID);
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoLoad
// Purpose   :
//    Loads a DIB bitmap from a file
// Parameters:
//    CString strFileName - path to the DIB to load
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoLoad(CString strFileName)
{
    ASSERT_VALID(this);

    HDIB hDib = NULL;
    HPALETTE hPalette = NULL;
    HBITMAP hBitmap = NULL;
    BOOL bResult = FALSE;

    if (strFileName.IsEmpty())
        return FALSE;

    // load the DIB
    hDib = ::XSDib_Load(strFileName);
    if (hDib)
    {
        // attach the DIB
        if (DoAttach(hDib))
        {
            bResult = TRUE;
            ::XSError_Set(XSERR_NOERROR);
        }
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoSave
// Purpose   :
//    Converts the attached bitmap to a DIB and saves it to the
//    specified file.
// Parameters:
//    CString strFileName - path of file to save to
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoSave(CString strFileName)
{
    ASSERT_VALID(this);
    ASSERT(GetSafeHandle());

    HDIB hDib = NULL;
    BOOL bResult = FALSE;

    // convert Bitmap to DIB
    hDib = ::XSBmp_ToDib((HBITMAP)GetSafeHandle(),
        (HPALETTE)m_Palette.GetSafeHandle());
    if (hDib)
    {
        // save DIB
        WORD wResult = ::XSDib_Save(hDib, strFileName);

        // destroy DIB
        ::XSDib_Destroy(hDib);
        if (wResult == 0)
        {
            bResult = TRUE;
            ::XSError_Set(XSERR_NOERROR);
        }
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoSerialize
// Purpose   :
//    Serialize the attached bitmap as a DIB into a document
// Parameters:
//    CArchive& ar - the archive to write into/read from
// Returns   :
//    Nothing. Throws an archive exception on error of type
//    CArchiveException::generic
// -------------------------------------------------------------
void
CXSBitmap::DoSerialize(CArchive& ar)
{
    ASSERT_VALID(this);

    CBitmap::Serialize(ar);

    HDIB hDib = NULL;

    if (ar.IsStoring())
    {
        // make sure there is something to store
        ASSERT(GetSafeHandle());

        // convert Bitmap to DIB
        hDib = ::XSBmp_ToDib((HBITMAP)GetSafeHandle(),
            (HPALETTE)m_Palette.GetSafeHandle());
        if (hDib)
        {
            // write of the DIB
            if (XSERR_NOERROR !=
                ::XSDib_WriteFile(hDib, *(ar.GetFile())))
                AfxThrowArchiveException(CArchiveException::generic);

            // remove the DIB memory
            ::XSDib_Destroy(hDib);

            ::XSError_Set(XSERR_NOERROR);
        }
        else
        {
            ::XSError_Set(XSERR_WRITE);
            AfxThrowArchiveException(CArchiveException::generic);
        }
    }
    else
    {
        hDib = ::XSDib_ReadFile(*(ar.GetFile()),
            ar.GetFile()->GetPosition());
        if (hDib)
        {
            DoAttach(hDib);
            ::XSError_Set(XSERR_NOERROR);
        }
        else
        {
            ::XSError_Set(XSERR_READ);
            AfxThrowArchiveException(CArchiveException::generic);
        }
    }
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::Size
// Purpose   :
//    Returns the bitmap width and height in a CSize
// Parameters:
//    None
// Returns   :
//    The width and height of the bitmap in a CSize
// -------------------------------------------------------------
CSize
CXSBitmap::Size()
{
    ::XSError_Set(XSERR_NOERROR);
    GetBitmap(&m_bm);
    return CSize(m_bm.bmWidth, m_bm.bmHeight);
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::Width
// Purpose   :
//    Returns the width of the bitmap
// Parameters:
//    None
// Returns   :
//    The width of the bitmap
// -------------------------------------------------------------
DWORD
CXSBitmap::Width()
{
    ::XSError_Set(XSERR_NOERROR);
    if (m_bm.bmWidth == 0 )
        Size();
    return m_bm.bmWidth;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::Height
// Purpose   :
//    Returns the height of the bitmap
// Parameters:
//    None
// Returns   :
//    The height of the bitmap
// -------------------------------------------------------------
DWORD
CXSBitmap::Height()
{
    ::XSError_Set(XSERR_NOERROR);
    if (m_bm.bmHeight == 0 )
        Size();
    return m_bm.bmHeight;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoPaintNormal
// Purpose   :
//    Paints the bitmap inside the CRect of the specified DC.
//    There is also an option to tile the bitmap
// Parameters:
//    CDC* pDC - pointer to the DC to write into
//    CRect rcDest - the destination rectangle
//    BOOL bTile - TRUE to tile the bitmap,
//               - FALSE to paint the bitmap normally (default)
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSBitmap::DoPaintNormal(CDC* pDC, CRect rcDest, BOOL bTile)
{
    ASSERT_VALID(this);
    ASSERT(GetSafeHandle());

    CDC imageDC;  // DC for image
    CDC memDC;    // DC for assembling image
    CPoint ptSize;

    CBitmap bmpMem;
    CBitmap* pbmpMem;
    CBitmap* pbmpImage;

    int cxBitmap = Width();    // current bitmap width
    int cyBitmap = Height();   // current bitmap height
    int cxWidth = rcDest.Width();   // destination width
    int cyHeight = rcDest.Height(); // destination width

    int j;  // counter
    int i;  // counter

    ::XSError_Set(XSERR_NOERROR);

    // create an image DC for the original bitmap and select it
    imageDC.CreateCompatibleDC(pDC);
    pbmpImage = (CBitmap*)imageDC.SelectObject(this);

    if (!bTile)
    {
        ptSize.x = cxBitmap;  // Width of drawing area
        ptSize.y = cyBitmap;  // Height of drawing area
    }
    else
    {
        ptSize.x = cxWidth;   // Width of drawing area
        ptSize.y = cyHeight;  // Height of drawing area
    }

    // create a memory DC
    memDC.CreateCompatibleDC(pDC);

    // create a bitmap to draw into and select into memory DC
    bmpMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
    pbmpMem = (CBitmap*)memDC.SelectObject(&bmpMem);

    // Set the proper mapping mode
    imageDC.SetMapMode(pDC->GetMapMode());

    if (bTile)
    {
        // paint the bitmap
        for (i = rcDest.left; i < rcDest.right; i += cxBitmap)
            for (j = rcDest.top; j < rcDest.bottom; j += cyBitmap)
                memDC.BitBlt(i, j, cxBitmap, cyBitmap, &imageDC,
                    0, 0, SRCCOPY);

        DoPaint( pDC, rcDest.left, rcDest.top,
            rcDest.Width(), rcDest.Height(),
            &memDC, 0, 0, 0, 0, SRCCOPY, NormalPaint);
    }
    else
    {
        DoPaint( pDC, rcDest.left, rcDest.top,
            cxBitmap, cyBitmap, &imageDC,
            0, 0, 0, 0, SRCCOPY, NormalPaint);
    }

    // Clean up
    memDC.SelectObject(pbmpMem);
    bmpMem.DeleteObject();
    if (pbmpImage)
        imageDC.SelectObject(pbmpImage);

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//    CXSBitmap::DoPaintTransparent
// Purpose   :
//    Paints the bitmap transparently inside the CRect of the
//    specified DC.  There is also an option to tile the bitmap
// Parameters:
//    CDC* pDC - pointer to the DC to write into
//    CRect rcDest - the destination rectangle
//    COLORREF crTransparentColor - transparent color
//    BOOL bTile - TRUE to tile the bitmap,
//               - FALSE to paint the bitmap normally (default)
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBitmap::DoPaintTransparent(CDC* pDC, CRect rcDest, 
                            COLORREF crTransparentColor, 
                            BOOL bTile)
{
    ASSERT_VALID(this);
    ASSERT(GetSafeHandle());

    CDC tempDC;          // Temp DC to hold original Bitmap
    CBitmap* pbmpTemp;   // old Bitmap for Temp DC
    CPoint ptSize;
    COLORREF crColor;    // old Color
    CDC imageDC;         // Image DC
    CDC backDC;          // Back DC
    CDC maskDC;          // Mask DC
    CDC memDC;           // Memory DC
    CBitmap bmpImage;    // drawing Bitmap for Image DC
    CBitmap bmpBack;     // drawing Bitmap for Back DC
    CBitmap bmpMask;     // drawing Bitmap for Mask DC
    CBitmap bmpMem;      // drawing Bitmap for Memory DC
    CBitmap* pbmpImage;  // old Bitmap for Image DC
    CBitmap* pbmpBack;   // old Bitmap for Back DC
    CBitmap* pbmpMask;   // old Bitmap for Mask DC
    CBitmap* pbmpMem;    // old Bitmap for Memory DC

    int cxBitmap = Width();   // bitmap width
    int cyBitmap = Height();  // bitmap height
    
    int j;  // counter
    int i;  // counter

    ::XSError_Set(XSERR_NOERROR);

    // Create an memory DC for the 
    // original bitmap and select it
    tempDC.CreateCompatibleDC(pDC);
    pbmpTemp = (CBitmap*)tempDC.SelectObject(this);

    if (!bTile)
    {
        ptSize.x = cxBitmap;  // Width actual drawing area
        ptSize.y = cyBitmap;  // Height actual drawing area
    }
    else
    {
        ptSize.x = rcDest.Width();   // Width of drawing area
        ptSize.y = rcDest.Height();  // Height of drawing area
    }
    
    // Create the image DC (this is the one we work with)
    imageDC.CreateCompatibleDC(pDC);
    bmpImage.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
    pbmpImage = (CBitmap*)imageDC.SelectObject(&bmpImage);
    
    if (!bTile)
    {
        // Put the bitmap into the Image DC
        imageDC.BitBlt(rcDest.left, rcDest.top, ptSize.x, 
            ptSize.y, &tempDC, 0, 0, SRCCOPY);
    }
    else
    {
        // Tile the bitmap into the Image DC
        for (i = rcDest.left; i < rcDest.right; i += cxBitmap)
            for (j = rcDest.top; j < rcDest.bottom; j += cyBitmap)
                imageDC.BitBlt(i, j, cxBitmap, cyBitmap, &tempDC, 
                    0, 0, SRCCOPY);
    }

    // Create DCs to hold temporary data
    backDC.CreateCompatibleDC(pDC);
    maskDC.CreateCompatibleDC(pDC);
    memDC.CreateCompatibleDC(pDC);

    // Monochrome DCs
    bmpBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
    bmpMask.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

    bmpMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);

    // Each DC must select a bitmap to store pixel data
    pbmpBack = backDC.SelectObject(&bmpBack);
    pbmpMask = maskDC.SelectObject(&bmpMask);
    pbmpMem = memDC.SelectObject(&bmpMem);

    // Set the proper mapping mode
    tempDC.SetMapMode(pDC->GetMapMode());

    // Set the background color of the source DC 
    // to the color contained in the parts of the 
    // bitmap that will be transparent
    crColor = imageDC.SetBkColor(crTransparentColor);

    // Create the mask for the bitmap by performing a BitBlt
    // from the source bitmap to a monochrome bitmap
    maskDC.BitBlt(0, 0, ptSize.x, ptSize.y, &imageDC, 
        0, 0, SRCCOPY);

    // Set the background color of the source DC back to the 
    // original color
    imageDC.SetBkColor(crColor);

    // Create the inverse of the mask
    backDC.BitBlt(0, 0, ptSize.x, ptSize.y, &maskDC, 
        0, 0, NOTSRCCOPY);

    // Copy the background of the main DC to the destination
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, 
        rcDest.left, rcDest.top, SRCCOPY);

    // Mask out the places where the bitmap will be placed
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, &maskDC, 
        0, 0, SRCAND);

    // Mask out the transparent colored pixels in the bitmap
    imageDC.BitBlt(0, 0, ptSize.x, ptSize.y, &backDC, 
        0, 0, SRCAND);

    // XOR the bitmap with the background on the destination DC
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, &imageDC, 
        0, 0, SRCPAINT);

    // Copy the source to the screen
    DoPaint( pDC, rcDest.left, rcDest.top, ptSize.x, ptSize.y, 
        &memDC, 0, 0, 0, 0, SRCCOPY, TransparentPaint);

    // Delete objects
    if (pbmpTemp)
        tempDC.SelectObject(pbmpTemp);

    imageDC.SelectObject(pbmpImage);
    bmpImage.DeleteObject();

    backDC.SelectObject(pbmpBack);
    bmpBack.DeleteObject();
    
    maskDC.SelectObject(pbmpMask);
    bmpMask.DeleteObject();
    
    memDC.SelectObject(pbmpMem);
    bmpMem.DeleteObject();
    
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBitmap::DoPaintStretch
// Purpose   : 
//    Paints the bitmap inside the CRect of the specified DC, 
//    stretching the bitmap to fill the CRect dimension
// Parameters: 
//    CDC* pDC - pointer to the DC to write into
//    CRect rcDest - the destination rectangle
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBitmap::DoPaintStretch(CDC* pDC, CRect rcDest)
{
    ASSERT_VALID(this);
    ASSERT(GetSafeHandle());

    CDC imageDC;   // DC for image
    CPoint ptSize;

    CBitmap* pbmpImage;              // old Bitmap for Image DC

    ::XSError_Set(XSERR_NOERROR);

    int cxBitmap = Width();          // current bitmap width
    int cyBitmap = Height();         // current bitmap height
    int cxWidth = rcDest.Width();    // destination width
    int cyHeight = rcDest.Height();  // destination height

    // create an image DC for the original bitmap and select it
    imageDC.CreateCompatibleDC(pDC);
    pbmpImage = (CBitmap*)imageDC.SelectObject(this);

    ptSize.x = cxWidth;   // Width of drawing area
    ptSize.y = cyHeight;  // Height of drawing area

    // stretch paint the bitmap
    DoPaint( pDC, rcDest.left, rcDest.top, 
        rcDest.Width(), rcDest.Height(), &imageDC, 0, 0, 
        cxBitmap, cyBitmap, SRCCOPY, StretchPaint);

    // clean up
    if (pbmpImage)
        imageDC.SelectObject(pbmpImage);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBitmap::DoPaintTransparentStretch
// Purpose   : 
//    Paints the bitmap inside the CRect of the specified DC 
//    using transparency and stretching
// Parameters: 
//    CDC* pDC - pointer to the DC to write into
//    CRect rcDest - the destination rectangle
//    COLORREF crTransparentColor - transparent color
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBitmap::DoPaintTransparentStretch(CDC* pDC, CRect rcDest, 
                                   COLORREF crTransparentColor)
{
    ASSERT_VALID(this);
    ASSERT(GetSafeHandle());

    CPoint ptSize;
    COLORREF crColor;      // old Color
    CDC stretchDC;         // DC for stretched image
    CDC imageDC;           // Image DC
    CDC backDC;            // Back DC
    CDC maskDC;            // Mask DC
    CDC memDC;             // Memory DC
    CBitmap bmpStretch;    // drawing Bitmap for Stretch DC
    CBitmap bmpImage;      // drawing Bitmap for Image DC
    CBitmap bmpBack;       // drawing Bitmap for Back DC
    CBitmap bmpMask;       // drawing Bitmap for Mask DC
    CBitmap bmpMem;        // drawing Bitmap for Memory DC
    CBitmap* pbmpStretch;  // old Bitmap for Stretch DC
    CBitmap* pbmpImage;    // old Bitmap for Image DC
    CBitmap* pbmpBack;     // old Bitmap for Back DC
    CBitmap* pbmpMask;     // old Bitmap for Mask DC
    CBitmap* pbmpMem;      // old Bitmap for Memory DC

    ::XSError_Set(XSERR_NOERROR);

    int cxBitmap = Width();         // current bitmap width
    int cyBitmap = Height();        // current bitmap height
    int cxWidth = rcDest.Width();   // destination width
    int cyHeight = rcDest.Height(); // destination height

    // create an image DC for the original bitmap and select it
    imageDC.CreateCompatibleDC(pDC);
    pbmpImage = (CBitmap*)imageDC.SelectObject(this);

    ptSize.x = cxWidth;   // Width of drawing area
    ptSize.y = cyHeight;  // Height of drawing area

    // stretched version of the bitmap
    stretchDC.CreateCompatibleDC(pDC);
    bmpStretch.CreateCompatibleBitmap(pDC, cxWidth, cyHeight);
    pbmpStretch = (CBitmap*)stretchDC.SelectObject(&bmpStretch);

    // See if this device is palette compatible
    if ((pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE) && 
        m_Palette.GetSafeHandle())
    {
        TRACE0("CXSImage: Palette supported\n");

        stretchDC.SelectPalette(&m_Palette, FALSE);
        stretchDC.RealizePalette();
    }

    // stretch the bitmap
    stretchDC.StretchBlt(rcDest.left, rcDest.top, 
        rcDest.Width(), rcDest.Height(), &imageDC, 0, 0, 
        cxBitmap, cyBitmap, SRCCOPY);

    // clean up
    imageDC.SelectObject(pbmpImage);

    // Create the image bitmap (this is the one we work with)
    bmpImage.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
    pbmpImage = (CBitmap*)imageDC.SelectObject(&bmpImage);
    
    // Put the bitmap into the Image DC
    imageDC.BitBlt(rcDest.left, rcDest.top, 
        ptSize.x, ptSize.y, &stretchDC, 0, 0, SRCCOPY);

    // Create DCs to hold temporary data
    backDC.CreateCompatibleDC(pDC);
    maskDC.CreateCompatibleDC(pDC);
    memDC.CreateCompatibleDC(pDC);

    // Monochrome DCs
    bmpBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
    bmpMask.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

    bmpMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);

    // Each DC must select a bitmap to store pixel data
    pbmpBack = backDC.SelectObject(&bmpBack);
    pbmpMask = maskDC.SelectObject(&bmpMask);
    pbmpMem = memDC.SelectObject(&bmpMem);

    // Set the proper mapping mode
    stretchDC.SetMapMode(pDC->GetMapMode());

    // Set the background color of the source DC 
    // to the color contained in the parts of the 
    // bitmap that will be transparent
    crColor = imageDC.SetBkColor(crTransparentColor);

    // Create the mask for the bitmap by performing 
    // a BitBlt from the source bitmap to a 
    // monochrome bitmap
    maskDC.BitBlt(0, 0, ptSize.x, ptSize.y, &imageDC, 
        0, 0, SRCCOPY);

    // Set the background color of the source DC back to the 
    // original color
    imageDC.SetBkColor(crColor);

    // Create the inverse of the mask
    backDC.BitBlt(0, 0, ptSize.x, ptSize.y, &maskDC, 
        0, 0, NOTSRCCOPY);

    // Copy the background of the main DC to the destination
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, 
        rcDest.left, rcDest.top, SRCCOPY);

    // Mask out the places where the bitmap will be placed
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, &maskDC, 
        0, 0, SRCAND);

    // Mask out the transparent colored pixels in the bitmap
    imageDC.BitBlt(0, 0, ptSize.x, ptSize.y, &backDC, 
        0, 0, SRCAND);

    // XOR the bitmap with the background on the destination DC
    memDC.BitBlt(0, 0, ptSize.x, ptSize.y, &imageDC, 
        0, 0, SRCPAINT);

    // Copy the source to the screen
    DoPaint( pDC, rcDest.left, rcDest.top, ptSize.x, ptSize.y, 
        &memDC, 0, 0, 0, 0, SRCCOPY, TransparentStretchPaint);

    // Delete objects
    if (pbmpImage)
        imageDC.SelectObject(pbmpImage);

    stretchDC.SelectObject(pbmpStretch);
    bmpStretch.DeleteObject();

    backDC.SelectObject(pbmpBack);
    bmpBack.DeleteObject();
    
    maskDC.SelectObject(pbmpMask);
    bmpMask.DeleteObject();
    
    memDC.SelectObject(pbmpMem);
    bmpMem.DeleteObject();
    
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBitmap::DoPaint
// Purpose   : 
//    Called by the painting functions to do the actual painting 
//    to the specified DC
// Parameters: 
//    CDC* pDC - DC to paint into
//    int x1 - left position of corner to write to
//    int y1 - top position of corner to write to
//    int cx1 - width of where we want to write to
//    int cy1 - height of where we want to write to
//    CDC* srcDC - source DC containing bitmap
//    int x2 - left position of corner to write from
//    int y2 - top position of corner to write from
//    int cx2 - width of where we want to write from
//              (Only needed for PAINT_STRETCH)
//    int cy2 - height of where we want to write from
//              (Only needed for PAINT_STRETCH)
//    DWORD dwROP - raster operation code
//    PaintType pntType - painting operation type
//              - PaintNormal
//              - PaintTransparent
//              - PaintStretch
//              - PaintTransparentStretch
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBitmap::DoPaint(CDC* pDC, int x1, int y1, int cx1, int cy1, 
                     CDC* srcDC, int x2, int y2, int cx2, int cy2, 
                     DWORD dwROP, PaintType pntType)
{
    ASSERT_VALID(this);
    ASSERT(pDC);
    ASSERT(srcDC);

    ::XSError_Set(XSERR_NOERROR);

    // See if this device is palette compatible
    if ((pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE) && 
        m_Palette.GetSafeHandle())
    {
        TRACE0("CXSBitmap: Palette supported\n");

        pDC->SelectPalette(&m_Palette, FALSE);
        pDC->RealizePalette();
    }

    switch (pntType)
    {
        case NormalPaint:
        case TransparentPaint:
        case TransparentStretchPaint:
            return pDC->BitBlt(x1, y1, cx1, cy1, srcDC, 
                x2, y2, dwROP);

        case StretchPaint:
            return pDC->StretchBlt(x1, y1, cx1, cy1, srcDC, 
                x2, y2, cx2, cy2, dwROP);

        default:
            // unsupported command
            ::XSError_Set(XSERR_INVALIDFORMAT);
            ASSERT(FALSE);
            return FALSE;
    }
}

BOOL
CXSBitmap::DoPaint(CDC* pDC, CRect rcDest, CDC* srcDC, CRect rcSrc, 
                   DWORD dwROP, PaintType pntType)
{
    return DoPaint(pDC, rcDest.left, rcDest.top, rcDest.Width(), 
        rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, 
        rcSrc.Width(), rcSrc.Height(), dwROP, pntType);
}


// -------------------------------------------------------------
// Function  : 
//    CXSBitmap::Rotate
// Purpose   : 
//    Rotates the current bitmap attached to this object by 90 
//    degrees.
// Parameters: 
//    BOOL - TRUE to rotate clockwise
//         - FALSE to rotate counter-clockwise
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL CXSBitmap::Rotate(BOOL bClockwise)
{
    HDIB hDibSrc;
    HDIB hDibDest;

    ASSERT_VALID(this);

    if (!GetSafeHandle())
        return FALSE;

    ::XSError_Set(XSERR_NOERROR);

    // Get a HDIB to work with from the current Bitmap
    hDibSrc = ::XSBmp_ToDib((HBITMAP)GetSafeHandle(), 
        (HPALETTE)m_Palette.GetSafeHandle());
    ASSERT(hDibSrc);  // sanity check

    if (!hDibSrc)
        return FALSE;

    // Rotate the DIB
    hDibDest = ::XSDib_Rotate(hDibSrc, bClockwise);

    // Destroy the temp DIB
    XSDib_Destroy(hDibSrc);

    ASSERT(hDibDest);  // sanity check
    if (!hDibDest)
        return FALSE;

    // Now that we have the rotated bitmap as a DIB, attach
    // the new DIB as a bitmap to this object
    // (DoAttach removes previous objects and creates new 
    // palette for us if we don't provide one)
    if (DoAttach(hDibDest))
        return TRUE;

    // If the attach failed, the original Bitmap is retained
    return FALSE;
}
