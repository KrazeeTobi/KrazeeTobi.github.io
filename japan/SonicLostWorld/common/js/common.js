$(function() {
	//IE10個別対応
	var ua = window.navigator.userAgent.toLowerCase();
	var ver = window.navigator.appVersion.toLowerCase();
	var dataName = "data.txt";
	//IE10
	if (ver.indexOf("msie 10.") != -1 ||
		ver.indexOf("trident/7") != -1){
		dataName = "data_IE10.txt";
	}
	
	//コンテンツデータ読み込み
	$("#impress").load(dataName,function(){
		//カラーボックス
		//iOSではColorboxやめる
		if(	ua.indexOf('iphone') == -1 ||ua.indexOf('ipod') == -1||ua.indexOf('ipad') == -1 ){
			$('#aside-trailer ul li a').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			$('.contnetsRokki div a').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			$('#contents-top a').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			
			$('#contents-wiiu-miiverse .buttonMovie').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			$('#contents-wiiu-colorpower .buttonMovie').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			$('#contents-n3ds-colorpower .buttonMovie').colorbox({iframe:true,innerWidth:640,innerHeight:360});
			
		}
		
		$('.screenWiiu li a').colorbox();
		$('.screenN3ds li a').colorbox();

		
		//トレイラー カルーセル
		$('#aside-trailer div ul').carouFredSel({
			prev: '#trailer-prev',
			next: '#trailer-next',
			pagination: "#pager2",
			auto: false
		});
	
		//上位メニュータブ
		$("#nav-main li a").on("click", function() {
			$("#nav-main li a").removeClass("selected");
			$("#tab-wrapper ul li a").removeClass("selected");
			$(this).addClass("selected");
			$("#tab-wrapper ul").fadeOut();
			if($(this).parent().attr("id") != "main-story"){
				$($(this).attr("href")).fadeToggle();
			}
			return false;
		});
		
		//下位メニュー
		$("#tab-wrapper ul li a").on("click", function() {
			$("#tab-wrapper ul li a").removeClass("selected");
			$(this).addClass("selected");
			return false;
		});
	
		//トップ
		$("#contents-title a").on("click", function() {
			$("#tab-wrapper ul").fadeOut();
			$("#nav-main li a").removeClass("selected");
			$("#tab-wrapper ul li a").removeClass("selected");
			return false;
		});
	
		//ものがたり
		
		intarvalID = setInterval( "slideSwitch()", 5000 );
	
		//キャラクター 六鬼衆
		/*
		$("#rokki-nav li a").on("click", function() {
			if($(this).attr("class") != "selected"){
				$("#rokki-nav li a").removeClass("selected");
				$(this).addClass("selected");
				$("#rokki-wrapper div").fadeOut();
				$($(this).attr("href")).fadeToggle();
			}
			return false;
		});
		*/
	
		//リサイズ
		$(window).resize(resizeFunc);
		//resizeFunc();
		contentsStart();
		
		var callCount=0;
		//使用している画像を配列に
		var urlArray = new Array();
		$('#impress img').each(function(){
			urlArray.push($(this).attr('src'));
		});
		
		for(i=0;i<urlArray.length;i++){
			var $Img = $('<img>');
			$Img.attr('src', urlArray[i]);	
			$Img.on('load', function(){
				imgLoaded();
			});
		}
		
		function imgLoaded(){
			if(++callCount >=urlArray.length){
				$('#loading').delay(1000).fadeOut("normal");
			}
		}
	});
});

function slideSwitch() {
	var $active = $('#slideshow img.active');
	if ( $active.length == 0 ) $active = $('#slideshow img:last');
	
	var $next =  $active.next().length ? $active.next() : $('#slideshow img:first');
	$active.addClass('last-active');
	$next.css({opacity: 0.0})
		.addClass('active')
		.animate({opacity: 1.0}, 3000, function() {
			$active.removeClass('active last-active');
	});
}

function resizeFunc(){
	objectWidth = Math.ceil(($('footer').width()-$('#contents-main').width())/2);
	objectHeight = Math.ceil($('#common-contents').height());

	$('#mask-left').width(objectWidth).height(objectHeight);
	$('#mask-right').width(objectWidth).height(objectHeight);
}