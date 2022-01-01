// JavaScript Document
var _agent = navigator.userAgent;
var _smartphone = ( _agent.indexOf('iPhone') != -1 ||
	_agent.indexOf('iPod') != -1 ||
//	_agent.indexOf('iPad') != -1 ||
	_agent.indexOf('PlayStation Vita') != -1 ||
	(-1 < _agent.indexOf('Android') &&
	-1 < _agent.indexOf('Mobile'))
);

$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	//チェック用ボックス
	//$('#common-navigation').after('<div class="checkBox"></div>')
	var _topPage = $("#navigation-pagetop");
	var _navigationMenu = $('#common-navigation ul');
	var _tabletMenuButton = $('#navigation-memu');
	var _navigationTop = 570;
	
	
	//分岐
	if (!_smartphone){
	}else{
	}

	//トレイラー
	$("#trailer-flexisel").flexisel({
		visibleItems: 4,
		itemsToScroll: 1
	});

	
	$(".swipeBox").swipebox({
		useSVG : false
	});

	$(".swipeBox2").swipebox({
		useSVG : false
	});

	//ストーリースライダー
	var _storySlider = $('#main-image').bxSlider({
		auto:true,
		pause:3000,
		speed:1500,
		mode:'fade',
		easing:'ease-in-out',
		pager:false,
		controls:false
	});

	var swiper = new Swiper('#character-main .swiper-container', {
		nextButton: '.swiper-button-next',
		prevButton: '.swiper-button-prev',
		pagination: '.swiper-pagination',
		paginationClickable: true
	});
	
	
	var swiper = new Swiper('#stage-main .swiper-container', {
		nextButton: '.swiper-button-next',
		prevButton: '.swiper-button-prev',
		paginationClickable: true
	});

/*	
	$(".swiper-pagination-bullet:nth-child(2),.swiper-pagination-bullet:nth-child(3),.swiper-pagination-bullet:nth-child(5)").append("<div class='newInfo'>new</div>");
	*/
	
/*------------------------------------------------------------
イベント
------------------------------------------------------------*/

	$("#bg-video").load("../video/bg.mp4",function(){
		$(this).delay(2000).fadeIn("slow");
	});


	//ページトップボタン
	/*
	if (!_smartphone){
		$(window).scroll(function () {
			if(stateDisplay(_tabletMenuButton)){
				//PCの場合
				if ($(this).scrollTop() > 500) {
					_topPage.slideDown("easeInQuad");
				} else {
					_topPage.slideUp("easeOutQuad");
				}
			}
		});
	}
	_topPage.hide();
	*/

	//タブレットメニューボタン
	_tabletMenuButton.click(function () {
		_navigationMenu.slideToggle();
	});
	
	//タブレット時、ナビゲーションボタンを押されたらナビゲーションを消す
	$('#common-navigation ul a').click(function(){
		console.log("a");
		if(!stateDisplay(_tabletMenuButton)){
			_navigationMenu.toggle();
		}
	});
	
	$(window).scroll(function () {
		var _scr_count = jQuery(document).scrollTop();
		if(_scr_count >= _navigationTop){
			$("#common-navigation").css({
				position: "fixed",
				top:0
			})
		}else{
			$("#common-navigation").css({
				position: "absolute",
				top:_navigationTop
			})
		}
	});
	
	
	//ナビゲーションスクロール

	$("a[href^='#']").click(function(){
		var _offset = -0;
		$('html,body').animate({
			scrollTop: $($(this).attr("href")).offset().top + _offset
			},
			1000,
			'easeOutQuint'
		);
		return false;
	});

	
	//リサイズ時に
	$(window).resize(function(){
		resizeSet();
		_storySlider.reloadSlider();
//		culumnHeightSet();
	});

	resizeSet();


/*------------------------------------------------------------
関数
------------------------------------------------------------*/
	function resizeSet(){
		resizeWindow();
		characterHeight();
	}

	//リサイズ時
	function resizeWindow(){
		if(stateDisplay(_tabletMenuButton)){
			//PCの場合
			_navigationMenu.css({display:"block"})
		}else{
			//tabletの場合
			_navigationMenu.css({display:"none"})
			_topPage.hide();
		}
	}
	
	/* タブレット用メニューの状態確認 */
	function stateDisplay(_obj){
		var state = _obj.css("display");
		if("none"==state){
			return true;
		}else{
			return false;
		}
	}
	
	/* キャラクターのタブレット時のheightリセット */
	/*  動画追加時にA位置の調整を加えるかもしれない */
	function characterHeight(){
		var _characterWidth = $("#character-main").width();
		if("block"==$("#query-tb").css("display")){
			//タブレット
			var _percentage = _characterWidth / 960;
			var _parentHight = _percentage * 580;
			var _childHight = _percentage * 460;
			var _navHight = _percentage * 120;
			$("#character-main").height(_parentHight);
			$("#character-main .swiper-wrapper").height(_childHight);
			$("#character-main .swiper-pagination").height(_navHight);
		}else if("block"==$("#query-pc").css("display")){
			//PC
			$("#character-main").height(580);
			$("#character-main .swiper-wrapper").height(460);
			$("#character-main .swiper-pagination").height(120);
		}else{
			//SP
			$("#character-main").height(580);
			$("#character-main .swiper-wrapper").height(460);
			$("#character-main .swiper-pagination").height(120);

		}
	}
	
	
	/* カラムの高さをチェックし親と同じ大きさに (ゲームシステム用 */
	/*
	function culumnHeightSet(){
		if(stateDisplay(_tabletMenuButton)){
			//PCの場合
			$('#contents-gamesystem div div').each(function(){
				var _height = $($(this).parent().get(0)).height();
				$(this).height(_height);
			});
		}else{
			//tabletの場合
			$("#contents-gamesystem div div").css({height:"auto"})
		}
	}
	
/*------------------------------------------------------------
実行
------------------------------------------------------------*/

//	culumnHeightSet()

	//他のページからのアンカーがある場合	
	/*
	var _hash = window.location.hash;
	_hash = _hash.split("?");
	_hash = _hash[0].split("#");
	
	if(_hash[1]!=""){
		var _offset = -40;
		$('html,body').animate({
			scrollTop: $("#"+_hash[1]).offset().top + _offset
			},
			500,
			'easeOutQuint'
		);
	}
	*/
});