(function() {
	var jsfiles = [
		"jquery-2.1.4.min.js",
		"jquery.easing.1.3.js",
		"jquery.flexisel.js",
		"jquery.bxslider.min.js",
		/*"jquery.colorbox-min.js",*/
		"jquery.swipebox.min.js",
		"swiper.min.js",
		"scripts.js"
	];
	function lastof(es)    { return es[es.length - 1]; }
	function dirname(path) { return path.substring(0, path.lastIndexOf('/')); }
	var prefix = dirname(lastof(document.getElementsByTagName('script')).src);

	for(var i = 0; i < jsfiles.length; i++) {
		document.write('<script type="text/javascript" src="' + prefix + '/' + jsfiles[i] + '"></script>');
	}
}).call(this);