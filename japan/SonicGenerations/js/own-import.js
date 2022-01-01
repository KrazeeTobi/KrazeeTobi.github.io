var _agent = navigator.userAgent;
if( _agent.indexOf('iPhone') != -1 ||
	_agent.indexOf('iPod') != -1 ||
	_agent.indexOf('iPad') != -1 ||
	_agent.indexOf('Android') != -1) {
		setTimeout("link()", 0);
		function link(){
			location.href='mobile.html';
		}
}else{
	document.write('<script src="js/pc.js" type="text/javascript"></script>'); 
	document.write('<script src="js/rsegajp.js" type="text/javascript"></script>'); 
}