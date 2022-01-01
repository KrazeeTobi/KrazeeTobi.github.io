var _agent = navigator.userAgent;
document.write('<script src="js/common.js" type="text/javascript"></script>');


if( _agent.indexOf('iPhone') != -1 ||
    _agent.indexOf('iPod') != -1 ||
    _agent.indexOf('iPad') != -1) {

	document.write('<script src="js/iphone.js" type="text/javascript"></script>');
	document.write('<link rel="stylesheet" href="common/css/iphone-import.css" type="text/css" media="all" />');
} else {
	
	document.write('<script src="js/pc.js" type="text/javascript"></script>'); 
	document.write('<link rel="stylesheet" href="common/css/common-import.css" type="text/css" media="all" />');
}
