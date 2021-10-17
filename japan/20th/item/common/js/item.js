document.write( '<script type="text/javascript" src="../common/js/paging.js"></script>' );

$(function(){

	/*---------------------------------------------
	*変数
	---------------------------------------------*/


	/*---------------------------------------------
	*■イベント　読み込み完了
	*初期化
	---------------------------------------------*/
	$(document).ready(function(){
		
		$("a[rel='screenshot']").colorbox();

		$("#contents-navigation ul").load('../item.xml li',null,function(){
			$("#contents-navigation ul").paging({count:7,disp:5});
		});

		
	});
	
});
