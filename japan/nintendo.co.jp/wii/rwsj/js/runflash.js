//User Agent
ua = navigator.userAgent;
if(ua.indexOf("Nintendo Wii")!=-1){
	var flashMode = "wii";
}
else{
	var flashMode = "pc";
}


//main flash
function runFlash(){
	mynum = Math.random();
if ( plugin ) {
		document.write (
		'<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="730" height="485">' +
		'<param name="movie" value="swf/movie.swf?locationMode=' + flashMode + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="transparent">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="swf/movie.swf?locationMode=' + flashMode + '" menu="false" quality="high" wmode="transparent" width="730" height="485" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/shockwave/download/index.cgi?Lang=Japanese&P1_Prod_Version=ShockwaveFlash"><\/embed><\/object><br>'
		);
	}else {
	document.write('<IMG SRC="img/index.jpg" WIDTH="730" HEIGHT="485" ALT="マリオ＆ソニックAT北京オリンピック" BORDER="0" usemap="#Map">');
} 
}

//opening movie
function runMovie(){
	mynum = Math.random();
if ( plugin ) {
		document.write (
		'<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="730" height="485">' +
		'<param name="movie" value="swf/wmovie_1.swf?locationMode=' + flashMode + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="transparent">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="swf/wmovie_1.swf?locationMode=' + flashMode + '" menu="false" quality="high" wmode="transparent" width="730" height="485" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/shockwave/download/index.cgi?Lang=Japanese&P1_Prod_Version=ShockwaveFlash"><\/embed><\/object><br>'
		);
}else {
	document.write('<IMG SRC="img/index_01.jpg" WIDTH="730" HEIGHT="485" ALT="オープニングムービー" BORDER="0" usemap="#Map">');
} 
}
//game movie
function runMovie2(){
	mynum = Math.random();
if ( plugin ) {
		document.write (
		'<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="730" height="485">' +
		'<param name="movie" value="swf/wmovie_2.swf?locationMode=' + flashMode + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="transparent">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="swf/wmovie_2.swf?locationMode=' + flashMode + '" menu="false" quality="high" wmode="transparent" width="730" height="485" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/shockwave/download/index.cgi?Lang=Japanese&P1_Prod_Version=ShockwaveFlash"><\/embed><\/object><br>'
		);
}else {
	document.write('<IMG SRC="img/index_01.jpg" WIDTH="730" HEIGHT="485" ALT="ゲームムービー" BORDER="0" usemap="#Map">');
} 
}
//screenshot
function runMovie3(){
	mynum = Math.random();
if ( plugin ) {
		document.write (
		'<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="https://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="730" height="485">' +
		'<param name="movie" value="swf/wscreenshot.swf?locationMode=' + flashMode + '">' +
		'<param name="menu" value="false">' +
		'<param name="quality" value="high">' +
		'<param name="wmode" value="transparent">' +
		'<param name="allowScriptAccess" value="sameDomain">' +
		'<embed src="swf/wscreenshot.swf?locationMode=' + flashMode + '" menu="false" quality="high" wmode="transparent" width="730" height="485" swLiveConnect="true" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/shockwave/download/index.cgi?Lang=Japanese&P1_Prod_Version=ShockwaveFlash"><\/embed><\/object><br>'
		);
}else {
	document.write('<IMG SRC="screenshot/img/01.jpg" WIDTH="730" HEIGHT="414" ALT="スクリーンショット" BORDER="0" usemap="#Map1"><IMG SRC="screenshot/img/navi.jpg" WIDTH="730" HEIGHT="71" ALT="スクリーンショット" BORDER="0" usemap="#Map2">');
} 
}

//Flash Vesion
var plugin = (navigator.mimeTypes && navigator.mimeTypes["application/x-shockwave-flash"]) ? navigator.mimeTypes["application/x-shockwave-flash"].enabledPlugin : 0;
if ( plugin ) {
	plugin = parseInt(plugin.description.match(/\d+\.\d+/)) >= 7;
} else if (navigator.userAgent && navigator.userAgent.indexOf("MSIE")>=0 
   && (navigator.userAgent.indexOf("Windows 95")>=0 || navigator.userAgent.indexOf("Windows 98")>=0 || navigator.userAgent.indexOf("Windows NT")>=0)) {
	document.write('<SCRIPT LANGUAGE=VBScript\> \n');
    document.write('on error resume next \n');
    document.write('plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.7")))\n');
    document.write('</SCRIPT\> \n');
}
