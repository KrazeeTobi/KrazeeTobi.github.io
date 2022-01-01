// JavaScript Document

	//ブラウザの横幅を取得してh1画像入替
var checkBrowserWidth = function() {

	var browserWidth = $(window).width();
//	if(browserWidth <= 768){
	if(browserWidth < 768){
			$('#contents-main h1 img').attr("src", "image/h1_smart.jpg");
			//$('#contents-main h1 img').attr("width", 900);
			//$('#contents-main h1 img').attr("height", 950);
	}else{
			$('#contents-main h1 img').attr("src", "image/h1.jpg");
	}
};


// JavaScript Document
$(document).ready(function(){
//	checkBrowserWidth();
	
	/* リサイズ処理をリサイズ終了後に変更 */
//	$(window).resize(checkBrowserWidth);

/*
	var timer = false;
	$(window).resize(function() {
		if (timer !== false) {
		clearTimeout(timer);
		}
		timer = setTimeout(function() {
			checkBrowserWidth();
		}, 200);
	});// end---------$(window).resize(function() 
*/
	
	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	http://www.jquerystudy.info/plugins/carou/fred1.html
	オプション
	prev…prevボタンの動作についての詳細設定
	next…nextボタンの動作についての詳細設定
	auto…自動スクロールについての詳細設定
	pagination…ページ表示についての詳細設定
	-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	/* 使用するプラグインを変更 
				http://9bitstudios.github.io/flexisel/
				https://github.com/9bitStudios/flexisel/blob/master/README.md
	$('#contents-trailer ul').carouFredSel({
		prev:"#trailer-prev",
		next:"#trailer-next",
		pagination:"#pager2",
		auto:false
	});
	*/
	
	$(window).load(function() {
			
			var myFlexisel = $.when(
			
				$("#trailer-flexisel").flexisel({
						visibleItems: 4,
						animationSpeed: 1000,
						autoPlay: false,
						autoPlaySpeed: 3000,            
						pauseOnHover: true,
						enableResponsiveBreakpoints: true,
						responsiveBreakpoints: { 
								portrait: { 
										changePoint:480,
										visibleItems: 1
								}, 
								landscape: { 
										changePoint:640,
										visibleItems: 2
								},
								tablet: { 
										changePoint:768,
										visibleItems: 3
								}
						}
				})

			); // .when
			
			myFlexisel.done(function(){
				
				$('#contents-trailer ul#trailer-flexisel li a').colorbox({
					iframe:true,
					innerWidth:640,
					innerHeight:360
				});
			
			});
			
			
			/* newInfoの配置位置もloadの後に */
			
			var positionNewInfo = function() {
				var newInfoWidth = $("ul#trailer-flexisel li a .newInfo").width();
				var aWidth = $("ul#trailer-flexisel li a").width();
				var offset = (aWidth-($("ul#trailer-flexisel li a img").width()))/2+4;
				$("ul#trailer-flexisel li a .newInfo").css("right", offset);
			};
			$(window).resize(positionNewInfo);
			positionNewInfo();
			
	
	});//------end   $(window).load(function() 
	



/* カルーセルのulがながーく書き換えられるので、またここで親#contents-trailer幅に書き換え*/
/*
	$(window).resize(function() {
		
			if($(window).width()<= 768){
				var contentsTrailerWith = $('#trailer-wrapper').innerWidth();
				
				$('#contents-trailer ul').parent("div").width(contentsTrailerWith) ;
				$('#contents-trailer ul').width(contentsTrailerWith);
				$('#contents-trailer ul').parent("div").height(84);
				$('#contents-trailer ul').height(84);
				
				// 一時的に※Firebugだけ上記ではうまくいかず、height168になったので。
				$('#trailer-wrapper').height(84);
			
			}else{
				location.reload();
			}
		
	});
*/


});