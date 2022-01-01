/**
 * 
 * Progression
 * 
 * @author Copyright (c) 2007-2008 taka:nium, supported by Spark project.
 * @version 3.0.0
 * @see http://progression.jp/
 * @see http://progression.libspark.org/
 * 
 * Developed by taka:nium
 * @see http://nium.jp/
 * 
 * Hosted by Spark project
 * @see http://www.libspark.org/
 * 
 * Progression is (c) 2007-2008 taka:nium and is released under the MIT License:
 * http://www.opensource.org/licenses/mit-license.php
 * 
 */

var Progression = function( version ) {
	this.version = version;
	( ( document.getElementById( "enableJavaScript" ) || {} ).style || {} ).display = "none";
};
Progression.prototype = {
	version:null,
	init:function() {
		var o = this;
		var w = window;
		var d = document;
		var s = ( ( d.getElementById( "attention" ) || {} ).style || {} );
		var t = 0;
		
		s.visibility = "hidden";
		d.write( ''
			+ '<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" width="1" height="1" id="external_version">'
			+ '<param name="allowScriptAccess" value="samedomain" />'
			+ '<param name="movie" value="contents/objects/version.swf" />'
			+ '<embed src="contents/objects/version.swf" name="external_version" width="1" height="1" allowScriptAccess="samedomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />'
			+ '</object>' );
		
		var check = function() {
			if ( !w.__progressionFlashPlayerVersion && t++ < 50 ) { return false; }
			
			clearInterval( timer );
			s.visibility = "visible";
			
			if ( w.__progressionFlashPlayerVersion ) {
				var flash_version = w.__progressionFlashPlayerVersion;
				flash_version = flash_version.split( " " )[1].split( "," ).join( "." );
				w.__progressionFlashPlayerVersion = undefined;
				
				if ( !o.compare( flash_version ) ) { return false; }
				
				o.onLoad();
				return true;
			}
			return false;
		};
		
		if ( !check() ) { var timer = setInterval( check, 100 ); }
	},
	compare:function( version ) {
		var ver1 = version.split( "." );
		var ver2 = this.version.split( "." );
		
		var d1 = parseInt( ver1[0] || "0" ) - parseInt( ver2[0] || "0" );
		var d2 = parseInt( ver1[1] || "0" ) - parseInt( ver2[1] || "0" );
		var d3 = parseInt( ver1[2] || "0" ) - parseInt( ver2[2] || "0" );
		var d4 = parseInt( ver1[3] || "0" ) - parseInt( ver2[3] || "0" );
		
		if ( d1 != 0 ) { return d1 > 0; }
		if ( d2 != 0 ) { return d2 > 0; }
		if ( d3 != 0 ) { return d3 > 0; }
		if ( d4 != 0 ) { return d4 > 0; }
		
		return true;
	},
	onLoad:function() {}
};




