$(document).ready(function(){
	$('.panel_chara').hide();
	
	$('.detail').collapser({
		target: 'next',
		effect: 'slide',
		changeText: 0,
	},
	function(){
		$('.panel_chara').slideUp();
	});
});