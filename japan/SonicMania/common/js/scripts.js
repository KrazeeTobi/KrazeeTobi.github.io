$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	var _contentsArray = ["whats","chara","mode","stage","dlc","plus","soundtrack"];
	var _navigationTop = 40; //ナビ位置
	var _navigationLogoTop = 500; //ナビ出現タイミング
	$(".swipeBox").swipebox({
		useSVG : false
	});
	//画像ローディング
	var _imgSrcs = [];
	
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
	if(_getDevice!=="other"){
		//ハッシュチェック
		var _hash1 = location.href.split("#")[1];
		if ( !_hash1 ) {
			_hash1 = "";
		}
		var _hash2 = "#" + _hash1;
		_contentsArray.forEach(function( val ) {
			if( _hash1 === val ){
				_hash2 = "#contents-" + _hash1;
			}
		});
		location.href='sp/index.html' + _hash2;
	}
	
	$('.preload').each(function(){
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
		$('#common-loading').delay(1000).slideUp({
			duration: 750, 
			easing: "easeOutBounce", 
			complete: load_end
		});
	});
	//ロード中
	_loader.on('progress', function(progress) { 
		var _prog = progress.loadedRatio; //進捗率を取得
		_prog = Math.floor(_prog * 100);
		$("#common-loading p").html("NOW LOADING... "+_prog+"%");
	});
	
	//スクロール
	$(window).scroll(function(){
		//背景アニメーション
		var _dy = $(this).scrollTop();
		var _bg1 = (_dy) * -1 + 'px '+ (_dy) * -1 + 'px';
		var _bg2 = (_dy) * -2 + 'px '+ (_dy) * -2 + 'px';
		var _bg3 = (_dy) * -3 + 'px '+ (_dy) * -3 + 'px';
		var _bgset = _bg1+","+_bg2+","+_bg3;
		$("body").css({"background-position":_bgset});
		
		//ナビの移動
		if(_dy >= _navigationTop){
			$("nav").css({
				position: "fixed",
				top:0
			});
		}else{
			$("nav").css({
				position: "absolute",
				top:_navigationTop
			});
		}
		//小ロゴ＆トップへ
		if(_dy >= _navigationLogoTop){
			$("nav div h1").addClass("active");
			$("nav div ul li:nth-child(5)").addClass("active");
		}else{
			$("nav div h1").removeClass("active");
			$("nav div ul li:nth-child(5)").removeClass("active");
		}
	});
	
	//スムースゲーションスクロール
	$("a[href^='#']").click(function(){
		
		scrollAnime($(this).attr("href"));
		
		/*
		var _offset = -70;
		$('html,body').animate({
			scrollTop: $($(this).attr("href")).offset().top + _offset
			},
			2000,
			'easeInOutCubic'
		);
		*/
		
		return false;
	});
/*------------------------------------------------------------
function
------------------------------------------------------------*/
	//ロード読み込み後inview開始
	function load_end(){
		//inview
		$('.inView').on('inview', function(event, isInView, visiblePartX, visiblePartY) {
			if(isInView){
				$(this).stop().delay(250).queue(function() {
					$(this).addClass('active').dequeue();
				});
			}
			else{
				$(this).stop().removeClass('active');
			}
		});
		
		//ハッシュチェック
		var _hash = location.href.split("#")[1];
		
		_contentsArray.forEach(function( val ) {
			if( _hash === val ){
				scrollAnime("#contents-" + _hash);
			}
		});
	}
	
	//ハッシュ位置に移動
	function scrollAnime(val){
		var _offset = -70;
		$('html,body').animate({
			scrollTop: $(val).offset().top + _offset
			},
			2000,
			'easeInOutCubic'
		);
	}
	
});