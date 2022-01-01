$(document).ready(function(){
	/*更新情報*/
	$("#common-infomation").load("infomation.txt");
	$("#common-header").next().css("display", "none");
	$("#common-infomation").wrap('<div class="divWrap"></div>');
});

var _agent = navigator.userAgent;
if( _agent.indexOf('iPhone') != -1 ||
		_agent.indexOf('iPod') != -1 ||
		_agent.indexOf('iPad') != -1) {
	document.write('<script src="js/iphone.js" type="text/javascript"></script>');

} else {
		document.write('<script src="js/pc.js" type="text/javascript"></script>'); 
	
}