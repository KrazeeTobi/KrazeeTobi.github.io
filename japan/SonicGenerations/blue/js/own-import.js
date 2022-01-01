var _agent = navigator.userAgent;
if( _agent.indexOf('iPhone') != -1 ||
	_agent.indexOf('iPod') != -1 ||
	_agent.indexOf('iPad') != -1 ||
	_agent.indexOf('Android') != -1) {
		document.write('<script src="js/mobile.js" type="text/javascript"></script>');
} else {
	document.write('<script src="js/pc.js" type="text/javascript"></script>'); 
	document.write('<script src="story/js/slideshow.js" type="text/javascript"></script>'); 
}