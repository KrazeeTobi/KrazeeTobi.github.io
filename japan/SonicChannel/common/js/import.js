(function() {
	//"use strict";
	var jsfiles = [
		"modernizr.js",
		"swiper.min.js",
		"jquery-2.1.4.min.js",
		"jquery.swipebox.min.js",
		"jquery.tubular.1.0.js",
		"velocity.min.js",
		"snsClick.js",
		"common-navigation.js",	
		"init.js"

		];
	function lastof(es)    { return es[es.length - 1]; }
	function dirname(path) { return path.substring(0, path.lastIndexOf('/')); }
	var prefix = dirname(lastof(document.getElementsByTagName('script')).src);

	for(var i = 0; i< jsfiles.length; i++) {
		document.write('<script type="text/javascript" src="' + prefix + '/' + jsfiles[i] + '"></script>');
	}
}).call(this);
