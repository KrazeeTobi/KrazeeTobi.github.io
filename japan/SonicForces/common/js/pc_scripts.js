$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	var _requestAnimationFrame = window.requestAnimationFrame
		|| window.webkitRequestAnimationFrame
		|| window.mozRequestAnimationFrame
		|| window.setTimeout;
	window.requestAnimationFrame = requestAnimationFrame;
	
	// 基準実行時間
	var _basetime = Date.now();
	// _fps
	var _fps = 1000/20;
	//変数
	var _x = 0;
	
	//リダイレクト
	var _getDevice = (function(){
		var ua = navigator.userAgent;
		if(ua.indexOf('iPhone') > 0 || ua.indexOf('iPod') > 0 || ua.indexOf('Android') > 0 && ua.indexOf('Mobile') > 0){
			return 'sp';
		}else if(ua.indexOf('iPad') > 0 || ua.indexOf('Android') > 0){
			return 'tab';
		}else{
			return 'other';
		}
	})();
	if(_getDevice!="other"){
		location.href='sp.html';
	}
	
	//「トップへ」出現タイミング
	var _navigationLogoTop = 500; 
	
	//swipebox
	$(".swipeBox").swipebox({
		useSVG : false
	});

	//トップページ
	 if ( $("body").hasClass("pageTop") ){
		 $("nav h1 img").attr("src", "common/image/logo1.png");
	 }
	
	
	//背景動画
	var _youtubeArray=["n7NS4toOQXU","NwhkTn4uI2c","5qAobRo4Smk","0alP3yMkRHU","-cgBEpJ0aD4","ihuUMMmj4D8","uQCj_WYQ3rs","xr7bxSDBdCg"];
	var _randam = Math.floor(Math.random() * _youtubeArray.length);
	var _youtubeSelect = _youtubeArray[_randam];
	
	var _tublar_options = { videoId: _youtubeSelect};
	$('body').tubular(_tublar_options);

	//画像ローディング
	var _imgSrcs = [];
	$('img').each(function(){
		_imgSrcs.push($(this).attr('src'));
	});
	var _loader = new $.ImgLoader({
		srcs : _imgSrcs, //プレロードした画像等のパスを配列に格納
		pipesize: 2, //同時にロードできる数の上限
		delay: 50,  //次のロードまでの遅延をミリ秒で指定
		timeout: 500,  //タイムアウトまでの時間をミリ秒で指定
		useXHR2: false //XMLHttpRequestVersion2を利用するかどうか
	});
	_loader.load();
	//$('#common-loading').fadeOut(50);//チェック用	
	
	
/*------------------------------------------------------------
イベント
------------------------------------------------------------*/
	//ロード終了後の処理
	_loader.on('allload', function(){
		//アニメーション開始
		animate_handler();
		
		//背景リセット
		scrollProcess();
		//Inviewセット
		setInview();
		$('#common-loading').delay(10).fadeOut(500);
		//チェック用
//		$('#common-loading').fadeOut(50);
	});
	//ロード中
	_loader.on('progress', function(progress) { 
		var _prog = progress.loadedRatio; //進捗率を取得
		_prog = Math.floor(_prog * 100);
		$("#common-loading p").html("NOW LOADING... "+_prog+"%");
	});
	
	//スワイプボックス利用時は背景を止める。
	$(".swipebox").on('click',function(){
		window.player.pauseVideo();
	});
	
	//スワイプボックスclose時は背景を動かす。
	$(".swipebox-close").on('click',function(){
		window.player.playVideo();
	});
	

	//スクロール
	$(window).scroll(function(){
		scrollProcess();
	});
	
	//スムースゲーションスクロール
	$("a[href^='#']").click(function(){
		$('html,body').animate({
			scrollTop: $($(this).attr("href")).offset().top 
			},
			2000,
			'easeInOutCubic'
		);
		return false;
	});
/*------------------------------------------------------------
FUNCTION
------------------------------------------------------------*/
	//スクロール処理
	function scrollProcess(){
		var _dy = $(this).scrollTop();
		var _bg1 = (_dy) * 0.1 + 'px '+ (_dy) * 5 + 'px';
		var _bg2 = (_dy) * 5 + 'px '+ (_dy) * 0.1 + 'px';
		var _bgset = _bg1+","+_bg2;
		$("#bg2").css({"background-position":_bgset});

		//トップへ　出現切り替え
		if(_dy >= _navigationLogoTop){
			$("nav>p").addClass("active");
		}else{
			$("nav>p").removeClass("active");
		}
	}	
	
	//ロード読み込み後inview開始
	function setInview(){
		//inview
		$('.inView').on('inview', function(event, isInView, visiblePartX, visiblePartY) {
			if(isInView){
				$(this).stop().delay(500).queue(function() {
					$(this).addClass('active').dequeue();
				});
			}
			else{
				$(this).stop().removeClass('active');
			}
		});
	}
	
	//アニメーション
	function animate_handler() {  
		var _now   = Date.now();
		var _check = _now - _basetime;
		if( _check / _fps >= 1 ) {
			_basetime = _now;
			draw();
		}
		_requestAnimationFrame( animate_handler, _fps );
	}
	//アニメーション処理
	function draw() {
		//スワイプボックスがオープン時もしくはPC以外は動かさない
		if(!$.swipebox.isOpen && _getDevice == "other"){
			if(++_x>=1300) _x=0;
			var _random = (Math.floor( Math.random() * 10 )/10) /20;
			var _bg2 = 0.2 + _random;
			var _newInfo = 0.4 + _random * 4;
//			$("#bg2").css({"opacity":_bg2});
			$(".newInfo1").css({"background-position":newColor()});
			$(".newInfo2").css({"background-position":newColor()});
		}
	}	
	//NEWのカラー
	function newColor(){
		var _color = Math.floor( Math.random() * 7 );
		var _positionArray = ["left top","left center","left bottom","left center","left center","left top","left top"];
		return _positionArray[_color];
	}
});