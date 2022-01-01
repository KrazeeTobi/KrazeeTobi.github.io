// JavaScript Document
var _agent = navigator.userAgent;
var _smartphone = ( _agent.indexOf('iPhone') != -1 ||
	_agent.indexOf('iPod') != -1 ||
//	_agent.indexOf('iPad') != -1 ||
	_agent.indexOf('PlayStation Vita') != -1 ||
	(-1 < _agent.indexOf('Android') &&
	-1 < _agent.indexOf('Mobile'))
);
$(window).load(function() {

	if (!_smartphone){
		//colorbox
		// !!TODO!! 後で調整 主に位置 スタイルも変更するかも
		$("a[rel='trailer']").colorbox({
			speed: 200,
			height:'auto',
			opacity:0.8,
			onOpen:function() {},
			onComplete:function() {},
			onClosed:function() {}
		});
	}else{
		 $("a[rel='trailer']").attr('target' , '_blank');
	}
});


$(document).ready(function(){
/*------------------------------------------------------------
初期化
------------------------------------------------------------*/
	//チェック用ボックス
	//$('#common-navigation').after('<div class="checkBox"></div>')

	var _topPage = $("#navigation-pagetop");
	var _navigationMenu = $('#common-navigation ul');
	var _tabletMenuButton = $('#navigation-memu');
	
	
	if (!_smartphone){
		//colorbox
		// !!TODO!! 後で調整 主に位置 スタイルも変更するかも
		$("a[rel='character'],a[rel='gamesystem'],a[rel='world']").colorbox({
			speed: 200,
			height:'auto',
			opacity:0.8,
			onOpen:function() {},
			onComplete:function() {},
			onClosed:function() {}
		});
		//動画用設定（）固有アクションのソニック
		$("a[rel='actionmovie']").colorbox({
			iframe:true,
			innerWidth:640,
			innerHeight:360
		});
		
	}else{
		 $("a[rel='character'],a[rel='gamesystem'],a[rel='world']").attr('target' , '_blank');
	}

	//ナビゲーション固定
	_navigationMenu.exFlexFixed({
		container : 'body'
	});

	//ページトップナビゲーション

	//ストーリースライダー
	var _storySlider = $('#contents-story ul').bxSlider({
		touchEnabled:false,
		auto:true,
		pause:3000,
		speed:3000,
		mode:'fade',
		pager:false,
		controls:false
	});

//	$(".checkBox").text("aaa");
//	$(".checkBox").text(stateDisplay(_tabletMenuButton));

/*------------------------------------------------------------
イベント
------------------------------------------------------------*/
	//ページトップボタン
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

	//タブレットメニューボタン
	_tabletMenuButton.click(function () {
		_navigationMenu.slideToggle();
	});
	
	//タブレット時、ナビゲーションボタンを押されたらナビゲーションを消す
	$('#common-navigation ul a').click(function(){
		if(!stateDisplay(_tabletMenuButton)){
			_navigationMenu.toggle();
		}
	});
	
	//ナビゲーションスクロール
	$("a[href^='#']").click(function(){
		var _offset = -40;
		$('html,body').animate({
			scrollTop: $($(this).attr("href")).offset().top + _offset
			},
			500,
			'easeOutQuint'
		);
		return false;
	});

	
	//リサイズ時に
	$(window).resize(function(){
		resizeWindow();
		culumnHeightSet();
		_storySlider.reloadSlider();
	});

/*------------------------------------------------------------
関数
------------------------------------------------------------*/
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
	
	/* カラムの高さをチェックし親と同じ大きさに (ゲームシステム用 */
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

	culumnHeightSet()

	//他のページからのアンカーがある場合	
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
});
