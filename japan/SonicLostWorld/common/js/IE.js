(function() {
	document.write('<link href="common/css/IE.css" rel="stylesheet" type="text/css" />');
	document.write('<script src="http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE9.js"></script>');
}).call(this);

function contentsStart(){
	//スライドウィンドウ処理
	$("a.contentsLink").on("click", function() {
		var timing = ($($(this).attr('href')).position().top + $("#impress").position().top)/4;
		if(timing <= 0) timing *= -1;
		timing += 700;
		$("#contents-main").animate({
			scrollTop: $($(this).attr('href')).position().top
		}, timing, 'easeInOutQuart');
		return false;
	});
	resizeFunc();
	
	
	//IE個別対応
	var ua = window.navigator.userAgent.toLowerCase();
	var ver = window.navigator.appVersion.toLowerCase();
	if (ua.indexOf("msie") != -1){
		//IE7/8
		if (ver.indexOf("msie 8.") != -1 || ver.indexOf("msie 7.") != -1 ){
			$('#loading').css({'display':'none'});
		}
		//IE8
		/*
		if (ver.indexOf("msie 8.") != -1){
		}
		*/
	}
}