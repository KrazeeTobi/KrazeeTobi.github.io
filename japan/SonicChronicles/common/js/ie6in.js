// JavaScript Document
$(document).ready(function() {
	//�u���E�U�m�F
	myAgent = navigator.userAgent;
	//IE���`�F�b�N
	if(myAgent.match(/MSIE (\d|.\d+)/)){
		//ver6���`�F�b�N
		if(RegExp.$1 == 6){
			$("#common-header ul").before('<div id="ie6header"></div>');
		}
	}
});