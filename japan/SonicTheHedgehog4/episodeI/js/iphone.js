//iphone
$(function(){
	$(document).ready(function(){
		
		//ムービー読み込み
		$("a[rel='gallerymovie']").each(function(){
			var _filepath = "contents-section06/swf/iphone_" + $(this).attr('href').split('/')[1].split('.')[0].split('_')[1]  + ".mp4";
			$(this).attr('href',_filepath)
		});
		
		/*背景読み込み*/
		$('#common-contents').after('<div id="common-background"></div>');
		$('#common-background').load('common/html/iphone-background.html');
	});
});