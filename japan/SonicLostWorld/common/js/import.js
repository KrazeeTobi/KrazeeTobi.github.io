(function() {
	var jsfiles = [
		"jquery-1.7.1.min.js",
		"jquery.easing.1.3.js",
		"jquery.carouFredSel-6.2.1-packed.js",
		"jquery.colorbox-min.js",
		"common.js"
	];
	function lastof(es)    { return es[es.length - 1]; }
	function dirname(path) { return path.substring(0, path.lastIndexOf('/')); }
	var prefix = dirname(lastof(document.getElementsByTagName('script')).src);

	for(var i = 0; i < jsfiles.length; i++) {
		document.write('<script type="text/javascript" src="' + prefix + '/' + jsfiles[i] + '"></script>');
	}
}).call(this);