//iphone
$(function(){
	$(document).ready(function(){
		
		//ムービー
		$("#contents-flash .movie").each(function(){
			var _filepath = 'swf/' + $(this).attr("id") + '.mp4';
			var _size = $(this).attr("data").split("-");
			var _width = _size[0];
			var _height = _size[1];
			
			var h = '<object width="'+ _width +'" height="'+ _height +'" data="'+ _filepath +'" type="video/mp4"><param name="src" value="'+ _filepath +'" /><param name="url" value="'+ _filepath +'" valuetype="ref" type="video/mp4" /><param name="autostart" value="0" /><param name="showcontrols" value="1" /></object>';
			$(this).html(h);
		});
		$('body').css('background','#fff url(../common/css/common-tag/iphone-body.gif) no-repeat center 60px scroll');
		
		$("#movieChange01 li").click(function(){
			$("#movieChange01 li").removeClass('selected');
			$(this).addClass('selected');
	
			var _size =$("#movie_02").attr("data").split("-");
			var _width = _size[0];
			var _height = _size[1];
			var _filepath = 'swf/' + $(this).attr('data') + '.mp4';
			
			var h = '<object width="'+ _width +'" height="'+ _height +'" data="'+ _filepath +'" type="video/mp4"><param name="src" value="'+ _filepath +'" /><param name="url" value="'+ _filepath +'" valuetype="ref" type="video/mp4" /><param name="autostart" value="1" /><param name="showcontrols" value="1" /></object>';
			$("#movie_02").html(h);
			
			$("#movieChange01_txt").html('<h5>'+$(this).attr('title')+'</h5>');
		});
		
	});
});