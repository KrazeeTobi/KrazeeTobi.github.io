$(function(){
	var backTop = $('.contensSubstance div.divWrap').backTop();
	
	var _agent = navigator.userAgent;
	if( _agent.indexOf('iPhone') != -1 || _agent.indexOf('iPod') != -1 || _agent.indexOf('iPad') != -1) {
		$('body').css('background','#fff url(../../common/css/common-tag/iphone-body.gif) no-repeat center 60px scroll');
	
	}
});
