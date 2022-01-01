$(function(){
	//メニュージャンプ
	var menu = $('.bodyEnjoy #contents-navigation').smoothMove();
	//上へ戻る
	var backTop = $('.contensSubstance article').backTop();
	
	//動画選択リストの表示
	$("#common-contents #contents-flash li").css('cursor','pointer').each(function(){
			mouseOut(this,0);
		
	}).hover(
		function(){
			if (!$(this).hasClass("selected")){
				$('img',this).fadeTo(300,1);
				mouseOver(this);
			}
		},
		function(){
			if (!$(this).hasClass("selected")){
				mouseOut(this,300);
			}
		}
		
	).click(
		function(){
			//リセット
			var _this = this;
			$("#common-contents #contents-flash li").each(function(){
				if(this != _this){
					mouseOut(this,0);
				}
			});
			
			mouseSelect(this);
		}
	);
	function mouseOver(_this,_time){
		if(!_time){_time=300;}
		$(_this).removeClass();
		$(_this).addClass('over');
		$('img',_this).fadeTo(_time,1);
	}
	function mouseOut(_this,_time){
		if(!_time){_time=300;}
		$(_this).removeClass();
		$('img',_this).fadeTo(_time,0.4);
	}
	function mouseSelect(_this,_time){
		if(!_time){_time=0;}
		$(_this).removeClass();
		$(_this).addClass('selected');
		$('img',_this).fadeTo(_time,1);
	}
		
	//初期
	$("#movieChange01 li:first").each(function(){
		mouseSelect(this);
		$("#movieChange01_txt").html('<h5>'+$(this).attr('title')+'</h5>');
	});

});
