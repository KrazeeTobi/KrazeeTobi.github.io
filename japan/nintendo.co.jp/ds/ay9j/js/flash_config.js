function isWin () { return (navigator.appVersion.indexOf ("Win") != -1); }
function isIE () { return (navigator.appName.indexOf ("Explorer") != -1); }
function isWinIE () { return (isWin () && isIE ()); }
function getFlashPlayerVersion() { if (navigator.plugins) with (navigator) { var s = "application/x-shockwave-flash"; if (mimeTypes && mimeTypes [s] && mimeTypes [s].enabledPlugin) nFlashPlayerVersion = navigator.plugins ["Shockwave Flash"].description.match (/\d+/); } return parseInt (nFlashPlayerVersion); }; var nFlashPlayerVersion = 0; if (isWinIE ()) document.write ('<scr' + 'ipt type="text/vbscript" language="VBScript"\>\nPrivate i, b\nOn Error Resume Next\nFor i = 8 To 1 Step -1\nb = (IsObject (CreateObject ("ShockwaveFlash.ShockwaveFlash." & i)))\nIf b Then \nnFlashPlayerVersion = i\nExit For\nEnd If\nNext\n</scr' + 'ipt\>');


function setFlash(verNumber,swfImgName,swfImgWidth,swfImgHeight,swfBgColor,pluginImgName,pluginImgAlt,pluginImgWidth,pluginImgHeight,mapMode,mapName){
	if (getFlashPlayerVersion() < verNumber && mapMode == 1) {
		document.write (
		'<img src="' + pluginImgName + '" alt="' + pluginImgAlt + '" width="' + pluginImgWidth + '" height="' + pluginImgHeight + '" usemap="' + mapName + '">'
		);
	} else if (getFlashPlayerVersion() < verNumber && mapMode == 0) {
		document.write (
		'<img src="' + pluginImgName + '" alt="' + pluginImgAlt + '" width="' + pluginImgWidth + '" height="' + pluginImgHeight + '" usemap="' + mapName + '">'
		);
	} else {
		document.write (
		'<P><object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=' + verNumber + ',0,0,0" width="' + swfImgWidth + '" height="' + swfImgHeight + '">' +
		'<param name="movie" value="' + swfImgName + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="opaque">' +
		'<param name="bgcolor" value="' + swfBgColor + '">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="' + swfImgName + '" menu="false" quality="high" wmode="opaque" bgcolor="' + swfBgColor + '" width="' + swfImgWidth + '" height="' + swfImgHeight + '" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="https://www.macromedia.com/go/getflashplayer"><\/embed><\/object></P>'
		);
	}
}

function setFlash1(verNumber,swfImgName,swfImgWidth,swfImgHeight,swfBgColor,mapMode){
	if (getFlashPlayerVersion() < verNumber && mapMode == 1) {
		document.write (
		'<P><IMG SRC="img/top_bgup.gif" ALT="" WIDTH="714" HEIGHT="11"></P>' +
		'<DIV ID="top_main">' +
		'<DIV ID="top_title">' +
		'<H1 class="noflash">�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;</H1>' +
		'<DIV ID="go_adobecom"><IMG SRC="common/spacer.gif" ALT="" WIDTH="355" HEIGHT="40" BORDER="0">' +
		'</DIV>' +
		'</DIV>' +
		'<DIV ID="top_DS">' +
		'<DIV ID="nindslogo"><A HREF="../index.html" TITLE="�j���e���h�[�c�r�̃g�b�v�y�[�W��">�j���e���h�[�c�r�̃g�b�v�y�[�W��</A></DIV>' +
		'<DIV TITLE="�}���I��\�j�b�N�ƃI�����s�b�N���Z�Ƀ`�������W"><H2>�}���I��\�j�b�N�ƃI�����s�b�N���Z�Ƀ`�������W</H2></DIV>' +
		'<DIV ID="gamen"><P>DS�Q�[�����</P></DIV>' +
		'</DIV>' +
		'<!--���j���[�{�^��-->' +
		'<DIV CLASS="clear" ID="menu_top">' +
		'<UL>' +
		'<LI CLASS="btn1"><A HREF="game/index.html" TITLE="�Q�[���Љ�">�c�r�ő���I���ԁI�j���I �Q�[���Љ�</A></LI>' +
		'<LI CLASS="btn2"><A HREF="player/index.html" TITLE="�o��I��̏Љ�">�}���I��\�j�b�N�����������I �o��I��̏Љ�</A></LI>' +
		'<LI CLASS="btn3"><A HREF="compe/index.html" TITLE="���Z�Љ�">�I�����s�b�N���Z�Ƀ`�������W�I ���Z�Љ�</A></LI>' +
		'<LI CLASS="btn4"><A HREF="dream/index.html" TITLE="�h���[�����Z">�A�C�e���⃏�U���g���ċ����I �h���[�����Z</A></LI>' +
		'<LI CLASS="btn5"><A HREF="record/index.html" TITLE="�ΐ큕�L�^">�F�B�Ƌ����I���E�ɒ���I �ΐ큕�L�^</A></LI>' +
		'</UL>' +
		'</DIV>' +
		'<!--���j���[�{�^�������-->' +
		'</DIV>' +
		'<!--���C���w�i�����-->' +
		'<DIV CLASS="clear" ID="top_under">' +
		'<!--�����R���e���c�Q��-->' +
		'<DIV ID="top_u_hidari">' +
		'<DIV ID="twinbtn">' +
		'<P ID="go_book" TITLE="�U���{���"><A HREF="book/index.html">�U���{���</A></P>' +
		'<DIV CLASS="clear"></DIV>' +
		'</DIV>' +
		'<DIV>' +
		'<P ID="tora" TITLE="���E�����L���O �`�������W�K�C�h"><A HREF="guide/index1.html" TARGET="_blank">���E�����L���O �`�������W�K�C�h</A></P>' +
		'</DIV>' +
		'</DIV>' +
		'<!--�����R���e���c�Q�������-->' +
		'<!--�����R���e���c�Q�E-->' +
		'<DIV ID="top_u_migi">' +
		'<DIV ID="info"TITLE="Product Outline �������F2008�N1��17�� ��]�������i�F4,800�~ �W�������F�X�|�[�c �v���C�l���F1�`4�l">' +
		'<P ID="prod">Product Outline</P>' +
		'<UL>' +
		'<LI>�������F2008�N1��17��</LI>' +
		'<LI>��]�������i�F4,800�~</LI>' +
		'<LI>�W�������F�X�|�[�c</LI>' +
		'<LI>�v���C�l���F1�`4�l</LI>' +
		'</UL>' +
		'<DIV ID="wifi"><P><IMG SRC="common/spacer.gif" ALT="wifi" WIDTH="35" HEIGHT="35" BORDER="0" USEMAP="#Map"></P></DIV>' +
		'</DIV>' +
		'<DIV ID="go_wii">' +
		'<H4><A HREF="http://www.nintendo.co.jp/wii/rwsj/index.html" TITLE="���w�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;�xWii�ł͂�����">���w�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;�xWii�ł͂�����</A></H4>' +
		'</DIV>' +
		'</DIV><!--�����R���e���c�Q�E�����-->' +
		'</DIV>'
		);
	} else if (getFlashPlayerVersion() < verNumber && mapMode == 0) {
		document.write (
		'<P><IMG SRC="img/top_bgup.gif" ALT="" WIDTH="714" HEIGHT="11"></P>' +
		'<DIV ID="top_main">' +
		'<DIV ID="top_title">' +
		'<H1 class="noflash">�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;</H1>' +
		'<DIV ID="go_adobecom"><IMG SRC="common/spacer.gif" ALT="" WIDTH="355" HEIGHT="40" BORDER="0">' +
		'</DIV>' +
		'</DIV>' +
		'<DIV ID="top_DS">' +
		'<DIV ID="nindslogo"><A HREF="../index.html" TITLE="�j���e���h�[�c�r�̃g�b�v�y�[�W��">�j���e���h�[�c�r�̃g�b�v�y�[�W��</A></DIV>' +
		'<DIV TITLE="�}���I��\�j�b�N�ƃI�����s�b�N���Z�Ƀ`�������W"><H2>�}���I��\�j�b�N�ƃI�����s�b�N���Z�Ƀ`�������W</H2></DIV>' +
		'<DIV ID="gamen"><P>DS�Q�[�����</P></DIV>' +
		'</DIV>' +
		'<!--���j���[�{�^��-->' +
		'<DIV CLASS="clear" ID="menu_top">' +
		'<UL>' +
		'<LI CLASS="btn1"><A HREF="game/index.html" TITLE="�Q�[���Љ�">�c�r�ő���I���ԁI�j���I �Q�[���Љ�</A></LI>' +
		'<LI CLASS="btn2"><A HREF="player/index.html" TITLE="�o��I��̏Љ�">�}���I��\�j�b�N�����������I �o��I��̏Љ�</A></LI>' +
		'<LI CLASS="btn3"><A HREF="compe/index.html" TITLE="���Z�Љ�">�I�����s�b�N���Z�Ƀ`�������W�I ���Z�Љ�</A></LI>' +
		'<LI CLASS="btn4"><A HREF="dream/index.html" TITLE="�h���[�����Z">�A�C�e���⃏�U���g���ċ����I �h���[�����Z</A></LI>' +
		'<LI CLASS="btn5"><A HREF="record/index.html" TITLE="�ΐ큕�L�^">�F�B�Ƌ����I���E�ɒ���I �ΐ큕�L�^</A></LI>' +
		'</UL>' +
		'</DIV>' +
		'<!--���j���[�{�^�������-->' +
		'</DIV>' +
		'<!--���C���w�i�����-->' +
		'<DIV CLASS="clear" ID="top_under">' +
		'<!--�����R���e���c�Q��-->' +
		'<DIV ID="top_u_hidari">' +
		'<DIV ID="twinbtn">' +
		'<P ID="go_book" TITLE="�U���{���"><A HREF="book/index.html">�U���{���</A></P>' +
		'<DIV CLASS="clear"></DIV>' +
		'</DIV>' +
		'<DIV>' +
		'<P ID="tora" TITLE="���E�����L���O �`�������W�K�C�h"><A HREF="guide/index1.html" TARGET="_blank">���E�����L���O �`�������W�K�C�h</A></P>' +
		'</DIV>' +
		'</DIV>' +
		'<!--�����R���e���c�Q�������-->' +
		'<!--�����R���e���c�Q�E-->' +
		'<DIV ID="top_u_migi">' +
		'<DIV ID="info"TITLE="Product Outline �������F2008�N1��17�� ��]�������i�F4,800�~ �W�������F�X�|�[�c �v���C�l���F1�`4�l">' +
		'<P ID="prod">Product Outline</P>' +
		'<UL>' +
		'<LI>�������F2008�N1��17��</LI>' +
		'<LI>��]�������i�F4,800�~</LI>' +
		'<LI>�W�������F�X�|�[�c</LI>' +
		'<LI>�v���C�l���F1�`4�l</LI>' +
		'</UL>' +
		'<DIV ID="wifi"><P><IMG SRC="common/spacer.gif" ALT="wifi" WIDTH="35" HEIGHT="35" BORDER="0" USEMAP="#Map"></P></DIV>' +
		'</DIV>' +
		'<DIV ID="go_wii">' +
		'<H4><A HREF="http://www.nintendo.co.jp/wii/rwsj/index.html" TITLE="���w�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;�xWii�ł͂�����">���w�}���I&amp;�\�j�b�N AT �k���I�����s�b�N&trade;�xWii�ł͂�����</A></H4>' +
		'</DIV>' +
		'</DIV><!--�����R���e���c�Q�E�����-->' +
		'</DIV>'
		);
	} else {
		document.write (
		'<P><object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=' + verNumber + ',0,0,0" width="' + swfImgWidth + '" height="' + swfImgHeight + '">' +
		'<param name="movie" value="' + swfImgName + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="opaque">' +
		'<param name="bgcolor" value="' + swfBgColor + '">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="' + swfImgName + '" menu="false" quality="high" wmode="opaque" bgcolor="' + swfBgColor + '" width="' + swfImgWidth + '" height="' + swfImgHeight + '" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="https://www.macromedia.com/go/getflashplayer"><\/embed><\/object></P>'
		);
	}
}