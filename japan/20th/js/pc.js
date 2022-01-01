

$(function(){
	
	//Flash 貼り付け
	var flashvars = {
	};
	var params = {
		scale:'noScale',
		salign:'t',
		menu:'false',
		allowScriptAccess: "always",
		wmode:	"transparent",
		bgcolor: "#FFFFFF"
	};
	var attributes = {};
	swfobject.embedSWF("swf/top.swf", "contents-flash", "100%", "500", "10", "expressInstall.swf", flashvars, params, attributes);
		
});