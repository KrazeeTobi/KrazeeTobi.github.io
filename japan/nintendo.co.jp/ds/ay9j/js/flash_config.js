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
		'<H1 class="noflash">マリオ&amp;ソニック AT 北京オリンピック&trade;</H1>' +
		'<DIV ID="go_adobecom"><IMG SRC="common/spacer.gif" ALT="" WIDTH="355" HEIGHT="40" BORDER="0">' +
		'</DIV>' +
		'</DIV>' +
		'<DIV ID="top_DS">' +
		'<DIV ID="nindslogo"><A HREF="../index.html" TITLE="ニンテンドーＤＳのトップページへ">ニンテンドーＤＳのトップページへ</A></DIV>' +
		'<DIV TITLE="マリオやソニックとオリンピック競技にチャレンジ"><H2>マリオやソニックとオリンピック競技にチャレンジ</H2></DIV>' +
		'<DIV ID="gamen"><P>DSゲーム画面</P></DIV>' +
		'</DIV>' +
		'<!--メニューボタン-->' +
		'<DIV CLASS="clear" ID="menu_top">' +
		'<UL>' +
		'<LI CLASS="btn1"><A HREF="game/index.html" TITLE="ゲーム紹介">ＤＳで走る！跳ぶ！泳ぐ！ ゲーム紹介</A></LI>' +
		'<LI CLASS="btn2"><A HREF="player/index.html" TITLE="出場選手の紹介">マリオやソニックたちが競演！ 出場選手の紹介</A></LI>' +
		'<LI CLASS="btn3"><A HREF="compe/index.html" TITLE="競技紹介">オリンピック競技にチャレンジ！ 競技紹介</A></LI>' +
		'<LI CLASS="btn4"><A HREF="dream/index.html" TITLE="ドリーム競技">アイテムやワザを使って競う！ ドリーム競技</A></LI>' +
		'<LI CLASS="btn5"><A HREF="record/index.html" TITLE="対戦＆記録">友達と競う！世界に挑戦！ 対戦＆記録</A></LI>' +
		'</UL>' +
		'</DIV>' +
		'<!--メニューボタンおわり-->' +
		'</DIV>' +
		'<!--メイン背景おわり-->' +
		'<DIV CLASS="clear" ID="top_under">' +
		'<!--下部コンテンツ＿左-->' +
		'<DIV ID="top_u_hidari">' +
		'<DIV ID="twinbtn">' +
		'<P ID="go_book" TITLE="攻略本情報"><A HREF="book/index.html">攻略本情報</A></P>' +
		'<DIV CLASS="clear"></DIV>' +
		'</DIV>' +
		'<DIV>' +
		'<P ID="tora" TITLE="世界ランキング チャレンジガイド"><A HREF="guide/index1.html" TARGET="_blank">世界ランキング チャレンジガイド</A></P>' +
		'</DIV>' +
		'</DIV>' +
		'<!--下部コンテンツ＿左おわり-->' +
		'<!--下部コンテンツ＿右-->' +
		'<DIV ID="top_u_migi">' +
		'<DIV ID="info"TITLE="Product Outline 発売日：2008年1月17日 希望小売価格：4,800円 ジャンル：スポーツ プレイ人数：1～4人">' +
		'<P ID="prod">Product Outline</P>' +
		'<UL>' +
		'<LI>発売日：2008年1月17日</LI>' +
		'<LI>希望小売価格：4,800円</LI>' +
		'<LI>ジャンル：スポーツ</LI>' +
		'<LI>プレイ人数：1～4人</LI>' +
		'</UL>' +
		'<DIV ID="wifi"><P><IMG SRC="common/spacer.gif" ALT="wifi" WIDTH="35" HEIGHT="35" BORDER="0" USEMAP="#Map"></P></DIV>' +
		'</DIV>' +
		'<DIV ID="go_wii">' +
		'<H4><A HREF="http://www.nintendo.co.jp/wii/rwsj/index.html" TITLE="→『マリオ&amp;ソニック AT 北京オリンピック&trade;』Wii版はこちら">→『マリオ&amp;ソニック AT 北京オリンピック&trade;』Wii版はこちら</A></H4>' +
		'</DIV>' +
		'</DIV><!--下部コンテンツ＿右おわり-->' +
		'</DIV>'
		);
	} else if (getFlashPlayerVersion() < verNumber && mapMode == 0) {
		document.write (
		'<P><IMG SRC="img/top_bgup.gif" ALT="" WIDTH="714" HEIGHT="11"></P>' +
		'<DIV ID="top_main">' +
		'<DIV ID="top_title">' +
		'<H1 class="noflash">マリオ&amp;ソニック AT 北京オリンピック&trade;</H1>' +
		'<DIV ID="go_adobecom"><IMG SRC="common/spacer.gif" ALT="" WIDTH="355" HEIGHT="40" BORDER="0">' +
		'</DIV>' +
		'</DIV>' +
		'<DIV ID="top_DS">' +
		'<DIV ID="nindslogo"><A HREF="../index.html" TITLE="ニンテンドーＤＳのトップページへ">ニンテンドーＤＳのトップページへ</A></DIV>' +
		'<DIV TITLE="マリオやソニックとオリンピック競技にチャレンジ"><H2>マリオやソニックとオリンピック競技にチャレンジ</H2></DIV>' +
		'<DIV ID="gamen"><P>DSゲーム画面</P></DIV>' +
		'</DIV>' +
		'<!--メニューボタン-->' +
		'<DIV CLASS="clear" ID="menu_top">' +
		'<UL>' +
		'<LI CLASS="btn1"><A HREF="game/index.html" TITLE="ゲーム紹介">ＤＳで走る！跳ぶ！泳ぐ！ ゲーム紹介</A></LI>' +
		'<LI CLASS="btn2"><A HREF="player/index.html" TITLE="出場選手の紹介">マリオやソニックたちが競演！ 出場選手の紹介</A></LI>' +
		'<LI CLASS="btn3"><A HREF="compe/index.html" TITLE="競技紹介">オリンピック競技にチャレンジ！ 競技紹介</A></LI>' +
		'<LI CLASS="btn4"><A HREF="dream/index.html" TITLE="ドリーム競技">アイテムやワザを使って競う！ ドリーム競技</A></LI>' +
		'<LI CLASS="btn5"><A HREF="record/index.html" TITLE="対戦＆記録">友達と競う！世界に挑戦！ 対戦＆記録</A></LI>' +
		'</UL>' +
		'</DIV>' +
		'<!--メニューボタンおわり-->' +
		'</DIV>' +
		'<!--メイン背景おわり-->' +
		'<DIV CLASS="clear" ID="top_under">' +
		'<!--下部コンテンツ＿左-->' +
		'<DIV ID="top_u_hidari">' +
		'<DIV ID="twinbtn">' +
		'<P ID="go_book" TITLE="攻略本情報"><A HREF="book/index.html">攻略本情報</A></P>' +
		'<DIV CLASS="clear"></DIV>' +
		'</DIV>' +
		'<DIV>' +
		'<P ID="tora" TITLE="世界ランキング チャレンジガイド"><A HREF="guide/index1.html" TARGET="_blank">世界ランキング チャレンジガイド</A></P>' +
		'</DIV>' +
		'</DIV>' +
		'<!--下部コンテンツ＿左おわり-->' +
		'<!--下部コンテンツ＿右-->' +
		'<DIV ID="top_u_migi">' +
		'<DIV ID="info"TITLE="Product Outline 発売日：2008年1月17日 希望小売価格：4,800円 ジャンル：スポーツ プレイ人数：1～4人">' +
		'<P ID="prod">Product Outline</P>' +
		'<UL>' +
		'<LI>発売日：2008年1月17日</LI>' +
		'<LI>希望小売価格：4,800円</LI>' +
		'<LI>ジャンル：スポーツ</LI>' +
		'<LI>プレイ人数：1～4人</LI>' +
		'</UL>' +
		'<DIV ID="wifi"><P><IMG SRC="common/spacer.gif" ALT="wifi" WIDTH="35" HEIGHT="35" BORDER="0" USEMAP="#Map"></P></DIV>' +
		'</DIV>' +
		'<DIV ID="go_wii">' +
		'<H4><A HREF="http://www.nintendo.co.jp/wii/rwsj/index.html" TITLE="→『マリオ&amp;ソニック AT 北京オリンピック&trade;』Wii版はこちら">→『マリオ&amp;ソニック AT 北京オリンピック&trade;』Wii版はこちら</A></H4>' +
		'</DIV>' +
		'</DIV><!--下部コンテンツ＿右おわり-->' +
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