//pc
$(function(){
	$(document).ready(function(){
	
		//ムービー
		$("#contents-flash .movie").each(function(){
			var _filepath = $(this).attr("id") + '.mp4';
			var _size = $(this).attr("data").split("-");
			var _width = _size[0];
			var _height = _size[1];
			var _name = "flv_"+$(this).attr("name");

			var h = '<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"  width="'+ _width +'" height="'+ _height +'" id="'+ _name +'"><param name="movie" value="swf/movie.swf" /><param name="quality" value="high" /><param name="wmode" value="transparent" /><param name="allowFullScreen" value="true" /><param name="allowScriptAccess" value="always" /><param name="FlashVars" value="moviePath='+ _filepath +'&amp;outplay=0"><embed src="swf/movie.swf" width="'+ _width +'" height="'+ _height +'" quality="high" wmode="transparent" FlashVars="moviePath='+ _filepath +'" name="'+ _name +'" allowFullScreen ="true" allowScriptAccess="always" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"></embed></object>';
			
			
			$(this).html(h);
		});
		$("#movieChange01 li").click(function(){
			$("#movieChange01 li").removeClass('selected');
			$(this).addClass('selected');
	
			var _filepath = $(this).attr('data') + '.mp4';
			getSWF("flv_message").movieChangeFunction(_filepath,1);
			
			$("#movieChange01_txt").html('<h5>'+$(this).attr('title')+'</h5>');
		});
		
	});
	
});

function getSWF(movieName){ 
	if (navigator.appName.indexOf("Microsoft") != -1){ 
		return window[movieName]; 
	}else{ 
		return document[movieName]; 
	} 
} 
