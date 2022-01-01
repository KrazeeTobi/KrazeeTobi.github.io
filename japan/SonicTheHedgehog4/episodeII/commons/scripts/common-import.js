var _agent = navigator.userAgent;
if( _agent.indexOf('iPhone') != -1 ||
	_agent.indexOf('iPod') != -1 ||
	_agent.indexOf('iPad') != -1 ||
	_agent.indexOf('Android') != -1 ) {
		setTimeout("link()", 0);
		function link(){
			location.href='mobile/index.html';
		}
}else{
	document.write('<script src="commons/scripts/swfobject/swfobject.js" type="text/javascript"></script>');
	document.write('<script src="commons/scripts/swfaddress/swfaddress.js"></script>');
    document.write('<script src="commons/scripts/progression.js" type="text/javascript"></script>');
}


function FlashPlayerVer(){
    //初期設定
    var flashplayer_ver = 0;
    //IE以外の場合
    if(navigator.plugins && navigator.mimeTypes['application/x-shockwave-flash']){
        var plugin = navigator.mimeTypes["application/x-shockwave-flash"].enabledPlugin;
        //Flash Playerがインストールされている場合
        if(plugin){flashplayer_ver = parseInt(plugin.description.match(/\d+\.\d+/));}
    }
    //IEの場合、もしくはFlash Playerがインストールされていない場合
    else{
        //IEでFlash Playerがインストールされている場合
        try{
            var flashOCX = new ActiveXObject("ShockwaveFlash.ShockwaveFlash").GetVariable("$version").match(/([0-9]+)/);
            if(flashOCX){flashplayer_ver = parseInt(flashOCX[0]);}
        }catch(e){}
    }
    //Flash Playerがインストールされていない、もしくはバージョンが6以下の場合
    if(flashplayer_ver <= 6){flashplayer_ver = 0;}
    return flashplayer_ver;
}