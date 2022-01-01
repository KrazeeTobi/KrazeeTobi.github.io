$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/

	
/*------------------------------------------------------------
イベント
------------------------------------------------------------*/
	var dy=0;

	//スクロール
	$(window).scroll(function(){
		dy = $(this).scrollTop();
		var _navy = $("#contents-nav ul").offset().top;
		 $(".characterObject").each(function(){
			var _id = $(this).context.id;
			var _num = $(this).context.id.slice(-1);
			var _y =  $(this).offset().top;
 			var _height =  $(this).height();
			
			if(_y <= _navy && _y + _height > _navy  ){
				
				$("#nav"+_num).addClass('active');
			}else{
				$("#nav"+_num).removeClass('active');
			}
		 });
	});
	
/*------------------------------------------------------------
イベント
------------------------------------------------------------*/
	/*
		$('.characterObject').on('inview', function(event, isInView, visiblePartX, visiblePartY) {
			if(isInView){
				var _num = $(this).context.id.slice(-1);
				$("#contents-nav ul li a").removeClass('active');
				$("#nav"+_num).addClass('active');
			}
		});
		*/
	//背景アニメーション
	function backgroundScroll(){
		/*
		var _dy = $(this).scrollTop();
		var _bg1 = (_dy) * 0.1 + 'px '+ (_dy) * 5 + 'px';
		var _bg2 = (_dy) * 5 + 'px '+ (_dy) * 0.1 + 'px';
		var _bgset = _bg1+","+_bg2;
		$("#bg2").css({"background-position":_bgset});
		*/
	}	
	
	
});