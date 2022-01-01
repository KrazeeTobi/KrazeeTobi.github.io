$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	//スマホかどうか
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
	var x = 0;

	//swipebox
	$(".swipeBox").swipebox({
		useSVG : false
	});
	
	if(_getDevice != "sp"){
		//tubular
		var _tublar_options = { videoId: 'xr7bxSDBdCg'};
		$('body').tubular(_tublar_options);
		
		if(_getDevice == "tab"){
			$("#bg1").css({"display":"none"});
			$("#bg2").css({"display":"none"});
		}
	}else{
		//スマホの場合背景変更
		$("#bg1").css({"display":"none"});
		$("#bg2").css({"display":"none"});
		$('#common-bg').css('background-image', 'url(image/sp_bg.jpg)');
	}
	
	
	
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
/*------------------------------------------------------------
イベント
------------------------------------------------------------*/
	//ロード終了後の処理
	_loader.on('allload', function(){
		animate_start();
		animate_handler();
		$('#common-loading').delay(1000).fadeOut(1000);
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

	
/*------------------------------------------------------------
function
------------------------------------------------------------*/
	//開始アニメ
	function animate_start(){
		//アニメーションを順次実行
		var que01 = $("#contents-main h1").delay(2500);
		var que02 = $.when(que01).pipe(function(){
			return $("#contents-main h1").addClass("action").delay(500);
		})
		var que03 = $.when(que02).pipe(function(){
			 $('#contents-main ul li:nth-of-type(1)').fadeIn(250,'easeOutQuad');
			 $('#contents-main ul li:nth-of-type(2)').delay(100).fadeIn(250,'easeOutQuad');
			return $('#contents-main ul li:nth-of-type(3)').delay(200).fadeIn(250,'easeOutQuad');
		})
		
		var que04 = $.when(que03).pipe(function(){
			return $("#contents-main p").delay(200).fadeIn(500,'easeInQuad').delay(1000);
		})
		var que05 = $.when(que04).pipe(function(){
			$('#text1').slideDown(1000,'easeOutBounce');
			$('#text2').slideDown(1000,'easeOutBounce');
			return $('#text3').slideDown(1000,'easeOutBounce');
		})
		
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
		if(!$.swipebox.isOpen && _getDevice=="other"){
			if(++x>=1300) x=0;
			var _random = (Math.floor( Math.random() * 10 )/10) /20;
			var _bg2 = 0.2 + _random;
			var _newInfo = 0.4 + _random * 4;
			$("#bg2").css({"opacity":_bg2});
			$(".newInfo").css({"opacity":_newInfo});
		}
	}	

});