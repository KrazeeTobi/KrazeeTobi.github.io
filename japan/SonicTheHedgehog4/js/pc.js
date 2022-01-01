$(function(){

	/*---------------------------------------------
	*変数
	---------------------------------------------*/
	var _commonarray = [$('#common-header'),$('#common-footer'),$('h1')];
	var _timer = 0 ;
	var _scrollval = $(this).scrollLeft();

	/*---------------------------------------------
	*■イベント　読み込み完了
	*初期化
	---------------------------------------------*/
	$(document).ready(function(){

		/* colorbox初期化*/
		$("a[rel='gallerymovie']").colorbox();

		/* IE6 幅100 first-child %*/
		myAgent = navigator.userAgent;
		if(myAgent.match(/MSIE (\d|.\d+)/)){
			if(RegExp.$1 == 6){
				$("#common-header").css('width',document.documentElement.clientWidth);
				$("#common-footer").css('width',document.documentElement.clientWidth);
				$("#contents-section05 h3:first-child").css("padding", "0")
			}
		}
		
		/*背景読み込み*/
		$('#common-contents').after('<div id="common-background"></div>');
		$('#common-background').load('common/html/background.html');
	
		/* アンカー指定箇所 訪問者用*/
		//
			positionChange()
	});

	/*---------------------------------------------
	*■イベント　クリック
	*ナビゲーションスクロール
	---------------------------------------------*/
	$('a[href^=#]').click(function() {
		var href= this.hash;
		var $target = $(href == '#_top' ? 'body' : href);
		if($target.size()) {
			$.scrollTo($target, 1200,{easing:'easeInOutExpo'});
		}
		return false;
	});

	/*---------------------------------------------
	*■イベント　マウスホイル
	*ホイール横スクロール
	---------------------------------------------*/
	$('body').mousewheel(function(event, wheelval) {
			if (wheelval > 0){
				scrollBy(-125,0);
			} else if (wheelval < 0){
				scrollBy(125,0);
			}
			return false;
	});

	/*---------------------------------------------
	*■イベント　スクロール
	*スプライト処理とヘッダ周り遅延移動
	---------------------------------------------*/
	$(window).scroll(function(){
		/* バックグラウンドスプライト処理*/
		 _scrollval	= Math.floor($(this).scrollLeft());
		$('#common-background01').css('left',_scrollval*-1);
		
		/* h1 ヘッダ・フッタ位置調整 */
		positionChange();

	});
	
	/*---------------------------------------------
	*■イベント　ウィンドウリサイズ
	*body背景の位置調整用
	---------------------------------------------*/
	$(window).resize(function(){
		/* リサイズ時fixed画像が戻らない場合がある為 */
		positionChange();
		
	});


	/*---------------------------------------------
	*●関数
	*body背景画像の位置調整
	*h1 ヘッダ・フッタ位置調整　遅延処理
	---------------------------------------------*/
	function positionChange(){
		//fixed背景の移動
		$('body').css({'background-position':'left '+ $(this).scrollTop()*-1 +'px'});
		//ヘッダフッタは間をおいて移動
		if(_timer)clearTimeout(_timer);
			_timer = setTimeout(function(){
				for(i=0;i<_commonarray.length;i++){
					_commonarray[i].animate({'left':_scrollval},{duration:'slow',easing:'easeInOutExpo'})
			}
		},300)
	}
	
	/*---------------------------------------------
	*マウスオーバー処理
	---------------------------------------------*/
	/*02*/
	$('.navigationBtn02').hover(
		function () {
			$('.backgoundR02').css('background-position','right top');
			$('.backgoundL02').css('background-position','right top');
		},
		function () {
			$('.backgoundR02').css('background-position','left top');
			$('.backgoundL02').css('background-position','left top');
	  }
	);
	/*03*/
	$('.navigationBtn03').hover(
		function () {
			$('.backgoundR03').css('background-position','right top');
			$('.backgoundL03').css('background-position','right top');
		},
		function () {
			$('.backgoundR03').css('background-position','left top');
			$('.backgoundL03').css('background-position','left top');
	  }
	);
	/*04*/
	$('.navigationBtn04').hover(
		function () {
			$('.backgoundR04').css('background-position','right top');
			$('.backgoundL04').css('background-position','right top');
		},
		function () {
			$('.backgoundR04').css('background-position','left top');
			$('.backgoundL04').css('background-position','left top');
	  }
	);
	/*05*/
	$('.navigationBtn05').hover(
		function () {
			$('.backgoundR05').css('background-position','right top');
			$('.backgoundL05').css('background-position','right top');
		},
		function () {
			$('.backgoundR05').css('background-position','left top');
			$('.backgoundL05').css('background-position','left top');
	  }
	);
	/*06*/
	$('.navigationBtn06').hover(
		function () {
			$('.backgoundR06').css('background-position','right top');
			$('.backgoundL06').css('background-position','right top');
		},
		function () {
			$('.backgoundR06').css('background-position','left top');
			$('.backgoundL06').css('background-position','left top');
	  }
	);
});