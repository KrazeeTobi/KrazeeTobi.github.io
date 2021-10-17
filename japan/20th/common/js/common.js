$(function(){

	/*---------------------------------------------
	*変数
	---------------------------------------------*/


	/*---------------------------------------------
	*■イベント　読み込み完了
	*初期化
	---------------------------------------------*/
		$('header').wrap('<div id="common-header"></div>');
		$('#common-header').after('<div style="height:60px;"></div>');//for IE
		$('#common-navigation h1').after('<div style="height:1px;"></div>');//for IE
		$('#common-contents nav#contents-navigation').after('<div style="height:1px;"></div>');//for IE
		$("footer").footer();
		$("#common-contents article h3").wrapInner('<div class="h3Wrap"></div>');
		$("#common-contents .contensSubstance").wrapInner('<div class="divWrap"></div>');
	
	
});
