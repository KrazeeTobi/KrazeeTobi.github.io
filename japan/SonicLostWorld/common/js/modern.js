(function() {
	var jsfiles = [
		"jmpress.custom.js"
	];
	function lastof(es)    { return es[es.length - 1]; }
	function dirname(path) { return path.substring(0, path.lastIndexOf('/')); }
	var prefix = dirname(lastof(document.getElementsByTagName('script')).src);

	for(var i = 0; i < jsfiles.length; i++) {
		document.write('<script type="text/javascript" src="' + prefix + '/' + jsfiles[i] + '"><\/script>');
	}
	
}).call(this);

function contentsStart(){
	//jmpress開始
	$('#impress').jmpress();
	resizeFunc();
	$('body').css({'overflow-y':'scroll'});

	//firefoxだけ出てこないスクロールバーを
	//透過度を変えると出てくるので設定
	if(navigator.userAgent.indexOf("Firefox") != -1){
		$('#contents-main').css({'opacity':'0.99999'});
		$('#contents-main').css({'opacity':'1'});
	}
}
