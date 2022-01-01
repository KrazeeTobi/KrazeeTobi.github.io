$(function(){
	$('#contents-section01 h2 a, #contents-section01 p a').hover(
		function () {
			$('#contents-section01 p a').css('background-position','0 -57px');
			$('#contents-section01 h2').css({'margin':'28px auto 8px', 'border':'5px solid #fff'});
		},
		function () {
			$('#contents-section01 p a').css('background-position','0 0');
			$('#contents-section01 h2').css({'margin':'33px auto 13px', 'border':'0'});
	  }
	);
	$('#contents-section02 h2 a, #contents-section02 p a').hover(
		function () {
			$('#contents-section02 p a').css('background-position','0 -57px');
			$('#contents-section02 h2').css({'margin':'28px auto 8px', 'border':'5px solid #fff'});
		},
		function () {
			$('#contents-section02 p a').css('background-position','0 0');
			$('#contents-section02 h2').css({'margin':'33px auto 13px', 'border':'0'});
	  }
	);
});