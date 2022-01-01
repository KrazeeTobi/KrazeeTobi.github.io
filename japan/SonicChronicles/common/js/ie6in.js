// JavaScript Document
$(document).ready(function() {
	//ブラウザ確認
	myAgent = navigator.userAgent;
	//IEかチェック
	if(myAgent.match(/MSIE (\d|.\d+)/)){
		//ver6かチェック
		if(RegExp.$1 == 6){
			$("#common-header ul").before('<div id="ie6header"></div>');
		}
	}
});