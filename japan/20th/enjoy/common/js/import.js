var _agent = navigator.userAgent;


if( _agent.indexOf('iPhone') != -1 ||
    _agent.indexOf('iPod') != -1 ||
    _agent.indexOf('iPad') != -1) {

	document.write('<script src="common/js/iphone.js" type="text/javascript"></script>');
} else {
	
	document.write('<script src="common/js/pc.js" type="text/javascript"></script>'); 
}
document.write('<script src="common/js/common.js" type="text/javascript"></script>');
