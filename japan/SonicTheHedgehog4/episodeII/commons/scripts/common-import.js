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
    //�����ݒ�
    var flashplayer_ver = 0;
    //IE�ȊO�̏ꍇ
    if(navigator.plugins && navigator.mimeTypes['application/x-shockwave-flash']){
        var plugin = navigator.mimeTypes["application/x-shockwave-flash"].enabledPlugin;
        //Flash Player���C���X�g�[������Ă���ꍇ
        if(plugin){flashplayer_ver = parseInt(plugin.description.match(/\d+\.\d+/));}
    }
    //IE�̏ꍇ�A��������Flash Player���C���X�g�[������Ă��Ȃ��ꍇ
    else{
        //IE��Flash Player���C���X�g�[������Ă���ꍇ
        try{
            var flashOCX = new ActiveXObject("ShockwaveFlash.ShockwaveFlash").GetVariable("$version").match(/([0-9]+)/);
            if(flashOCX){flashplayer_ver = parseInt(flashOCX[0]);}
        }catch(e){}
    }
    //Flash Player���C���X�g�[������Ă��Ȃ��A�������̓o�[�W������6�ȉ��̏ꍇ
    if(flashplayer_ver <= 6){flashplayer_ver = 0;}
    return flashplayer_ver;
}