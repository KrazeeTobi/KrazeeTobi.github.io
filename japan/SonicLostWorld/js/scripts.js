// JavaScript Document
$(document).ready(function(){
	//要素追加
	$('header').after('<div id="header-after"></div>');
	$('#contents-aggregate').after('<div id="aggregate-after"></div>');
	
	//ロールオーバー
    /*$('a img').hover(function(){
       $(this).attr('src', $(this).attr('src').replace('_off', '_on'));
         }, function(){
            if (!$(this).hasClass('currentPage')) {
            $(this).attr('src', $(this).attr('src').replace('_on', '_off'));
       }
  });*/
   
	//カラーボックスを表示
	$('#contents-aggregate ul li a').colorbox({iframe:true,innerWidth:640,innerHeight:360});


	//アニメーションを順次実行
	var que01 = $('#common-contents').delay(1);
	var que02 = $.when(que01).pipe(function(){
		$('#common-contents').delay(1000).animate({opacity:'1'},3000,'easeInQuad');
		return $("#common-contents h1").delay(500).slideDown(4000,'easeInQuint');
	})
	var que03 = $.when(que02).pipe(function(){
		$("#aggregate-after").delay(500).show("slide", {direction: "left"}, 700,'easeOutCirc');
		return $("#contents-aggregate").delay(700).fadeIn(1000,'easeInQuad');
	})
	var que04 = $.when(que03).pipe(function(){
		$('#contents-aggregate p').delay(1000).toggle("drop", {"direction": "right"}, 900,"easeInOutQuart");
	})
});


