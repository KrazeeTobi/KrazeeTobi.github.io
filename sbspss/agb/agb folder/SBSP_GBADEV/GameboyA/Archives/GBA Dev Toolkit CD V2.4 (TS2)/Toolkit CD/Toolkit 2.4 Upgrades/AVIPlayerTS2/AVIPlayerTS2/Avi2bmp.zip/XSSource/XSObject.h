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

#if !defined(AFX_XSOBJECT_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
#define AFX_XSOBJECT_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// Forward declarations
class CXSNotify;

class XSCLASS
CXSObject : public CXSSubWndCtrl
{
// Construction
public:
                  CXSObject();
    virtual       ~CXSObject();

    virtual BOOL  DoInstall(CWnd* pWnd, BOOL bNotify = FALSE);
    virtual BOOL  DoPreInstall();

    LRESULT CallParentDefault();

    // XSEL message helpers
    BOOL    SetParentNotify(CWnd* pWnd);

protected:
    // Our window proc
    virtual LRESULT DoWindowProc(UINT nMsg, WPARAM wParam, 
        LPARAM lParam);

    // XSEL (Registered) Message handlers
    virtual BOOL OnSetParentNotify(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPreNcDestroy(WPARAM wParam, LPARAM lParam);

protected:
    CWnd*&          m_pWnd;

    //  For parent message reflection of common controls
    CXSNotify       m_Notify;

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSObject);

protected:
    virtual BOOL OnCreate(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnDestroy(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSize(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnKillFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnEnable(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetRedraw(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetText(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnGetText(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnGetTextLength(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnPaint(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnClose(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQueryEndSession(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnQuit(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQueryOpen(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnEraseBkgnd(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSysColorChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnEndSession(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnShowWindow(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSettingChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDevModeChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnActivateApp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnFontChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTimeChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCancelMode(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetCursor(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMouseActivate(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnChildActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQueueSync(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaintIcon(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNextDlgCtl(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSpoolerStatus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDrawItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMeasureItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDeleteItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnVKeyToItem(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCharToItem(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSetFont(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnGetFont(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSetHotKey(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnGetHotKey(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnQueryDragIcon(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCompareItem(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCompacting(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPower(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnCopyData(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnInputLangChangeRequest(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInputLangChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTCard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHelp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnUserChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyFormat(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnContextMenu(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnStyleChanging(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnStyleChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDisplayChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnGetIcon(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSetIcon(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNcCreate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcDestroy(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcCalcSize(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNcHitTest(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNcPaint(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcActivate(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnGetDlgCode(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNcMouseHover(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcMouseLeave(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcMouseMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcLButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcLButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcRButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcRButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcMButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcMButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnKeyUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnChar(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDeadChar(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysKeyUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysChar(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysDeadChar(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInitDialog(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTimer(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHScroll(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnVScroll(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInitMenu(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInitMenuPopup(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMenuSelect(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMenuChar(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnEnterIdle(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCtlColorMsgBox(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorEdit(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorListBox(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorBtn(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorDlg(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorScrollBar(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnCtlColorStatic(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMouseMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMButtonDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMouseWheel(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnParentNotify(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnEnterMenuLoop(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnExitMenuLoop(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNextMenu(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSizing(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCaptureChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMoving(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPowerBroadcast(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnDeviceChange(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMdiCreate(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMdiDestroy(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiRestore(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiNext(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiMaximize(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiTile(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMdiCascade(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMdiIconArrange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiGetActive(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMdiSetMenu(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnExitSizeMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDropFiles(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMdiRefreshMenu(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnMouseHover(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCut(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCopy(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaste(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnClear(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnUndo(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnRenderFormat(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRenderAllFormats(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDestroyClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDrawClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaintClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnVScrollClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSizeClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnAskCbFormatName(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnChangeCbChain(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHScrollClipboard(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQueryNewPalette(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnPaletteIsChanging(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaletteChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHotKey(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPrint(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPrintClient(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyOutOfMemory(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyClick(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyDblClk(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyReturn(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyRClick(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifyRDblClk(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifySetFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyKillFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyCustomDraw(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifyHover(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNotifyNcHitTest(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifyKeyDown(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifyReleasedCapture(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifySetCursor(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnNotifyChar(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNotifyTooltipsCreated(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPropSheetApply(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetGetObject(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPropSheetHelp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPropSheetKillActive(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetQueryCancel(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetReset(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetSetActive(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetWizBack(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetWizFinish(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnPropSheetWizNext(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);


    virtual BOOL OnHeaderBeginDrag(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnHeaderEndDrag(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnHeaderItemChanging(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnHeaderItemChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHeaderItemClick(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHeaderItemDblClick(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHeaderDividerDblClick(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHeaderBeginTrack(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnHeaderEndTrack(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHeaderTrack(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnHeaderGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarGetButtonInfo(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnToolbarBeginDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarEndDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarBeginAdjust(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarEndAdjust(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarReset(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarQueryInsert(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnToolbarQueryDelete(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnToolbarToolbarChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarCustHelp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarDropDown(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnToolbarGetObject(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarHotItemChange(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnToolbarDragOut(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarDeletingButton(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnToolbarGetInfoTip(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarHeightChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarGetObject(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarLayoutChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarAutoSize(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarBeginDrag(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnRebarEndDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarDeletingBand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarDeleteBand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRebarChildSize(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTooltipGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTooltipNeedText(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTooltipShow(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTooltipPop(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnStatusBarSimpleModeChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnUpDownDeltaPos(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnListviewItemChanging(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnListviewItemChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewInsertItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewDeleteItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewDeleteAllItems(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnListviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnListviewEndLabelEdit(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnListviewColumnClick(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewBeginDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewBeginRDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewOdCacheHit(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewOdFindItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewItemActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewOdStateChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewHotTrack(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnListviewGetInfoTip(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewMarqueeBegin(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnListviewGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewSetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnListviewKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewSelChanging(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnTreeviewSelChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewSetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewItemExpanding(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnTreeviewItemExpanded(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewBeginDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewBeginRDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewDeleteItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnTreeviewEndLabelEdit(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnTreeviewKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewGetInfoTip(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTreeviewSingleExpand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCbeGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCbeInsertItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCbeDeleteItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCbeBeginEdit(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCbeEndEdit(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnCbeDragBegin(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTabKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTabSelChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnTabSelChanging(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnTabGetObject(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMonCalSelChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMonCalGetDayState(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnMonCalSelect(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeUserString(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeWmKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeFormat(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeFormatQuery(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeDropDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDateTimeCloseUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPagerScroll(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPagerCalcSize(WPARAM wParam, LPARAM lParam);

    virtual BOOL OnQueryAfxWndProc(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSizeParent(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnSetMessageString(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnIdleUpdateCmdUi(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInitialUpdate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCommandHelp(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHelpHitTest(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnExitHelpMode(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnRecalcParent(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSizeChild(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnKickIdle(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDisableModal(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnFloatStatus(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnQuery3dControls(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSocketNotify(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSocketDead(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPopMessageString(WPARAM wParam, LPARAM lParam,
        LRESULT& lResult);
    virtual BOOL OnQueueSentinel(WPARAM wParam, LPARAM lParam);

public:
    friend CXSNotify;
};

#endif // !defined(AFX_XSOBJECT_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
