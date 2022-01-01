//popup window
function popWin(popUrl,popName,popWidth,popHeight,popBar,popLoca,popMenu,popStatus) {
	if(!popName) popName = "popWindow";
	if(!popBar) popBar = "yes";
	if(!popLoca) popLoca = "yes";
	if(!popMenu) popMenu = "yes";
	if(!popStatus) popStatus = "yes";
	window.open(popUrl,popName,"width="+popWidth+",height="+popHeight+",location="+popLoca+",menubar="+popMenu+",personalbar=no,directories=no,scrollbars="+popBar+",status="+popStatus+",toolbar=no,copyhistory=no,resizable=yes");
}
