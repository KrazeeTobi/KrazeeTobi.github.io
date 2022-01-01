//共通利用JS
$(function(){
	
	$(document).ready(function(){
		/* colorbox初期化*/
		$("a[rel='screenshot']").colorbox();
		
		
		/*タイトル装飾の差し込み*/
		$('h1').append('<div id="common-background03"></div>');
		
		/*各コンテンツ用ウィンドウ差し込み*/
		$('#contents-section02 div').before('<div class="innerWindow"></div>');
		$('#contents-section03 div').before('<div class="innerWindow"></div>');
		$('#contents-section04 div').before('<div class="innerWindow"></div>');
		$('#contents-section05 div').before('<div class="innerWindow"></div>');
		$('#contents-section06 div').before('<div class="innerWindow"></div>');
	});
	
	
	/*---------------------------------------------
	*■イベント　クリック
	*section03 キャラHTML差し換え
	---------------------------------------------*/
	$('#section03-character li a').click(function () {
		var _idname = $(this).parent().get(0).id.substr(20,2);
		$('#contents-section03 div.contentsArea').slideUp('normal',function () {
			$('#contents-section03 div.contentsArea').load('contents-section03/character_'+_idname+'.html',function () {
				$('#contents-section03 div.contentsArea').slideDown('slow');
			});
		});
		return false;
	});

	/*---------------------------------------------
	*■イベント　クリック
	*section03 エネミーHTML差し換え
	---------------------------------------------*/
	$('#section03-enemy li a').click(function () {
		var _idname = $(this).parent().get(0).id.substr(16,2);
		$('#contents-section03 div.contentsArea').slideUp('normal',function () {
			$('#contents-section03 div.contentsArea').load('contents-section03/enemy_'+_idname+'.html',function () {
				$('#contents-section03 div.contentsArea').slideDown('slow');
			});
		});
		return false;
	});

	/*---------------------------------------------
	*■イベント　クリック
	*section04 ゾーンHTML差し換え
	---------------------------------------------*/
	$('#section04-navigation li a').click(function () {
		var _idname = $(this).parent().get(0).id.substr(15,2);

		$('#contents-section04 div.contentsArea').fadeOut('normal',function () {
			$('#contents-section04 div.contentsArea').load('contents-section04/'+_idname+'.html',function () {
				$('#contents-section04 div.contentsArea').fadeIn('slow');
			});
		});
		return false;
	});

});