//index

function runflash(){
	mynum = Math.random();
if ( plugin ) {
	document.write('<OBJECT classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"');
	document.write('  codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" ');
	document.write(' ID="myflash" WIDTH=730 HEIGHT=485>');
	document.write(' <PARAM NAME=movie VALUE="swf/movie.swf"> <PARAM NAME=quality VALUE=high> <PARAM NAME="wmode" VALUE="transparent">  '); 
    document.write(' <PARAM name="menu" value="false">  '); 
	document.write(' <EMBED src="swf/movie.swf" quality="high" wmode="transparent" menu="false"');
	document.write(' swLiveConnect=FALSE WIDTH=730 HEIGHT=485');
	document.write(' TYPE="application/x-shockwave-flash" PLUGINSPAGE="http://www.adobe.com/shockwave/download/index.cgi?Lang=Japanese&P1_Prod_Version=ShockwaveFlash">');
	document.write(' </EMBED>');
	document.write(' </OBJECT>');
} else {
	document.write('<IMG SRC="img/index.jpg" WIDTH="730" HEIGHT="485" ALT="‘Îí•‹L˜^" BORDER="0" usemap="#Map">');
} 
}

//Flash Vesion
var plugin = (navigator.mimeTypes && navigator.mimeTypes["application/x-shockwave-flash"]) ? navigator.mimeTypes["application/x-shockwave-flash"].enabledPlugin : 0;
if ( plugin ) {
	plugin = parseInt(plugin.description.match(/\d+\.\d+/)) >= 7;
}


else if (navigator.userAgent && navigator.userAgent.indexOf("MSIE")>=0 
   && (navigator.userAgent.indexOf("Windows 95")>=0 || navigator.userAgent.indexOf("Windows 98")>=0 || navigator.userAgent.indexOf("Windows NT")>=0)) {
	document.write('<SCRIPT LANGUAGE=VBScript\> \n');
    document.write('on error resume next \n');
    document.write('plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.7")))\n');
    document.write('</SCRIPT\> \n');
}
