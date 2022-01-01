$(document).ready(function(){
	$(window).scroll(function() {
		scrollMask();
	});
	$("body").on('touchmove', function() {
		scrollMask();
		
	});
	
	$(window).resize(function() {
	//	scrollMask();
	});
	scrollMask();
});

function consoleDiv(){
	$(".consoleDiv").text($(window).scrollTop());
}

function scrollMask(){
	consoleDiv();
	$(".maskBG svg").each(function(){
		var _parentY = $(this).parent().parent().offset().top;
		var _parentH = $(this).parent().parent().height();
		var _currentScroll = $(window).scrollTop();
		var _obj = {};
		var _distance = Math.max(_currentScroll - _parentY,0);
	//	console.log(_distance);
		$(this).find(".maskImage").css({'transform': 'translate(0, ' + _distance / 2.25 + 'px)'});
	})

}