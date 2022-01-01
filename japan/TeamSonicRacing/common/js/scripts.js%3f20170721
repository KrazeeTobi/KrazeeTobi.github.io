$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	
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
	
	//swipebox
	$(".swipeBox").swipebox({
		useSVG : false,
		removeBarsOnMobile : false, // false will show top bar on mobile devices
		hideBarsDelay : 300000 // delay before hiding bars on desktop
	});
	
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
		$('#common-loading').delay(10).fadeOut(500).queue(function() {
		//上が元の チェック終わったら戻す
		//	$('#common-loading').fadeOut(2).queue(function() {
			intScene();
		});
	});
	//ロード中
	_loader.on('progress', function(progress) { 
		var _prog = progress.loadedRatio; //進捗率を取得
		_prog = Math.floor(_prog * 100);
		$("#common-loading p").html("NOW LOADING... "+_prog+"%");
	});
/*------------------------------------------------------------
FUNCTION
------------------------------------------------------------*/
	//ロード終了後処理
	function intScene(){
		//inview
		$('.inView').on('inview', function(event, isInView, visiblePartX, visiblePartY) {
			if(isInView){
				$(this).stop().delay(500).queue(function() {
					$(this).addClass('active').dequeue();
				});
		//	}else{
		//	$(this).stop().removeClass('active');
			}
		});
		//ナビ
		if($("body").hasClass("pageGame")){
			$("#nav-game a").addClass("active");
		}else if($("body").hasClass("pageCharacters")){
			$("#nav-characters a").addClass("active");
		}else if($("body").hasClass("pageVideo")){
			$("#nav-video a").addClass("active");
		}
		
	}
});