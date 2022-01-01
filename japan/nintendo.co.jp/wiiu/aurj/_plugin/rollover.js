
// Image rollOver .
function rollOverImages($owner){
	$('.imgover').hover(
		function(){$(this).attr('src', $(this).attr('src').replace(/.(jpg|png|gif)$/, '_o.$1'));},
		function(){$(this).attr('src', $(this).attr('src').replace(/_o.(jpg|png|gif)$/, '.$1'));}
	);
}
$(function(){rollOverImages();});